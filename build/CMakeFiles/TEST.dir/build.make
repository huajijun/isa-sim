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
CMAKE_SOURCE_DIR = /work/isa-sim

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /work/isa-sim/build

# Include any dependencies generated for this target.
include CMakeFiles/TEST.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/TEST.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/TEST.dir/flags.make

CMakeFiles/TEST.dir/device.cc.o: CMakeFiles/TEST.dir/flags.make
CMakeFiles/TEST.dir/device.cc.o: ../device.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/work/isa-sim/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/TEST.dir/device.cc.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/TEST.dir/device.cc.o -c /work/isa-sim/device.cc

CMakeFiles/TEST.dir/device.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TEST.dir/device.cc.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /work/isa-sim/device.cc > CMakeFiles/TEST.dir/device.cc.i

CMakeFiles/TEST.dir/device.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TEST.dir/device.cc.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /work/isa-sim/device.cc -o CMakeFiles/TEST.dir/device.cc.s

CMakeFiles/TEST.dir/htif.cc.o: CMakeFiles/TEST.dir/flags.make
CMakeFiles/TEST.dir/htif.cc.o: ../htif.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/work/isa-sim/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/TEST.dir/htif.cc.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/TEST.dir/htif.cc.o -c /work/isa-sim/htif.cc

CMakeFiles/TEST.dir/htif.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TEST.dir/htif.cc.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /work/isa-sim/htif.cc > CMakeFiles/TEST.dir/htif.cc.i

CMakeFiles/TEST.dir/htif.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TEST.dir/htif.cc.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /work/isa-sim/htif.cc -o CMakeFiles/TEST.dir/htif.cc.s

CMakeFiles/TEST.dir/memif.cc.o: CMakeFiles/TEST.dir/flags.make
CMakeFiles/TEST.dir/memif.cc.o: ../memif.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/work/isa-sim/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/TEST.dir/memif.cc.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/TEST.dir/memif.cc.o -c /work/isa-sim/memif.cc

CMakeFiles/TEST.dir/memif.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TEST.dir/memif.cc.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /work/isa-sim/memif.cc > CMakeFiles/TEST.dir/memif.cc.i

CMakeFiles/TEST.dir/memif.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TEST.dir/memif.cc.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /work/isa-sim/memif.cc -o CMakeFiles/TEST.dir/memif.cc.s

CMakeFiles/TEST.dir/option_parser.cc.o: CMakeFiles/TEST.dir/flags.make
CMakeFiles/TEST.dir/option_parser.cc.o: ../option_parser.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/work/isa-sim/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/TEST.dir/option_parser.cc.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/TEST.dir/option_parser.cc.o -c /work/isa-sim/option_parser.cc

CMakeFiles/TEST.dir/option_parser.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TEST.dir/option_parser.cc.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /work/isa-sim/option_parser.cc > CMakeFiles/TEST.dir/option_parser.cc.i

CMakeFiles/TEST.dir/option_parser.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TEST.dir/option_parser.cc.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /work/isa-sim/option_parser.cc -o CMakeFiles/TEST.dir/option_parser.cc.s

CMakeFiles/TEST.dir/sim.cc.o: CMakeFiles/TEST.dir/flags.make
CMakeFiles/TEST.dir/sim.cc.o: ../sim.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/work/isa-sim/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/TEST.dir/sim.cc.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/TEST.dir/sim.cc.o -c /work/isa-sim/sim.cc

CMakeFiles/TEST.dir/sim.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TEST.dir/sim.cc.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /work/isa-sim/sim.cc > CMakeFiles/TEST.dir/sim.cc.i

CMakeFiles/TEST.dir/sim.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TEST.dir/sim.cc.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /work/isa-sim/sim.cc -o CMakeFiles/TEST.dir/sim.cc.s

CMakeFiles/TEST.dir/spike.cc.o: CMakeFiles/TEST.dir/flags.make
CMakeFiles/TEST.dir/spike.cc.o: ../spike.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/work/isa-sim/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/TEST.dir/spike.cc.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/TEST.dir/spike.cc.o -c /work/isa-sim/spike.cc

CMakeFiles/TEST.dir/spike.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TEST.dir/spike.cc.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /work/isa-sim/spike.cc > CMakeFiles/TEST.dir/spike.cc.i

CMakeFiles/TEST.dir/spike.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TEST.dir/spike.cc.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /work/isa-sim/spike.cc -o CMakeFiles/TEST.dir/spike.cc.s

# Object files for target TEST
TEST_OBJECTS = \
"CMakeFiles/TEST.dir/device.cc.o" \
"CMakeFiles/TEST.dir/htif.cc.o" \
"CMakeFiles/TEST.dir/memif.cc.o" \
"CMakeFiles/TEST.dir/option_parser.cc.o" \
"CMakeFiles/TEST.dir/sim.cc.o" \
"CMakeFiles/TEST.dir/spike.cc.o"

# External object files for target TEST
TEST_EXTERNAL_OBJECTS =

TEST: CMakeFiles/TEST.dir/device.cc.o
TEST: CMakeFiles/TEST.dir/htif.cc.o
TEST: CMakeFiles/TEST.dir/memif.cc.o
TEST: CMakeFiles/TEST.dir/option_parser.cc.o
TEST: CMakeFiles/TEST.dir/sim.cc.o
TEST: CMakeFiles/TEST.dir/spike.cc.o
TEST: CMakeFiles/TEST.dir/build.make
TEST: CMakeFiles/TEST.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/work/isa-sim/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX executable TEST"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/TEST.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/TEST.dir/build: TEST

.PHONY : CMakeFiles/TEST.dir/build

CMakeFiles/TEST.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/TEST.dir/cmake_clean.cmake
.PHONY : CMakeFiles/TEST.dir/clean

CMakeFiles/TEST.dir/depend:
	cd /work/isa-sim/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /work/isa-sim /work/isa-sim /work/isa-sim/build /work/isa-sim/build /work/isa-sim/build/CMakeFiles/TEST.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/TEST.dir/depend
