#include <iostream>

#include "00_Common/CommonTypes.hpp"
#include "01_LocalMapGenerator/MapGenerator.hpp"
#include "02_BehaviorPlanning/BehaviorPlanning.hpp"
#include "03_PlanningAndControl/PlanningAndControl.hpp"
#include "04_VehicleStateUpdate/VehicleStateUpdate.hpp"

int main() {
    MapInfo stMapInfo;
    BehaviorInfo_t stBehaviorInfo;
    PlanningResults_t stPlanningInfo;
    ControlResults_t stControlInfo = {0};
    VehicleState_t stEgoState = {0};

    // Viz Window

    // 01_ Map Info Generator
    MapGenerator(&stMapInfo);

    // Initialize Ego State


    // while (1)
    // { 
        // Update Vehicle State

        // 02_Behavior Planning
        BehaviorPlanning(&stMapInfo, &stBehaviorInfo);

        // 03_Planning And Control
        PlanningAndControl(&stBehaviorInfo, &stPlanningInfo, &stControlInfo);

        //
        VehicleStateUpdate(&stControlInfo, &stEgoState);
        // Viz Draw
    // }

    return 0;
}