cmake_minimum_required(VERSION 3.29)
project(pairpal LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

# Add third-party libraries
find_package(nlohmann_json CONFIG REQUIRED)
find_package(cppzmq CONFIG REQUIRED)
find_package(GTest CONFIG REQUIRED)

# Configure third-party libraries
set(nlohmann-json_IMPLICIT_CONVERSIONS OFF)

enable_testing()

# API library
add_library(api STATIC
        include/api/client.hpp
        src/api/client.cpp
        include/api/message.hpp
        include/api/server.hpp
        src/api/server.cpp
        src/api/message.cpp
)
target_include_directories(api PUBLIC include)
target_link_libraries(api PUBLIC nlohmann_json::nlohmann_json cppzmq cppzmq-static)

add_library(chat STATIC
        include/chat/dialog.hpp
        include/chat/message.hpp
        src/chat/message.cpp
        src/chat/dialog.cpp)
add_library(pair STATIC
        include/pair/pair.hpp
        src/pair/pair.cpp)
add_library(storage STATIC
        include/storage/storage.hpp
        src/storage/storage.cpp
        include/storage/user.hpp
        src/storage/user.cpp)
add_library(ui STATIC
        include/ui/ui.hpp
        src/ui/ui.cpp)


target_include_directories(chat PUBLIC include)
target_include_directories(pair PUBLIC include)
target_include_directories(storage PUBLIC include)


# Define backend
add_executable(backend
        src/backend.cpp)

target_link_libraries(backend PUBLIC storage chat pair api)

# Define frontend
add_executable(frontend
        src/frontend.cpp)

# Link libraries to the frontend executable
target_link_libraries(frontend PUBLIC api ui)


# Tests
# API
## Client test
add_executable(test-client test/api/test-client.cpp)
target_link_libraries(test-client PRIVATE api GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)
add_test(NAME test-client COMMAND test-client)
## Message test
add_executable(test-message test/api/test-message.cpp)
target_link_libraries(test-message PRIVATE api GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)
add_test(NAME test-message COMMAND test-message)
