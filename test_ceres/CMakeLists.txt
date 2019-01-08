cmake_minimum_required(VERSION 2.8)
project(ceres)

find_package(Ceres REQUIRED)
find_package(OpenCV REQUIRED)

include_directories(${CERES_INCLUDE_DIRS})
include_directories($(OpenCV_INCLUDE_DIRS))
include_directories(/usr/include/eigen3/)

add_executable(use_ceres src/sample_ceres.cpp)
target_link_libraries(use_ceres ${CERES_LIBRARIES})

add_executable(localization src/loc_optima.cpp)
target_link_libraries(localization ${CERES_LIBRARIES}
        ${OpenCV_LIBRARIES})



