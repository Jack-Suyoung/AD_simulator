#ifndef COMMON_TYPES_HPP
#define COMMON_TYPES_HPP

#include <vector>

// 공통 구조체 정의
struct Point {
    double x, y;
};

typedef struct tVehicleState{
    double Global_X_m;
    double Global_Y_m;
    double Global_Heading_rad;
    double FrontWhlAng_rad;
    double speed_mps;
    double WheelBase_m;
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
    std::vector<Point> stLocalPath;
}PlanningResults_t;

typedef struct tControlResults {
    double stStrCmd_rad;
    double stAccelCmd_mps2;
}ControlResults_t;

typedef struct tVizDebug {
    std::vector<Point> stPathPlanningGlobal;
}VizDebug_t;


#endif // COMMON_TYPES_HPP
