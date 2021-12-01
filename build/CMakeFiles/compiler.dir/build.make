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
CMAKE_SOURCE_DIR = /mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/build

# Include any dependencies generated for this target.
include CMakeFiles/compiler.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/compiler.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/compiler.dir/flags.make

parser.tab.cpp: ../src/parser.y
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "[BISON][Parser] Building parser with bison 3.5.1"
	cd /mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template && /usr/bin/bison -d -o /mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/build/parser.tab.cpp /mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/src/parser.y

parser.tab.hpp: parser.tab.cpp
	@$(CMAKE_COMMAND) -E touch_nocreate parser.tab.hpp

lexer.lex.cpp: ../src/lexer.l
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "[FLEX][Lexer] Building scanner with flex 2.6.4"
	cd /mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template && /usr/bin/flex -o/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/build/lexer.lex.cpp /mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/src/lexer.l

CMakeFiles/compiler.dir/src/ast.cpp.o: CMakeFiles/compiler.dir/flags.make
CMakeFiles/compiler.dir/src/ast.cpp.o: ../src/ast.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/compiler.dir/src/ast.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/compiler.dir/src/ast.cpp.o -c /mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/src/ast.cpp

CMakeFiles/compiler.dir/src/ast.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/compiler.dir/src/ast.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/src/ast.cpp > CMakeFiles/compiler.dir/src/ast.cpp.i

CMakeFiles/compiler.dir/src/ast.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/compiler.dir/src/ast.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/src/ast.cpp -o CMakeFiles/compiler.dir/src/ast.cpp.s

CMakeFiles/compiler.dir/src/main.cpp.o: CMakeFiles/compiler.dir/flags.make
CMakeFiles/compiler.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/compiler.dir/src/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/compiler.dir/src/main.cpp.o -c /mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/src/main.cpp

CMakeFiles/compiler.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/compiler.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/src/main.cpp > CMakeFiles/compiler.dir/src/main.cpp.i

CMakeFiles/compiler.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/compiler.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/src/main.cpp -o CMakeFiles/compiler.dir/src/main.cpp.s

CMakeFiles/compiler.dir/src/sym.cpp.o: CMakeFiles/compiler.dir/flags.make
CMakeFiles/compiler.dir/src/sym.cpp.o: ../src/sym.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/compiler.dir/src/sym.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/compiler.dir/src/sym.cpp.o -c /mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/src/sym.cpp

CMakeFiles/compiler.dir/src/sym.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/compiler.dir/src/sym.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/src/sym.cpp > CMakeFiles/compiler.dir/src/sym.cpp.i

CMakeFiles/compiler.dir/src/sym.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/compiler.dir/src/sym.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/src/sym.cpp -o CMakeFiles/compiler.dir/src/sym.cpp.s

CMakeFiles/compiler.dir/lexer.lex.cpp.o: CMakeFiles/compiler.dir/flags.make
CMakeFiles/compiler.dir/lexer.lex.cpp.o: lexer.lex.cpp
CMakeFiles/compiler.dir/lexer.lex.cpp.o: parser.tab.hpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/compiler.dir/lexer.lex.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/compiler.dir/lexer.lex.cpp.o -c /mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/build/lexer.lex.cpp

CMakeFiles/compiler.dir/lexer.lex.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/compiler.dir/lexer.lex.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/build/lexer.lex.cpp > CMakeFiles/compiler.dir/lexer.lex.cpp.i

CMakeFiles/compiler.dir/lexer.lex.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/compiler.dir/lexer.lex.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/build/lexer.lex.cpp -o CMakeFiles/compiler.dir/lexer.lex.cpp.s

CMakeFiles/compiler.dir/parser.tab.cpp.o: CMakeFiles/compiler.dir/flags.make
CMakeFiles/compiler.dir/parser.tab.cpp.o: parser.tab.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/compiler.dir/parser.tab.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/compiler.dir/parser.tab.cpp.o -c /mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/build/parser.tab.cpp

CMakeFiles/compiler.dir/parser.tab.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/compiler.dir/parser.tab.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/build/parser.tab.cpp > CMakeFiles/compiler.dir/parser.tab.cpp.i

CMakeFiles/compiler.dir/parser.tab.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/compiler.dir/parser.tab.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/build/parser.tab.cpp -o CMakeFiles/compiler.dir/parser.tab.cpp.s

# Object files for target compiler
compiler_OBJECTS = \
"CMakeFiles/compiler.dir/src/ast.cpp.o" \
"CMakeFiles/compiler.dir/src/main.cpp.o" \
"CMakeFiles/compiler.dir/src/sym.cpp.o" \
"CMakeFiles/compiler.dir/lexer.lex.cpp.o" \
"CMakeFiles/compiler.dir/parser.tab.cpp.o"

# External object files for target compiler
compiler_EXTERNAL_OBJECTS =

compiler: CMakeFiles/compiler.dir/src/ast.cpp.o
compiler: CMakeFiles/compiler.dir/src/main.cpp.o
compiler: CMakeFiles/compiler.dir/src/sym.cpp.o
compiler: CMakeFiles/compiler.dir/lexer.lex.cpp.o
compiler: CMakeFiles/compiler.dir/parser.tab.cpp.o
compiler: CMakeFiles/compiler.dir/build.make
compiler: CMakeFiles/compiler.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking CXX executable compiler"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/compiler.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/compiler.dir/build: compiler

.PHONY : CMakeFiles/compiler.dir/build

CMakeFiles/compiler.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/compiler.dir/cmake_clean.cmake
.PHONY : CMakeFiles/compiler.dir/clean

CMakeFiles/compiler.dir/depend: parser.tab.cpp
CMakeFiles/compiler.dir/depend: parser.tab.hpp
CMakeFiles/compiler.dir/depend: lexer.lex.cpp
	cd /mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template /mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template /mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/build /mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/build /mnt/e/PKU/大四上/编译原理/实习/sysy-cmake-template/build/CMakeFiles/compiler.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/compiler.dir/depend
