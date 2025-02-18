#include <iostream>
#include <cmath>
#include <vector>
#include <Eigen/Dense>

#include "../00_Common/CommonTypes.hpp"
#include "../00_Common/CommonFunc.hpp"

#include "LateralControl.hpp"
#include "PlanningAndControl.hpp"

static void PathPlanning(const BehaviorInfo_t* behavior_info, const VehicleState_t* ego_state, PlanningResults_t* path_result);



void PlanningAndControl(const BehaviorInfo_t* pstBPInfo, VehicleState_t* ego_state, PlanningResults_t* pstPlanningInfo, ControlResults_t* pstControlInfo)
{
    // Planning
    
    // Path Planning
    PathPlanning(pstBPInfo, ego_state, pstPlanningInfo);

    // Speed Planning

    // Control
    // Path Control
    pstControlInfo->stStrCmd_rad = StanleyControl(pstPlanningInfo, ego_state, 1.5, 2.0);

    // Speed Control
    pstControlInfo->stAccelCmd_mps2 = 0.0;
}

class QuinticPolynomial{
    public:
        Eigen::VectorXd coeffs;

        QuinticPolynomial(double x0, double dx0, double ddx0, 
            double xT, double dxT, double ddxT, double T){
                Eigen::MatrixXd A(6, 6);
                Eigen::VectorXd b(6);

                A << 1, 0, 0, 0, 0, 0,
                0, 1, 0, 0, 0, 0,
                0, 0, 2, 0, 0, 0,
                1, T, T*T, T*T*T, T*T*T*T, T*T*T*T*T,
                0, 1, 2*T, 3*T*T, 4*T*T*T, 5*T*T*T*T,
                0, 0, 2, 6*T, 12*T*T, 20*T*T*T;
   
                b << x0, dx0, ddx0, xT, dxT, ddxT;

                coeffs = A.colPivHouseholderQr().solve(b);  // 5차 다항식 계수 계산
            }

    double evaluate(double t) {
        return coeffs(0) + coeffs(1) * t + coeffs(2) * t*t + coeffs(3) * t*t*t +
               coeffs(4) * t*t*t*t + coeffs(5) * t*t*t*t*t;
    }
};

// Path Planning 함수
static void PathPlanning(const BehaviorInfo_t* behavior_info, const VehicleState_t* ego_state, PlanningResults_t* path_result) {
    const double f64LookAheadTime_s = 3.0;


    if (!behavior_info || !ego_state || !path_result) {
        std::cerr << "Error: Null pointer received in PathPlanning()" << std::endl;
        return;
    }

    // 현재 Ego 차량 위치에서 가장 가까운 Center Line 점 찾기
    int closest_index = FindClosestWaypoint(behavior_info->stEgoLaneInfo.center_line, ego_state->Global_X_m, ego_state->Global_Y_m);
    if (closest_index >= behavior_info->stEgoLaneInfo.center_line.size() - 1) return;

    // 속도(mps) × 0.6초 후의 Goal Point 찾기
    double lookahead_distance = ego_state->speed_mps * f64LookAheadTime_s;
    double accumulated_distance = 0.0;
    int goal_index = closest_index;

    for (size_t i = closest_index; i < behavior_info->stEgoLaneInfo.center_line.size() - 1; ++i) {
        double dx = behavior_info->stEgoLaneInfo.center_line[i + 1].x - behavior_info->stEgoLaneInfo.center_line[i].x;
        double dy = behavior_info->stEgoLaneInfo.center_line[i + 1].y - behavior_info->stEgoLaneInfo.center_line[i].y;
        double segment_distance = std::sqrt(dx * dx + dy * dy);
        accumulated_distance += segment_distance;

        if (accumulated_distance >= lookahead_distance) {
            goal_index = i + 1;
            break;
        }
    }

    // Goal Point 설정
    Point goal_point = behavior_info->stEgoLaneInfo.center_line[goal_index];

    // Ego 차량의 초기 N 값 계산 (Reference Path 대비)
    double ref_x = behavior_info->stEgoLaneInfo.center_line[closest_index].x;
    double ref_y = behavior_info->stEgoLaneInfo.center_line[closest_index].y;
    double ref_theta = atan2(
        behavior_info->stEgoLaneInfo.center_line[closest_index + 1].y - ref_y,
        behavior_info->stEgoLaneInfo.center_line[closest_index + 1].x - ref_x
    );

    double dx = ego_state->Global_X_m - ref_x;
    double dy = ego_state->Global_Y_m - ref_y;
    double n_ego = -dx * sin(ref_theta) + dy * cos(ref_theta); // N 방향 거리 계산


    // Ego 차량 기준 좌표 변환 (S-N 좌표계)
    double s_ego = 0.0;  // Ego 차량의 초기 S 위치
    double s_goal = accumulated_distance;
    double n_goal = 0.0;  // Reference Path에 수렴해야 하므로 N=0으로 설정

    // 5차 다항식 경로 생성
    double T = 3.0;  // 목표 지점까지 도달하는 시간 (3초)
    QuinticPolynomial quintic_poly(n_ego, 0, 0, n_goal, 0, 0, T);

    // S-N 좌표계 경로 생성
    std::vector<Point> sn_path;
    for (double t = 0; t <= T; t += 0.1) {
        double s = (s_goal / T) * t;  // S 값은 선형적으로 증가
        double n = quintic_poly.evaluate(t);
        sn_path.push_back({s, n});
    }

    // S-N 경로를 X-Y 좌표로 변환
    std::vector<Point> xy_path;
    for (const auto& sn_point : sn_path) {
        int ref_index = closest_index;
        for (size_t i = closest_index; i < behavior_info->stEgoLaneInfo.center_line.size() - 1; ++i) {
            double dx = behavior_info->stEgoLaneInfo.center_line[i + 1].x - behavior_info->stEgoLaneInfo.center_line[i].x;
            double dy = behavior_info->stEgoLaneInfo.center_line[i + 1].y - behavior_info->stEgoLaneInfo.center_line[i].y;
            double segment_distance = std::sqrt(dx * dx + dy * dy);

            if (sn_point.x <= segment_distance) {
                ref_index = i;
                break;
            }
        }

        double x_base = behavior_info->stEgoLaneInfo.center_line[ref_index].x;
        double y_base = behavior_info->stEgoLaneInfo.center_line[ref_index].y;
        double theta_base = atan2(
            behavior_info->stEgoLaneInfo.center_line[ref_index + 1].y - y_base,
            behavior_info->stEgoLaneInfo.center_line[ref_index + 1].x - x_base
        );

        Point xy_point;
        xy_point.x = x_base + sn_point.x * cos(theta_base) - sn_point.y * sin(theta_base);
        xy_point.y = y_base + sn_point.x * sin(theta_base) + sn_point.y * cos(theta_base);
        xy_path.push_back(xy_point);
    }

    // 결과 저장
    path_result->stLocalPath = xy_path;

    // 디버깅 출력
    std::cout << "Path Planning Completed: " << xy_path.size() << " points\n";
    for (const auto& p : xy_path) {
        std::cout << "X: " << p.x << ", Y: " << p.y << std::endl;
    }
}