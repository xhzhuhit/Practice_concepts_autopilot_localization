#ifndef OPTIMIZATION_HPP
#define OPTIMIZATION_HPP

#include "basic_structs.h"
#include "ceres/ceres.h"
#include "gflags/gflags.h"
#include "glog/logging.h"
#include <opencv2/core.hpp>

#include <typeinfo>

class DistanceFromMapCost{
public:
    DistanceFromMapCost(double observe_x, double observe_y) : _observe_x(observe_x), 
        _observe_y(observe_y) {}    //_xx and _yy are observed data
    
    //calc distance
    template <typename T> T calc_dis_2_had(T& pt1_x,
                    T& pt1_y, T& pt2_x, T& pt2_y,
                    T& pose_x, T& pose_y) const {
        T k = T((pt2_y - pt1_y) / (pt2_x - pt1_x));
        std::cout << typeid(T).name() << std::endl; 
        std::cout << "k = " << k << std::endl;
        std::cout << "y = " << pt2_y - pt1_y << std::endl;
        std::cout << "x = " << pt2_x - pt1_x << std::endl;
        T dis = T(abs(pose_y - pt1_y - k * (pose_x - pt1_x)) / sqrt(T(1) + k * k));
        return dis;
    } 
    template <typename T> bool operator()(const T* const pose_xyyaw_1,
                    const T* const pose_xyyaw_2,
                    T* residual) const {
        //std::cout << "fuck: " << pose_xyyaw_1[0] << std::endl;
        std::cout << "ad: " << typeid(T).name() << std::endl;
        T pt1_x = static_cast<T>(_pt1.x);
        T pt1_y = static_cast<T>(_pt1.y);
        T pt2_x = static_cast<T>(_pt2.x);
        T pt2_y = static_cast<T>(_pt2.y);
        
        //Eigen::Matrix<T, 2, 1> dat((*pose_xyyaw)[0], (*pose_xyyaw)[1]);
        T pose_x = _observe_x - *pose_xyyaw_1;
        T pose_y = _observe_y - *pose_xyyaw_2;
        std::cout << "obbb: " << _pt1.x << "  " << _pt1.y << std::endl;
        //T pose_yaw = pose_xyyaw[2];
        std::cout << "bs: " << pt1_x << "  " << pt2_x << std::endl;
        std::cout << "bs: " << pt1_y << "  " << pt2_y << std::endl;
        T dis_to_hd = calc_dis_2_had(pt1_x, pt1_y, pt2_x, pt2_y, pose_x, pose_y);
        //T dis_to_hd = T(0.5);
        //std::cout << "pt1_x = " << pt1_x << std::endl; 
        std::cout << "dis_to_hd: " << dis_to_hd << std::endl;
        //std::cout << "obser = " << *pose_xyyaw_1 << std::endl;
        residual[0] = dis_to_hd; 
        return true;
    } 
    //x, y and theta are pose
    bool set_hd_points(cv::Point2d pt1, cv::Point2d pt2) {
        _pt1 = pt1;
        _pt2 = pt2;
    }
private:
    double _observe_x;
    double _observe_y;
    
    cv::Point2d _pt1;
    cv::Point2d _pt2;
};

#endif
