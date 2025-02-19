#ifndef SIMULATOR_MANAGER_HPP
#define SIMULATOR_MANAGER_HPP

#include <iostream>
#include <cmath>
#include "00_Common/CommonTypes.hpp"
#include "01_LocalMapGenerator/MapGenerator.hpp"
#include "02_BehaviorPlanning/BehaviorPlanning.hpp"
#include "03_PlanningAndControl/PlanningAndControl.hpp"
#include "04_VehicleStateUpdate/VehicleStateUpdate.hpp"

class SimulatorManager {
public:
    SimulatorManager();
    void Initialize();  // 초기화
    void Update();      // 한 프레임 실행
    void PrintFrame() const;

    // Getter 함수 (Visualizer에서 데이터 조회)
    int GetCurrentFrame() const { return current_frame_; }
    const VehicleState_t& GetVehicleState() const { return ego_state_; }
    const PlanningResults_t& GetPathResult() const { return planning_info_; } // 🔹 Path 정보 반환
    const MapInfo& GetMapInfo() const { return map_info_; } // 🔹 맵 정보 반환
    const VizDebug_t& GetVizDebug() const { return viz_debug_; }  // 🔹 Visualizer용 디버깅 데이터 반환

private:
    int current_frame_;  // 현재 프레임

    // 시뮬레이션에 필요한 데이터 구조체
    MapInfo map_info_;
    BehaviorInfo_t behavior_info_;
    PlanningResults_t planning_info_;
    ControlResults_t control_info_;
    VehicleState_t ego_state_;
    VizDebug_t viz_debug_;  // 🔹 Visualizer 디버깅 데이터

    void ConvertLocalToGlobalPath();  // 🔹 로컬 좌표 -> 글로벌 좌표 변환 함수
};

#endif // SIMULATOR_MANAGER_HPP
