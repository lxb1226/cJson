# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_SOURCE_DIR = /home/heyjude/workspace/projects/cJson

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/heyjude/workspace/projects/cJson/build

# Include any dependencies generated for this target.
include tests/CMakeFiles/cjson_unittest.dir/depend.make

# Include the progress variables for this target.
include tests/CMakeFiles/cjson_unittest.dir/progress.make

# Include the compile flags for this target's objects.
include tests/CMakeFiles/cjson_unittest.dir/flags.make

tests/CMakeFiles/cjson_unittest.dir/cjson_unittest.cpp.o: tests/CMakeFiles/cjson_unittest.dir/flags.make
tests/CMakeFiles/cjson_unittest.dir/cjson_unittest.cpp.o: ../tests/cjson_unittest.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/heyjude/workspace/projects/cJson/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object tests/CMakeFiles/cjson_unittest.dir/cjson_unittest.cpp.o"
	cd /home/heyjude/workspace/projects/cJson/build/tests && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/cjson_unittest.dir/cjson_unittest.cpp.o -c /home/heyjude/workspace/projects/cJson/tests/cjson_unittest.cpp

tests/CMakeFiles/cjson_unittest.dir/cjson_unittest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cjson_unittest.dir/cjson_unittest.cpp.i"
	cd /home/heyjude/workspace/projects/cJson/build/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/heyjude/workspace/projects/cJson/tests/cjson_unittest.cpp > CMakeFiles/cjson_unittest.dir/cjson_unittest.cpp.i

tests/CMakeFiles/cjson_unittest.dir/cjson_unittest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cjson_unittest.dir/cjson_unittest.cpp.s"
	cd /home/heyjude/workspace/projects/cJson/build/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/heyjude/workspace/projects/cJson/tests/cjson_unittest.cpp -o CMakeFiles/cjson_unittest.dir/cjson_unittest.cpp.s

tests/CMakeFiles/cjson_unittest.dir/__/src/cJson.cpp.o: tests/CMakeFiles/cjson_unittest.dir/flags.make
tests/CMakeFiles/cjson_unittest.dir/__/src/cJson.cpp.o: ../src/cJson.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/heyjude/workspace/projects/cJson/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object tests/CMakeFiles/cjson_unittest.dir/__/src/cJson.cpp.o"
	cd /home/heyjude/workspace/projects/cJson/build/tests && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/cjson_unittest.dir/__/src/cJson.cpp.o -c /home/heyjude/workspace/projects/cJson/src/cJson.cpp

tests/CMakeFiles/cjson_unittest.dir/__/src/cJson.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cjson_unittest.dir/__/src/cJson.cpp.i"
	cd /home/heyjude/workspace/projects/cJson/build/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/heyjude/workspace/projects/cJson/src/cJson.cpp > CMakeFiles/cjson_unittest.dir/__/src/cJson.cpp.i

tests/CMakeFiles/cjson_unittest.dir/__/src/cJson.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cjson_unittest.dir/__/src/cJson.cpp.s"
	cd /home/heyjude/workspace/projects/cJson/build/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/heyjude/workspace/projects/cJson/src/cJson.cpp -o CMakeFiles/cjson_unittest.dir/__/src/cJson.cpp.s

# Object files for target cjson_unittest
cjson_unittest_OBJECTS = \
"CMakeFiles/cjson_unittest.dir/cjson_unittest.cpp.o" \
"CMakeFiles/cjson_unittest.dir/__/src/cJson.cpp.o"

# External object files for target cjson_unittest
cjson_unittest_EXTERNAL_OBJECTS =

tests/cjson_unittest: tests/CMakeFiles/cjson_unittest.dir/cjson_unittest.cpp.o
tests/cjson_unittest: tests/CMakeFiles/cjson_unittest.dir/__/src/cJson.cpp.o
tests/cjson_unittest: tests/CMakeFiles/cjson_unittest.dir/build.make
tests/cjson_unittest: /usr/local/lib/libgmock.a
tests/cjson_unittest: /usr/local/lib/libgmock.a
tests/cjson_unittest: /usr/local/lib/libgtest.a
tests/cjson_unittest: /usr/local/lib/libgtest_main.a
tests/cjson_unittest: tests/CMakeFiles/cjson_unittest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/heyjude/workspace/projects/cJson/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable cjson_unittest"
	cd /home/heyjude/workspace/projects/cJson/build/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/cjson_unittest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/CMakeFiles/cjson_unittest.dir/build: tests/cjson_unittest

.PHONY : tests/CMakeFiles/cjson_unittest.dir/build

tests/CMakeFiles/cjson_unittest.dir/clean:
	cd /home/heyjude/workspace/projects/cJson/build/tests && $(CMAKE_COMMAND) -P CMakeFiles/cjson_unittest.dir/cmake_clean.cmake
.PHONY : tests/CMakeFiles/cjson_unittest.dir/clean

tests/CMakeFiles/cjson_unittest.dir/depend:
	cd /home/heyjude/workspace/projects/cJson/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/heyjude/workspace/projects/cJson /home/heyjude/workspace/projects/cJson/tests /home/heyjude/workspace/projects/cJson/build /home/heyjude/workspace/projects/cJson/build/tests /home/heyjude/workspace/projects/cJson/build/tests/CMakeFiles/cjson_unittest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tests/CMakeFiles/cjson_unittest.dir/depend
