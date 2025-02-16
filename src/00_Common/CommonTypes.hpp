#ifndef COMMON_TYPES_HPP
#define COMMON_TYPES_HPP

#include <vector>

// 공통 구조체 정의
struct Point {
    double x, y;
};

typedef struct tVehicleState{
    double X_m;
    double Y_m;
    double Heading_rad;
    double FrontWhlAng_rad;
    double speed_mps;
}VehicleState_t;

// Map Generator 표준 인터페이스
struct MapInfo {
    std::vector<Point> center_line; // 차로 중앙선
    std::vector<Point> left_lane;   // 좌측 차선
    std::vector<Point> right_lane;  // 우측 차선
};

// Behavior Planning 표준 인터페이스
typedef struct tEgoLane {
    std::vector<Point> center_line; // 차로 중앙선
    std::vector<Point> left_lane;   // 좌측 차선
    std::vector<Point> right_lane;  // 우측 차선
}EgoLane_t;

typedef struct tBehaviorInfo {
    EgoLane_t stEgoLaneInfo;
}BehaviorInfo_t;

// Planning And Control 표준 인터페이스
typedef struct tPlanningResults {
    std::vector<VehicleState_t> stLocalPath;
}PlanningResults_t;

typedef struct tControlResults {
    double stStrCmd;
    double stAccelCmd;
}ControlResults_t;

#endif // COMMON_TYPES_HPP
