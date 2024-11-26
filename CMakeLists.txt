cmake_minimum_required(VERSION 3.29)
project(pairpal LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Add third-party libraries
find_package(nlohmann_json CONFIG REQUIRED)
find_package(cppzmq CONFIG REQUIRED)
find_package(GTest CONFIG REQUIRED)
find_package(Qt5 COMPONENTS Core Gui Widgets LinguistTools REQUIRED)

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
set(UI_FORMS
        src/ui/ui/dialog.ui
        src/ui/ui/eat.ui
        src/ui/ui/pairpal.ui
        src/ui/ui/play.ui
        src/ui/ui/registerpage.ui
        src/ui/ui/self.ui
        src/ui/ui/sport.ui
        src/ui/ui/study.ui)
# Add translation files
set(TRANSLATIONS
        src/ui/translations/page1_zh_CN.ts)

qt5_wrap_ui(UI_HEADERS ${UI_FORMS})
qt5_add_translation(QM_FILES ${TRANSLATIONS})

# Define frontend
add_executable(frontend
        src/frontend.cpp
        src/ui/dialog.cpp
        include/ui/dialog.h
        src/ui/eat.cpp
        include/ui/eat.h
        src/ui/pairpal.cpp
        include/ui/pairpal.h
        src/ui/play.cpp
        include/ui/play.h
        src/ui/registerpage.cpp
        include/ui/registerpage.h
        src/ui/self.cpp
        include/ui/self.h
        src/ui/sport.cpp
        include/ui/sport.h
        src/ui/study.cpp
        include/ui/sport.h)
target_link_libraries(frontend PUBLIC api ui Qt5::Widgets Qt5::Core Qt5::Gui)
target_sources(frontend PRIVATE ${UI_HEADERS} ${QM_FILES})
target_include_directories(frontend PUBLIC include)

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
