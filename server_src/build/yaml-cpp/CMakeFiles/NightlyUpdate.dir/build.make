# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_SOURCE_DIR = "/home/santiago/Escritorio/Taller de Programación/jazz-jackrabbit-2/server_src/build"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/santiago/Escritorio/Taller de Programación/jazz-jackrabbit-2/server_src/build"

# Utility rule file for NightlyUpdate.

# Include any custom commands dependencies for this target.
include yaml-cpp/CMakeFiles/NightlyUpdate.dir/compiler_depend.make

# Include the progress variables for this target.
include yaml-cpp/CMakeFiles/NightlyUpdate.dir/progress.make

yaml-cpp/CMakeFiles/NightlyUpdate:
	cd "/home/santiago/Escritorio/Taller de Programación/jazz-jackrabbit-2/server_src/build/yaml-cpp" && /usr/bin/ctest -D NightlyUpdate

NightlyUpdate: yaml-cpp/CMakeFiles/NightlyUpdate
NightlyUpdate: yaml-cpp/CMakeFiles/NightlyUpdate.dir/build.make
.PHONY : NightlyUpdate

# Rule to build all files generated by this target.
yaml-cpp/CMakeFiles/NightlyUpdate.dir/build: NightlyUpdate
.PHONY : yaml-cpp/CMakeFiles/NightlyUpdate.dir/build

yaml-cpp/CMakeFiles/NightlyUpdate.dir/clean:
	cd "/home/santiago/Escritorio/Taller de Programación/jazz-jackrabbit-2/server_src/build/yaml-cpp" && $(CMAKE_COMMAND) -P CMakeFiles/NightlyUpdate.dir/cmake_clean.cmake
.PHONY : yaml-cpp/CMakeFiles/NightlyUpdate.dir/clean

yaml-cpp/CMakeFiles/NightlyUpdate.dir/depend:
	cd "/home/santiago/Escritorio/Taller de Programación/jazz-jackrabbit-2/server_src/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/santiago/Escritorio/Taller de Programación/jazz-jackrabbit-2/server_src/build" "/home/santiago/Escritorio/Taller de Programación/jazz-jackrabbit-2/server_src/build/yaml-cpp" "/home/santiago/Escritorio/Taller de Programación/jazz-jackrabbit-2/server_src/build" "/home/santiago/Escritorio/Taller de Programación/jazz-jackrabbit-2/server_src/build/yaml-cpp" "/home/santiago/Escritorio/Taller de Programación/jazz-jackrabbit-2/server_src/build/yaml-cpp/CMakeFiles/NightlyUpdate.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : yaml-cpp/CMakeFiles/NightlyUpdate.dir/depend

