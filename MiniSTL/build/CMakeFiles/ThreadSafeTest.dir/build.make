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
include CMakeFiles/ThreadSafeTest.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/ThreadSafeTest.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ThreadSafeTest.dir/flags.make

CMakeFiles/ThreadSafeTest.dir/hahatest/hahatest.cc.o: CMakeFiles/ThreadSafeTest.dir/flags.make
CMakeFiles/ThreadSafeTest.dir/hahatest/hahatest.cc.o: ../hahatest/hahatest.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/chs/my_stl_learning/MiniSTL/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/ThreadSafeTest.dir/hahatest/hahatest.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ThreadSafeTest.dir/hahatest/hahatest.cc.o -c /home/chs/my_stl_learning/MiniSTL/hahatest/hahatest.cc

CMakeFiles/ThreadSafeTest.dir/hahatest/hahatest.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ThreadSafeTest.dir/hahatest/hahatest.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/chs/my_stl_learning/MiniSTL/hahatest/hahatest.cc > CMakeFiles/ThreadSafeTest.dir/hahatest/hahatest.cc.i

CMakeFiles/ThreadSafeTest.dir/hahatest/hahatest.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ThreadSafeTest.dir/hahatest/hahatest.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/chs/my_stl_learning/MiniSTL/hahatest/hahatest.cc -o CMakeFiles/ThreadSafeTest.dir/hahatest/hahatest.cc.s

CMakeFiles/ThreadSafeTest.dir/hahatest/hahatest.cc.o.requires:

.PHONY : CMakeFiles/ThreadSafeTest.dir/hahatest/hahatest.cc.o.requires

CMakeFiles/ThreadSafeTest.dir/hahatest/hahatest.cc.o.provides: CMakeFiles/ThreadSafeTest.dir/hahatest/hahatest.cc.o.requires
	$(MAKE) -f CMakeFiles/ThreadSafeTest.dir/build.make CMakeFiles/ThreadSafeTest.dir/hahatest/hahatest.cc.o.provides.build
.PHONY : CMakeFiles/ThreadSafeTest.dir/hahatest/hahatest.cc.o.provides

CMakeFiles/ThreadSafeTest.dir/hahatest/hahatest.cc.o.provides.build: CMakeFiles/ThreadSafeTest.dir/hahatest/hahatest.cc.o


CMakeFiles/ThreadSafeTest.dir/test/ThreadSafeTest.cpp.o: CMakeFiles/ThreadSafeTest.dir/flags.make
CMakeFiles/ThreadSafeTest.dir/test/ThreadSafeTest.cpp.o: ../test/ThreadSafeTest.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/chs/my_stl_learning/MiniSTL/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/ThreadSafeTest.dir/test/ThreadSafeTest.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ThreadSafeTest.dir/test/ThreadSafeTest.cpp.o -c /home/chs/my_stl_learning/MiniSTL/test/ThreadSafeTest.cpp

CMakeFiles/ThreadSafeTest.dir/test/ThreadSafeTest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ThreadSafeTest.dir/test/ThreadSafeTest.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/chs/my_stl_learning/MiniSTL/test/ThreadSafeTest.cpp > CMakeFiles/ThreadSafeTest.dir/test/ThreadSafeTest.cpp.i

CMakeFiles/ThreadSafeTest.dir/test/ThreadSafeTest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ThreadSafeTest.dir/test/ThreadSafeTest.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/chs/my_stl_learning/MiniSTL/test/ThreadSafeTest.cpp -o CMakeFiles/ThreadSafeTest.dir/test/ThreadSafeTest.cpp.s

CMakeFiles/ThreadSafeTest.dir/test/ThreadSafeTest.cpp.o.requires:

.PHONY : CMakeFiles/ThreadSafeTest.dir/test/ThreadSafeTest.cpp.o.requires

CMakeFiles/ThreadSafeTest.dir/test/ThreadSafeTest.cpp.o.provides: CMakeFiles/ThreadSafeTest.dir/test/ThreadSafeTest.cpp.o.requires
	$(MAKE) -f CMakeFiles/ThreadSafeTest.dir/build.make CMakeFiles/ThreadSafeTest.dir/test/ThreadSafeTest.cpp.o.provides.build
.PHONY : CMakeFiles/ThreadSafeTest.dir/test/ThreadSafeTest.cpp.o.provides

CMakeFiles/ThreadSafeTest.dir/test/ThreadSafeTest.cpp.o.provides.build: CMakeFiles/ThreadSafeTest.dir/test/ThreadSafeTest.cpp.o


# Object files for target ThreadSafeTest
ThreadSafeTest_OBJECTS = \
"CMakeFiles/ThreadSafeTest.dir/hahatest/hahatest.cc.o" \
"CMakeFiles/ThreadSafeTest.dir/test/ThreadSafeTest.cpp.o"

# External object files for target ThreadSafeTest
ThreadSafeTest_EXTERNAL_OBJECTS =

bin/ThreadSafeTest: CMakeFiles/ThreadSafeTest.dir/hahatest/hahatest.cc.o
bin/ThreadSafeTest: CMakeFiles/ThreadSafeTest.dir/test/ThreadSafeTest.cpp.o
bin/ThreadSafeTest: CMakeFiles/ThreadSafeTest.dir/build.make
bin/ThreadSafeTest: CMakeFiles/ThreadSafeTest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/chs/my_stl_learning/MiniSTL/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable bin/ThreadSafeTest"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ThreadSafeTest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ThreadSafeTest.dir/build: bin/ThreadSafeTest

.PHONY : CMakeFiles/ThreadSafeTest.dir/build

CMakeFiles/ThreadSafeTest.dir/requires: CMakeFiles/ThreadSafeTest.dir/hahatest/hahatest.cc.o.requires
CMakeFiles/ThreadSafeTest.dir/requires: CMakeFiles/ThreadSafeTest.dir/test/ThreadSafeTest.cpp.o.requires

.PHONY : CMakeFiles/ThreadSafeTest.dir/requires

CMakeFiles/ThreadSafeTest.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ThreadSafeTest.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ThreadSafeTest.dir/clean

CMakeFiles/ThreadSafeTest.dir/depend:
	cd /home/chs/my_stl_learning/MiniSTL/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/chs/my_stl_learning/MiniSTL /home/chs/my_stl_learning/MiniSTL /home/chs/my_stl_learning/MiniSTL/build /home/chs/my_stl_learning/MiniSTL/build /home/chs/my_stl_learning/MiniSTL/build/CMakeFiles/ThreadSafeTest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ThreadSafeTest.dir/depend
