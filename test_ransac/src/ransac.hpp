#ifndef LANE_DETECTION_RANSAC_H
#define LANE_DETECTION_RANSAC_H

#include <opencv2/opencv.hpp>
#include <time.h>
//#include "basic_struct.h"
//#include "localization/localization_matcher.hpp"

struct trjPoint {
    double x;
    double y;
    float weight;
    trjPoint(double x = 0.0, double y = 0, int weight = 0): x(x), y(y), weight(weight){}
};

class RansacFitting {
public:
    int do_init(float success_probability, float max_outliers, float thres) {
        _success_probability = success_probability;
        _max_outliers = max_outliers;
        _thres = thres;

        return 0;
    }

public:

    std::vector<trjPoint> ransac_fitting_weighted(const std::vector<trjPoint>& pts,
            cv::Vec4f& line_parameters) {
        if (pts.size() < 2) {
            std::vector<trjPoint> ret;
            line_parameters = cv::Vec4f(1, 1, 1, 1);
            return ret;
        }

        float numerator = log(1 - _success_probability);
        float denominator = log(1 - (1 - _max_outliers) * (1 - _max_outliers));
        int ransac_iter = ceil(numerator / denominator);

        srand((unsigned)time(NULL));
        int len = pts.size();

        // 1. search the best vec
        std::vector<cv::Point2f> candidates;
        float max_inliers = INT_MIN;
        cv::Vec4f vec;

        for (int i = 0; i < ransac_iter; ++i) {
            candidates.clear();

            // 1.1. find 2 points
            int idx1 = rand() % len;
            int idx2;

            while (1) {
                idx2 = rand() % len;

                if (idx1 != idx2) {
                    break;
                }
            }

            candidates.push_back(cv::Point2f(pts[idx1].x, pts[idx1].y));
            candidates.push_back(cv::Point2f(pts[idx2].x, pts[idx2].y));

            // 1.2. line fitting
            cv::fitLine(candidates, vec, CV_DIST_L2, 0, 0.01, 0.01);
            double tmp = vec.val[0];
            vec.val[0] = -vec.val[1];
            vec.val[1] = tmp;

            // 1.3. count inliers
            float count_inliers = 0;
            int count_all = 0;

            for (int i = 0; i < len; i++) {
                if (is_inlier_line(vec, cv::Point2f(pts[i].x, pts[i].y))) {
                    count_inliers += pts[i].weight;
                    ++count_all;
                }
            }

            // 1.4. find a max one
            if (count_inliers > max_inliers) {
                max_inliers = count_inliers;
                line_parameters = vec;
            }
        }

        // 2. re-ransac
        candidates.clear();
        std::vector<trjPoint> ret_pts;

        for (int i = 0; i < len; i++) {
            if (is_inlier_line(line_parameters, cv::Point2f(pts[i].x, pts[i].y))) {
                trjPoint pt = pts[i];
                //pt.pt.y = pts[i].pt.x;
                //pt.pt.x = pts[i].pt.y;
                ret_pts.push_back(pt);
                
                //change weight effects num of points, as final valuation turn out num of inner points  
                //need change weight into num of point
                for (int iter = 0; iter < pts[i].weight; ++iter) {
                    candidates.push_back(cv::Point2f(pts[i].x, pts[i].y));
                }

            }
        }

        if (candidates.size() >= 2) {
            cv::fitLine(candidates, vec, CV_DIST_L2, 0, 0.01, 0.01);
            double tmp = vec.val[0];
            vec.val[0] = -vec.val[1];
            vec.val[1] = tmp;

            line_parameters = vec;
        }

        return ret_pts;
    }
    
    
    std::vector<trjPoint> ransac_fit_poly_weighted(const std::vector<trjPoint>& pts,
            cv::Vec4f& poly_parameters) {
        if (pts.size() < 3) {
            std::vector<trjPoint> ret;
            poly_parameters = cv::Vec4f(1, 1, 1, 1);
            return ret;
        }

        // 1. determine the iteration times
        double numerator = log(1 - _success_probability);
        double denominator = log(1 - pow(1 - _max_outliers, 3));
        int ransac_num = ceil(numerator / denominator);
        //ransac_num = 5;

        srand((unsigned)time(NULL));
        int len = pts.size();

        int max_inliers = 0;

        std::vector<cv::Point2f> candidate_points;
        cv::Vec4f vec;

        // 2. iterate for poly fitting
        for (int iter = 0; iter < ransac_num; iter++) {
            candidate_points.clear();

            // 2.1. collect 3 points randomly
            for (int i = 0; i < 3; i++) {
                int idx = 0;

                while (1) {
                    bool flag = true;
                    idx = rand() % len;

                    for (int j = 0; j < candidate_points.size(); ++j) {
                        if (fabs(candidate_points[j].x - pts[idx].x) < 0.00001
                                && fabs(candidate_points[j].y - pts[idx].y) < 0.00001) {
                            flag == false;
                        }
                    }

                    if (flag == true) {
                        break;
                    }
                }

                candidate_points.push_back(cv::Point2f(pts[idx].x, pts[idx].y));
            }

            // 2.2. fitting
            calculate_parameters(vec, candidate_points, cv::DECOMP_LU);

            int count_inliers = 0;
            int count_all = 0;

            for (int i = 0; i < len; i++) {
                if (is_inlier_poly(vec, cv::Point2f(pts[i].x, pts[i].y))) {
                    count_inliers += pts[i].weight;
                    ++count_all;
                }
            }

            // 寻找内点概率最大的那一组解
            if (count_inliers > max_inliers) {
                max_inliers = count_inliers;
                poly_parameters = vec;
            }
        }

        // 利用那一组解再进行结果的更新
        candidate_points.clear();

        // 随机选取numForEstimate个点
        std::vector<trjPoint> ret_pts;

        for (int i = 0; i < len; i++) {
            if (is_inlier_poly(poly_parameters, cv::Point2f(pts[i].x, pts[i].y))) {
                trjPoint pt = pts[i];
                //pt.pt.y = pts[i].pt.x;
                //pt.pt.x = pts[i].pt.y;
                ret_pts.push_back(pt);

                for (int iter = 0; iter < pts[i].weight; ++iter) {
                    candidate_points.push_back(cv::Point2f(pts[i].x, pts[i].y));
                }
            }
        }

        if (candidate_points.size() >= 3) {
            calculate_parameters(vec, candidate_points, cv::DECOMP_SVD);
            poly_parameters = vec;

            return ret_pts;
        }
        //std::vector<trjPoint> ret;
        //return ret;
    }
    
    float get_dist(const cv::Vec4f& vec, const cv::Point2f& pt) {
        return fabs(vec[0] * (pt.x - vec[2]) + vec[1] * (pt.y - vec[3]));
    }

    float from_y_to_x(const cv::Vec4f& vec, const float& y) {
        // 1. since v0 * (y - v2) + v1 *(x - v3) = 0
        return -vec[0] / vec[1] * (y - vec[2]) + vec[3];
    }

private:
    // vertical vector + center point
    bool is_inlier_line(const cv::Vec4f& vec, const cv::Point2f& pt) {
        return get_dist(vec, pt) <= _thres;
    }

    bool is_inlier_poly(const cv::Vec4f& vec, const cv::Point2f& point) {
        // 1. an approximate method to calculate the distance
        float x = point.x;
        float y = vec[0] * x * x +
                  vec[1] * x +
                  vec[2];

        return fabs(y - point.y) <= _thres;
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
    float _success_probability;
    float _max_outliers;
    float _thres;
};

#endif
