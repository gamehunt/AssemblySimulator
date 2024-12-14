cmake_minimum_required(VERSION 3.16)

project(AssemblySimulator VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Help)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(libs/LibParse)
add_subdirectory(libs/LibAssembly)
add_subdirectory(libs/Assemblies/AMD64)
add_subdirectory(docs)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)

qt_add_executable(AssemblySimulator
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        icons.qrc
        utils.h
        memorybrowserwidget.h memorybrowserwidget.cpp memorybrowserwidget.ui
        codeedit.h codeedit.cpp
        codeeditlinenumberarea.h codeeditlinenumberarea.cpp
        memoryeditdialog.h memoryeditdialog.cpp memoryeditdialog.ui
        disassemblerdialog.h disassemblerdialog.cpp disassemblerdialog.ui
        helpbrowser.h helpbrowser.cpp
        README.md
        examples.qrc
)

# Define target properties for Android with Qt 6 as:
#    set_property(TARGET AssemblySimulator APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(AssemblySimulator SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(AssemblySimulator
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(AssemblySimulator PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Help keystone Assembly)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.AssemblySimulator)
endif()

set_target_properties(AssemblySimulator PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS AssemblySimulator
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(AssemblySimulator)
endif()

add_custom_target(install_assemblies ALL
    COMMAND mkdir -p assemblies
    COMMAND cp ${CMAKE_BINARY_DIR}/libs/Assemblies/AMD64/*.so ${CMAKE_BINARY_DIR}/assemblies/
    DEPENDS AMD64
)
