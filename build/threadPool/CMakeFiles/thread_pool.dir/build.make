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
CMAKE_SOURCE_DIR = /home/zoe/webServer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/zoe/webServer/build

# Include any dependencies generated for this target.
include threadPool/CMakeFiles/thread_pool.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include threadPool/CMakeFiles/thread_pool.dir/compiler_depend.make

# Include the progress variables for this target.
include threadPool/CMakeFiles/thread_pool.dir/progress.make

# Include the compile flags for this target's objects.
include threadPool/CMakeFiles/thread_pool.dir/flags.make

threadPool/CMakeFiles/thread_pool.dir/Thread.cpp.o: threadPool/CMakeFiles/thread_pool.dir/flags.make
threadPool/CMakeFiles/thread_pool.dir/Thread.cpp.o: ../threadPool/Thread.cpp
threadPool/CMakeFiles/thread_pool.dir/Thread.cpp.o: threadPool/CMakeFiles/thread_pool.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zoe/webServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object threadPool/CMakeFiles/thread_pool.dir/Thread.cpp.o"
	cd /home/zoe/webServer/build/threadPool && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT threadPool/CMakeFiles/thread_pool.dir/Thread.cpp.o -MF CMakeFiles/thread_pool.dir/Thread.cpp.o.d -o CMakeFiles/thread_pool.dir/Thread.cpp.o -c /home/zoe/webServer/threadPool/Thread.cpp

threadPool/CMakeFiles/thread_pool.dir/Thread.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/thread_pool.dir/Thread.cpp.i"
	cd /home/zoe/webServer/build/threadPool && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zoe/webServer/threadPool/Thread.cpp > CMakeFiles/thread_pool.dir/Thread.cpp.i

threadPool/CMakeFiles/thread_pool.dir/Thread.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/thread_pool.dir/Thread.cpp.s"
	cd /home/zoe/webServer/build/threadPool && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zoe/webServer/threadPool/Thread.cpp -o CMakeFiles/thread_pool.dir/Thread.cpp.s

# Object files for target thread_pool
thread_pool_OBJECTS = \
"CMakeFiles/thread_pool.dir/Thread.cpp.o"

# External object files for target thread_pool
thread_pool_EXTERNAL_OBJECTS =

../lib/libthread_pool.a: threadPool/CMakeFiles/thread_pool.dir/Thread.cpp.o
../lib/libthread_pool.a: threadPool/CMakeFiles/thread_pool.dir/build.make
../lib/libthread_pool.a: threadPool/CMakeFiles/thread_pool.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/zoe/webServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library ../../lib/libthread_pool.a"
	cd /home/zoe/webServer/build/threadPool && $(CMAKE_COMMAND) -P CMakeFiles/thread_pool.dir/cmake_clean_target.cmake
	cd /home/zoe/webServer/build/threadPool && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/thread_pool.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
threadPool/CMakeFiles/thread_pool.dir/build: ../lib/libthread_pool.a
.PHONY : threadPool/CMakeFiles/thread_pool.dir/build

threadPool/CMakeFiles/thread_pool.dir/clean:
	cd /home/zoe/webServer/build/threadPool && $(CMAKE_COMMAND) -P CMakeFiles/thread_pool.dir/cmake_clean.cmake
.PHONY : threadPool/CMakeFiles/thread_pool.dir/clean

threadPool/CMakeFiles/thread_pool.dir/depend:
	cd /home/zoe/webServer/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/zoe/webServer /home/zoe/webServer/threadPool /home/zoe/webServer/build /home/zoe/webServer/build/threadPool /home/zoe/webServer/build/threadPool/CMakeFiles/thread_pool.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : threadPool/CMakeFiles/thread_pool.dir/depend

