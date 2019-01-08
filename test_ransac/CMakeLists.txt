project(test_ransac)
cmake_minimum_required(VERSION 2.8)
IF(CMAKE_VERSION VERSION_GREATER "2.8.11")
  CMAKE_POLICY(SET CMP0022 OLD)
ENDIF()
message('project source dir' ${PROJECT_SOURCE_DIR})

add_definitions(-std=c++11)

include_directories(${PROJECT_SOURCE_DIR}/include)

find_package(OpenCV)

message("CMAKE_SOURCE_DIR is -----------------" ${CMAKE_SOURCE_DIR})

#/home/nvidia/liuxueqing/apollo/caffe-deeplab/.build_release/lib/libcaffe.a)

add_executable(test_ransac src/main.cpp)
target_link_libraries(test_ransac 
                    ${OpenCV_LIBS} 
                    dl )
