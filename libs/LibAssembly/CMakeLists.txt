cmake_minimum_required(VERSION 3.16)

project(LibAssembly LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Widgets)
find_package(Doxygen)

add_library(Assembly SHARED
  LibAssembly_global.h
  libassembly.cpp
  libassembly.h
  assembly.h
  assembly.cpp
  memory.h
  statemanager.h
  memory.cpp
  statemanager.cpp
)

set(DOXYGEN_GENERATE_HTML YES)
doxygen_add_docs(
    doxygen
    ${PROJECT_SOURCE_DIR}
    ALL
)

target_link_libraries(Assembly PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Widgets)

target_compile_definitions(Assembly PRIVATE LIBASSEMBLY_LIBRARY)
