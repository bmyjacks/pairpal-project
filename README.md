# PairPal

![GitHub Actions Workflow Status](https://img.shields.io/github/actions/workflow/status/bmyjacks/pairpal-project/cmake.yml)
![GitHub code size in bytes](https://img.shields.io/github/languages/code-size/bmyjacks/pairpal-project)

This is the project for our CSC3002 course. We are going to implement a matching system for students to find their
partners for various activities.

We intentionally keep everyone's code not to be re-formatted to show the difference in coding style.

Documentation is available at [here](https://bmyjacks.github.io/pairpal-project/).

## Components

- Frontend
    - [x] Login page

- API gateway
    - [x] API for client
    - [x] API for server

- Chat system
    - [ ] Chat system

- Matching system
    - [x] Tags-based matching
    - [x] ~~Machine learning-based matching~~ (unnecessary)

- Storage
    - [ ] Database

## How to run

### Build

```shell
# Install and bootstrap vcpkg
git clone https://github.com/microsoft/vcpkg
. vcpkg/bootstrap-vcpkg.sh

# Install dependencies with vcpkg
vcpkg/vcpkg install

# Configure CMake
cmake -B build -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=vcpkg/scripts/buildsystems/vcpkg.cmake

# Build program
cmake --build build --config Release
```

### Run

First, you need to start the server:

```shell
./build/backend
```

Then, you can start the client:

```shell
./build/frontend
```

## Team members

- [Mingyi](https://github.com/bmyjacks) for API gateway and matching system
- [Jinghan](https://github.com/Bella2005464) and [Jiayue](https://github.com/daijiayue) for frontend
- [Jinlong](https://github.com/Sheriaties) for storage
- [Yingying](https://github.com/yvvonie) for chat system

## Thanks

- [CMake](https://cmake.org/) for building the project
- [vcpkg](https://vcpkg.io/en/) for managing dependencies
- [googletest](https://github.com/google/googletest) for testing
- [nlohmann-json](https://github.com/nlohmann/json) for JSON serialization
- [cppzmq](https://github.com/zeromq/cppzmq) for networking
- [Qt](https://www.qt.io/) for GUI

