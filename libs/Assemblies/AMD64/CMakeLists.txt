cmake_minimum_required(VERSION 3.16)

project(AMD64 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Gui Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Gui Widgets)

add_library(AMD64 SHARED
  amd64assemblyplugin.cpp
  amd64assemblyplugin.h
  AMD64.json
  amd64assembly.h amd64assembly.cpp amd64syntaxhighlighter.cpp amd64syntaxhighlighter.h amd64states.ui amd64states.cpp amd64states.h
)

target_link_libraries(AMD64 PRIVATE Qt${QT_VERSION_MAJOR}::Gui Qt${QT_VERSION_MAJOR}::Widgets Assembly)

target_compile_definitions(AMD64 PRIVATE AMD64_LIBRARY)
