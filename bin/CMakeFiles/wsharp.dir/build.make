# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

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
CMAKE_SOURCE_DIR = /home/suky/dev/compiler/wsharp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/suky/dev/compiler/wsharp/bin

# Include any dependencies generated for this target.
include CMakeFiles/wsharp.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/wsharp.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/wsharp.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/wsharp.dir/flags.make

CMakeFiles/wsharp.dir/src/main.cpp.o: CMakeFiles/wsharp.dir/flags.make
CMakeFiles/wsharp.dir/src/main.cpp.o: /home/suky/dev/compiler/wsharp/src/main.cpp
CMakeFiles/wsharp.dir/src/main.cpp.o: CMakeFiles/wsharp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/suky/dev/compiler/wsharp/bin/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/wsharp.dir/src/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/wsharp.dir/src/main.cpp.o -MF CMakeFiles/wsharp.dir/src/main.cpp.o.d -o CMakeFiles/wsharp.dir/src/main.cpp.o -c /home/suky/dev/compiler/wsharp/src/main.cpp

CMakeFiles/wsharp.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/wsharp.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/suky/dev/compiler/wsharp/src/main.cpp > CMakeFiles/wsharp.dir/src/main.cpp.i

CMakeFiles/wsharp.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/wsharp.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/suky/dev/compiler/wsharp/src/main.cpp -o CMakeFiles/wsharp.dir/src/main.cpp.s

CMakeFiles/wsharp.dir/src/asm_compile.cpp.o: CMakeFiles/wsharp.dir/flags.make
CMakeFiles/wsharp.dir/src/asm_compile.cpp.o: /home/suky/dev/compiler/wsharp/src/asm_compile.cpp
CMakeFiles/wsharp.dir/src/asm_compile.cpp.o: CMakeFiles/wsharp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/suky/dev/compiler/wsharp/bin/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/wsharp.dir/src/asm_compile.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/wsharp.dir/src/asm_compile.cpp.o -MF CMakeFiles/wsharp.dir/src/asm_compile.cpp.o.d -o CMakeFiles/wsharp.dir/src/asm_compile.cpp.o -c /home/suky/dev/compiler/wsharp/src/asm_compile.cpp

CMakeFiles/wsharp.dir/src/asm_compile.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/wsharp.dir/src/asm_compile.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/suky/dev/compiler/wsharp/src/asm_compile.cpp > CMakeFiles/wsharp.dir/src/asm_compile.cpp.i

CMakeFiles/wsharp.dir/src/asm_compile.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/wsharp.dir/src/asm_compile.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/suky/dev/compiler/wsharp/src/asm_compile.cpp -o CMakeFiles/wsharp.dir/src/asm_compile.cpp.s

CMakeFiles/wsharp.dir/src/file_output.cpp.o: CMakeFiles/wsharp.dir/flags.make
CMakeFiles/wsharp.dir/src/file_output.cpp.o: /home/suky/dev/compiler/wsharp/src/file_output.cpp
CMakeFiles/wsharp.dir/src/file_output.cpp.o: CMakeFiles/wsharp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/suky/dev/compiler/wsharp/bin/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/wsharp.dir/src/file_output.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/wsharp.dir/src/file_output.cpp.o -MF CMakeFiles/wsharp.dir/src/file_output.cpp.o.d -o CMakeFiles/wsharp.dir/src/file_output.cpp.o -c /home/suky/dev/compiler/wsharp/src/file_output.cpp

CMakeFiles/wsharp.dir/src/file_output.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/wsharp.dir/src/file_output.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/suky/dev/compiler/wsharp/src/file_output.cpp > CMakeFiles/wsharp.dir/src/file_output.cpp.i

CMakeFiles/wsharp.dir/src/file_output.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/wsharp.dir/src/file_output.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/suky/dev/compiler/wsharp/src/file_output.cpp -o CMakeFiles/wsharp.dir/src/file_output.cpp.s

CMakeFiles/wsharp.dir/src/global_functions.cpp.o: CMakeFiles/wsharp.dir/flags.make
CMakeFiles/wsharp.dir/src/global_functions.cpp.o: /home/suky/dev/compiler/wsharp/src/global_functions.cpp
CMakeFiles/wsharp.dir/src/global_functions.cpp.o: CMakeFiles/wsharp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/suky/dev/compiler/wsharp/bin/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/wsharp.dir/src/global_functions.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/wsharp.dir/src/global_functions.cpp.o -MF CMakeFiles/wsharp.dir/src/global_functions.cpp.o.d -o CMakeFiles/wsharp.dir/src/global_functions.cpp.o -c /home/suky/dev/compiler/wsharp/src/global_functions.cpp

CMakeFiles/wsharp.dir/src/global_functions.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/wsharp.dir/src/global_functions.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/suky/dev/compiler/wsharp/src/global_functions.cpp > CMakeFiles/wsharp.dir/src/global_functions.cpp.i

CMakeFiles/wsharp.dir/src/global_functions.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/wsharp.dir/src/global_functions.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/suky/dev/compiler/wsharp/src/global_functions.cpp -o CMakeFiles/wsharp.dir/src/global_functions.cpp.s

CMakeFiles/wsharp.dir/src/lexer.cpp.o: CMakeFiles/wsharp.dir/flags.make
CMakeFiles/wsharp.dir/src/lexer.cpp.o: /home/suky/dev/compiler/wsharp/src/lexer.cpp
CMakeFiles/wsharp.dir/src/lexer.cpp.o: CMakeFiles/wsharp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/suky/dev/compiler/wsharp/bin/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/wsharp.dir/src/lexer.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/wsharp.dir/src/lexer.cpp.o -MF CMakeFiles/wsharp.dir/src/lexer.cpp.o.d -o CMakeFiles/wsharp.dir/src/lexer.cpp.o -c /home/suky/dev/compiler/wsharp/src/lexer.cpp

CMakeFiles/wsharp.dir/src/lexer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/wsharp.dir/src/lexer.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/suky/dev/compiler/wsharp/src/lexer.cpp > CMakeFiles/wsharp.dir/src/lexer.cpp.i

CMakeFiles/wsharp.dir/src/lexer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/wsharp.dir/src/lexer.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/suky/dev/compiler/wsharp/src/lexer.cpp -o CMakeFiles/wsharp.dir/src/lexer.cpp.s

CMakeFiles/wsharp.dir/src/parser.cpp.o: CMakeFiles/wsharp.dir/flags.make
CMakeFiles/wsharp.dir/src/parser.cpp.o: /home/suky/dev/compiler/wsharp/src/parser.cpp
CMakeFiles/wsharp.dir/src/parser.cpp.o: CMakeFiles/wsharp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/suky/dev/compiler/wsharp/bin/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/wsharp.dir/src/parser.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/wsharp.dir/src/parser.cpp.o -MF CMakeFiles/wsharp.dir/src/parser.cpp.o.d -o CMakeFiles/wsharp.dir/src/parser.cpp.o -c /home/suky/dev/compiler/wsharp/src/parser.cpp

CMakeFiles/wsharp.dir/src/parser.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/wsharp.dir/src/parser.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/suky/dev/compiler/wsharp/src/parser.cpp > CMakeFiles/wsharp.dir/src/parser.cpp.i

CMakeFiles/wsharp.dir/src/parser.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/wsharp.dir/src/parser.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/suky/dev/compiler/wsharp/src/parser.cpp -o CMakeFiles/wsharp.dir/src/parser.cpp.s

# Object files for target wsharp
wsharp_OBJECTS = \
"CMakeFiles/wsharp.dir/src/main.cpp.o" \
"CMakeFiles/wsharp.dir/src/asm_compile.cpp.o" \
"CMakeFiles/wsharp.dir/src/file_output.cpp.o" \
"CMakeFiles/wsharp.dir/src/global_functions.cpp.o" \
"CMakeFiles/wsharp.dir/src/lexer.cpp.o" \
"CMakeFiles/wsharp.dir/src/parser.cpp.o"

# External object files for target wsharp
wsharp_EXTERNAL_OBJECTS =

wsharp: CMakeFiles/wsharp.dir/src/main.cpp.o
wsharp: CMakeFiles/wsharp.dir/src/asm_compile.cpp.o
wsharp: CMakeFiles/wsharp.dir/src/file_output.cpp.o
wsharp: CMakeFiles/wsharp.dir/src/global_functions.cpp.o
wsharp: CMakeFiles/wsharp.dir/src/lexer.cpp.o
wsharp: CMakeFiles/wsharp.dir/src/parser.cpp.o
wsharp: CMakeFiles/wsharp.dir/build.make
wsharp: CMakeFiles/wsharp.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/suky/dev/compiler/wsharp/bin/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX executable wsharp"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/wsharp.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/wsharp.dir/build: wsharp
.PHONY : CMakeFiles/wsharp.dir/build

CMakeFiles/wsharp.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/wsharp.dir/cmake_clean.cmake
.PHONY : CMakeFiles/wsharp.dir/clean

CMakeFiles/wsharp.dir/depend:
	cd /home/suky/dev/compiler/wsharp/bin && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/suky/dev/compiler/wsharp /home/suky/dev/compiler/wsharp /home/suky/dev/compiler/wsharp/bin /home/suky/dev/compiler/wsharp/bin /home/suky/dev/compiler/wsharp/bin/CMakeFiles/wsharp.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/wsharp.dir/depend

