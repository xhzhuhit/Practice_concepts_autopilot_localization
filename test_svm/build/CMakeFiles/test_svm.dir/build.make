# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_SOURCE_DIR = /home/zhuxiaohui/test_svm

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/zhuxiaohui/test_svm/build

# Include any dependencies generated for this target.
include CMakeFiles/test_svm.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/test_svm.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/test_svm.dir/flags.make

CMakeFiles/test_svm.dir/src/detect_lane_change.cpp.o: CMakeFiles/test_svm.dir/flags.make
CMakeFiles/test_svm.dir/src/detect_lane_change.cpp.o: ../src/detect_lane_change.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zhuxiaohui/test_svm/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/test_svm.dir/src/detect_lane_change.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test_svm.dir/src/detect_lane_change.cpp.o -c /home/zhuxiaohui/test_svm/src/detect_lane_change.cpp

CMakeFiles/test_svm.dir/src/detect_lane_change.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_svm.dir/src/detect_lane_change.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zhuxiaohui/test_svm/src/detect_lane_change.cpp > CMakeFiles/test_svm.dir/src/detect_lane_change.cpp.i

CMakeFiles/test_svm.dir/src/detect_lane_change.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_svm.dir/src/detect_lane_change.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zhuxiaohui/test_svm/src/detect_lane_change.cpp -o CMakeFiles/test_svm.dir/src/detect_lane_change.cpp.s

CMakeFiles/test_svm.dir/src/detect_lane_change.cpp.o.requires:

.PHONY : CMakeFiles/test_svm.dir/src/detect_lane_change.cpp.o.requires

CMakeFiles/test_svm.dir/src/detect_lane_change.cpp.o.provides: CMakeFiles/test_svm.dir/src/detect_lane_change.cpp.o.requires
	$(MAKE) -f CMakeFiles/test_svm.dir/build.make CMakeFiles/test_svm.dir/src/detect_lane_change.cpp.o.provides.build
.PHONY : CMakeFiles/test_svm.dir/src/detect_lane_change.cpp.o.provides

CMakeFiles/test_svm.dir/src/detect_lane_change.cpp.o.provides.build: CMakeFiles/test_svm.dir/src/detect_lane_change.cpp.o


# Object files for target test_svm
test_svm_OBJECTS = \
"CMakeFiles/test_svm.dir/src/detect_lane_change.cpp.o"

# External object files for target test_svm
test_svm_EXTERNAL_OBJECTS =

test_svm: CMakeFiles/test_svm.dir/src/detect_lane_change.cpp.o
test_svm: CMakeFiles/test_svm.dir/build.make
test_svm: /opt/ros/kinetic/lib/libopencv_stitching3.so.3.2.0
test_svm: /opt/ros/kinetic/lib/libopencv_superres3.so.3.2.0
test_svm: /opt/ros/kinetic/lib/libopencv_videostab3.so.3.2.0
test_svm: /opt/ros/kinetic/lib/libopencv_aruco3.so.3.2.0
test_svm: /opt/ros/kinetic/lib/libopencv_bgsegm3.so.3.2.0
test_svm: /opt/ros/kinetic/lib/libopencv_bioinspired3.so.3.2.0
test_svm: /opt/ros/kinetic/lib/libopencv_ccalib3.so.3.2.0
test_svm: /opt/ros/kinetic/lib/libopencv_cvv3.so.3.2.0
test_svm: /opt/ros/kinetic/lib/libopencv_datasets3.so.3.2.0
test_svm: /opt/ros/kinetic/lib/libopencv_dpm3.so.3.2.0
test_svm: /opt/ros/kinetic/lib/libopencv_face3.so.3.2.0
test_svm: /opt/ros/kinetic/lib/libopencv_fuzzy3.so.3.2.0
test_svm: /opt/ros/kinetic/lib/libopencv_hdf3.so.3.2.0
test_svm: /opt/ros/kinetic/lib/libopencv_line_descriptor3.so.3.2.0
test_svm: /opt/ros/kinetic/lib/libopencv_optflow3.so.3.2.0
test_svm: /opt/ros/kinetic/lib/libopencv_plot3.so.3.2.0
test_svm: /opt/ros/kinetic/lib/libopencv_reg3.so.3.2.0
test_svm: /opt/ros/kinetic/lib/libopencv_saliency3.so.3.2.0
test_svm: /opt/ros/kinetic/lib/libopencv_stereo3.so.3.2.0
test_svm: /opt/ros/kinetic/lib/libopencv_structured_light3.so.3.2.0
test_svm: /opt/ros/kinetic/lib/libopencv_surface_matching3.so.3.2.0
test_svm: /opt/ros/kinetic/lib/libopencv_text3.so.3.2.0
test_svm: /opt/ros/kinetic/lib/libopencv_xfeatures2d3.so.3.2.0
test_svm: /opt/ros/kinetic/lib/libopencv_ximgproc3.so.3.2.0
test_svm: /opt/ros/kinetic/lib/libopencv_xobjdetect3.so.3.2.0
test_svm: /opt/ros/kinetic/lib/libopencv_xphoto3.so.3.2.0
test_svm: /opt/ros/kinetic/lib/libopencv_shape3.so.3.2.0
test_svm: /opt/ros/kinetic/lib/libopencv_video3.so.3.2.0
test_svm: /opt/ros/kinetic/lib/libopencv_viz3.so.3.2.0
test_svm: /opt/ros/kinetic/lib/libopencv_phase_unwrapping3.so.3.2.0
test_svm: /opt/ros/kinetic/lib/libopencv_rgbd3.so.3.2.0
test_svm: /opt/ros/kinetic/lib/libopencv_calib3d3.so.3.2.0
test_svm: /opt/ros/kinetic/lib/libopencv_features2d3.so.3.2.0
test_svm: /opt/ros/kinetic/lib/libopencv_flann3.so.3.2.0
test_svm: /opt/ros/kinetic/lib/libopencv_objdetect3.so.3.2.0
test_svm: /opt/ros/kinetic/lib/libopencv_ml3.so.3.2.0
test_svm: /opt/ros/kinetic/lib/libopencv_highgui3.so.3.2.0
test_svm: /opt/ros/kinetic/lib/libopencv_photo3.so.3.2.0
test_svm: /opt/ros/kinetic/lib/libopencv_videoio3.so.3.2.0
test_svm: /opt/ros/kinetic/lib/libopencv_imgcodecs3.so.3.2.0
test_svm: /opt/ros/kinetic/lib/libopencv_imgproc3.so.3.2.0
test_svm: /opt/ros/kinetic/lib/libopencv_core3.so.3.2.0
test_svm: CMakeFiles/test_svm.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/zhuxiaohui/test_svm/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable test_svm"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_svm.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/test_svm.dir/build: test_svm

.PHONY : CMakeFiles/test_svm.dir/build

CMakeFiles/test_svm.dir/requires: CMakeFiles/test_svm.dir/src/detect_lane_change.cpp.o.requires

.PHONY : CMakeFiles/test_svm.dir/requires

CMakeFiles/test_svm.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/test_svm.dir/cmake_clean.cmake
.PHONY : CMakeFiles/test_svm.dir/clean

CMakeFiles/test_svm.dir/depend:
	cd /home/zhuxiaohui/test_svm/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/zhuxiaohui/test_svm /home/zhuxiaohui/test_svm /home/zhuxiaohui/test_svm/build /home/zhuxiaohui/test_svm/build /home/zhuxiaohui/test_svm/build/CMakeFiles/test_svm.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/test_svm.dir/depend

