#include <iostream>

#include "01_LocalMapGenerator/LocalMapGeneratorInterface.hpp"
#include "02_BehaviorPlanning/BehaviorPlanningInterface.hpp"

int main() {
    LocalMapData stMapInfo;
    BehaviorInfo_t stBehaviorInfo;

    // Main

    // 01_ Map Info Generator
    MapGenerator(&stMapInfo);

    // 02_Behavior Planning
    BehaviorPlanning(&stMapInfo, &stBehaviorInfo);


    // Viz
    return 0;
}