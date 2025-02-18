#include <iostream>
#include <cmath>
#include <vector>

#include "../00_Common/CommonTypes.hpp"
#include "../00_Common/CommonFunc.hpp"

#include "00_Common/CommonTypes.hpp"
#include "LateralControl.hpp"


// Target Point 찾기 
int FindTargetPoint(const std::vector<Point>& path, double lookahead_distance) {
    double accumulated_distance = 0.0;
    int target_index = 0;

    for (size_t i = 0; i < path.size() - 1; ++i) {
        double dx = path[i + 1].x - path[i].x;
        double dy = path[i + 1].y - path[i].y;
        double segment_distance = std::sqrt(dx * dx + dy * dy);
        accumulated_distance += segment_distance;

        if (accumulated_distance >= lookahead_distance) {
            target_index = i + 1;
            break;
        }
    }
    return target_index;
}

// Stanley Controller 함수
double StanleyControl(const PlanningResults_t* path_result, const VehicleState_t* ego_state, double k, double v0) {
    if (!path_result || !ego_state) {
        std::cerr << "Error: Null pointer received in StanleyControl()" << std::endl;
        return 0.0;
    }

    // 속도 x 0.6초 후의 Target Point 찾기
    double lookahead_distance = ego_state->speed_mps * 0.6;
    int target_index = FindTargetPoint(path_result->stLocalPath, lookahead_distance);
    if (target_index >= path_result->stLocalPath.size() - 1) return 0.0;

    // Reference Path 방향 벡터 계산
    Point target_point = path_result->stLocalPath[target_index];
    Point next_target_point = path_result->stLocalPath[target_index + 1];

    double path_dx = next_target_point.x - target_point.x;
    double path_dy = next_target_point.y - target_point.y;
    double path_heading = atan2(path_dy, path_dx); // Reference Path의 진행 방향

    // Ego 차량의 Heading Error (차량 진행 방향과 Reference Path 방향 차이)
    double heading_error = ego_state->Global_Heading_rad - path_heading;
    while (heading_error > M_PI) heading_error -= 2 * M_PI;
    while (heading_error < -M_PI) heading_error += 2 * M_PI;

    // Cross Track Error (Ego 차량과 Target Point 간 거리)
    double dx = ego_state->Global_X_m - target_point.x;
    double dy = ego_state->Global_Y_m - target_point.y;
    double cross_track_error = dx * sin(path_heading) - dy * cos(path_heading);

    // Stanley Control Law 적용
    double velocity = ego_state->speed_mps;
    double steering_angle = heading_error + atan2(k * cross_track_error, velocity + v0);

    // Steering Angle 제한 (-30도 ~ +30도)
    double max_steer = M_PI / 6;  // 30도 (rad 단위)
    if (steering_angle > max_steer) steering_angle = max_steer;
    if (steering_angle < -max_steer) steering_angle = -max_steer;

    return steering_angle;
}