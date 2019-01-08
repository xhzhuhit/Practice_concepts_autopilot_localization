#include "../include/make_data.hpp"
#include "../include/optimization.hpp"
int main() {
    MakeData _mda;
    _mda.generate_data();
    std::cout << _mda.hd_line_markings.size() << "" << std::endl;  //locz::Line
    std::cout << _mda.perceptions.size() << std::endl;  //locz::percep
    
    ceres::Problem problem;
    ceres::LossFunction* loss = new ceres::CauchyLoss(0.2);
    
    //double pose[3];
    //double line_points[4];    
    //std::vector<double> pose;
    //locz::Vector2d pose;
    int count = 1;
    std::vector<double> line_points;
    std::vector<locz::percep> perceptions_bake = _mda.perceptions;
    for (size_t i = 0; i < _mda.perceptions.size(); ++i) {
        for (size_t j = 0; j < _mda.perceptions[i].line_markings.size(); ++j) {
            DistanceFromMapCost* dis_from_map_cost = new DistanceFromMapCost(
                            _mda.perceptions[i].line_markings[j].points[0].x,
                            _mda.perceptions[i].line_markings[j].points[0].y);
            cv::Point2d pt1;
            cv::Point2d pt2;
            for (size_t m = 0; m < _mda.hd_line_markings[j].points.size()-1; ++m) {
                if (_mda.hd_line_markings[j].points[m].x <= _mda.perceptions[i].cur_pose.x &&
                    _mda.hd_line_markings[j].points[m+1].x > _mda.perceptions[i].cur_pose.x) {
                    //line_points[0] = _mda.hd_line_markings[j].points[m].x;
                    //line_points[1] = _mda.hd_line_markings[j].points[m].y;
                    //line_points[2] = _mda.hd_line_markings[j].points[m+1].x;
                    //line_points[3] = _mda.hd_line_markings[j].points[m+1].y;
                        std::cout << "hdx: " << _mda.hd_line_markings[j].points[m].x << std::endl;
                        std::cout << "currx: " << _mda.perceptions[i].cur_pose.x << std::endl;
                        std::cout << "hdx+1: " << _mda.hd_line_markings[j].points[m+1].x << std::endl;
                    pt1.x = _mda.hd_line_markings[j].points[m].x;
                    pt1.y = _mda.hd_line_markings[j].points[m].y;
                    pt2.x = _mda.hd_line_markings[j].points[m+1].x;
                    pt2.y = _mda.hd_line_markings[j].points[m+1].y;
                    break;
                }
            }
            dis_from_map_cost->set_hd_points(pt1, pt2);
            std::cout << "mmp:  "  << i << "  " << j << std::endl;
            //std::cout << "mmp:  "  << _mda.perceptions[i].line_markings[j].points[0].x
            //        << "  " << _mda.perceptions[i].line_markings[j].points[0].y << std::endl;
            ceres::CostFunction* cost = new ceres::AutoDiffCostFunction<DistanceFromMapCost, 1, 1, 1>(
                            dis_from_map_cost);
                            //new DistanceFromMapCost(_mda.perceptions[i].line_markings[j].points[0].x,
                            //        _mda.perceptions[i].line_markings[j].points[0].y));
            //pose[0] = _mda.perceptions[i].cur_pose.x;
            //pose[1] = _mda.perceptions[i].cur_pose.y;
            //pose[2] = _mda.perceptions[i].cur_pose.heading;
            locz::Vector2d pda(_mda.perceptions[i].cur_pose.x, _mda.perceptions[i].cur_pose.y);
            locz::Vector2d& pose = pda;
            //pose.push_back(_mda.perceptions[i].cur_pose.heading);
            //std::cout << "avv:  "  << i << "  " << j << std::endl;

            //problem.AddResidualBlock(cost, NULL, pose.data(), line_points.data());
            //std::cout << "mda_x = " << _mda.perceptions[i].cur_pose.x << std::endl;
            //std::cout << "mda_y = " << _mda.perceptions[i].cur_pose.y << std::endl;
            problem.AddResidualBlock(cost, NULL, &(_mda.perceptions[i].cur_pose.x),
                            &(_mda.perceptions[i].cur_pose.y));
        }
    } 
        
    ceres::Solver::Options options;
    options.max_num_iterations = 500;
    options.linear_solver_type = ceres::DENSE_QR;
    ceres::Solver::Summary summary;
    ceres::Solve(options, &problem, &summary);

    std::cout << summary.BriefReport() << std::endl;
    for (size_t i = 0; i < _mda.perceptions.size(); ++i) {
        std::cout << "before: " << perceptions_bake[i].cur_pose.x << "  " 
                << perceptions_bake[i].cur_pose.y << std::endl; 
        std::cout << "after: " << _mda.perceptions[i].cur_pose.x << "  " 
                << _mda.perceptions[i].cur_pose.y << std::endl;
    }
    return 0;
}
