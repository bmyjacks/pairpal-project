cmake_minimum_required(VERSION 3.29)
project(pairpal LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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
find_package(nlohmann_json CONFIG REQUIRED)
set(nlohmann-json_IMPLICIT_CONVERSIONS OFF)
find_package(cppzmq CONFIG REQUIRED)
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

target_link_libraries(backend PRIVATE storage chat pair api)

# Define frontend
add_executable(frontend
        src/frontend.cpp)

# Link libraries to the frontend executable
target_link_libraries(frontend PRIVATE api ui)


# Tests
## Add google test
find_package(GTest CONFIG REQUIRED)

## API tests
add_executable(test-message test/api/test-message.cpp)
target_link_libraries(test-message PRIVATE api GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)
add_test(NAME test-message COMMAND test-message)


add_executable(pair-test test/pair/sample-test.cpp)
target_link_libraries(pair-test pair)

add_test(NAME pair-test COMMAND pair-test)
