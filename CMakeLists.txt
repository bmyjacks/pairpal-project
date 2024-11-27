cmake_minimum_required(VERSION 3.29)
project(pairpal LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

# Add third-party libraries
find_package(nlohmann_json CONFIG REQUIRED)
find_package(cppzmq CONFIG REQUIRED)
find_package(GTest CONFIG REQUIRED)
find_package(Qt5 REQUIRED COMPONENTS Core Gui LinguistTools Widgets)

# Configure third-party libraries
set(nlohmann-json_IMPLICIT_CONVERSIONS OFF)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

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

# Chat library
add_library(chat STATIC
        include/chat/dialog.hpp
        include/chat/message.hpp
        src/chat/message.cpp
        src/chat/dialog.cpp)
target_include_directories(chat PUBLIC include)

# Pair library
add_library(pair STATIC
        include/pair/pair.hpp
        src/pair/pair.cpp)
target_include_directories(pair PUBLIC include)
target_link_libraries(pair PUBLIC storage)

# Storage library
add_library(storage STATIC
        include/storage/storage.hpp
        src/storage/storage.cpp
        include/storage/user.hpp
        src/storage/user.cpp)
target_include_directories(storage PUBLIC include)

# Add UI forms
set(UI_SOURCES
        src/ui/dialog.ui
        src/ui/eat.ui
        src/ui/pairpal.ui
        src/ui/play.ui
        src/ui/registerpage.ui
        src/ui/self.ui
        src/ui/sport.ui
        src/ui/study.ui)
# Add translation files
set(TRANSLATIONS
        src/ui/page1_zh_CN.ts)

qt5_add_translation(QM_FILES ${TRANSLATIONS})

# Define frontend
add_executable(frontend
        src/ui/main.cpp
        src/ui/dialog.cpp
        src/ui/eat.cpp
        src/ui/pairpal.cpp
        src/ui/play.cpp
        src/ui/registerpage.cpp
        src/ui/self.cpp
        src/ui/sport.cpp
        src/ui/study.cpp
        ${UI_SOURCES}
        ${QM_FILES}
)
target_include_directories(frontend PUBLIC include)
target_link_libraries(frontend PUBLIC api Qt5::Widgets Qt5::Core Qt5::Gui)


# Define backend
add_executable(backend
        src/backend.cpp)
target_link_libraries(backend PUBLIC storage chat pair api)


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

# Pair
add_executable(test-pair test/pair/test-pair.cpp)
target_link_libraries(test-pair PRIVATE pair GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)
add_test(NAME test-pair COMMAND test-pair)
