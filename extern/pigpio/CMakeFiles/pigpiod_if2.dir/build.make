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
include extern/pigpio/CMakeFiles/pigpiod_if2.dir/depend.make

# Include the progress variables for this target.
include extern/pigpio/CMakeFiles/pigpiod_if2.dir/progress.make

# Include the compile flags for this target's objects.
include extern/pigpio/CMakeFiles/pigpiod_if2.dir/flags.make

extern/pigpio/CMakeFiles/pigpiod_if2.dir/pigpiod_if2.c.o: extern/pigpio/CMakeFiles/pigpiod_if2.dir/flags.make
extern/pigpio/CMakeFiles/pigpiod_if2.dir/pigpiod_if2.c.o: extern/pigpio/pigpiod_if2.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/stephan/workspace/misc_cpp/flurlicht/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object extern/pigpio/CMakeFiles/pigpiod_if2.dir/pigpiod_if2.c.o"
	cd /home/stephan/workspace/misc_cpp/flurlicht/extern/pigpio && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/pigpiod_if2.dir/pigpiod_if2.c.o   -c /home/stephan/workspace/misc_cpp/flurlicht/extern/pigpio/pigpiod_if2.c

extern/pigpio/CMakeFiles/pigpiod_if2.dir/pigpiod_if2.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/pigpiod_if2.dir/pigpiod_if2.c.i"
	cd /home/stephan/workspace/misc_cpp/flurlicht/extern/pigpio && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/stephan/workspace/misc_cpp/flurlicht/extern/pigpio/pigpiod_if2.c > CMakeFiles/pigpiod_if2.dir/pigpiod_if2.c.i

extern/pigpio/CMakeFiles/pigpiod_if2.dir/pigpiod_if2.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/pigpiod_if2.dir/pigpiod_if2.c.s"
	cd /home/stephan/workspace/misc_cpp/flurlicht/extern/pigpio && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/stephan/workspace/misc_cpp/flurlicht/extern/pigpio/pigpiod_if2.c -o CMakeFiles/pigpiod_if2.dir/pigpiod_if2.c.s

extern/pigpio/CMakeFiles/pigpiod_if2.dir/command.c.o: extern/pigpio/CMakeFiles/pigpiod_if2.dir/flags.make
extern/pigpio/CMakeFiles/pigpiod_if2.dir/command.c.o: extern/pigpio/command.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/stephan/workspace/misc_cpp/flurlicht/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object extern/pigpio/CMakeFiles/pigpiod_if2.dir/command.c.o"
	cd /home/stephan/workspace/misc_cpp/flurlicht/extern/pigpio && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/pigpiod_if2.dir/command.c.o   -c /home/stephan/workspace/misc_cpp/flurlicht/extern/pigpio/command.c

extern/pigpio/CMakeFiles/pigpiod_if2.dir/command.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/pigpiod_if2.dir/command.c.i"
	cd /home/stephan/workspace/misc_cpp/flurlicht/extern/pigpio && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/stephan/workspace/misc_cpp/flurlicht/extern/pigpio/command.c > CMakeFiles/pigpiod_if2.dir/command.c.i

extern/pigpio/CMakeFiles/pigpiod_if2.dir/command.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/pigpiod_if2.dir/command.c.s"
	cd /home/stephan/workspace/misc_cpp/flurlicht/extern/pigpio && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/stephan/workspace/misc_cpp/flurlicht/extern/pigpio/command.c -o CMakeFiles/pigpiod_if2.dir/command.c.s

# Object files for target pigpiod_if2
pigpiod_if2_OBJECTS = \
"CMakeFiles/pigpiod_if2.dir/pigpiod_if2.c.o" \
"CMakeFiles/pigpiod_if2.dir/command.c.o"

# External object files for target pigpiod_if2
pigpiod_if2_EXTERNAL_OBJECTS =

extern/pigpio/libpigpiod_if2.a: extern/pigpio/CMakeFiles/pigpiod_if2.dir/pigpiod_if2.c.o
extern/pigpio/libpigpiod_if2.a: extern/pigpio/CMakeFiles/pigpiod_if2.dir/command.c.o
extern/pigpio/libpigpiod_if2.a: extern/pigpio/CMakeFiles/pigpiod_if2.dir/build.make
extern/pigpio/libpigpiod_if2.a: extern/pigpio/CMakeFiles/pigpiod_if2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/stephan/workspace/misc_cpp/flurlicht/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C static library libpigpiod_if2.a"
	cd /home/stephan/workspace/misc_cpp/flurlicht/extern/pigpio && $(CMAKE_COMMAND) -P CMakeFiles/pigpiod_if2.dir/cmake_clean_target.cmake
	cd /home/stephan/workspace/misc_cpp/flurlicht/extern/pigpio && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/pigpiod_if2.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
extern/pigpio/CMakeFiles/pigpiod_if2.dir/build: extern/pigpio/libpigpiod_if2.a

.PHONY : extern/pigpio/CMakeFiles/pigpiod_if2.dir/build

extern/pigpio/CMakeFiles/pigpiod_if2.dir/clean:
	cd /home/stephan/workspace/misc_cpp/flurlicht/extern/pigpio && $(CMAKE_COMMAND) -P CMakeFiles/pigpiod_if2.dir/cmake_clean.cmake
.PHONY : extern/pigpio/CMakeFiles/pigpiod_if2.dir/clean

extern/pigpio/CMakeFiles/pigpiod_if2.dir/depend:
	cd /home/stephan/workspace/misc_cpp/flurlicht && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/stephan/workspace/misc_cpp/flurlicht /home/stephan/workspace/misc_cpp/flurlicht/extern/pigpio /home/stephan/workspace/misc_cpp/flurlicht /home/stephan/workspace/misc_cpp/flurlicht/extern/pigpio /home/stephan/workspace/misc_cpp/flurlicht/extern/pigpio/CMakeFiles/pigpiod_if2.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : extern/pigpio/CMakeFiles/pigpiod_if2.dir/depend

