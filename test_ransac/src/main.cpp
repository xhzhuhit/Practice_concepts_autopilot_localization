#include <iostream>
#include <opencv2/opencv.hpp>
#include "ransac.hpp"
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <math.h>

const int image_rows = 600;
const int image_cols = 600;
RansacFitting ransac;

void plot () { 
    //RansacFitting ransac;
    std::vector<trjPoint> pts;
    //srand((unsigned)time(NULL));
    for (int i = 0; i < 20; ++i) {
        trjPoint pt;
        pt.x = i + (rand() % 20) / 40.0; 
        std::cout << (rand()%20) / 10.0 << std::endl;
        //pt.y = i * 1.5 + (rand() % 20) / 40.0; //* i;
        pt.y = 0.1 * pow(pt.x, 2) + 0.1 * pt.x + 0.9 + (rand() % 20) / 40.0;
        pt.weight = 1.0 / 20;
        pts.push_back(pt);
        std::cout << pt.x << "  " << pt.y << std::endl;
    }
    //solve 
    cv::Vec4f param;
    std::vector <trjPoint> useful_pts = ransac.ransac_fit_poly_weighted(pts, param);
    std::cout << "a = " << param[0] << "  b = " << param[1] << "  c = " << param[2] << std::endl; 
    //draw
    cv::namedWindow("ransac-zhuxiaohui");
    cv::Mat img(image_rows, image_cols, CV_8UC3, cv::Scalar(48, 48, 48)); 
    for (int i = 0; i < pts.size(); ++i) {
        cv::circle(img, cv::Point2d(pts[i].x * 20, pts[i].y * 20), 3, CV_RGB(0, 255, 0), -1);
    }
    std::cout << "aa" << std::endl;
    for (int i = 0; i < pts.size()-1; ++i) {
        cv::Point pt1;
        cv::Point pt2;
        pt1.x = pts[i].x * 20;
        pt1.y = 20 * (param[0] * pow(pts[i].x, 2) + param[1] * pow(pts[i].x, 1) + param[2]);
        pt2.x = pts[i+1].x * 20;
        pt2.y = 20 * (param[0] * pow(pts[i+1].x, 2) + param[1] * pow(pts[i+1].x, 1) + param[2]);
        cv::line(img, pt1, pt2, cv::Scalar(0, 0, 255));
        std::cout << "bb" << std::endl;
    }
    std::cout << "cc" << std::endl;
    cv::imshow("ransac-zhuxiaohui", img);
    cv::waitKey(2000);
    //std::cout << "love you baby." << std::endl; 
    //return 0;
}

int main (int argc, char* argv[]) {
    ransac.do_init(0.999999, 0.1, 8);
    srand((unsigned)time(NULL));
    for (int i = 0; i < 5000; ++i) {
        plot();
    }
    return 0;
}
