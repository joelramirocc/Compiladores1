# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.18

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
CMAKE_COMMAND = /snap/cmake/619/bin/cmake

# The command to remove a file.
RM = /snap/cmake/619/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/joel/Escritorio/compi/Examen1_P5_2020/Parser/tests

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/joel/Escritorio/compi/Examen1_P5_2020/Parser/b

# Include any dependencies generated for this target.
include CMakeFiles/test_parser.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/test_parser.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/test_parser.dir/flags.make

CMakeFiles/test_parser.dir/home/joel/Escritorio/compi/Examen1_P5_2020/Parser/expr_parser.cpp.o: CMakeFiles/test_parser.dir/flags.make
CMakeFiles/test_parser.dir/home/joel/Escritorio/compi/Examen1_P5_2020/Parser/expr_parser.cpp.o: /home/joel/Escritorio/compi/Examen1_P5_2020/Parser/expr_parser.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/joel/Escritorio/compi/Examen1_P5_2020/Parser/b/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/test_parser.dir/home/joel/Escritorio/compi/Examen1_P5_2020/Parser/expr_parser.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test_parser.dir/home/joel/Escritorio/compi/Examen1_P5_2020/Parser/expr_parser.cpp.o -c /home/joel/Escritorio/compi/Examen1_P5_2020/Parser/expr_parser.cpp

CMakeFiles/test_parser.dir/home/joel/Escritorio/compi/Examen1_P5_2020/Parser/expr_parser.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_parser.dir/home/joel/Escritorio/compi/Examen1_P5_2020/Parser/expr_parser.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/joel/Escritorio/compi/Examen1_P5_2020/Parser/expr_parser.cpp > CMakeFiles/test_parser.dir/home/joel/Escritorio/compi/Examen1_P5_2020/Parser/expr_parser.cpp.i

CMakeFiles/test_parser.dir/home/joel/Escritorio/compi/Examen1_P5_2020/Parser/expr_parser.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_parser.dir/home/joel/Escritorio/compi/Examen1_P5_2020/Parser/expr_parser.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/joel/Escritorio/compi/Examen1_P5_2020/Parser/expr_parser.cpp -o CMakeFiles/test_parser.dir/home/joel/Escritorio/compi/Examen1_P5_2020/Parser/expr_parser.cpp.s

CMakeFiles/test_parser.dir/test_parser.cpp.o: CMakeFiles/test_parser.dir/flags.make
CMakeFiles/test_parser.dir/test_parser.cpp.o: /home/joel/Escritorio/compi/Examen1_P5_2020/Parser/tests/test_parser.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/joel/Escritorio/compi/Examen1_P5_2020/Parser/b/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/test_parser.dir/test_parser.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test_parser.dir/test_parser.cpp.o -c /home/joel/Escritorio/compi/Examen1_P5_2020/Parser/tests/test_parser.cpp

CMakeFiles/test_parser.dir/test_parser.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_parser.dir/test_parser.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/joel/Escritorio/compi/Examen1_P5_2020/Parser/tests/test_parser.cpp > CMakeFiles/test_parser.dir/test_parser.cpp.i

CMakeFiles/test_parser.dir/test_parser.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_parser.dir/test_parser.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/joel/Escritorio/compi/Examen1_P5_2020/Parser/tests/test_parser.cpp -o CMakeFiles/test_parser.dir/test_parser.cpp.s

# Object files for target test_parser
test_parser_OBJECTS = \
"CMakeFiles/test_parser.dir/home/joel/Escritorio/compi/Examen1_P5_2020/Parser/expr_parser.cpp.o" \
"CMakeFiles/test_parser.dir/test_parser.cpp.o"

# External object files for target test_parser
test_parser_EXTERNAL_OBJECTS =

test_parser: CMakeFiles/test_parser.dir/home/joel/Escritorio/compi/Examen1_P5_2020/Parser/expr_parser.cpp.o
test_parser: CMakeFiles/test_parser.dir/test_parser.cpp.o
test_parser: CMakeFiles/test_parser.dir/build.make
test_parser: CMakeFiles/test_parser.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/joel/Escritorio/compi/Examen1_P5_2020/Parser/b/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable test_parser"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_parser.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/test_parser.dir/build: test_parser

.PHONY : CMakeFiles/test_parser.dir/build

CMakeFiles/test_parser.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/test_parser.dir/cmake_clean.cmake
.PHONY : CMakeFiles/test_parser.dir/clean

CMakeFiles/test_parser.dir/depend:
	cd /home/joel/Escritorio/compi/Examen1_P5_2020/Parser/b && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/joel/Escritorio/compi/Examen1_P5_2020/Parser/tests /home/joel/Escritorio/compi/Examen1_P5_2020/Parser/tests /home/joel/Escritorio/compi/Examen1_P5_2020/Parser/b /home/joel/Escritorio/compi/Examen1_P5_2020/Parser/b /home/joel/Escritorio/compi/Examen1_P5_2020/Parser/b/CMakeFiles/test_parser.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/test_parser.dir/depend

