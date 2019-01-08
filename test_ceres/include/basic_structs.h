#ifndef BASIC_STRUCT_H
#define BASIC_STRUCT_H

#include <iostream>
#include <vector>
#include <math.h>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <Eigen/Core>
#include <Eigen/Dense>


namespace locz {

typedef Eigen::Matrix<double, 2, 1> Vector2d;
typedef Eigen::Matrix<double, 3, 1> Vector3d;
typedef Eigen::Matrix<double, 4, 1> Vector4d;

struct vec4d {
    float a;
    float b;
    float c;
    float d;
};

struct pose {
    double x;
    double y;
    double heading;
};

struct Point2d {
    double x;
    double y;
};

enum LaneType {
    dash = 0,
    solid = 1
};

struct Line {
    std::vector <Point2d> points;
    LaneType type;
    vec4d param;
};

struct percep {
    pose cur_pose;
    std::vector <Line> line_markings;
};

};

#endif
