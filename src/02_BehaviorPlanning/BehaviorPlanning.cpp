#include <iostream>
#include <cmath>
#include <vector>

#include "../00_Common/CommonTypes.hpp"
#include "../00_Common/CommonFunc.hpp"

#include "BehaviorPlanning.hpp"

// Function Declaration
static Point TransformToLocal(const Point& global_point, const VehicleState_t& ego_state);

// Functino Definition
void BehaviorPlanning(const MapInfo* pstLMDoutput, VehicleState_t *pstEgoState, BehaviorInfo_t* pstBPoutput)
{
    const double f64LookAheadTime_s = 10.0;


    // Input Processing
    if (!pstLMDoutput || !pstEgoState || !pstBPoutput) {
        std::cerr << "Error: Null pointer received in BehaviorPlanning()" << std::endl;
        return;
    }

    // Core
    double f64LookAheadDist_m = pstEgoState->speed_mps * f64LookAheadTime_s;

    int s32ClosestIdx = FindClosestWaypoint(pstLMDoutput->center_line, pstEgoState->Global_X_m, pstEgoState->Global_Y_m);

    std::vector<Point> global_center_path, global_left_path, global_right_path;
    std::vector<Point> local_center_path, local_left_path, local_right_path;
    double accumulated_distance_m = 0.0;

    for (size_t i = s32ClosestIdx; i < pstLMDoutput->center_line.size() - 1; ++i) {
        double dx = pstLMDoutput->center_line[i + 1].x - pstLMDoutput->center_line[i].x;
        double dy = pstLMDoutput->center_line[i + 1].y - pstLMDoutput->center_line[i].y;
        double segment_distance_m = std::sqrt(dx * dx + dy * dy);
        accumulated_distance_m += segment_distance_m;

        if (accumulated_distance_m <= f64LookAheadDist_m) {
            // 전역 좌표 경로 저장
            global_center_path.push_back(pstLMDoutput->center_line[i]);
            global_left_path.push_back(pstLMDoutput->left_lane[i]);
            global_right_path.push_back(pstLMDoutput->right_lane[i]);

            // 로컬 좌표로 변환하여 저장
            local_center_path.push_back(TransformToLocal(pstLMDoutput->center_line[i], *pstEgoState));
            local_left_path.push_back(TransformToLocal(pstLMDoutput->left_lane[i], *pstEgoState));
            local_right_path.push_back(TransformToLocal(pstLMDoutput->right_lane[i], *pstEgoState));
        } else {
            break;
        }
    }

    // Output Processing
    pstBPoutput->stEgoLaneInfo.center_line = local_center_path;
    pstBPoutput->stEgoLaneInfo.left_lane = local_left_path;
    pstBPoutput->stEgoLaneInfo.right_lane = local_right_path;

    if(pstBPoutput->stEgoLaneInfo.center_line.size() != 0){
        std::cout << "BehaviroPlanner: 행동 계획 성공!" << std::endl;
    }

   // 결과 출력 (디버깅용)
//    std::cout << "Ego Speed (mps): " << pstEgoState->speed_mps << ", Lookahead Distance: " << f64LookAheadDist_m << "m\n";
//    std::cout << "Selected Path Points (Center Line, Left Lane, Right Lane): " << local_center_path.size() << " points\n";

//    for (size_t i = 0; i < local_center_path.size(); ++i) {
//        std::cout << "[Local Center] X: " << local_center_path[i].x << ", Y: " << local_center_path[i].y
//                  << " | [Local Left] X: " << local_left_path[i].x << ", Y: " << local_left_path[i].y
//                  << " | [Local Right] X: " << local_right_path[i].x << ", Y: " << local_right_path[i].y << std::endl;
//    }

}



// 전역 좌표 → 로컬 좌표 변환 함수
Point TransformToLocal(const Point& global_point, const VehicleState_t& ego_state) {
    double dx = global_point.x - ego_state.Global_X_m;
    double dy = global_point.y - ego_state.Global_Y_m;
    double cos_theta = std::cos(-ego_state.Global_Heading_rad);
    double sin_theta = std::sin(-ego_state.Global_Heading_rad);

    Point local_point;
    local_point.x = (dx * cos_theta) - (dy * sin_theta);
    local_point.y = (dx * sin_theta) + (dy * cos_theta);
    return local_point;
}