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
CMAKE_SOURCE_DIR = /home/heyjude/workspace/projects/cJson

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/heyjude/workspace/projects/cJson/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/cJson_test.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/cJson_test.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/cJson_test.dir/flags.make

CMakeFiles/cJson_test.dir/test.c.o: CMakeFiles/cJson_test.dir/flags.make
CMakeFiles/cJson_test.dir/test.c.o: ../test.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/heyjude/workspace/projects/cJson/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/cJson_test.dir/test.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/cJson_test.dir/test.c.o   -c /home/heyjude/workspace/projects/cJson/test.c

CMakeFiles/cJson_test.dir/test.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/cJson_test.dir/test.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/heyjude/workspace/projects/cJson/test.c > CMakeFiles/cJson_test.dir/test.c.i

CMakeFiles/cJson_test.dir/test.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/cJson_test.dir/test.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/heyjude/workspace/projects/cJson/test.c -o CMakeFiles/cJson_test.dir/test.c.s

CMakeFiles/cJson_test.dir/test.c.o.requires:

.PHONY : CMakeFiles/cJson_test.dir/test.c.o.requires

CMakeFiles/cJson_test.dir/test.c.o.provides: CMakeFiles/cJson_test.dir/test.c.o.requires
	$(MAKE) -f CMakeFiles/cJson_test.dir/build.make CMakeFiles/cJson_test.dir/test.c.o.provides.build
.PHONY : CMakeFiles/cJson_test.dir/test.c.o.provides

CMakeFiles/cJson_test.dir/test.c.o.provides.build: CMakeFiles/cJson_test.dir/test.c.o


# Object files for target cJson_test
cJson_test_OBJECTS = \
"CMakeFiles/cJson_test.dir/test.c.o"

# External object files for target cJson_test
cJson_test_EXTERNAL_OBJECTS =

cJson_test: CMakeFiles/cJson_test.dir/test.c.o
cJson_test: CMakeFiles/cJson_test.dir/build.make
cJson_test: libcJson.a
cJson_test: CMakeFiles/cJson_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/heyjude/workspace/projects/cJson/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable cJson_test"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/cJson_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/cJson_test.dir/build: cJson_test

.PHONY : CMakeFiles/cJson_test.dir/build

CMakeFiles/cJson_test.dir/requires: CMakeFiles/cJson_test.dir/test.c.o.requires

.PHONY : CMakeFiles/cJson_test.dir/requires

CMakeFiles/cJson_test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/cJson_test.dir/cmake_clean.cmake
.PHONY : CMakeFiles/cJson_test.dir/clean

CMakeFiles/cJson_test.dir/depend:
	cd /home/heyjude/workspace/projects/cJson/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/heyjude/workspace/projects/cJson /home/heyjude/workspace/projects/cJson /home/heyjude/workspace/projects/cJson/cmake-build-debug /home/heyjude/workspace/projects/cJson/cmake-build-debug /home/heyjude/workspace/projects/cJson/cmake-build-debug/CMakeFiles/cJson_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/cJson_test.dir/depend

