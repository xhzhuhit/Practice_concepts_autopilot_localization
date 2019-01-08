#ifndef MINMSE_H
#define MINMSE_H

#include <opencv2/opencv.hpp>
#include <deque>
class MinMSE {
public:
    MinMSE():_threshold(0.12) {};
    ~MinMSE() {};
    
public:
    std::vector<float> do_minMSE_fitting(std::deque<float>& ratios, cv::Vec4f& param) {
        int sz = ratios.size();
        std::vector<float> useful_ratios;
        float minmse = 10000.0;
        int max_inner_points_num = 0;
        cv::Vec4f vec;
        for (int i = 0; i < sz-2; ++i) {
            for (int j = i+1; j < sz-1; ++j) {
                for (int k = j+1; k < sz; ++k) {
                    std::vector<cv::Point2f> candidate_points;
                    candidate_points.push_back(cv::Point2f(i, ratios[i]));
                    candidate_points.push_back(cv::Point2f(j, ratios[j]));
                    candidate_points.push_back(cv::Point2f(k, ratios[k]));
                    int inner_points_num = 0;
                    float tmp = calc_minMSE(candidate_points, ratios, vec, inner_points_num);
                    //std::cout << i << "\t" << j << "\t" << k << "\t" << tmp << std::endl;
                    std::cout << "inner_points_num: " << inner_points_num << std::endl;
                    if (inner_points_num > max_inner_points_num ||
                                    (inner_points_num == max_inner_points_num && tmp < minmse)) {
                        max_inner_points_num = inner_points_num;
                        minmse = tmp;
                        param = vec;
                        std::cout << "minmse: " << minmse << std::endl;
                        useful_ratios.clear();
                        useful_ratios.push_back(ratios[i]);
                        useful_ratios.push_back(ratios[j]);
                        useful_ratios.push_back(ratios[k]);
                    }
                }
            }
        } 
        return useful_ratios;
    }

private:
    float calc_minMSE(std::vector<cv::Point2f>& candidate_points, 
                    std::deque<float>& ratios,
                    cv::Vec4f& param,
                    int& inner_points_num) {
        //cv::Vec4f param;
        float mse = 0;
        calculate_parameters(param, candidate_points, cv::DECOMP_SVD);
        for (int i = 0; i < ratios.size(); ++i) {
            //std::cout << "ratio comp: " << param[0] * i * i + param[1] * i + param[2]
            //        << "\t" << ratios[i] << std::endl
            float delta_ratio = fabs((param[0] * i * i + param[1] * i + param[2]) - ratios[i]);
            if (delta_ratio <= _threshold) {
                ++inner_points_num;
                mse += delta_ratio;
            }
        } 
        //cv::fitLine(candidate_points, param, CV_DIST_L2, 0, 0.01, 0.01);
        //for (int i = 0; i < ratios.size(); ++i) {
        //    mse += fabs((param[0] * i + param[1]) - ratios[i]);
        //} 
        return mse;
    }
    int calculate_parameters(cv::Vec4f& vec, const std::vector<cv::Point2f>& pts,
                                          const int& solve_type) {
        // 1. fill A and b
        cv::Mat A(pts.size(), 3, CV_32FC1);
        cv::Mat b(pts.size(), 1, CV_32FC1);
        cv::Mat x(3, 1, CV_32FC1);
        for (int i = 0; i < pts.size(); i++) {
            b.at<float>(i, 0) = pts[i].y;
            for (int j = 0; j < 3; j++) {
                A.at<float>(i, j) = pow(pts[i].x, 2 - j);
            }
        }
         
        // 2. calculate vec according Ax=b
        solve(A, b, x, solve_type);
         
        for (int i = 0; i < 3; i++) {
            vec.val[i] = x.at<float>(i, 0);
        }
         
        return 0;
    }
private:
    float _threshold;
};
#endif
