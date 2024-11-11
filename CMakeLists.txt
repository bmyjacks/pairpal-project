cmake_minimum_required(VERSION 3.29)
project(pairpal)

set(CMAKE_CXX_STANDARD 20)

add_library(api STATIC
        include/api/gateway.hpp
        src/api/gateway.cpp
)
add_library(chat STATIC
        include/chat/dialog.hpp
        include/chat/message.hpp
        src/chat/message.cpp
        src/chat/dialog.cpp)
add_library(storage STATIC
        include/storage/storage.hpp
        src/storage/storage.cpp
        include/storage/user.hpp)


target_include_directories(api PUBLIC include)
target_include_directories(storage PUBLIC include)
target_include_directories(chat PUBLIC include)

# Define backend
add_executable(backend
        src/backend.cpp)

target_link_libraries(backend PRIVATE storage chat)

# Define frontend
add_executable(frontend
        src/frontend.cpp)

# Link libraries to the frontend executable
target_link_libraries(frontend PRIVATE api)
