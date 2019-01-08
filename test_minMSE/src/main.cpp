#include <iostream>
#include <opencv2/opencv.hpp>
#include "minMSE.hpp"
#include <vector>
#include <deque>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <math.h>

const int image_rows = 600;
const int image_cols = 600;
const int lengt = 8;
MinMSE _min_mse;

float pre_trans_ratio(float former_ratio, float curr_ratio) {                                                
    float trans_curr_ratio = 0.0;
    if (curr_ratio < 0.3 && former_ratio > 0.75) {
        trans_curr_ratio = curr_ratio + 1;
    } else if (curr_ratio > 0.7 && former_ratio < 0.3) {
        trans_curr_ratio = curr_ratio - 1;
    } else {
        trans_curr_ratio = curr_ratio;
    }
    return trans_curr_ratio;
}

void plot (std::deque<float>& true_ratios) { 
    //RansacFitting ransac;
    std::deque<float> ratios;
    //srand((unsigned)time(NULL));
    for (int i = 0; i < lengt; ++i) {
        float ratio;
        ratio = 0.5 + (rand() % 10) / 100.0;
        if (i == 2 || i == 9 || i == 14) {
            ratio += 0.4;
        }
        if (i == 6 || i == 13) {
            ratio -= 0.3;
        }
        ratios.push_back(ratio); 
        //std::cout << (rand()%20) / 10.0 << std::endl;
        //pt.y = i * 1.5 + (rand() % 20) / 40.0; //* i;
        //pt.y = 0.1 * pow(pt.x, 2) + 0.1 * pt.x + 0.9 + (rand() % 20) / 40.0;
        //pt.weight = 1.0 / 20;
        //pts.push_back(pt);
        //std::cout << pt.x << "  " << pt.y << std::endl;
    }
    ratios = true_ratios;
    //solve 
    cv::Vec4f param;
    std::vector <float> useful_pts = _min_mse.do_minMSE_fitting(ratios, param);;
    std::cout << "a = " << param[0] << "  b = " << param[1] << "  c = " << param[2] << std::endl; 
    //draw
    cv::namedWindow("ransac-zhuxiaohui");
    cv::Mat img(image_rows, image_cols, CV_8UC3, cv::Scalar(48, 48, 48)); 
    for (unsigned i = 0; i < ratios.size(); ++i) {
        cv::circle(img, cv::Point2d(i * image_cols/lengt, 
                        ratios[i] * image_rows / 2 + 200), 3, CV_RGB(0, 255, 0), -1);
    }
    std::cout << "aa" << std::endl;
    for (unsigned i = 0; i < ratios.size()-1; ++i) {
        cv::Point pt1;
        cv::Point pt2;
        pt1.x = i * (image_cols / lengt);
        pt1.y = image_rows * (param[0] * pow(i, 2) + param[1] * pow(i, 1) + param[2]) / 2 + 200;
        pt2.x = (i+1) * (image_cols / lengt);
        pt2.y = image_rows * (param[0] * pow(i+1, 2) + param[1] * pow(i+1, 1) + param[2]) / 2 + 200;
        cv::line(img, pt1, pt2, cv::Scalar(0, 0, 255));
        std::cout << "bb" << std::endl;
    }
    cv::line(img, cv::Point2d(0, 100), cv::Point2d(600, 100), cv::Scalar(255, 0, 0));
    cv::line(img, cv::Point2d(0, 500), cv::Point2d(600, 500), cv::Scalar(255, 0, 0));
    std::cout << "cc" << std::endl;
    cv::imshow("ransac-zhuxiaohui", img);
    cv::waitKey(2000);
    //std::cout << "love you baby." << std::endl; 
    //return 0;
}

int main (int argc, char* argv[]) {
    //ransac.do_init(0.999999, 0.1, 8);
    srand((unsigned)time(NULL));
    //for (int i = 0; i < 5000; ++i) {
    //    plot();
    //}
    std::string dataname = argv[1];
    std::ifstream fin;
    fin.open(dataname, std::ios::in);
    std::vector<float> all_ratios;
    std::deque<float> curr_ratio;
    float rat;
    std::cout << "aa" << std::endl;
    while (fin) {
        fin >> rat;
        std::cout << rat << std::endl;
        all_ratios.push_back(rat);
    }
    //read done
    for (int i = 0; i < lengt; ++i) {
        curr_ratio.push_back(all_ratios[i]);
    }
    std::cout << "bb" << std::endl;
    for (int i = 8; i < 4000; ++i) {
        //plot(curr_ratio);
        std::deque<float> same_ratio;
        for (unsigned i = 0; i < curr_ratio.size(); ++i) {
            same_ratio.push_back(pre_trans_ratio(curr_ratio[curr_ratio.size()-1], curr_ratio[i]));
        }
        plot(same_ratio);
        curr_ratio.pop_front();
        curr_ratio.push_back(all_ratios[i]);
    }
    return 0;
}
