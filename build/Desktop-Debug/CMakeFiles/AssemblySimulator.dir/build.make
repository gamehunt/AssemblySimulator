# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.30

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /hdd/Projects/Labs/PS/CourseWork/AssemblySimulator

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /hdd/Projects/Labs/PS/CourseWork/AssemblySimulator/build/Desktop-Debug

# Include any dependencies generated for this target.
include CMakeFiles/AssemblySimulator.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/AssemblySimulator.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/AssemblySimulator.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/AssemblySimulator.dir/flags.make

AssemblySimulator_autogen/timestamp: /usr/lib/qt6/moc
AssemblySimulator_autogen/timestamp: /usr/lib/qt6/uic
AssemblySimulator_autogen/timestamp: CMakeFiles/AssemblySimulator.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/hdd/Projects/Labs/PS/CourseWork/AssemblySimulator/build/Desktop-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Automatic MOC and UIC for target AssemblySimulator"
	/usr/bin/cmake -E cmake_autogen /hdd/Projects/Labs/PS/CourseWork/AssemblySimulator/build/Desktop-Debug/CMakeFiles/AssemblySimulator_autogen.dir/AutogenInfo.json Debug
	/usr/bin/cmake -E touch /hdd/Projects/Labs/PS/CourseWork/AssemblySimulator/build/Desktop-Debug/AssemblySimulator_autogen/timestamp

AssemblySimulator_autogen/EWIEGA46WW/qrc_icons.cpp: /hdd/Projects/Labs/PS/CourseWork/AssemblySimulator/icons.qrc
AssemblySimulator_autogen/EWIEGA46WW/qrc_icons.cpp: CMakeFiles/AssemblySimulator_autogen.dir/AutoRcc_icons_EWIEGA46WW_Info.json
AssemblySimulator_autogen/EWIEGA46WW/qrc_icons.cpp: /hdd/Projects/Labs/PS/CourseWork/AssemblySimulator/icons/bytecode.ico
AssemblySimulator_autogen/EWIEGA46WW/qrc_icons.cpp: /hdd/Projects/Labs/PS/CourseWork/AssemblySimulator/icons/step.ico
AssemblySimulator_autogen/EWIEGA46WW/qrc_icons.cpp: /hdd/Projects/Labs/PS/CourseWork/AssemblySimulator/icons/run.ico
AssemblySimulator_autogen/EWIEGA46WW/qrc_icons.cpp: /hdd/Projects/Labs/PS/CourseWork/AssemblySimulator/icons/x86.ico
AssemblySimulator_autogen/EWIEGA46WW/qrc_icons.cpp: /hdd/Projects/Labs/PS/CourseWork/AssemblySimulator/icons/x64.ico
AssemblySimulator_autogen/EWIEGA46WW/qrc_icons.cpp: /hdd/Projects/Labs/PS/CourseWork/AssemblySimulator/icons/mem.ico
AssemblySimulator_autogen/EWIEGA46WW/qrc_icons.cpp: /usr/lib/qt6/rcc
AssemblySimulator_autogen/EWIEGA46WW/qrc_icons.cpp: /usr/lib/qt6/rcc
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/hdd/Projects/Labs/PS/CourseWork/AssemblySimulator/build/Desktop-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Automatic RCC for icons.qrc"
	/usr/bin/cmake -E cmake_autorcc /hdd/Projects/Labs/PS/CourseWork/AssemblySimulator/build/Desktop-Debug/CMakeFiles/AssemblySimulator_autogen.dir/AutoRcc_icons_EWIEGA46WW_Info.json Debug

CMakeFiles/AssemblySimulator.dir/AssemblySimulator_autogen/mocs_compilation.cpp.o: CMakeFiles/AssemblySimulator.dir/flags.make
CMakeFiles/AssemblySimulator.dir/AssemblySimulator_autogen/mocs_compilation.cpp.o: AssemblySimulator_autogen/mocs_compilation.cpp
CMakeFiles/AssemblySimulator.dir/AssemblySimulator_autogen/mocs_compilation.cpp.o: CMakeFiles/AssemblySimulator.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/hdd/Projects/Labs/PS/CourseWork/AssemblySimulator/build/Desktop-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/AssemblySimulator.dir/AssemblySimulator_autogen/mocs_compilation.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/AssemblySimulator.dir/AssemblySimulator_autogen/mocs_compilation.cpp.o -MF CMakeFiles/AssemblySimulator.dir/AssemblySimulator_autogen/mocs_compilation.cpp.o.d -o CMakeFiles/AssemblySimulator.dir/AssemblySimulator_autogen/mocs_compilation.cpp.o -c /hdd/Projects/Labs/PS/CourseWork/AssemblySimulator/build/Desktop-Debug/AssemblySimulator_autogen/mocs_compilation.cpp

CMakeFiles/AssemblySimulator.dir/AssemblySimulator_autogen/mocs_compilation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/AssemblySimulator.dir/AssemblySimulator_autogen/mocs_compilation.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /hdd/Projects/Labs/PS/CourseWork/AssemblySimulator/build/Desktop-Debug/AssemblySimulator_autogen/mocs_compilation.cpp > CMakeFiles/AssemblySimulator.dir/AssemblySimulator_autogen/mocs_compilation.cpp.i

CMakeFiles/AssemblySimulator.dir/AssemblySimulator_autogen/mocs_compilation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/AssemblySimulator.dir/AssemblySimulator_autogen/mocs_compilation.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /hdd/Projects/Labs/PS/CourseWork/AssemblySimulator/build/Desktop-Debug/AssemblySimulator_autogen/mocs_compilation.cpp -o CMakeFiles/AssemblySimulator.dir/AssemblySimulator_autogen/mocs_compilation.cpp.s

CMakeFiles/AssemblySimulator.dir/main.cpp.o: CMakeFiles/AssemblySimulator.dir/flags.make
CMakeFiles/AssemblySimulator.dir/main.cpp.o: /hdd/Projects/Labs/PS/CourseWork/AssemblySimulator/main.cpp
CMakeFiles/AssemblySimulator.dir/main.cpp.o: CMakeFiles/AssemblySimulator.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/hdd/Projects/Labs/PS/CourseWork/AssemblySimulator/build/Desktop-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/AssemblySimulator.dir/main.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/AssemblySimulator.dir/main.cpp.o -MF CMakeFiles/AssemblySimulator.dir/main.cpp.o.d -o CMakeFiles/AssemblySimulator.dir/main.cpp.o -c /hdd/Projects/Labs/PS/CourseWork/AssemblySimulator/main.cpp

CMakeFiles/AssemblySimulator.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/AssemblySimulator.dir/main.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /hdd/Projects/Labs/PS/CourseWork/AssemblySimulator/main.cpp > CMakeFiles/AssemblySimulator.dir/main.cpp.i

CMakeFiles/AssemblySimulator.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/AssemblySimulator.dir/main.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /hdd/Projects/Labs/PS/CourseWork/AssemblySimulator/main.cpp -o CMakeFiles/AssemblySimulator.dir/main.cpp.s

CMakeFiles/AssemblySimulator.dir/mainwindow.cpp.o: CMakeFiles/AssemblySimulator.dir/flags.make
CMakeFiles/AssemblySimulator.dir/mainwindow.cpp.o: /hdd/Projects/Labs/PS/CourseWork/AssemblySimulator/mainwindow.cpp
CMakeFiles/AssemblySimulator.dir/mainwindow.cpp.o: CMakeFiles/AssemblySimulator.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/hdd/Projects/Labs/PS/CourseWork/AssemblySimulator/build/Desktop-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/AssemblySimulator.dir/mainwindow.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/AssemblySimulator.dir/mainwindow.cpp.o -MF CMakeFiles/AssemblySimulator.dir/mainwindow.cpp.o.d -o CMakeFiles/AssemblySimulator.dir/mainwindow.cpp.o -c /hdd/Projects/Labs/PS/CourseWork/AssemblySimulator/mainwindow.cpp

CMakeFiles/AssemblySimulator.dir/mainwindow.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/AssemblySimulator.dir/mainwindow.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /hdd/Projects/Labs/PS/CourseWork/AssemblySimulator/mainwindow.cpp > CMakeFiles/AssemblySimulator.dir/mainwindow.cpp.i

CMakeFiles/AssemblySimulator.dir/mainwindow.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/AssemblySimulator.dir/mainwindow.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /hdd/Projects/Labs/PS/CourseWork/AssemblySimulator/mainwindow.cpp -o CMakeFiles/AssemblySimulator.dir/mainwindow.cpp.s

CMakeFiles/AssemblySimulator.dir/states/amd64states.cpp.o: CMakeFiles/AssemblySimulator.dir/flags.make
CMakeFiles/AssemblySimulator.dir/states/amd64states.cpp.o: /hdd/Projects/Labs/PS/CourseWork/AssemblySimulator/states/amd64states.cpp
CMakeFiles/AssemblySimulator.dir/states/amd64states.cpp.o: CMakeFiles/AssemblySimulator.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/hdd/Projects/Labs/PS/CourseWork/AssemblySimulator/build/Desktop-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/AssemblySimulator.dir/states/amd64states.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/AssemblySimulator.dir/states/amd64states.cpp.o -MF CMakeFiles/AssemblySimulator.dir/states/amd64states.cpp.o.d -o CMakeFiles/AssemblySimulator.dir/states/amd64states.cpp.o -c /hdd/Projects/Labs/PS/CourseWork/AssemblySimulator/states/amd64states.cpp

CMakeFiles/AssemblySimulator.dir/states/amd64states.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/AssemblySimulator.dir/states/amd64states.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /hdd/Projects/Labs/PS/CourseWork/AssemblySimulator/states/amd64states.cpp > CMakeFiles/AssemblySimulator.dir/states/amd64states.cpp.i

CMakeFiles/AssemblySimulator.dir/states/amd64states.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/AssemblySimulator.dir/states/amd64states.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /hdd/Projects/Labs/PS/CourseWork/AssemblySimulator/states/amd64states.cpp -o CMakeFiles/AssemblySimulator.dir/states/amd64states.cpp.s

CMakeFiles/AssemblySimulator.dir/AssemblySimulator_autogen/EWIEGA46WW/qrc_icons.cpp.o: CMakeFiles/AssemblySimulator.dir/flags.make
CMakeFiles/AssemblySimulator.dir/AssemblySimulator_autogen/EWIEGA46WW/qrc_icons.cpp.o: AssemblySimulator_autogen/EWIEGA46WW/qrc_icons.cpp
CMakeFiles/AssemblySimulator.dir/AssemblySimulator_autogen/EWIEGA46WW/qrc_icons.cpp.o: CMakeFiles/AssemblySimulator.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/hdd/Projects/Labs/PS/CourseWork/AssemblySimulator/build/Desktop-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/AssemblySimulator.dir/AssemblySimulator_autogen/EWIEGA46WW/qrc_icons.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/AssemblySimulator.dir/AssemblySimulator_autogen/EWIEGA46WW/qrc_icons.cpp.o -MF CMakeFiles/AssemblySimulator.dir/AssemblySimulator_autogen/EWIEGA46WW/qrc_icons.cpp.o.d -o CMakeFiles/AssemblySimulator.dir/AssemblySimulator_autogen/EWIEGA46WW/qrc_icons.cpp.o -c /hdd/Projects/Labs/PS/CourseWork/AssemblySimulator/build/Desktop-Debug/AssemblySimulator_autogen/EWIEGA46WW/qrc_icons.cpp

CMakeFiles/AssemblySimulator.dir/AssemblySimulator_autogen/EWIEGA46WW/qrc_icons.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/AssemblySimulator.dir/AssemblySimulator_autogen/EWIEGA46WW/qrc_icons.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /hdd/Projects/Labs/PS/CourseWork/AssemblySimulator/build/Desktop-Debug/AssemblySimulator_autogen/EWIEGA46WW/qrc_icons.cpp > CMakeFiles/AssemblySimulator.dir/AssemblySimulator_autogen/EWIEGA46WW/qrc_icons.cpp.i

CMakeFiles/AssemblySimulator.dir/AssemblySimulator_autogen/EWIEGA46WW/qrc_icons.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/AssemblySimulator.dir/AssemblySimulator_autogen/EWIEGA46WW/qrc_icons.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /hdd/Projects/Labs/PS/CourseWork/AssemblySimulator/build/Desktop-Debug/AssemblySimulator_autogen/EWIEGA46WW/qrc_icons.cpp -o CMakeFiles/AssemblySimulator.dir/AssemblySimulator_autogen/EWIEGA46WW/qrc_icons.cpp.s

# Object files for target AssemblySimulator
AssemblySimulator_OBJECTS = \
"CMakeFiles/AssemblySimulator.dir/AssemblySimulator_autogen/mocs_compilation.cpp.o" \
"CMakeFiles/AssemblySimulator.dir/main.cpp.o" \
"CMakeFiles/AssemblySimulator.dir/mainwindow.cpp.o" \
"CMakeFiles/AssemblySimulator.dir/states/amd64states.cpp.o" \
"CMakeFiles/AssemblySimulator.dir/AssemblySimulator_autogen/EWIEGA46WW/qrc_icons.cpp.o"

# External object files for target AssemblySimulator
AssemblySimulator_EXTERNAL_OBJECTS =

AssemblySimulator: CMakeFiles/AssemblySimulator.dir/AssemblySimulator_autogen/mocs_compilation.cpp.o
AssemblySimulator: CMakeFiles/AssemblySimulator.dir/main.cpp.o
AssemblySimulator: CMakeFiles/AssemblySimulator.dir/mainwindow.cpp.o
AssemblySimulator: CMakeFiles/AssemblySimulator.dir/states/amd64states.cpp.o
AssemblySimulator: CMakeFiles/AssemblySimulator.dir/AssemblySimulator_autogen/EWIEGA46WW/qrc_icons.cpp.o
AssemblySimulator: CMakeFiles/AssemblySimulator.dir/build.make
AssemblySimulator: /usr/lib/libQt6Widgets.so.6.7.2
AssemblySimulator: /usr/lib/libQt6Gui.so.6.7.2
AssemblySimulator: /usr/lib/libQt6Core.so.6.7.2
AssemblySimulator: /usr/lib/libGLX.so
AssemblySimulator: /usr/lib/libOpenGL.so
AssemblySimulator: CMakeFiles/AssemblySimulator.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/hdd/Projects/Labs/PS/CourseWork/AssemblySimulator/build/Desktop-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking CXX executable AssemblySimulator"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/AssemblySimulator.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/AssemblySimulator.dir/build: AssemblySimulator
.PHONY : CMakeFiles/AssemblySimulator.dir/build

CMakeFiles/AssemblySimulator.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/AssemblySimulator.dir/cmake_clean.cmake
.PHONY : CMakeFiles/AssemblySimulator.dir/clean

CMakeFiles/AssemblySimulator.dir/depend: AssemblySimulator_autogen/EWIEGA46WW/qrc_icons.cpp
CMakeFiles/AssemblySimulator.dir/depend: AssemblySimulator_autogen/timestamp
	cd /hdd/Projects/Labs/PS/CourseWork/AssemblySimulator/build/Desktop-Debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /hdd/Projects/Labs/PS/CourseWork/AssemblySimulator /hdd/Projects/Labs/PS/CourseWork/AssemblySimulator /hdd/Projects/Labs/PS/CourseWork/AssemblySimulator/build/Desktop-Debug /hdd/Projects/Labs/PS/CourseWork/AssemblySimulator/build/Desktop-Debug /hdd/Projects/Labs/PS/CourseWork/AssemblySimulator/build/Desktop-Debug/CMakeFiles/AssemblySimulator.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/AssemblySimulator.dir/depend

