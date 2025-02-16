#ifndef BEHAVIOR_PLANNING_INTERFACE_H
#define BEHAVIOR_PLANNING_INTERFACE_H

#include <vector>

#include "../00_Common/CommonTypes.hpp"

typedef struct tEgoLane {
    std::vector<Point> center_line; // 차로 중앙선
    std::vector<Point> left_lane;   // 좌측 차선
    std::vector<Point> right_lane;  // 우측 차선
}EgoLane_t;

typedef struct tBehaviorInfo {
    EgoLane_t stEgoLaneInfo;
}BehaviorInfo_t;

void BehaviorPlanning(const LocalMapData* pstLMDoutput, BehaviorInfo_t* pstBPoutput);

#endif // BEHAVIOR_PLANNING_INTERFACE_H
