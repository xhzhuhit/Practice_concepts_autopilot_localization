#ifndef MAKE_DATA_H
#define MAKE_DATA_H

#include "basic_structs.h"

class MakeData {
public:
    MakeData() {};
    ~MakeData() {};
    
    int _data_size;
    std::vector<locz::Line> hd_line_markings;
    std::vector<locz::percep> perceptions;
private:
    cv::RNG _rng;
public:
    bool generate_data() {
        //generate hd data
        for (size_t i = 0; i < 4; ++i) {
            locz::Line  linemark;
            linemark.param.a = 0.002;
            linemark.param.b = 0.01;
            linemark.param.a = 0.992;
            linemark.param.d = 0.5 + 3.75 * i;
            if (0 == i || 3 == i) {
                linemark.type = locz::solid;
            } else {
                linemark.type = locz::dash;
            }
            //generate points
            for (size_t j = 0; j < 20; ++j) {
                locz::Point2d pt;
                pt.x = j * 5;
                pt.y = linemark.param.a * pow(pt.x, 3) + linemark.param.b * pow(pt.x, 2) + 
                       linemark.param.c * pt.x + linemark.param.d;
               linemark.points.push_back(pt); 
            }
            hd_line_markings.push_back(linemark);
        } 
        //generate fake perception data
        for (size_t i = 0; i < 10; ++i) {
            locz::percep perception;
            locz::pose curr_pose;
            curr_pose.x = 2.0 + i * 9.0;
            curr_pose.y = 0.002 * pow(curr_pose.x, 3) + 0.01 * pow(curr_pose.x, 2) +
                    0.994 * curr_pose.x + 5.78;
            curr_pose.heading = 0.0;
            perception.cur_pose = curr_pose;

            //generate fake linemarking by hd and poses
            for (size_t j = 0; j < 4; ++j) {
                locz::Line line;
                locz::Point2d pt;
                pt.x = curr_pose.x;
                pt.y = hd_line_markings[j].param.a * pow(pt.x, 3) + 
                        hd_line_markings[j].param.b * pow(pt.x, 2) +
                        hd_line_markings[j].param.c * pt.x + 
                        hd_line_markings[j].param.d + _rng.uniform(0.0, 0.3);
                line.points.push_back(pt);
                if (0 == i || 3 == i) {
                    line.type = locz::solid;
                } else {
                    line.type = locz::dash;
                }
                perception.line_markings.push_back(line);
            }
            perceptions.push_back(perception);
        } 
        
        return true; 
    }

};

#endif
