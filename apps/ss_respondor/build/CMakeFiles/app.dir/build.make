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
CMAKE_SOURCE_DIR = /home/ggory15/git/DWM1001_Firmware_Localization/apps/ss_respondor

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ggory15/git/DWM1001_Firmware_Localization/apps/ss_respondor/build

# Include any dependencies generated for this target.
include CMakeFiles/app.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/app.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/app.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/app.dir/flags.make

CMakeFiles/app.dir/main.c.obj: CMakeFiles/app.dir/flags.make
CMakeFiles/app.dir/main.c.obj: ../main.c
CMakeFiles/app.dir/main.c.obj: CMakeFiles/app.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ggory15/git/DWM1001_Firmware_Localization/apps/ss_respondor/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/app.dir/main.c.obj"
	ccache /home/ggory15/zephyr-sdk-0.12.4/arm-zephyr-eabi/bin/arm-zephyr-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/app.dir/main.c.obj -MF CMakeFiles/app.dir/main.c.obj.d -o CMakeFiles/app.dir/main.c.obj -c /home/ggory15/git/DWM1001_Firmware_Localization/apps/ss_respondor/main.c

CMakeFiles/app.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/app.dir/main.c.i"
	/home/ggory15/zephyr-sdk-0.12.4/arm-zephyr-eabi/bin/arm-zephyr-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ggory15/git/DWM1001_Firmware_Localization/apps/ss_respondor/main.c > CMakeFiles/app.dir/main.c.i

CMakeFiles/app.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/app.dir/main.c.s"
	/home/ggory15/zephyr-sdk-0.12.4/arm-zephyr-eabi/bin/arm-zephyr-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ggory15/git/DWM1001_Firmware_Localization/apps/ss_respondor/main.c -o CMakeFiles/app.dir/main.c.s

CMakeFiles/app.dir/home/ggory15/git/DWM1001_Firmware_Localization/decadriver/deca_device.c.obj: CMakeFiles/app.dir/flags.make
CMakeFiles/app.dir/home/ggory15/git/DWM1001_Firmware_Localization/decadriver/deca_device.c.obj: /home/ggory15/git/DWM1001_Firmware_Localization/decadriver/deca_device.c
CMakeFiles/app.dir/home/ggory15/git/DWM1001_Firmware_Localization/decadriver/deca_device.c.obj: CMakeFiles/app.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ggory15/git/DWM1001_Firmware_Localization/apps/ss_respondor/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/app.dir/home/ggory15/git/DWM1001_Firmware_Localization/decadriver/deca_device.c.obj"
	ccache /home/ggory15/zephyr-sdk-0.12.4/arm-zephyr-eabi/bin/arm-zephyr-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/app.dir/home/ggory15/git/DWM1001_Firmware_Localization/decadriver/deca_device.c.obj -MF CMakeFiles/app.dir/home/ggory15/git/DWM1001_Firmware_Localization/decadriver/deca_device.c.obj.d -o CMakeFiles/app.dir/home/ggory15/git/DWM1001_Firmware_Localization/decadriver/deca_device.c.obj -c /home/ggory15/git/DWM1001_Firmware_Localization/decadriver/deca_device.c

CMakeFiles/app.dir/home/ggory15/git/DWM1001_Firmware_Localization/decadriver/deca_device.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/app.dir/home/ggory15/git/DWM1001_Firmware_Localization/decadriver/deca_device.c.i"
	/home/ggory15/zephyr-sdk-0.12.4/arm-zephyr-eabi/bin/arm-zephyr-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ggory15/git/DWM1001_Firmware_Localization/decadriver/deca_device.c > CMakeFiles/app.dir/home/ggory15/git/DWM1001_Firmware_Localization/decadriver/deca_device.c.i

CMakeFiles/app.dir/home/ggory15/git/DWM1001_Firmware_Localization/decadriver/deca_device.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/app.dir/home/ggory15/git/DWM1001_Firmware_Localization/decadriver/deca_device.c.s"
	/home/ggory15/zephyr-sdk-0.12.4/arm-zephyr-eabi/bin/arm-zephyr-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ggory15/git/DWM1001_Firmware_Localization/decadriver/deca_device.c -o CMakeFiles/app.dir/home/ggory15/git/DWM1001_Firmware_Localization/decadriver/deca_device.c.s

CMakeFiles/app.dir/home/ggory15/git/DWM1001_Firmware_Localization/decadriver/deca_params_init.c.obj: CMakeFiles/app.dir/flags.make
CMakeFiles/app.dir/home/ggory15/git/DWM1001_Firmware_Localization/decadriver/deca_params_init.c.obj: /home/ggory15/git/DWM1001_Firmware_Localization/decadriver/deca_params_init.c
CMakeFiles/app.dir/home/ggory15/git/DWM1001_Firmware_Localization/decadriver/deca_params_init.c.obj: CMakeFiles/app.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ggory15/git/DWM1001_Firmware_Localization/apps/ss_respondor/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/app.dir/home/ggory15/git/DWM1001_Firmware_Localization/decadriver/deca_params_init.c.obj"
	ccache /home/ggory15/zephyr-sdk-0.12.4/arm-zephyr-eabi/bin/arm-zephyr-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/app.dir/home/ggory15/git/DWM1001_Firmware_Localization/decadriver/deca_params_init.c.obj -MF CMakeFiles/app.dir/home/ggory15/git/DWM1001_Firmware_Localization/decadriver/deca_params_init.c.obj.d -o CMakeFiles/app.dir/home/ggory15/git/DWM1001_Firmware_Localization/decadriver/deca_params_init.c.obj -c /home/ggory15/git/DWM1001_Firmware_Localization/decadriver/deca_params_init.c

CMakeFiles/app.dir/home/ggory15/git/DWM1001_Firmware_Localization/decadriver/deca_params_init.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/app.dir/home/ggory15/git/DWM1001_Firmware_Localization/decadriver/deca_params_init.c.i"
	/home/ggory15/zephyr-sdk-0.12.4/arm-zephyr-eabi/bin/arm-zephyr-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ggory15/git/DWM1001_Firmware_Localization/decadriver/deca_params_init.c > CMakeFiles/app.dir/home/ggory15/git/DWM1001_Firmware_Localization/decadriver/deca_params_init.c.i

CMakeFiles/app.dir/home/ggory15/git/DWM1001_Firmware_Localization/decadriver/deca_params_init.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/app.dir/home/ggory15/git/DWM1001_Firmware_Localization/decadriver/deca_params_init.c.s"
	/home/ggory15/zephyr-sdk-0.12.4/arm-zephyr-eabi/bin/arm-zephyr-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ggory15/git/DWM1001_Firmware_Localization/decadriver/deca_params_init.c -o CMakeFiles/app.dir/home/ggory15/git/DWM1001_Firmware_Localization/decadriver/deca_params_init.c.s

CMakeFiles/app.dir/home/ggory15/git/DWM1001_Firmware_Localization/platform/port.c.obj: CMakeFiles/app.dir/flags.make
CMakeFiles/app.dir/home/ggory15/git/DWM1001_Firmware_Localization/platform/port.c.obj: /home/ggory15/git/DWM1001_Firmware_Localization/platform/port.c
CMakeFiles/app.dir/home/ggory15/git/DWM1001_Firmware_Localization/platform/port.c.obj: CMakeFiles/app.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ggory15/git/DWM1001_Firmware_Localization/apps/ss_respondor/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/app.dir/home/ggory15/git/DWM1001_Firmware_Localization/platform/port.c.obj"
	ccache /home/ggory15/zephyr-sdk-0.12.4/arm-zephyr-eabi/bin/arm-zephyr-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/app.dir/home/ggory15/git/DWM1001_Firmware_Localization/platform/port.c.obj -MF CMakeFiles/app.dir/home/ggory15/git/DWM1001_Firmware_Localization/platform/port.c.obj.d -o CMakeFiles/app.dir/home/ggory15/git/DWM1001_Firmware_Localization/platform/port.c.obj -c /home/ggory15/git/DWM1001_Firmware_Localization/platform/port.c

CMakeFiles/app.dir/home/ggory15/git/DWM1001_Firmware_Localization/platform/port.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/app.dir/home/ggory15/git/DWM1001_Firmware_Localization/platform/port.c.i"
	/home/ggory15/zephyr-sdk-0.12.4/arm-zephyr-eabi/bin/arm-zephyr-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ggory15/git/DWM1001_Firmware_Localization/platform/port.c > CMakeFiles/app.dir/home/ggory15/git/DWM1001_Firmware_Localization/platform/port.c.i

CMakeFiles/app.dir/home/ggory15/git/DWM1001_Firmware_Localization/platform/port.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/app.dir/home/ggory15/git/DWM1001_Firmware_Localization/platform/port.c.s"
	/home/ggory15/zephyr-sdk-0.12.4/arm-zephyr-eabi/bin/arm-zephyr-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ggory15/git/DWM1001_Firmware_Localization/platform/port.c -o CMakeFiles/app.dir/home/ggory15/git/DWM1001_Firmware_Localization/platform/port.c.s

CMakeFiles/app.dir/home/ggory15/git/DWM1001_Firmware_Localization/platform/deca_mutex.c.obj: CMakeFiles/app.dir/flags.make
CMakeFiles/app.dir/home/ggory15/git/DWM1001_Firmware_Localization/platform/deca_mutex.c.obj: /home/ggory15/git/DWM1001_Firmware_Localization/platform/deca_mutex.c
CMakeFiles/app.dir/home/ggory15/git/DWM1001_Firmware_Localization/platform/deca_mutex.c.obj: CMakeFiles/app.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ggory15/git/DWM1001_Firmware_Localization/apps/ss_respondor/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/app.dir/home/ggory15/git/DWM1001_Firmware_Localization/platform/deca_mutex.c.obj"
	ccache /home/ggory15/zephyr-sdk-0.12.4/arm-zephyr-eabi/bin/arm-zephyr-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/app.dir/home/ggory15/git/DWM1001_Firmware_Localization/platform/deca_mutex.c.obj -MF CMakeFiles/app.dir/home/ggory15/git/DWM1001_Firmware_Localization/platform/deca_mutex.c.obj.d -o CMakeFiles/app.dir/home/ggory15/git/DWM1001_Firmware_Localization/platform/deca_mutex.c.obj -c /home/ggory15/git/DWM1001_Firmware_Localization/platform/deca_mutex.c

CMakeFiles/app.dir/home/ggory15/git/DWM1001_Firmware_Localization/platform/deca_mutex.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/app.dir/home/ggory15/git/DWM1001_Firmware_Localization/platform/deca_mutex.c.i"
	/home/ggory15/zephyr-sdk-0.12.4/arm-zephyr-eabi/bin/arm-zephyr-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ggory15/git/DWM1001_Firmware_Localization/platform/deca_mutex.c > CMakeFiles/app.dir/home/ggory15/git/DWM1001_Firmware_Localization/platform/deca_mutex.c.i

CMakeFiles/app.dir/home/ggory15/git/DWM1001_Firmware_Localization/platform/deca_mutex.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/app.dir/home/ggory15/git/DWM1001_Firmware_Localization/platform/deca_mutex.c.s"
	/home/ggory15/zephyr-sdk-0.12.4/arm-zephyr-eabi/bin/arm-zephyr-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ggory15/git/DWM1001_Firmware_Localization/platform/deca_mutex.c -o CMakeFiles/app.dir/home/ggory15/git/DWM1001_Firmware_Localization/platform/deca_mutex.c.s

CMakeFiles/app.dir/home/ggory15/git/DWM1001_Firmware_Localization/platform/deca_range_tables.c.obj: CMakeFiles/app.dir/flags.make
CMakeFiles/app.dir/home/ggory15/git/DWM1001_Firmware_Localization/platform/deca_range_tables.c.obj: /home/ggory15/git/DWM1001_Firmware_Localization/platform/deca_range_tables.c
CMakeFiles/app.dir/home/ggory15/git/DWM1001_Firmware_Localization/platform/deca_range_tables.c.obj: CMakeFiles/app.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ggory15/git/DWM1001_Firmware_Localization/apps/ss_respondor/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/app.dir/home/ggory15/git/DWM1001_Firmware_Localization/platform/deca_range_tables.c.obj"
	ccache /home/ggory15/zephyr-sdk-0.12.4/arm-zephyr-eabi/bin/arm-zephyr-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/app.dir/home/ggory15/git/DWM1001_Firmware_Localization/platform/deca_range_tables.c.obj -MF CMakeFiles/app.dir/home/ggory15/git/DWM1001_Firmware_Localization/platform/deca_range_tables.c.obj.d -o CMakeFiles/app.dir/home/ggory15/git/DWM1001_Firmware_Localization/platform/deca_range_tables.c.obj -c /home/ggory15/git/DWM1001_Firmware_Localization/platform/deca_range_tables.c

CMakeFiles/app.dir/home/ggory15/git/DWM1001_Firmware_Localization/platform/deca_range_tables.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/app.dir/home/ggory15/git/DWM1001_Firmware_Localization/platform/deca_range_tables.c.i"
	/home/ggory15/zephyr-sdk-0.12.4/arm-zephyr-eabi/bin/arm-zephyr-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ggory15/git/DWM1001_Firmware_Localization/platform/deca_range_tables.c > CMakeFiles/app.dir/home/ggory15/git/DWM1001_Firmware_Localization/platform/deca_range_tables.c.i

CMakeFiles/app.dir/home/ggory15/git/DWM1001_Firmware_Localization/platform/deca_range_tables.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/app.dir/home/ggory15/git/DWM1001_Firmware_Localization/platform/deca_range_tables.c.s"
	/home/ggory15/zephyr-sdk-0.12.4/arm-zephyr-eabi/bin/arm-zephyr-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ggory15/git/DWM1001_Firmware_Localization/platform/deca_range_tables.c -o CMakeFiles/app.dir/home/ggory15/git/DWM1001_Firmware_Localization/platform/deca_range_tables.c.s

CMakeFiles/app.dir/home/ggory15/git/DWM1001_Firmware_Localization/platform/deca_sleep.c.obj: CMakeFiles/app.dir/flags.make
CMakeFiles/app.dir/home/ggory15/git/DWM1001_Firmware_Localization/platform/deca_sleep.c.obj: /home/ggory15/git/DWM1001_Firmware_Localization/platform/deca_sleep.c
CMakeFiles/app.dir/home/ggory15/git/DWM1001_Firmware_Localization/platform/deca_sleep.c.obj: CMakeFiles/app.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ggory15/git/DWM1001_Firmware_Localization/apps/ss_respondor/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object CMakeFiles/app.dir/home/ggory15/git/DWM1001_Firmware_Localization/platform/deca_sleep.c.obj"
	ccache /home/ggory15/zephyr-sdk-0.12.4/arm-zephyr-eabi/bin/arm-zephyr-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/app.dir/home/ggory15/git/DWM1001_Firmware_Localization/platform/deca_sleep.c.obj -MF CMakeFiles/app.dir/home/ggory15/git/DWM1001_Firmware_Localization/platform/deca_sleep.c.obj.d -o CMakeFiles/app.dir/home/ggory15/git/DWM1001_Firmware_Localization/platform/deca_sleep.c.obj -c /home/ggory15/git/DWM1001_Firmware_Localization/platform/deca_sleep.c

CMakeFiles/app.dir/home/ggory15/git/DWM1001_Firmware_Localization/platform/deca_sleep.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/app.dir/home/ggory15/git/DWM1001_Firmware_Localization/platform/deca_sleep.c.i"
	/home/ggory15/zephyr-sdk-0.12.4/arm-zephyr-eabi/bin/arm-zephyr-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ggory15/git/DWM1001_Firmware_Localization/platform/deca_sleep.c > CMakeFiles/app.dir/home/ggory15/git/DWM1001_Firmware_Localization/platform/deca_sleep.c.i

CMakeFiles/app.dir/home/ggory15/git/DWM1001_Firmware_Localization/platform/deca_sleep.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/app.dir/home/ggory15/git/DWM1001_Firmware_Localization/platform/deca_sleep.c.s"
	/home/ggory15/zephyr-sdk-0.12.4/arm-zephyr-eabi/bin/arm-zephyr-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ggory15/git/DWM1001_Firmware_Localization/platform/deca_sleep.c -o CMakeFiles/app.dir/home/ggory15/git/DWM1001_Firmware_Localization/platform/deca_sleep.c.s

CMakeFiles/app.dir/home/ggory15/git/DWM1001_Firmware_Localization/platform/deca_spi.c.obj: CMakeFiles/app.dir/flags.make
CMakeFiles/app.dir/home/ggory15/git/DWM1001_Firmware_Localization/platform/deca_spi.c.obj: /home/ggory15/git/DWM1001_Firmware_Localization/platform/deca_spi.c
CMakeFiles/app.dir/home/ggory15/git/DWM1001_Firmware_Localization/platform/deca_spi.c.obj: CMakeFiles/app.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ggory15/git/DWM1001_Firmware_Localization/apps/ss_respondor/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building C object CMakeFiles/app.dir/home/ggory15/git/DWM1001_Firmware_Localization/platform/deca_spi.c.obj"
	ccache /home/ggory15/zephyr-sdk-0.12.4/arm-zephyr-eabi/bin/arm-zephyr-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/app.dir/home/ggory15/git/DWM1001_Firmware_Localization/platform/deca_spi.c.obj -MF CMakeFiles/app.dir/home/ggory15/git/DWM1001_Firmware_Localization/platform/deca_spi.c.obj.d -o CMakeFiles/app.dir/home/ggory15/git/DWM1001_Firmware_Localization/platform/deca_spi.c.obj -c /home/ggory15/git/DWM1001_Firmware_Localization/platform/deca_spi.c

CMakeFiles/app.dir/home/ggory15/git/DWM1001_Firmware_Localization/platform/deca_spi.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/app.dir/home/ggory15/git/DWM1001_Firmware_Localization/platform/deca_spi.c.i"
	/home/ggory15/zephyr-sdk-0.12.4/arm-zephyr-eabi/bin/arm-zephyr-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ggory15/git/DWM1001_Firmware_Localization/platform/deca_spi.c > CMakeFiles/app.dir/home/ggory15/git/DWM1001_Firmware_Localization/platform/deca_spi.c.i

CMakeFiles/app.dir/home/ggory15/git/DWM1001_Firmware_Localization/platform/deca_spi.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/app.dir/home/ggory15/git/DWM1001_Firmware_Localization/platform/deca_spi.c.s"
	/home/ggory15/zephyr-sdk-0.12.4/arm-zephyr-eabi/bin/arm-zephyr-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ggory15/git/DWM1001_Firmware_Localization/platform/deca_spi.c -o CMakeFiles/app.dir/home/ggory15/git/DWM1001_Firmware_Localization/platform/deca_spi.c.s

# Object files for target app
app_OBJECTS = \
"CMakeFiles/app.dir/main.c.obj" \
"CMakeFiles/app.dir/home/ggory15/git/DWM1001_Firmware_Localization/decadriver/deca_device.c.obj" \
"CMakeFiles/app.dir/home/ggory15/git/DWM1001_Firmware_Localization/decadriver/deca_params_init.c.obj" \
"CMakeFiles/app.dir/home/ggory15/git/DWM1001_Firmware_Localization/platform/port.c.obj" \
"CMakeFiles/app.dir/home/ggory15/git/DWM1001_Firmware_Localization/platform/deca_mutex.c.obj" \
"CMakeFiles/app.dir/home/ggory15/git/DWM1001_Firmware_Localization/platform/deca_range_tables.c.obj" \
"CMakeFiles/app.dir/home/ggory15/git/DWM1001_Firmware_Localization/platform/deca_sleep.c.obj" \
"CMakeFiles/app.dir/home/ggory15/git/DWM1001_Firmware_Localization/platform/deca_spi.c.obj"

# External object files for target app
app_EXTERNAL_OBJECTS =

app/libapp.a: CMakeFiles/app.dir/main.c.obj
app/libapp.a: CMakeFiles/app.dir/home/ggory15/git/DWM1001_Firmware_Localization/decadriver/deca_device.c.obj
app/libapp.a: CMakeFiles/app.dir/home/ggory15/git/DWM1001_Firmware_Localization/decadriver/deca_params_init.c.obj
app/libapp.a: CMakeFiles/app.dir/home/ggory15/git/DWM1001_Firmware_Localization/platform/port.c.obj
app/libapp.a: CMakeFiles/app.dir/home/ggory15/git/DWM1001_Firmware_Localization/platform/deca_mutex.c.obj
app/libapp.a: CMakeFiles/app.dir/home/ggory15/git/DWM1001_Firmware_Localization/platform/deca_range_tables.c.obj
app/libapp.a: CMakeFiles/app.dir/home/ggory15/git/DWM1001_Firmware_Localization/platform/deca_sleep.c.obj
app/libapp.a: CMakeFiles/app.dir/home/ggory15/git/DWM1001_Firmware_Localization/platform/deca_spi.c.obj
app/libapp.a: CMakeFiles/app.dir/build.make
app/libapp.a: CMakeFiles/app.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ggory15/git/DWM1001_Firmware_Localization/apps/ss_respondor/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Linking C static library app/libapp.a"
	$(CMAKE_COMMAND) -P CMakeFiles/app.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/app.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/app.dir/build: app/libapp.a
.PHONY : CMakeFiles/app.dir/build

CMakeFiles/app.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/app.dir/cmake_clean.cmake
.PHONY : CMakeFiles/app.dir/clean

CMakeFiles/app.dir/depend:
	cd /home/ggory15/git/DWM1001_Firmware_Localization/apps/ss_respondor/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ggory15/git/DWM1001_Firmware_Localization/apps/ss_respondor /home/ggory15/git/DWM1001_Firmware_Localization/apps/ss_respondor /home/ggory15/git/DWM1001_Firmware_Localization/apps/ss_respondor/build /home/ggory15/git/DWM1001_Firmware_Localization/apps/ss_respondor/build /home/ggory15/git/DWM1001_Firmware_Localization/apps/ss_respondor/build/CMakeFiles/app.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/app.dir/depend

