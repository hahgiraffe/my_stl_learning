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
include CMakeFiles/SequenceContainertest.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/SequenceContainertest.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/SequenceContainertest.dir/flags.make

CMakeFiles/SequenceContainertest.dir/hahatest/hahatest.cc.o: CMakeFiles/SequenceContainertest.dir/flags.make
CMakeFiles/SequenceContainertest.dir/hahatest/hahatest.cc.o: ../hahatest/hahatest.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/chs/my_stl_learning/MiniSTL/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/SequenceContainertest.dir/hahatest/hahatest.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/SequenceContainertest.dir/hahatest/hahatest.cc.o -c /home/chs/my_stl_learning/MiniSTL/hahatest/hahatest.cc

CMakeFiles/SequenceContainertest.dir/hahatest/hahatest.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SequenceContainertest.dir/hahatest/hahatest.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/chs/my_stl_learning/MiniSTL/hahatest/hahatest.cc > CMakeFiles/SequenceContainertest.dir/hahatest/hahatest.cc.i

CMakeFiles/SequenceContainertest.dir/hahatest/hahatest.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SequenceContainertest.dir/hahatest/hahatest.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/chs/my_stl_learning/MiniSTL/hahatest/hahatest.cc -o CMakeFiles/SequenceContainertest.dir/hahatest/hahatest.cc.s

CMakeFiles/SequenceContainertest.dir/hahatest/hahatest.cc.o.requires:

.PHONY : CMakeFiles/SequenceContainertest.dir/hahatest/hahatest.cc.o.requires

CMakeFiles/SequenceContainertest.dir/hahatest/hahatest.cc.o.provides: CMakeFiles/SequenceContainertest.dir/hahatest/hahatest.cc.o.requires
	$(MAKE) -f CMakeFiles/SequenceContainertest.dir/build.make CMakeFiles/SequenceContainertest.dir/hahatest/hahatest.cc.o.provides.build
.PHONY : CMakeFiles/SequenceContainertest.dir/hahatest/hahatest.cc.o.provides

CMakeFiles/SequenceContainertest.dir/hahatest/hahatest.cc.o.provides.build: CMakeFiles/SequenceContainertest.dir/hahatest/hahatest.cc.o


CMakeFiles/SequenceContainertest.dir/test/SequenceContainerTest.cpp.o: CMakeFiles/SequenceContainertest.dir/flags.make
CMakeFiles/SequenceContainertest.dir/test/SequenceContainerTest.cpp.o: ../test/SequenceContainerTest.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/chs/my_stl_learning/MiniSTL/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/SequenceContainertest.dir/test/SequenceContainerTest.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/SequenceContainertest.dir/test/SequenceContainerTest.cpp.o -c /home/chs/my_stl_learning/MiniSTL/test/SequenceContainerTest.cpp

CMakeFiles/SequenceContainertest.dir/test/SequenceContainerTest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SequenceContainertest.dir/test/SequenceContainerTest.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/chs/my_stl_learning/MiniSTL/test/SequenceContainerTest.cpp > CMakeFiles/SequenceContainertest.dir/test/SequenceContainerTest.cpp.i

CMakeFiles/SequenceContainertest.dir/test/SequenceContainerTest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SequenceContainertest.dir/test/SequenceContainerTest.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/chs/my_stl_learning/MiniSTL/test/SequenceContainerTest.cpp -o CMakeFiles/SequenceContainertest.dir/test/SequenceContainerTest.cpp.s

CMakeFiles/SequenceContainertest.dir/test/SequenceContainerTest.cpp.o.requires:

.PHONY : CMakeFiles/SequenceContainertest.dir/test/SequenceContainerTest.cpp.o.requires

CMakeFiles/SequenceContainertest.dir/test/SequenceContainerTest.cpp.o.provides: CMakeFiles/SequenceContainertest.dir/test/SequenceContainerTest.cpp.o.requires
	$(MAKE) -f CMakeFiles/SequenceContainertest.dir/build.make CMakeFiles/SequenceContainertest.dir/test/SequenceContainerTest.cpp.o.provides.build
.PHONY : CMakeFiles/SequenceContainertest.dir/test/SequenceContainerTest.cpp.o.provides

CMakeFiles/SequenceContainertest.dir/test/SequenceContainerTest.cpp.o.provides.build: CMakeFiles/SequenceContainertest.dir/test/SequenceContainerTest.cpp.o


# Object files for target SequenceContainertest
SequenceContainertest_OBJECTS = \
"CMakeFiles/SequenceContainertest.dir/hahatest/hahatest.cc.o" \
"CMakeFiles/SequenceContainertest.dir/test/SequenceContainerTest.cpp.o"

# External object files for target SequenceContainertest
SequenceContainertest_EXTERNAL_OBJECTS =

bin/SequenceContainertest: CMakeFiles/SequenceContainertest.dir/hahatest/hahatest.cc.o
bin/SequenceContainertest: CMakeFiles/SequenceContainertest.dir/test/SequenceContainerTest.cpp.o
bin/SequenceContainertest: CMakeFiles/SequenceContainertest.dir/build.make
bin/SequenceContainertest: CMakeFiles/SequenceContainertest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/chs/my_stl_learning/MiniSTL/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable bin/SequenceContainertest"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/SequenceContainertest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/SequenceContainertest.dir/build: bin/SequenceContainertest

.PHONY : CMakeFiles/SequenceContainertest.dir/build

CMakeFiles/SequenceContainertest.dir/requires: CMakeFiles/SequenceContainertest.dir/hahatest/hahatest.cc.o.requires
CMakeFiles/SequenceContainertest.dir/requires: CMakeFiles/SequenceContainertest.dir/test/SequenceContainerTest.cpp.o.requires

.PHONY : CMakeFiles/SequenceContainertest.dir/requires

CMakeFiles/SequenceContainertest.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/SequenceContainertest.dir/cmake_clean.cmake
.PHONY : CMakeFiles/SequenceContainertest.dir/clean

CMakeFiles/SequenceContainertest.dir/depend:
	cd /home/chs/my_stl_learning/MiniSTL/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/chs/my_stl_learning/MiniSTL /home/chs/my_stl_learning/MiniSTL /home/chs/my_stl_learning/MiniSTL/build /home/chs/my_stl_learning/MiniSTL/build /home/chs/my_stl_learning/MiniSTL/build/CMakeFiles/SequenceContainertest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/SequenceContainertest.dir/depend

