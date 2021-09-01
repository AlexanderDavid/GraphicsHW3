# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.21

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
CMAKE_SOURCE_DIR = /home/alex/code/GraphicsHW1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/alex/code/GraphicsHW1/build

# Include any dependencies generated for this target.
include src/CMakeFiles/hw1_lib.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/CMakeFiles/hw1_lib.dir/compiler_depend.make

# Include the progress variables for this target.
include src/CMakeFiles/hw1_lib.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/hw1_lib.dir/flags.make

src/CMakeFiles/hw1_lib.dir/Triangle.cc.o: src/CMakeFiles/hw1_lib.dir/flags.make
src/CMakeFiles/hw1_lib.dir/Triangle.cc.o: ../src/Triangle.cc
src/CMakeFiles/hw1_lib.dir/Triangle.cc.o: src/CMakeFiles/hw1_lib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alex/code/GraphicsHW1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/hw1_lib.dir/Triangle.cc.o"
	cd /home/alex/code/GraphicsHW1/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/hw1_lib.dir/Triangle.cc.o -MF CMakeFiles/hw1_lib.dir/Triangle.cc.o.d -o CMakeFiles/hw1_lib.dir/Triangle.cc.o -c /home/alex/code/GraphicsHW1/src/Triangle.cc

src/CMakeFiles/hw1_lib.dir/Triangle.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/hw1_lib.dir/Triangle.cc.i"
	cd /home/alex/code/GraphicsHW1/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/alex/code/GraphicsHW1/src/Triangle.cc > CMakeFiles/hw1_lib.dir/Triangle.cc.i

src/CMakeFiles/hw1_lib.dir/Triangle.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/hw1_lib.dir/Triangle.cc.s"
	cd /home/alex/code/GraphicsHW1/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/alex/code/GraphicsHW1/src/Triangle.cc -o CMakeFiles/hw1_lib.dir/Triangle.cc.s

src/CMakeFiles/hw1_lib.dir/Viewer.cc.o: src/CMakeFiles/hw1_lib.dir/flags.make
src/CMakeFiles/hw1_lib.dir/Viewer.cc.o: ../src/Viewer.cc
src/CMakeFiles/hw1_lib.dir/Viewer.cc.o: src/CMakeFiles/hw1_lib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alex/code/GraphicsHW1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/CMakeFiles/hw1_lib.dir/Viewer.cc.o"
	cd /home/alex/code/GraphicsHW1/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/hw1_lib.dir/Viewer.cc.o -MF CMakeFiles/hw1_lib.dir/Viewer.cc.o.d -o CMakeFiles/hw1_lib.dir/Viewer.cc.o -c /home/alex/code/GraphicsHW1/src/Viewer.cc

src/CMakeFiles/hw1_lib.dir/Viewer.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/hw1_lib.dir/Viewer.cc.i"
	cd /home/alex/code/GraphicsHW1/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/alex/code/GraphicsHW1/src/Viewer.cc > CMakeFiles/hw1_lib.dir/Viewer.cc.i

src/CMakeFiles/hw1_lib.dir/Viewer.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/hw1_lib.dir/Viewer.cc.s"
	cd /home/alex/code/GraphicsHW1/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/alex/code/GraphicsHW1/src/Viewer.cc -o CMakeFiles/hw1_lib.dir/Viewer.cc.s

src/CMakeFiles/hw1_lib.dir/TriangleViewer.cc.o: src/CMakeFiles/hw1_lib.dir/flags.make
src/CMakeFiles/hw1_lib.dir/TriangleViewer.cc.o: ../src/TriangleViewer.cc
src/CMakeFiles/hw1_lib.dir/TriangleViewer.cc.o: src/CMakeFiles/hw1_lib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alex/code/GraphicsHW1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object src/CMakeFiles/hw1_lib.dir/TriangleViewer.cc.o"
	cd /home/alex/code/GraphicsHW1/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/hw1_lib.dir/TriangleViewer.cc.o -MF CMakeFiles/hw1_lib.dir/TriangleViewer.cc.o.d -o CMakeFiles/hw1_lib.dir/TriangleViewer.cc.o -c /home/alex/code/GraphicsHW1/src/TriangleViewer.cc

src/CMakeFiles/hw1_lib.dir/TriangleViewer.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/hw1_lib.dir/TriangleViewer.cc.i"
	cd /home/alex/code/GraphicsHW1/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/alex/code/GraphicsHW1/src/TriangleViewer.cc > CMakeFiles/hw1_lib.dir/TriangleViewer.cc.i

src/CMakeFiles/hw1_lib.dir/TriangleViewer.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/hw1_lib.dir/TriangleViewer.cc.s"
	cd /home/alex/code/GraphicsHW1/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/alex/code/GraphicsHW1/src/TriangleViewer.cc -o CMakeFiles/hw1_lib.dir/TriangleViewer.cc.s

# Object files for target hw1_lib
hw1_lib_OBJECTS = \
"CMakeFiles/hw1_lib.dir/Triangle.cc.o" \
"CMakeFiles/hw1_lib.dir/Viewer.cc.o" \
"CMakeFiles/hw1_lib.dir/TriangleViewer.cc.o"

# External object files for target hw1_lib
hw1_lib_EXTERNAL_OBJECTS =

lib/libhw1_lib.a: src/CMakeFiles/hw1_lib.dir/Triangle.cc.o
lib/libhw1_lib.a: src/CMakeFiles/hw1_lib.dir/Viewer.cc.o
lib/libhw1_lib.a: src/CMakeFiles/hw1_lib.dir/TriangleViewer.cc.o
lib/libhw1_lib.a: src/CMakeFiles/hw1_lib.dir/build.make
lib/libhw1_lib.a: src/CMakeFiles/hw1_lib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/alex/code/GraphicsHW1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX static library ../lib/libhw1_lib.a"
	cd /home/alex/code/GraphicsHW1/build/src && $(CMAKE_COMMAND) -P CMakeFiles/hw1_lib.dir/cmake_clean_target.cmake
	cd /home/alex/code/GraphicsHW1/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/hw1_lib.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/hw1_lib.dir/build: lib/libhw1_lib.a
.PHONY : src/CMakeFiles/hw1_lib.dir/build

src/CMakeFiles/hw1_lib.dir/clean:
	cd /home/alex/code/GraphicsHW1/build/src && $(CMAKE_COMMAND) -P CMakeFiles/hw1_lib.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/hw1_lib.dir/clean

src/CMakeFiles/hw1_lib.dir/depend:
	cd /home/alex/code/GraphicsHW1/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/alex/code/GraphicsHW1 /home/alex/code/GraphicsHW1/src /home/alex/code/GraphicsHW1/build /home/alex/code/GraphicsHW1/build/src /home/alex/code/GraphicsHW1/build/src/CMakeFiles/hw1_lib.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/hw1_lib.dir/depend

