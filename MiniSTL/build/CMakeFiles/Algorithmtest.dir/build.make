# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
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
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/chs/my_stl_learning/MiniSTL

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/chs/my_stl_learning/MiniSTL/build

# Include any dependencies generated for this target.
include CMakeFiles/Algorithmtest.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Algorithmtest.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Algorithmtest.dir/flags.make

CMakeFiles/Algorithmtest.dir/test/AlgorithmTest.cpp.o: CMakeFiles/Algorithmtest.dir/flags.make
CMakeFiles/Algorithmtest.dir/test/AlgorithmTest.cpp.o: ../test/AlgorithmTest.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/chs/my_stl_learning/MiniSTL/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Algorithmtest.dir/test/AlgorithmTest.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Algorithmtest.dir/test/AlgorithmTest.cpp.o -c /home/chs/my_stl_learning/MiniSTL/test/AlgorithmTest.cpp

CMakeFiles/Algorithmtest.dir/test/AlgorithmTest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Algorithmtest.dir/test/AlgorithmTest.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/chs/my_stl_learning/MiniSTL/test/AlgorithmTest.cpp > CMakeFiles/Algorithmtest.dir/test/AlgorithmTest.cpp.i

CMakeFiles/Algorithmtest.dir/test/AlgorithmTest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Algorithmtest.dir/test/AlgorithmTest.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/chs/my_stl_learning/MiniSTL/test/AlgorithmTest.cpp -o CMakeFiles/Algorithmtest.dir/test/AlgorithmTest.cpp.s

CMakeFiles/Algorithmtest.dir/test/AlgorithmTest.cpp.o.requires:

.PHONY : CMakeFiles/Algorithmtest.dir/test/AlgorithmTest.cpp.o.requires

CMakeFiles/Algorithmtest.dir/test/AlgorithmTest.cpp.o.provides: CMakeFiles/Algorithmtest.dir/test/AlgorithmTest.cpp.o.requires
	$(MAKE) -f CMakeFiles/Algorithmtest.dir/build.make CMakeFiles/Algorithmtest.dir/test/AlgorithmTest.cpp.o.provides.build
.PHONY : CMakeFiles/Algorithmtest.dir/test/AlgorithmTest.cpp.o.provides

CMakeFiles/Algorithmtest.dir/test/AlgorithmTest.cpp.o.provides.build: CMakeFiles/Algorithmtest.dir/test/AlgorithmTest.cpp.o


# Object files for target Algorithmtest
Algorithmtest_OBJECTS = \
"CMakeFiles/Algorithmtest.dir/test/AlgorithmTest.cpp.o"

# External object files for target Algorithmtest
Algorithmtest_EXTERNAL_OBJECTS =

bin/Algorithmtest: CMakeFiles/Algorithmtest.dir/test/AlgorithmTest.cpp.o
bin/Algorithmtest: CMakeFiles/Algorithmtest.dir/build.make
bin/Algorithmtest: CMakeFiles/Algorithmtest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/chs/my_stl_learning/MiniSTL/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable bin/Algorithmtest"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Algorithmtest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Algorithmtest.dir/build: bin/Algorithmtest

.PHONY : CMakeFiles/Algorithmtest.dir/build

CMakeFiles/Algorithmtest.dir/requires: CMakeFiles/Algorithmtest.dir/test/AlgorithmTest.cpp.o.requires

.PHONY : CMakeFiles/Algorithmtest.dir/requires

CMakeFiles/Algorithmtest.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Algorithmtest.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Algorithmtest.dir/clean

CMakeFiles/Algorithmtest.dir/depend:
	cd /home/chs/my_stl_learning/MiniSTL/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/chs/my_stl_learning/MiniSTL /home/chs/my_stl_learning/MiniSTL /home/chs/my_stl_learning/MiniSTL/build /home/chs/my_stl_learning/MiniSTL/build /home/chs/my_stl_learning/MiniSTL/build/CMakeFiles/Algorithmtest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Algorithmtest.dir/depend
