# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

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
CMAKE_SOURCE_DIR = /home/ggory15/git/DWM1001_Firmware_Localization/apps/ss_initiator

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ggory15/git/DWM1001_Firmware_Localization/apps/ss_initiator/build

# Utility rule file for usage.

# Include any custom commands dependencies for this target.
include zephyr/cmake/usage/CMakeFiles/usage.dir/compiler_depend.make

# Include the progress variables for this target.
include zephyr/cmake/usage/CMakeFiles/usage.dir/progress.make

zephyr/cmake/usage/CMakeFiles/usage:
	cd /home/ggory15/git/DWM1001_Firmware_Localization/apps/ss_initiator/build/zephyr/cmake/usage && /usr/bin/cmake -DZEPHYR_BASE=/home/ggory15/zephyrproject/zephyr -DCMAKE_MAKE_PROGRAM=/usr/bin/make -P /home/ggory15/zephyrproject/zephyr/cmake/usage/usage.cmake

usage: zephyr/cmake/usage/CMakeFiles/usage
usage: zephyr/cmake/usage/CMakeFiles/usage.dir/build.make
.PHONY : usage

# Rule to build all files generated by this target.
zephyr/cmake/usage/CMakeFiles/usage.dir/build: usage
.PHONY : zephyr/cmake/usage/CMakeFiles/usage.dir/build

zephyr/cmake/usage/CMakeFiles/usage.dir/clean:
	cd /home/ggory15/git/DWM1001_Firmware_Localization/apps/ss_initiator/build/zephyr/cmake/usage && $(CMAKE_COMMAND) -P CMakeFiles/usage.dir/cmake_clean.cmake
.PHONY : zephyr/cmake/usage/CMakeFiles/usage.dir/clean

zephyr/cmake/usage/CMakeFiles/usage.dir/depend:
	cd /home/ggory15/git/DWM1001_Firmware_Localization/apps/ss_initiator/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ggory15/git/DWM1001_Firmware_Localization/apps/ss_initiator /home/ggory15/zephyrproject/zephyr/cmake/usage /home/ggory15/git/DWM1001_Firmware_Localization/apps/ss_initiator/build /home/ggory15/git/DWM1001_Firmware_Localization/apps/ss_initiator/build/zephyr/cmake/usage /home/ggory15/git/DWM1001_Firmware_Localization/apps/ss_initiator/build/zephyr/cmake/usage/CMakeFiles/usage.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : zephyr/cmake/usage/CMakeFiles/usage.dir/depend

