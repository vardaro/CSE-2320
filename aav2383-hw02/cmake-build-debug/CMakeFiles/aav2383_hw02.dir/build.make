# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

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
CMAKE_COMMAND = /snap/clion/73/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/73/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/anthony/Desktop/School/Summer2019/CSE2320/Homework/aav2383-hw02

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/anthony/Desktop/School/Summer2019/CSE2320/Homework/aav2383-hw02/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/aav2383_hw02.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/aav2383_hw02.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/aav2383_hw02.dir/flags.make

CMakeFiles/aav2383_hw02.dir/hw02.c.o: CMakeFiles/aav2383_hw02.dir/flags.make
CMakeFiles/aav2383_hw02.dir/hw02.c.o: ../hw02.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/anthony/Desktop/School/Summer2019/CSE2320/Homework/aav2383-hw02/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/aav2383_hw02.dir/hw02.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/aav2383_hw02.dir/hw02.c.o   -c /home/anthony/Desktop/School/Summer2019/CSE2320/Homework/aav2383-hw02/hw02.c

CMakeFiles/aav2383_hw02.dir/hw02.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/aav2383_hw02.dir/hw02.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/anthony/Desktop/School/Summer2019/CSE2320/Homework/aav2383-hw02/hw02.c > CMakeFiles/aav2383_hw02.dir/hw02.c.i

CMakeFiles/aav2383_hw02.dir/hw02.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/aav2383_hw02.dir/hw02.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/anthony/Desktop/School/Summer2019/CSE2320/Homework/aav2383-hw02/hw02.c -o CMakeFiles/aav2383_hw02.dir/hw02.c.s

# Object files for target aav2383_hw02
aav2383_hw02_OBJECTS = \
"CMakeFiles/aav2383_hw02.dir/hw02.c.o"

# External object files for target aav2383_hw02
aav2383_hw02_EXTERNAL_OBJECTS = \
"/home/anthony/Desktop/School/Summer2019/CSE2320/Homework/aav2383-hw02/hw02-lib.o"

aav2383_hw02: CMakeFiles/aav2383_hw02.dir/hw02.c.o
aav2383_hw02: ../hw02-lib.o
aav2383_hw02: CMakeFiles/aav2383_hw02.dir/build.make
aav2383_hw02: CMakeFiles/aav2383_hw02.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/anthony/Desktop/School/Summer2019/CSE2320/Homework/aav2383-hw02/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable aav2383_hw02"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/aav2383_hw02.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/aav2383_hw02.dir/build: aav2383_hw02

.PHONY : CMakeFiles/aav2383_hw02.dir/build

CMakeFiles/aav2383_hw02.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/aav2383_hw02.dir/cmake_clean.cmake
.PHONY : CMakeFiles/aav2383_hw02.dir/clean

CMakeFiles/aav2383_hw02.dir/depend:
	cd /home/anthony/Desktop/School/Summer2019/CSE2320/Homework/aav2383-hw02/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/anthony/Desktop/School/Summer2019/CSE2320/Homework/aav2383-hw02 /home/anthony/Desktop/School/Summer2019/CSE2320/Homework/aav2383-hw02 /home/anthony/Desktop/School/Summer2019/CSE2320/Homework/aav2383-hw02/cmake-build-debug /home/anthony/Desktop/School/Summer2019/CSE2320/Homework/aav2383-hw02/cmake-build-debug /home/anthony/Desktop/School/Summer2019/CSE2320/Homework/aav2383-hw02/cmake-build-debug/CMakeFiles/aav2383_hw02.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/aav2383_hw02.dir/depend

