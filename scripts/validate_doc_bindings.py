#!/usr/bin/env python3

from __future__ import annotations

import re
import sys
import xml.etree.ElementTree as ET
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
SRC_DIR = ROOT / "src"
DOC_DIR = ROOT / "doc_classes"


def normalize_type(type_name: str) -> str:
    return type_name.removeprefix("godot::")


def scan_source():
    classes: dict[str, str] = {}
    methods: dict[str, dict[str, tuple[str, ...]]] = {}
    properties: dict[str, set[str]] = {}
    signals: dict[str, set[str]] = {}

    class_re = re.compile(r"GDCLASS\(\s*([A-Za-z_][A-Za-z0-9_]*)\s*,\s*([A-Za-z_:][A-Za-z0-9_:]*)\s*\)")
    method_re = re.compile(
        r"(?:godot::)?ClassDB::bind_method\s*\(\s*(?:godot::)?D_METHOD\(([^)]*)\)\s*,\s*&(?:godot::)?([A-Za-z_][A-Za-z0-9_]*)::([A-Za-z_][A-Za-z0-9_]*)",
        re.DOTALL,
    )
    signal_re = re.compile(
        r"(?:ADD_SIGNAL|add_signal)\s*\(\s*MethodInfo\(\s*\"([^\"]+)\"",
        re.DOTALL,
    )
    property_re = re.compile(
        r"ADD_PROPERTY\s*\(\s*PropertyInfo\([^,]+,\s*\"([^\"]+)\"",
        re.DOTALL,
    )
    bind_methods_class_re = re.compile(
        r"(?:void|static void)\s+([A-Za-z_][A-Za-z0-9_]*)::_bind_methods\s*\(",
        re.DOTALL,
    )

    for path in sorted(SRC_DIR.glob("*.h")) + sorted(SRC_DIR.glob("*.cpp")):
        text = path.read_text(encoding="utf-8")
        file_classes = {match.group(1) for match in class_re.finditer(text)}
        file_classes.update(match.group(1) for match in bind_methods_class_re.finditer(text))
        if not file_classes:
            file_classes = {extract_class_from_path(path)}

        for class_match in class_re.finditer(text):
            class_name = class_match.group(1)
            parent_name = normalize_type(class_match.group(2))
            classes[class_name] = parent_name

        for method_match in method_re.finditer(text):
            dmethod_args = re.findall(r'"([^"]+)"', method_match.group(1))
            if not dmethod_args:
                continue
            class_name = method_match.group(2)
            method_name = dmethod_args[0]
            param_names = tuple(dmethod_args[1:])
            methods.setdefault(class_name, {})[method_name] = param_names

        for signal_match in signal_re.finditer(text):
            for class_name in file_classes:
                signals.setdefault(class_name, set()).add(signal_match.group(1))

        for property_match in property_re.finditer(text):
            for class_name in file_classes:
                properties.setdefault(class_name, set()).add(property_match.group(1))

    return classes, methods, properties, signals


def extract_class_from_path(path: Path) -> str:
    return path.stem


def scan_docs():
    docs = {}
    for path in sorted(DOC_DIR.glob("*.xml")):
        tree = ET.parse(path)
        root = tree.getroot()
        if root.tag != "class":
            raise ValueError(f"{path}: root element must be <class>")

        class_name = root.attrib.get("name", "")
        inherits = normalize_type(root.attrib.get("inherits", ""))

        def collect(container_name: str, item_name: str):
            result = []
            container = root.find(container_name)
            if container is None:
                return result
            for element in container.findall(item_name):
                result.append(element)
            return result

        docs[class_name] = {
            "path": path,
            "inherits": inherits,
            "methods": collect("methods", "method"),
            "properties": collect("properties", "property"),
            "members": collect("members", "member"),
            "signals": collect("signals", "signal"),
            "constructors": collect("constructors", "constructor"),
            "operators": collect("operators", "operator"),
            "constants": collect("constants", "constant"),
            "annotations": collect("annotations", "annotation"),
            "theme_items": collect("theme_properties", "theme_item"),
        }
    return docs


def emit(errors: list[str]) -> int:
    if errors:
        print("\n".join(errors))
        return 1
    return 0


def main() -> int:
    errors: list[str] = []
    classes, source_methods, source_properties, source_signals = scan_source()
    docs = scan_docs()

    if not docs:
        return emit(["No doc_classes/*.xml files were found."])

    for class_name, parent_name in sorted(classes.items()):
        doc = docs.get(class_name)
        if doc is None:
            errors.append(f"{class_name}: missing doc_classes/{class_name}.xml")
            continue

        if doc["path"].stem != class_name:
            errors.append(f"{doc['path']}: file name does not match class name {class_name}")

        if doc["inherits"] != parent_name:
            errors.append(
                f"{doc['path']}: inherits='{doc['inherits']}' does not match source base '{parent_name}'"
            )

        if doc["methods"] is not None:
            source_method_map = source_methods.get(class_name, {})
            doc_method_names = set()
            for method in doc["methods"]:
                name = method.attrib.get("name", "")
                doc_method_names.add(name)
                source_param_names = source_method_map.get(name)
                if source_param_names is None:
                    errors.append(f"{doc['path']}: unknown method '{name}'")
                    continue

                doc_param_names = tuple(param.attrib.get("name", "") for param in method.findall("param"))
                if doc_param_names != source_param_names:
                    errors.append(
                        f"{doc['path']}: method '{name}' parameters {doc_param_names} do not match source {source_param_names}"
                    )

            for source_name in sorted(source_method_map):
                if source_name not in doc_method_names:
                    errors.append(f"{doc['path']}: missing method '{source_name}'")

        source_property_names = source_properties.get(class_name, set())
        doc_property_names = {prop.attrib.get("name", "") for prop in doc["properties"]}
        if doc_property_names != source_property_names:
            if doc_property_names or source_property_names:
                errors.append(
                    f"{doc['path']}: property names {sorted(doc_property_names)} do not match source {sorted(source_property_names)}"
                )

        if doc["members"]:
            errors.append(f"{doc['path']}: members are declared in docs but no member bindings exist")
        source_signal_names = source_signals.get(class_name, set())
        doc_signal_names = {sig.attrib.get("name", "") for sig in doc["signals"]}
        if doc_signal_names != source_signal_names:
            if doc_signal_names or source_signal_names:
                errors.append(
                    f"{doc['path']}: signal names {sorted(doc_signal_names)} do not match source {sorted(source_signal_names)}"
                )
        if doc["constructors"]:
            errors.append(f"{doc['path']}: constructors are declared in docs but no constructor bindings exist")
        if doc["operators"]:
            errors.append(f"{doc['path']}: operators are declared in docs but no operator bindings exist")
        if doc["constants"]:
            errors.append(f"{doc['path']}: constants are declared in docs but no constant bindings exist")
        if doc["annotations"]:
            errors.append(f"{doc['path']}: annotations are declared in docs but no annotation bindings exist")
        if doc["theme_items"]:
            errors.append(f"{doc['path']}: theme_properties are declared in docs but no theme bindings exist")

    for class_name in sorted(docs):
        if class_name not in classes:
            errors.append(f"{docs[class_name]['path']}: doc class has no matching GDCLASS definition")

    return emit(errors)


if __name__ == "__main__":
    raise SystemExit(main())
