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
CMAKE_COMMAND = /snap/clion/111/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/111/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ruben/Desktop/FEUP/CAL/TPs/TP5

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ruben/Desktop/FEUP/CAL/TPs/TP5/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/CAL_FP05.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/CAL_FP05.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/CAL_FP05.dir/flags.make

CMakeFiles/CAL_FP05.dir/main.cpp.o: CMakeFiles/CAL_FP05.dir/flags.make
CMakeFiles/CAL_FP05.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ruben/Desktop/FEUP/CAL/TPs/TP5/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/CAL_FP05.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/CAL_FP05.dir/main.cpp.o -c /home/ruben/Desktop/FEUP/CAL/TPs/TP5/main.cpp

CMakeFiles/CAL_FP05.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CAL_FP05.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ruben/Desktop/FEUP/CAL/TPs/TP5/main.cpp > CMakeFiles/CAL_FP05.dir/main.cpp.i

CMakeFiles/CAL_FP05.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CAL_FP05.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ruben/Desktop/FEUP/CAL/TPs/TP5/main.cpp -o CMakeFiles/CAL_FP05.dir/main.cpp.s

CMakeFiles/CAL_FP05.dir/Tests/tests.cpp.o: CMakeFiles/CAL_FP05.dir/flags.make
CMakeFiles/CAL_FP05.dir/Tests/tests.cpp.o: ../Tests/tests.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ruben/Desktop/FEUP/CAL/TPs/TP5/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/CAL_FP05.dir/Tests/tests.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/CAL_FP05.dir/Tests/tests.cpp.o -c /home/ruben/Desktop/FEUP/CAL/TPs/TP5/Tests/tests.cpp

CMakeFiles/CAL_FP05.dir/Tests/tests.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CAL_FP05.dir/Tests/tests.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ruben/Desktop/FEUP/CAL/TPs/TP5/Tests/tests.cpp > CMakeFiles/CAL_FP05.dir/Tests/tests.cpp.i

CMakeFiles/CAL_FP05.dir/Tests/tests.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CAL_FP05.dir/Tests/tests.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ruben/Desktop/FEUP/CAL/TPs/TP5/Tests/tests.cpp -o CMakeFiles/CAL_FP05.dir/Tests/tests.cpp.s

# Object files for target CAL_FP05
CAL_FP05_OBJECTS = \
"CMakeFiles/CAL_FP05.dir/main.cpp.o" \
"CMakeFiles/CAL_FP05.dir/Tests/tests.cpp.o"

# External object files for target CAL_FP05
CAL_FP05_EXTERNAL_OBJECTS =

CAL_FP05: CMakeFiles/CAL_FP05.dir/main.cpp.o
CAL_FP05: CMakeFiles/CAL_FP05.dir/Tests/tests.cpp.o
CAL_FP05: CMakeFiles/CAL_FP05.dir/build.make
CAL_FP05: lib/libgtestd.a
CAL_FP05: lib/libgtest_maind.a
CAL_FP05: lib/libgtestd.a
CAL_FP05: CMakeFiles/CAL_FP05.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ruben/Desktop/FEUP/CAL/TPs/TP5/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable CAL_FP05"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/CAL_FP05.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/CAL_FP05.dir/build: CAL_FP05

.PHONY : CMakeFiles/CAL_FP05.dir/build

CMakeFiles/CAL_FP05.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/CAL_FP05.dir/cmake_clean.cmake
.PHONY : CMakeFiles/CAL_FP05.dir/clean

CMakeFiles/CAL_FP05.dir/depend:
	cd /home/ruben/Desktop/FEUP/CAL/TPs/TP5/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ruben/Desktop/FEUP/CAL/TPs/TP5 /home/ruben/Desktop/FEUP/CAL/TPs/TP5 /home/ruben/Desktop/FEUP/CAL/TPs/TP5/cmake-build-debug /home/ruben/Desktop/FEUP/CAL/TPs/TP5/cmake-build-debug /home/ruben/Desktop/FEUP/CAL/TPs/TP5/cmake-build-debug/CMakeFiles/CAL_FP05.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/CAL_FP05.dir/depend

