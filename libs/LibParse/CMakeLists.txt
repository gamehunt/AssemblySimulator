cmake_minimum_required(VERSION 3.16)

project(LibParse LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

add_library(Parse SHARED
  libparse.cpp
  libparse.h

  builtin-features.inc
  builtin-features/functions.inc
  builtin-features/operations.inc
  builtin-features/reservedWords.inc
  builtin-features/typeSpecificFunctions.inc
  builtin-features.cpp

  functions.h
  functions.cpp

  containers.h
  containers.cpp

  shunting-yard.h
  shunting-yard-exceptions.h
  shunting-yard.cpp

  packToken.h
  packToken.cpp
)

target_link_libraries(Parse PRIVATE Qt${QT_VERSION_MAJOR}::Core)
target_compile_definitions(Parse PRIVATE LIBPARSE_LIBRARY)
