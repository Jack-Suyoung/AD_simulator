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

private:
    int current_frame_;  // 현재 프레임

    // 시뮬레이션에 필요한 데이터 구조체
    MapInfo map_info_;
    BehaviorInfo_t behavior_info_;
    PlanningResults_t planning_info_;
    ControlResults_t control_info_;
    VehicleState_t ego_state_;
};

#endif // SIMULATOR_MANAGER_HPP
