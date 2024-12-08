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
        include/api/client.hpp
        src/api/client.cpp
        include/api/server.hpp
        src/api/server.cpp
        include/api/network_message.hpp
        src/api/network_message.cpp)
target_include_directories(api PUBLIC include/api)
target_link_libraries(api PRIVATE chat pair storage nlohmann_json::nlohmann_json cppzmq cppzmq-static)

# Chat library
add_library(chat STATIC
        include/chat/chat.hpp
        src/chat/chat.cpp
        include/chat/dialog.hpp
        src/chat/dialog.cpp
        include/chat/message.hpp
        src/chat/message.cpp
        include/chat/message_store.hpp
        src/chat/message_store.cpp)
target_include_directories(chat PUBLIC include/chat)
target_link_libraries(chat PRIVATE storage)

# Pair library
add_library(pair STATIC
        include/pair/pair.hpp
        src/pair/pair.cpp)
target_include_directories(pair PUBLIC include/pair)
target_link_libraries(pair PRIVATE storage)

# Storage library
add_library(storage STATIC
        include/storage/storage.hpp
        src/storage/storage.cpp
        include/storage/sqlite3.h
        src/storage/sqlite3.c)
target_include_directories(storage PUBLIC include/storage)

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
target_include_directories(frontend PRIVATE src/frontend)
target_link_libraries(frontend PRIVATE api Qt5::Widgets Qt5::Core Qt5::Gui)


# Define backend
add_executable(backend
        src/backend.cpp
        src/api/network_message.cpp
        src/api/server.cpp)
target_link_libraries(backend PRIVATE storage chat pair api)

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
add_executable(test-storage test/storage/test-storage.cpp)
target_link_libraries(test-storage PUBLIC storage GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)
add_test(NAME test-storage COMMAND test-storage)

add_executable(s-test test/Storage_test/s-test.cpp)
target_link_libraries(s-test storage)
add_test(NAME s-test COMMAND s-test)

# Chat
add_executable(chat-test test/Chat_test/chat-test.cpp
        src/chat/message_store.cpp)
target_link_libraries(chat-test chat)
add_test(NAME chat-test COMMAND chat-test)

# Pair
add_executable(test-pair test/pair/test-pair.cpp)
target_link_libraries(test-pair PUBLIC pair GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)
add_test(NAME test-pair COMMAND test-pair)
