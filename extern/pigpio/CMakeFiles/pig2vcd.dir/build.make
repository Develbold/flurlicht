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
CMAKE_SOURCE_DIR = /home/stephan/workspace/misc_cpp/flurlicht

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/stephan/workspace/misc_cpp/flurlicht

# Include any dependencies generated for this target.
include extern/pigpio/CMakeFiles/pig2vcd.dir/depend.make

# Include the progress variables for this target.
include extern/pigpio/CMakeFiles/pig2vcd.dir/progress.make

# Include the compile flags for this target's objects.
include extern/pigpio/CMakeFiles/pig2vcd.dir/flags.make

extern/pigpio/CMakeFiles/pig2vcd.dir/pig2vcd.c.o: extern/pigpio/CMakeFiles/pig2vcd.dir/flags.make
extern/pigpio/CMakeFiles/pig2vcd.dir/pig2vcd.c.o: extern/pigpio/pig2vcd.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/stephan/workspace/misc_cpp/flurlicht/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object extern/pigpio/CMakeFiles/pig2vcd.dir/pig2vcd.c.o"
	cd /home/stephan/workspace/misc_cpp/flurlicht/extern/pigpio && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/pig2vcd.dir/pig2vcd.c.o   -c /home/stephan/workspace/misc_cpp/flurlicht/extern/pigpio/pig2vcd.c

extern/pigpio/CMakeFiles/pig2vcd.dir/pig2vcd.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/pig2vcd.dir/pig2vcd.c.i"
	cd /home/stephan/workspace/misc_cpp/flurlicht/extern/pigpio && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/stephan/workspace/misc_cpp/flurlicht/extern/pigpio/pig2vcd.c > CMakeFiles/pig2vcd.dir/pig2vcd.c.i

extern/pigpio/CMakeFiles/pig2vcd.dir/pig2vcd.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/pig2vcd.dir/pig2vcd.c.s"
	cd /home/stephan/workspace/misc_cpp/flurlicht/extern/pigpio && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/stephan/workspace/misc_cpp/flurlicht/extern/pigpio/pig2vcd.c -o CMakeFiles/pig2vcd.dir/pig2vcd.c.s

extern/pigpio/CMakeFiles/pig2vcd.dir/command.c.o: extern/pigpio/CMakeFiles/pig2vcd.dir/flags.make
extern/pigpio/CMakeFiles/pig2vcd.dir/command.c.o: extern/pigpio/command.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/stephan/workspace/misc_cpp/flurlicht/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object extern/pigpio/CMakeFiles/pig2vcd.dir/command.c.o"
	cd /home/stephan/workspace/misc_cpp/flurlicht/extern/pigpio && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/pig2vcd.dir/command.c.o   -c /home/stephan/workspace/misc_cpp/flurlicht/extern/pigpio/command.c

extern/pigpio/CMakeFiles/pig2vcd.dir/command.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/pig2vcd.dir/command.c.i"
	cd /home/stephan/workspace/misc_cpp/flurlicht/extern/pigpio && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/stephan/workspace/misc_cpp/flurlicht/extern/pigpio/command.c > CMakeFiles/pig2vcd.dir/command.c.i

extern/pigpio/CMakeFiles/pig2vcd.dir/command.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/pig2vcd.dir/command.c.s"
	cd /home/stephan/workspace/misc_cpp/flurlicht/extern/pigpio && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/stephan/workspace/misc_cpp/flurlicht/extern/pigpio/command.c -o CMakeFiles/pig2vcd.dir/command.c.s

# Object files for target pig2vcd
pig2vcd_OBJECTS = \
"CMakeFiles/pig2vcd.dir/pig2vcd.c.o" \
"CMakeFiles/pig2vcd.dir/command.c.o"

# External object files for target pig2vcd
pig2vcd_EXTERNAL_OBJECTS =

extern/pigpio/pig2vcd: extern/pigpio/CMakeFiles/pig2vcd.dir/pig2vcd.c.o
extern/pigpio/pig2vcd: extern/pigpio/CMakeFiles/pig2vcd.dir/command.c.o
extern/pigpio/pig2vcd: extern/pigpio/CMakeFiles/pig2vcd.dir/build.make
extern/pigpio/pig2vcd: extern/pigpio/CMakeFiles/pig2vcd.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/stephan/workspace/misc_cpp/flurlicht/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable pig2vcd"
	cd /home/stephan/workspace/misc_cpp/flurlicht/extern/pigpio && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/pig2vcd.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
extern/pigpio/CMakeFiles/pig2vcd.dir/build: extern/pigpio/pig2vcd

.PHONY : extern/pigpio/CMakeFiles/pig2vcd.dir/build

extern/pigpio/CMakeFiles/pig2vcd.dir/clean:
	cd /home/stephan/workspace/misc_cpp/flurlicht/extern/pigpio && $(CMAKE_COMMAND) -P CMakeFiles/pig2vcd.dir/cmake_clean.cmake
.PHONY : extern/pigpio/CMakeFiles/pig2vcd.dir/clean

extern/pigpio/CMakeFiles/pig2vcd.dir/depend:
	cd /home/stephan/workspace/misc_cpp/flurlicht && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/stephan/workspace/misc_cpp/flurlicht /home/stephan/workspace/misc_cpp/flurlicht/extern/pigpio /home/stephan/workspace/misc_cpp/flurlicht /home/stephan/workspace/misc_cpp/flurlicht/extern/pigpio /home/stephan/workspace/misc_cpp/flurlicht/extern/pigpio/CMakeFiles/pig2vcd.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : extern/pigpio/CMakeFiles/pig2vcd.dir/depend
