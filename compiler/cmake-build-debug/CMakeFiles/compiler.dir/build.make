# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.12

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/jjjjjjjiyun/学习/buaa_compiler/compiler

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/jjjjjjjiyun/学习/buaa_compiler/compiler/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/compiler.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/compiler.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/compiler.dir/flags.make

CMakeFiles/compiler.dir/main.cpp.o: CMakeFiles/compiler.dir/flags.make
CMakeFiles/compiler.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/jjjjjjjiyun/学习/buaa_compiler/compiler/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/compiler.dir/main.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/compiler.dir/main.cpp.o -c /Users/jjjjjjjiyun/学习/buaa_compiler/compiler/main.cpp

CMakeFiles/compiler.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/compiler.dir/main.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/jjjjjjjiyun/学习/buaa_compiler/compiler/main.cpp > CMakeFiles/compiler.dir/main.cpp.i

CMakeFiles/compiler.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/compiler.dir/main.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/jjjjjjjiyun/学习/buaa_compiler/compiler/main.cpp -o CMakeFiles/compiler.dir/main.cpp.s

CMakeFiles/compiler.dir/Compiler.cpp.o: CMakeFiles/compiler.dir/flags.make
CMakeFiles/compiler.dir/Compiler.cpp.o: ../Compiler.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/jjjjjjjiyun/学习/buaa_compiler/compiler/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/compiler.dir/Compiler.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/compiler.dir/Compiler.cpp.o -c /Users/jjjjjjjiyun/学习/buaa_compiler/compiler/Compiler.cpp

CMakeFiles/compiler.dir/Compiler.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/compiler.dir/Compiler.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/jjjjjjjiyun/学习/buaa_compiler/compiler/Compiler.cpp > CMakeFiles/compiler.dir/Compiler.cpp.i

CMakeFiles/compiler.dir/Compiler.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/compiler.dir/Compiler.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/jjjjjjjiyun/学习/buaa_compiler/compiler/Compiler.cpp -o CMakeFiles/compiler.dir/Compiler.cpp.s

CMakeFiles/compiler.dir/Lexer.cpp.o: CMakeFiles/compiler.dir/flags.make
CMakeFiles/compiler.dir/Lexer.cpp.o: ../Lexer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/jjjjjjjiyun/学习/buaa_compiler/compiler/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/compiler.dir/Lexer.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/compiler.dir/Lexer.cpp.o -c /Users/jjjjjjjiyun/学习/buaa_compiler/compiler/Lexer.cpp

CMakeFiles/compiler.dir/Lexer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/compiler.dir/Lexer.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/jjjjjjjiyun/学习/buaa_compiler/compiler/Lexer.cpp > CMakeFiles/compiler.dir/Lexer.cpp.i

CMakeFiles/compiler.dir/Lexer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/compiler.dir/Lexer.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/jjjjjjjiyun/学习/buaa_compiler/compiler/Lexer.cpp -o CMakeFiles/compiler.dir/Lexer.cpp.s

CMakeFiles/compiler.dir/Syntax.cpp.o: CMakeFiles/compiler.dir/flags.make
CMakeFiles/compiler.dir/Syntax.cpp.o: ../Syntax.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/jjjjjjjiyun/学习/buaa_compiler/compiler/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/compiler.dir/Syntax.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/compiler.dir/Syntax.cpp.o -c /Users/jjjjjjjiyun/学习/buaa_compiler/compiler/Syntax.cpp

CMakeFiles/compiler.dir/Syntax.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/compiler.dir/Syntax.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/jjjjjjjiyun/学习/buaa_compiler/compiler/Syntax.cpp > CMakeFiles/compiler.dir/Syntax.cpp.i

CMakeFiles/compiler.dir/Syntax.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/compiler.dir/Syntax.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/jjjjjjjiyun/学习/buaa_compiler/compiler/Syntax.cpp -o CMakeFiles/compiler.dir/Syntax.cpp.s

CMakeFiles/compiler.dir/Error.cpp.o: CMakeFiles/compiler.dir/flags.make
CMakeFiles/compiler.dir/Error.cpp.o: ../Error.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/jjjjjjjiyun/学习/buaa_compiler/compiler/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/compiler.dir/Error.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/compiler.dir/Error.cpp.o -c /Users/jjjjjjjiyun/学习/buaa_compiler/compiler/Error.cpp

CMakeFiles/compiler.dir/Error.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/compiler.dir/Error.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/jjjjjjjiyun/学习/buaa_compiler/compiler/Error.cpp > CMakeFiles/compiler.dir/Error.cpp.i

CMakeFiles/compiler.dir/Error.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/compiler.dir/Error.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/jjjjjjjiyun/学习/buaa_compiler/compiler/Error.cpp -o CMakeFiles/compiler.dir/Error.cpp.s

CMakeFiles/compiler.dir/SymbolTab.cpp.o: CMakeFiles/compiler.dir/flags.make
CMakeFiles/compiler.dir/SymbolTab.cpp.o: ../SymbolTab.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/jjjjjjjiyun/学习/buaa_compiler/compiler/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/compiler.dir/SymbolTab.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/compiler.dir/SymbolTab.cpp.o -c /Users/jjjjjjjiyun/学习/buaa_compiler/compiler/SymbolTab.cpp

CMakeFiles/compiler.dir/SymbolTab.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/compiler.dir/SymbolTab.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/jjjjjjjiyun/学习/buaa_compiler/compiler/SymbolTab.cpp > CMakeFiles/compiler.dir/SymbolTab.cpp.i

CMakeFiles/compiler.dir/SymbolTab.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/compiler.dir/SymbolTab.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/jjjjjjjiyun/学习/buaa_compiler/compiler/SymbolTab.cpp -o CMakeFiles/compiler.dir/SymbolTab.cpp.s

# Object files for target compiler
compiler_OBJECTS = \
"CMakeFiles/compiler.dir/main.cpp.o" \
"CMakeFiles/compiler.dir/Compiler.cpp.o" \
"CMakeFiles/compiler.dir/Lexer.cpp.o" \
"CMakeFiles/compiler.dir/Syntax.cpp.o" \
"CMakeFiles/compiler.dir/Error.cpp.o" \
"CMakeFiles/compiler.dir/SymbolTab.cpp.o"

# External object files for target compiler
compiler_EXTERNAL_OBJECTS =

compiler: CMakeFiles/compiler.dir/main.cpp.o
compiler: CMakeFiles/compiler.dir/Compiler.cpp.o
compiler: CMakeFiles/compiler.dir/Lexer.cpp.o
compiler: CMakeFiles/compiler.dir/Syntax.cpp.o
compiler: CMakeFiles/compiler.dir/Error.cpp.o
compiler: CMakeFiles/compiler.dir/SymbolTab.cpp.o
compiler: CMakeFiles/compiler.dir/build.make
compiler: CMakeFiles/compiler.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/jjjjjjjiyun/学习/buaa_compiler/compiler/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX executable compiler"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/compiler.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/compiler.dir/build: compiler

.PHONY : CMakeFiles/compiler.dir/build

CMakeFiles/compiler.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/compiler.dir/cmake_clean.cmake
.PHONY : CMakeFiles/compiler.dir/clean

CMakeFiles/compiler.dir/depend:
	cd /Users/jjjjjjjiyun/学习/buaa_compiler/compiler/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/jjjjjjjiyun/学习/buaa_compiler/compiler /Users/jjjjjjjiyun/学习/buaa_compiler/compiler /Users/jjjjjjjiyun/学习/buaa_compiler/compiler/cmake-build-debug /Users/jjjjjjjiyun/学习/buaa_compiler/compiler/cmake-build-debug /Users/jjjjjjjiyun/学习/buaa_compiler/compiler/cmake-build-debug/CMakeFiles/compiler.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/compiler.dir/depend

