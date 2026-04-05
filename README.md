# OpenCASCADE.gd

This project provides OpenCASCADE Technology (OCCT) integration for the Godot Engine using GDExtension.

It focuses on being a low-level yet complete wrapper, designed as a solid foundation for building higher-level CAD/CAM/CAE functionality while still accounting for rare edge cases.

## ✨ Features

- **Cross-Platform Support**: Runs on desktop (Windows, macOS, Linux) platforms.
- **Demo Project**: includes [demo scene](demo/) to get you started quickly.
- **Comprehensive Documentation**: includes [class references](doc_classes/) for seamless Godot editor integration.
- **High Performance**: leverages C++ for optimized performance and low-level access.
- **Easy Integration**: drop-in [GDExtension](https://docs.godotengine.org/en/stable/tutorials/scripting/gdextension/index.html) with simple Godot API bindings.
- **Automated Builds**: uses GitHub Actions for continuous integration, including tests and prebuilt binaries.
- **Dependency Management**: integrated [VCPKG](https://github.com/microsoft/vcpkg) for hassle-free library management.

## 🚀 Quick Start

1. **Download**: [latest release](https://github.com/yeicor-gd/sqlite3.gd/releases) or [nightly builds](https://github.com/yeicor-gd/sqlite3.gd/actions) (look for `...-addon.zip`).
2. **Extract**: the downloaded `...-addon.zip` into your project's root.
3. **Profit**: see [demo/demo.gd](demo/demo.gd) for a complete example.

## 🧩 Using this project as a template for other GDExtensions

1. **Rename the Project**: update `project({old-name} CXX)` in [CMakeLists.txt](CMakeLists.txt), and rename [demo/addons/{old-name}/](demo/addons/sqlite3.gd/) to match your new addon name.
2. **Update Dependencies**: modify [vcpkg_ports/gdext/vcpkg.json](vcpkg_ports/gdext/vcpkg.json) to include your required libraries, and link them in [CMakeLists.txt](CMakeLists.txt) following VCPKG instructions.
3. **Customize Builds**: edit [vcpkg_ports/](vcpkg_ports/) and [vcpkg_triplets/](vcpkg_triplets/) as needed to ensure compatibility across platforms.
4. **Implement Your Logic**: add your C++ bindings in [src/](src/), document classes in [doc_classes/](doc_classes/), and create tests/demos in [demo/](demo/) (refer to existing examples).
5. **Update Metadata**: replace placeholders in this README (e.g., [Your Project Name], [YourGitHubUsername]) with your project's details and links.
