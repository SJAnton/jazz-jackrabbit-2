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
CMAKE_SOURCE_DIR = "/home/agustin/Escritorio/Taller 1/TP Final/jazz-jackrabbit-2"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/agustin/Escritorio/Taller 1/TP Final/jazz-jackrabbit-2/build"

# Include any dependencies generated for this target.
include CMakeFiles/client.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/client.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/client.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/client.dir/flags.make

CMakeFiles/client.dir/client_src/client_main.cpp.o: CMakeFiles/client.dir/flags.make
CMakeFiles/client.dir/client_src/client_main.cpp.o: ../client_src/client_main.cpp
CMakeFiles/client.dir/client_src/client_main.cpp.o: CMakeFiles/client.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/agustin/Escritorio/Taller 1/TP Final/jazz-jackrabbit-2/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/client.dir/client_src/client_main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/client.dir/client_src/client_main.cpp.o -MF CMakeFiles/client.dir/client_src/client_main.cpp.o.d -o CMakeFiles/client.dir/client_src/client_main.cpp.o -c "/home/agustin/Escritorio/Taller 1/TP Final/jazz-jackrabbit-2/client_src/client_main.cpp"

CMakeFiles/client.dir/client_src/client_main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/client.dir/client_src/client_main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/agustin/Escritorio/Taller 1/TP Final/jazz-jackrabbit-2/client_src/client_main.cpp" > CMakeFiles/client.dir/client_src/client_main.cpp.i

CMakeFiles/client.dir/client_src/client_main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/client.dir/client_src/client_main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/agustin/Escritorio/Taller 1/TP Final/jazz-jackrabbit-2/client_src/client_main.cpp" -o CMakeFiles/client.dir/client_src/client_main.cpp.s

CMakeFiles/client.dir/client_src/client_player.cpp.o: CMakeFiles/client.dir/flags.make
CMakeFiles/client.dir/client_src/client_player.cpp.o: ../client_src/client_player.cpp
CMakeFiles/client.dir/client_src/client_player.cpp.o: CMakeFiles/client.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/agustin/Escritorio/Taller 1/TP Final/jazz-jackrabbit-2/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/client.dir/client_src/client_player.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/client.dir/client_src/client_player.cpp.o -MF CMakeFiles/client.dir/client_src/client_player.cpp.o.d -o CMakeFiles/client.dir/client_src/client_player.cpp.o -c "/home/agustin/Escritorio/Taller 1/TP Final/jazz-jackrabbit-2/client_src/client_player.cpp"

CMakeFiles/client.dir/client_src/client_player.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/client.dir/client_src/client_player.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/agustin/Escritorio/Taller 1/TP Final/jazz-jackrabbit-2/client_src/client_player.cpp" > CMakeFiles/client.dir/client_src/client_player.cpp.i

CMakeFiles/client.dir/client_src/client_player.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/client.dir/client_src/client_player.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/agustin/Escritorio/Taller 1/TP Final/jazz-jackrabbit-2/client_src/client_player.cpp" -o CMakeFiles/client.dir/client_src/client_player.cpp.s

CMakeFiles/client.dir/client_src/client_protocol.cpp.o: CMakeFiles/client.dir/flags.make
CMakeFiles/client.dir/client_src/client_protocol.cpp.o: ../client_src/client_protocol.cpp
CMakeFiles/client.dir/client_src/client_protocol.cpp.o: CMakeFiles/client.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/agustin/Escritorio/Taller 1/TP Final/jazz-jackrabbit-2/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/client.dir/client_src/client_protocol.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/client.dir/client_src/client_protocol.cpp.o -MF CMakeFiles/client.dir/client_src/client_protocol.cpp.o.d -o CMakeFiles/client.dir/client_src/client_protocol.cpp.o -c "/home/agustin/Escritorio/Taller 1/TP Final/jazz-jackrabbit-2/client_src/client_protocol.cpp"

CMakeFiles/client.dir/client_src/client_protocol.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/client.dir/client_src/client_protocol.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/agustin/Escritorio/Taller 1/TP Final/jazz-jackrabbit-2/client_src/client_protocol.cpp" > CMakeFiles/client.dir/client_src/client_protocol.cpp.i

CMakeFiles/client.dir/client_src/client_protocol.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/client.dir/client_src/client_protocol.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/agustin/Escritorio/Taller 1/TP Final/jazz-jackrabbit-2/client_src/client_protocol.cpp" -o CMakeFiles/client.dir/client_src/client_protocol.cpp.s

CMakeFiles/client.dir/client_src/client_receiver.cpp.o: CMakeFiles/client.dir/flags.make
CMakeFiles/client.dir/client_src/client_receiver.cpp.o: ../client_src/client_receiver.cpp
CMakeFiles/client.dir/client_src/client_receiver.cpp.o: CMakeFiles/client.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/agustin/Escritorio/Taller 1/TP Final/jazz-jackrabbit-2/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/client.dir/client_src/client_receiver.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/client.dir/client_src/client_receiver.cpp.o -MF CMakeFiles/client.dir/client_src/client_receiver.cpp.o.d -o CMakeFiles/client.dir/client_src/client_receiver.cpp.o -c "/home/agustin/Escritorio/Taller 1/TP Final/jazz-jackrabbit-2/client_src/client_receiver.cpp"

CMakeFiles/client.dir/client_src/client_receiver.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/client.dir/client_src/client_receiver.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/agustin/Escritorio/Taller 1/TP Final/jazz-jackrabbit-2/client_src/client_receiver.cpp" > CMakeFiles/client.dir/client_src/client_receiver.cpp.i

CMakeFiles/client.dir/client_src/client_receiver.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/client.dir/client_src/client_receiver.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/agustin/Escritorio/Taller 1/TP Final/jazz-jackrabbit-2/client_src/client_receiver.cpp" -o CMakeFiles/client.dir/client_src/client_receiver.cpp.s

CMakeFiles/client.dir/client_src/client_renderer.cpp.o: CMakeFiles/client.dir/flags.make
CMakeFiles/client.dir/client_src/client_renderer.cpp.o: ../client_src/client_renderer.cpp
CMakeFiles/client.dir/client_src/client_renderer.cpp.o: CMakeFiles/client.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/agustin/Escritorio/Taller 1/TP Final/jazz-jackrabbit-2/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/client.dir/client_src/client_renderer.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/client.dir/client_src/client_renderer.cpp.o -MF CMakeFiles/client.dir/client_src/client_renderer.cpp.o.d -o CMakeFiles/client.dir/client_src/client_renderer.cpp.o -c "/home/agustin/Escritorio/Taller 1/TP Final/jazz-jackrabbit-2/client_src/client_renderer.cpp"

CMakeFiles/client.dir/client_src/client_renderer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/client.dir/client_src/client_renderer.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/agustin/Escritorio/Taller 1/TP Final/jazz-jackrabbit-2/client_src/client_renderer.cpp" > CMakeFiles/client.dir/client_src/client_renderer.cpp.i

CMakeFiles/client.dir/client_src/client_renderer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/client.dir/client_src/client_renderer.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/agustin/Escritorio/Taller 1/TP Final/jazz-jackrabbit-2/client_src/client_renderer.cpp" -o CMakeFiles/client.dir/client_src/client_renderer.cpp.s

CMakeFiles/client.dir/client_src/client_sender.cpp.o: CMakeFiles/client.dir/flags.make
CMakeFiles/client.dir/client_src/client_sender.cpp.o: ../client_src/client_sender.cpp
CMakeFiles/client.dir/client_src/client_sender.cpp.o: CMakeFiles/client.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/agustin/Escritorio/Taller 1/TP Final/jazz-jackrabbit-2/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/client.dir/client_src/client_sender.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/client.dir/client_src/client_sender.cpp.o -MF CMakeFiles/client.dir/client_src/client_sender.cpp.o.d -o CMakeFiles/client.dir/client_src/client_sender.cpp.o -c "/home/agustin/Escritorio/Taller 1/TP Final/jazz-jackrabbit-2/client_src/client_sender.cpp"

CMakeFiles/client.dir/client_src/client_sender.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/client.dir/client_src/client_sender.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/agustin/Escritorio/Taller 1/TP Final/jazz-jackrabbit-2/client_src/client_sender.cpp" > CMakeFiles/client.dir/client_src/client_sender.cpp.i

CMakeFiles/client.dir/client_src/client_sender.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/client.dir/client_src/client_sender.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/agustin/Escritorio/Taller 1/TP Final/jazz-jackrabbit-2/client_src/client_sender.cpp" -o CMakeFiles/client.dir/client_src/client_sender.cpp.s

CMakeFiles/client.dir/client_src/interfaz_grafica.cpp.o: CMakeFiles/client.dir/flags.make
CMakeFiles/client.dir/client_src/interfaz_grafica.cpp.o: ../client_src/interfaz_grafica.cpp
CMakeFiles/client.dir/client_src/interfaz_grafica.cpp.o: CMakeFiles/client.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/agustin/Escritorio/Taller 1/TP Final/jazz-jackrabbit-2/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/client.dir/client_src/interfaz_grafica.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/client.dir/client_src/interfaz_grafica.cpp.o -MF CMakeFiles/client.dir/client_src/interfaz_grafica.cpp.o.d -o CMakeFiles/client.dir/client_src/interfaz_grafica.cpp.o -c "/home/agustin/Escritorio/Taller 1/TP Final/jazz-jackrabbit-2/client_src/interfaz_grafica.cpp"

CMakeFiles/client.dir/client_src/interfaz_grafica.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/client.dir/client_src/interfaz_grafica.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/agustin/Escritorio/Taller 1/TP Final/jazz-jackrabbit-2/client_src/interfaz_grafica.cpp" > CMakeFiles/client.dir/client_src/interfaz_grafica.cpp.i

CMakeFiles/client.dir/client_src/interfaz_grafica.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/client.dir/client_src/interfaz_grafica.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/agustin/Escritorio/Taller 1/TP Final/jazz-jackrabbit-2/client_src/interfaz_grafica.cpp" -o CMakeFiles/client.dir/client_src/interfaz_grafica.cpp.s

CMakeFiles/client.dir/client_src/sprite_object.cpp.o: CMakeFiles/client.dir/flags.make
CMakeFiles/client.dir/client_src/sprite_object.cpp.o: ../client_src/sprite_object.cpp
CMakeFiles/client.dir/client_src/sprite_object.cpp.o: CMakeFiles/client.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/agustin/Escritorio/Taller 1/TP Final/jazz-jackrabbit-2/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/client.dir/client_src/sprite_object.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/client.dir/client_src/sprite_object.cpp.o -MF CMakeFiles/client.dir/client_src/sprite_object.cpp.o.d -o CMakeFiles/client.dir/client_src/sprite_object.cpp.o -c "/home/agustin/Escritorio/Taller 1/TP Final/jazz-jackrabbit-2/client_src/sprite_object.cpp"

CMakeFiles/client.dir/client_src/sprite_object.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/client.dir/client_src/sprite_object.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/agustin/Escritorio/Taller 1/TP Final/jazz-jackrabbit-2/client_src/sprite_object.cpp" > CMakeFiles/client.dir/client_src/sprite_object.cpp.i

CMakeFiles/client.dir/client_src/sprite_object.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/client.dir/client_src/sprite_object.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/agustin/Escritorio/Taller 1/TP Final/jazz-jackrabbit-2/client_src/sprite_object.cpp" -o CMakeFiles/client.dir/client_src/sprite_object.cpp.s

CMakeFiles/client.dir/client_src/spritesManager.cpp.o: CMakeFiles/client.dir/flags.make
CMakeFiles/client.dir/client_src/spritesManager.cpp.o: ../client_src/spritesManager.cpp
CMakeFiles/client.dir/client_src/spritesManager.cpp.o: CMakeFiles/client.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/agustin/Escritorio/Taller 1/TP Final/jazz-jackrabbit-2/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/client.dir/client_src/spritesManager.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/client.dir/client_src/spritesManager.cpp.o -MF CMakeFiles/client.dir/client_src/spritesManager.cpp.o.d -o CMakeFiles/client.dir/client_src/spritesManager.cpp.o -c "/home/agustin/Escritorio/Taller 1/TP Final/jazz-jackrabbit-2/client_src/spritesManager.cpp"

CMakeFiles/client.dir/client_src/spritesManager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/client.dir/client_src/spritesManager.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/agustin/Escritorio/Taller 1/TP Final/jazz-jackrabbit-2/client_src/spritesManager.cpp" > CMakeFiles/client.dir/client_src/spritesManager.cpp.i

CMakeFiles/client.dir/client_src/spritesManager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/client.dir/client_src/spritesManager.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/agustin/Escritorio/Taller 1/TP Final/jazz-jackrabbit-2/client_src/spritesManager.cpp" -o CMakeFiles/client.dir/client_src/spritesManager.cpp.s

CMakeFiles/client.dir/client_src/spritesheet.cpp.o: CMakeFiles/client.dir/flags.make
CMakeFiles/client.dir/client_src/spritesheet.cpp.o: ../client_src/spritesheet.cpp
CMakeFiles/client.dir/client_src/spritesheet.cpp.o: CMakeFiles/client.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/agustin/Escritorio/Taller 1/TP Final/jazz-jackrabbit-2/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/client.dir/client_src/spritesheet.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/client.dir/client_src/spritesheet.cpp.o -MF CMakeFiles/client.dir/client_src/spritesheet.cpp.o.d -o CMakeFiles/client.dir/client_src/spritesheet.cpp.o -c "/home/agustin/Escritorio/Taller 1/TP Final/jazz-jackrabbit-2/client_src/spritesheet.cpp"

CMakeFiles/client.dir/client_src/spritesheet.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/client.dir/client_src/spritesheet.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/agustin/Escritorio/Taller 1/TP Final/jazz-jackrabbit-2/client_src/spritesheet.cpp" > CMakeFiles/client.dir/client_src/spritesheet.cpp.i

CMakeFiles/client.dir/client_src/spritesheet.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/client.dir/client_src/spritesheet.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/agustin/Escritorio/Taller 1/TP Final/jazz-jackrabbit-2/client_src/spritesheet.cpp" -o CMakeFiles/client.dir/client_src/spritesheet.cpp.s

CMakeFiles/client.dir/client_src/spritesheetPlayer.cpp.o: CMakeFiles/client.dir/flags.make
CMakeFiles/client.dir/client_src/spritesheetPlayer.cpp.o: ../client_src/spritesheetPlayer.cpp
CMakeFiles/client.dir/client_src/spritesheetPlayer.cpp.o: CMakeFiles/client.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/agustin/Escritorio/Taller 1/TP Final/jazz-jackrabbit-2/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/client.dir/client_src/spritesheetPlayer.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/client.dir/client_src/spritesheetPlayer.cpp.o -MF CMakeFiles/client.dir/client_src/spritesheetPlayer.cpp.o.d -o CMakeFiles/client.dir/client_src/spritesheetPlayer.cpp.o -c "/home/agustin/Escritorio/Taller 1/TP Final/jazz-jackrabbit-2/client_src/spritesheetPlayer.cpp"

CMakeFiles/client.dir/client_src/spritesheetPlayer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/client.dir/client_src/spritesheetPlayer.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/agustin/Escritorio/Taller 1/TP Final/jazz-jackrabbit-2/client_src/spritesheetPlayer.cpp" > CMakeFiles/client.dir/client_src/spritesheetPlayer.cpp.i

CMakeFiles/client.dir/client_src/spritesheetPlayer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/client.dir/client_src/spritesheetPlayer.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/agustin/Escritorio/Taller 1/TP Final/jazz-jackrabbit-2/client_src/spritesheetPlayer.cpp" -o CMakeFiles/client.dir/client_src/spritesheetPlayer.cpp.s

CMakeFiles/client.dir/common_src/liberror.cpp.o: CMakeFiles/client.dir/flags.make
CMakeFiles/client.dir/common_src/liberror.cpp.o: ../common_src/liberror.cpp
CMakeFiles/client.dir/common_src/liberror.cpp.o: CMakeFiles/client.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/agustin/Escritorio/Taller 1/TP Final/jazz-jackrabbit-2/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object CMakeFiles/client.dir/common_src/liberror.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/client.dir/common_src/liberror.cpp.o -MF CMakeFiles/client.dir/common_src/liberror.cpp.o.d -o CMakeFiles/client.dir/common_src/liberror.cpp.o -c "/home/agustin/Escritorio/Taller 1/TP Final/jazz-jackrabbit-2/common_src/liberror.cpp"

CMakeFiles/client.dir/common_src/liberror.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/client.dir/common_src/liberror.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/agustin/Escritorio/Taller 1/TP Final/jazz-jackrabbit-2/common_src/liberror.cpp" > CMakeFiles/client.dir/common_src/liberror.cpp.i

CMakeFiles/client.dir/common_src/liberror.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/client.dir/common_src/liberror.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/agustin/Escritorio/Taller 1/TP Final/jazz-jackrabbit-2/common_src/liberror.cpp" -o CMakeFiles/client.dir/common_src/liberror.cpp.s

CMakeFiles/client.dir/common_src/resolver.cpp.o: CMakeFiles/client.dir/flags.make
CMakeFiles/client.dir/common_src/resolver.cpp.o: ../common_src/resolver.cpp
CMakeFiles/client.dir/common_src/resolver.cpp.o: CMakeFiles/client.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/agustin/Escritorio/Taller 1/TP Final/jazz-jackrabbit-2/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_13) "Building CXX object CMakeFiles/client.dir/common_src/resolver.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/client.dir/common_src/resolver.cpp.o -MF CMakeFiles/client.dir/common_src/resolver.cpp.o.d -o CMakeFiles/client.dir/common_src/resolver.cpp.o -c "/home/agustin/Escritorio/Taller 1/TP Final/jazz-jackrabbit-2/common_src/resolver.cpp"

CMakeFiles/client.dir/common_src/resolver.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/client.dir/common_src/resolver.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/agustin/Escritorio/Taller 1/TP Final/jazz-jackrabbit-2/common_src/resolver.cpp" > CMakeFiles/client.dir/common_src/resolver.cpp.i

CMakeFiles/client.dir/common_src/resolver.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/client.dir/common_src/resolver.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/agustin/Escritorio/Taller 1/TP Final/jazz-jackrabbit-2/common_src/resolver.cpp" -o CMakeFiles/client.dir/common_src/resolver.cpp.s

CMakeFiles/client.dir/common_src/resolvererror.cpp.o: CMakeFiles/client.dir/flags.make
CMakeFiles/client.dir/common_src/resolvererror.cpp.o: ../common_src/resolvererror.cpp
CMakeFiles/client.dir/common_src/resolvererror.cpp.o: CMakeFiles/client.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/agustin/Escritorio/Taller 1/TP Final/jazz-jackrabbit-2/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_14) "Building CXX object CMakeFiles/client.dir/common_src/resolvererror.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/client.dir/common_src/resolvererror.cpp.o -MF CMakeFiles/client.dir/common_src/resolvererror.cpp.o.d -o CMakeFiles/client.dir/common_src/resolvererror.cpp.o -c "/home/agustin/Escritorio/Taller 1/TP Final/jazz-jackrabbit-2/common_src/resolvererror.cpp"

CMakeFiles/client.dir/common_src/resolvererror.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/client.dir/common_src/resolvererror.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/agustin/Escritorio/Taller 1/TP Final/jazz-jackrabbit-2/common_src/resolvererror.cpp" > CMakeFiles/client.dir/common_src/resolvererror.cpp.i

CMakeFiles/client.dir/common_src/resolvererror.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/client.dir/common_src/resolvererror.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/agustin/Escritorio/Taller 1/TP Final/jazz-jackrabbit-2/common_src/resolvererror.cpp" -o CMakeFiles/client.dir/common_src/resolvererror.cpp.s

CMakeFiles/client.dir/common_src/socket.cpp.o: CMakeFiles/client.dir/flags.make
CMakeFiles/client.dir/common_src/socket.cpp.o: ../common_src/socket.cpp
CMakeFiles/client.dir/common_src/socket.cpp.o: CMakeFiles/client.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/agustin/Escritorio/Taller 1/TP Final/jazz-jackrabbit-2/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_15) "Building CXX object CMakeFiles/client.dir/common_src/socket.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/client.dir/common_src/socket.cpp.o -MF CMakeFiles/client.dir/common_src/socket.cpp.o.d -o CMakeFiles/client.dir/common_src/socket.cpp.o -c "/home/agustin/Escritorio/Taller 1/TP Final/jazz-jackrabbit-2/common_src/socket.cpp"

CMakeFiles/client.dir/common_src/socket.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/client.dir/common_src/socket.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/agustin/Escritorio/Taller 1/TP Final/jazz-jackrabbit-2/common_src/socket.cpp" > CMakeFiles/client.dir/common_src/socket.cpp.i

CMakeFiles/client.dir/common_src/socket.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/client.dir/common_src/socket.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/agustin/Escritorio/Taller 1/TP Final/jazz-jackrabbit-2/common_src/socket.cpp" -o CMakeFiles/client.dir/common_src/socket.cpp.s

# Object files for target client
client_OBJECTS = \
"CMakeFiles/client.dir/client_src/client_main.cpp.o" \
"CMakeFiles/client.dir/client_src/client_player.cpp.o" \
"CMakeFiles/client.dir/client_src/client_protocol.cpp.o" \
"CMakeFiles/client.dir/client_src/client_receiver.cpp.o" \
"CMakeFiles/client.dir/client_src/client_renderer.cpp.o" \
"CMakeFiles/client.dir/client_src/client_sender.cpp.o" \
"CMakeFiles/client.dir/client_src/interfaz_grafica.cpp.o" \
"CMakeFiles/client.dir/client_src/sprite_object.cpp.o" \
"CMakeFiles/client.dir/client_src/spritesManager.cpp.o" \
"CMakeFiles/client.dir/client_src/spritesheet.cpp.o" \
"CMakeFiles/client.dir/client_src/spritesheetPlayer.cpp.o" \
"CMakeFiles/client.dir/common_src/liberror.cpp.o" \
"CMakeFiles/client.dir/common_src/resolver.cpp.o" \
"CMakeFiles/client.dir/common_src/resolvererror.cpp.o" \
"CMakeFiles/client.dir/common_src/socket.cpp.o"

# External object files for target client
client_EXTERNAL_OBJECTS =

client: CMakeFiles/client.dir/client_src/client_main.cpp.o
client: CMakeFiles/client.dir/client_src/client_player.cpp.o
client: CMakeFiles/client.dir/client_src/client_protocol.cpp.o
client: CMakeFiles/client.dir/client_src/client_receiver.cpp.o
client: CMakeFiles/client.dir/client_src/client_renderer.cpp.o
client: CMakeFiles/client.dir/client_src/client_sender.cpp.o
client: CMakeFiles/client.dir/client_src/interfaz_grafica.cpp.o
client: CMakeFiles/client.dir/client_src/sprite_object.cpp.o
client: CMakeFiles/client.dir/client_src/spritesManager.cpp.o
client: CMakeFiles/client.dir/client_src/spritesheet.cpp.o
client: CMakeFiles/client.dir/client_src/spritesheetPlayer.cpp.o
client: CMakeFiles/client.dir/common_src/liberror.cpp.o
client: CMakeFiles/client.dir/common_src/resolver.cpp.o
client: CMakeFiles/client.dir/common_src/resolvererror.cpp.o
client: CMakeFiles/client.dir/common_src/socket.cpp.o
client: CMakeFiles/client.dir/build.make
client: /usr/local/lib/libSDL2.so
client: CMakeFiles/client.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/agustin/Escritorio/Taller 1/TP Final/jazz-jackrabbit-2/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_16) "Linking CXX executable client"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/client.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/client.dir/build: client
.PHONY : CMakeFiles/client.dir/build

CMakeFiles/client.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/client.dir/cmake_clean.cmake
.PHONY : CMakeFiles/client.dir/clean

CMakeFiles/client.dir/depend:
	cd "/home/agustin/Escritorio/Taller 1/TP Final/jazz-jackrabbit-2/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/agustin/Escritorio/Taller 1/TP Final/jazz-jackrabbit-2" "/home/agustin/Escritorio/Taller 1/TP Final/jazz-jackrabbit-2" "/home/agustin/Escritorio/Taller 1/TP Final/jazz-jackrabbit-2/build" "/home/agustin/Escritorio/Taller 1/TP Final/jazz-jackrabbit-2/build" "/home/agustin/Escritorio/Taller 1/TP Final/jazz-jackrabbit-2/build/CMakeFiles/client.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/client.dir/depend

