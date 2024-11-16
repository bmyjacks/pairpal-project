cmake_minimum_required(VERSION 3.29)
project(pairpal)

set(CMAKE_CXX_STANDARD 20)

enable_testing()

add_library(api STATIC
        include/api/client.hpp
        src/api/client.cpp
        include/api/server.hpp
        src/api/server.cpp
)
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
        src/storage/user.cpp
        include/storage/sqlite3.h
        src/storage/sqlite3.c
        test/Storage_test/s-test.cpp)
add_library(ui STATIC
        include/ui/ui.hpp
        src/ui/ui.cpp)


target_include_directories(api PUBLIC include)
target_include_directories(chat PUBLIC include)
target_include_directories(pair PUBLIC include)
target_include_directories(storage PUBLIC include)


# Define backend
add_executable(backend
        src/backend.cpp
        include/storage/sqlite3.h
        src/storage/sqlite3.c)

target_link_libraries(backend PRIVATE storage chat pair api)

# Define frontend
add_executable(frontend
        src/frontend.cpp
        include/storage/sqlite3.h
        src/storage/sqlite3.c)

# Link libraries to the frontend executable
target_link_libraries(frontend PRIVATE api ui)


# Tests
add_executable(pair-test test/pair/sample-test.cpp
        include/storage/sqlite3.h
        src/storage/sqlite3.c)
target_link_libraries(pair-test pair)

add_test(NAME pair-test COMMAND pair-test)
