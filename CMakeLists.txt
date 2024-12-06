cmake_minimum_required(VERSION 3.29)
#project(pairpal LANGUAGES CXX) // Some one bring a CC file, so we cannot use this line
project(pairpal)

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
        src/api/client.cpp
        src/api/server.cpp
        src/api/message.cpp
        src/api/message.cpp
        src/api/server.cpp)
target_include_directories(api PUBLIC include)
target_link_libraries(api PUBLIC pair nlohmann_json::nlohmann_json cppzmq cppzmq-static)

# Chat library
add_library(chat STATIC
        src/chat/chat.cpp
        src/chat/dialog.cpp
        src/chat/message.cpp)
target_include_directories(chat PUBLIC include)

# Pair library
add_library(pair STATIC
        src/pair/pair.cpp)
target_include_directories(pair PUBLIC include)
target_link_libraries(pair PUBLIC storage)

# Storage library
add_library(storage STATIC
        src/storage/storage.cpp
        src/storage/user.cpp
        src/storage/sqlite3.c)
target_include_directories(storage PUBLIC include)

# Add UI forms
set(UI_SOURCES
        src/frontend/chat.ui
        src/frontend/dialog.ui
        src/frontend/eat.ui
        src/frontend/list.ui
        src/frontend/messagelist.ui
        src/frontend/pairpal.ui
        src/frontend/play.ui
        src/frontend/registerpage.ui
        src/frontend/self.ui
        src/frontend/sport.ui
        src/frontend/study.ui)
# Add translation files
set(TRANSLATIONS
        src/frontend/page1_zh_CN.ts)

qt5_add_translation(QM_FILES ${TRANSLATIONS})

# Define frontend
add_executable(frontend
        src/frontend/chat.cpp
        src/frontend/dialog.cpp
        src/frontend/eat.cpp
        src/frontend/list.cpp
        src/frontend/main.cpp
        src/frontend/pairpal.cpp
        src/frontend/play.cpp
        src/frontend/registerpage.cpp
        src/frontend/self.cpp
        src/frontend/sport.cpp
        src/frontend/study.cpp
        src/frontend/ui.cpp
        ${UI_SOURCES}
        ${QM_FILES}
)
target_include_directories(frontend PUBLIC include)
target_link_libraries(frontend PUBLIC api Qt5::Widgets Qt5::Core Qt5::Gui)


# Define backend
add_executable(backend
        src/backend.cpp
        src/api/message.cpp
        src/api/server.cpp)
target_link_libraries(backend PUBLIC storage chat pair api)

# Tests
# API
## Client test
add_executable(test-client test/api/test-client.cpp)
target_link_libraries(test-client PUBLIC api GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)
add_test(NAME test-client COMMAND test-client)
## Message test
add_executable(test-message test/api/test-message.cpp)
target_link_libraries(test-message PUBLIC api GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)
add_test(NAME test-message COMMAND test-message)
## Server test
add_executable(test-server test/api/test-server.cpp)
target_link_libraries(test-server PUBLIC api GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)
add_test(NAME test-server COMMAND test-server)

# Storage
add_executable(s-test test/Storage_test/s-test.cpp)
target_link_libraries(s-test storage)
add_test(NAME s-test COMMAND s-test)


# Pair
add_executable(test-pair test/pair/test-pair.cpp)
target_link_libraries(test-pair PUBLIC pair GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)
add_test(NAME test-pair COMMAND test-pair)
