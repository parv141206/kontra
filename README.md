<p align="center">
  <img src="./docs/kontra_logo.svg" height="300">
</p>

<h1 align="center">Kontra</h1>
<p align="center"><b>A modern C++ Terminal UI library <br> because `std::cout` just doesn’t cut it anymore.</b></p>

---

# 🚀 What is Kontra?

**Kontra** lets you build awesome terminal user interfaces with C++.  
No clunky GUI frameworks, no weird DSLs — just clean code, styled boxes, and full control.

It’s built for devs who love the terminal and want their apps to feel sharp, responsive, and fun to use.  
Layout systems, input handling, styled text, borders — all baked in and easy to use.

---

### ⚡ Why you'll love it

- 🔲 Layouts that don’t fight you  
- 🎨 Customizable styling (hello, ANSI magic)  
- 🎯 Smooth keyboard input & focus handling  
- 🧩 Build clean components and compose them with ease  
- 🧵 Looks terminal, feels modern

---

## 🚀 Installation & Usage

Getting Kontra TUI into your project is designed to be simple and modern using CMake. Here are the two recommended ways to get started.

### Method 1: The Modern Way with `CPM.cmake` (Recommended ✨)

This is the fastest and easiest way to integrate Kontra. It automatically fetches the library from GitHub when you configure your project.

**Prerequisites:**
*   A C++17 compatible compiler.
*   CMake (version 3.16 or higher).

**Steps:**

1.  **Download `CPM.cmake`**
    Download the latest `CPM.cmake` script from its [GitHub repository](https://github.com/cpm-cmake/CPM.cmake) and place it in a `cmake` folder within your project.

    ```
    YourCoolApp/
    ├── main.cpp
    ├── CMakeLists.txt
    └── cmake/
        └── CPM.cmake
    ```

2.  **Add Kontra to your `CMakeLists.txt`**
    Add the following block to your project's `CMakeLists.txt`. It will include `CPM`, download Kontra, and link it to your application.

    ```cmake
    # YourCoolApp/CMakeLists.txt

    cmake_minimum_required(VERSION 3.16)
    project(YourCoolApp LANGUAGES CXX)

    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)

    # Tell CMake where to find the CPM.cmake script
    list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
    include(CPM)

    # ----------------------------------------------------
    # ✨ Add Kontra TUI to your project!
    # ----------------------------------------------------
    # This command tells CPM to fetch the Kontra library directly from GitHub.
    # We recommend pinning to a specific version/release tag for stability.
    CPMAddPackage(
        NAME Kontra
        GITHUB_REPOSITORY parv141206/kontra # Replace with your actual username/repo
        GIT_TAG main                     # Or use a release tag like "v1.0.0"
    )

    # Create your application executable
    add_executable(YourCoolApp main.cpp)

    # Link against the 'kontra' library. CPM makes this target available automatically!
    target_link_libraries(YourCoolApp PRIVATE kontra)
    ```

3.  **Configure and Build**
    That's it! Now, when you run CMake to configure your project, it will automatically download and set up Kontra.

    ```bash
    # Create a build directory
    cmake -S . -B build

    # Build your project
    cmake --build build
    ```

### Method 2: The Classic Way with `git submodule` 📦

This method is great if you want to work offline or have a local copy of the library source code locked to your project's git history.

**Prerequisites:**
*   `git` installed on your system.
*   A C++17 compatible compiler.
*   CMake (version 3.16 or higher).

**Steps:**

1.  **Add Kontra as a Git Submodule**
    From the root directory of your project, run the following command. This will clone the Kontra repository into a subfolder named `external/kontra`.

    ```bash
    git submodule add https://github.com/parv141206/kontra.git external/kontra
    git submodule update --init --recursive
    ```
    Your project structure will now look like this:
    ```
    YourCoolApp/
    ├── main.cpp
    ├── CMakeLists.txt
    └── external/
        └── kontra/
            └── (Kontra TUI source code...)
    ```

2.  **Add the Subdirectory in `CMakeLists.txt`**
    Modify your project's `CMakeLists.txt` to include the downloaded library as part of your build.

    ```cmake
    # YourCoolApp/CMakeLists.txt

    cmake_minimum_required(VERSION 3.16)
    project(YourCoolApp LANGUAGES CXX)

    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)

    # ----------------------------------------------------
    # 📦 Add the Kontra TUI subdirectory
    # ----------------------------------------------------
    # This command tells CMake to find and process the CMakeLists.txt
    # inside the submodule folder. This creates the 'kontra' library target.
    add_subdirectory(external/kontra)

    # Create your application executable
    add_executable(YourCoolApp main.cpp)

    # Link against the 'kontra' library target, which is now available.
    target_link_libraries(YourCoolApp PRIVATE kontra)
    ```

3.  **Configure and Build**
    The process is the same. Because the files are already local, no download will occur.

    ```bash
    # Create a build directory
    cmake -S . -B build

    # Build your project
    cmake --build build
    ```

---
Happy building! 💖 I am excited to see what you create with Kontra TUI :)