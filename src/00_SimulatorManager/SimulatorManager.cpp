#include "SimulatorManager.hpp"

// 생성자
SimulatorManager::SimulatorManager() : current_frame_(0) {}

// 초기화 함수
void SimulatorManager::Initialize() {
    // 01_ 맵 데이터 생성
    MapGenerator(&map_info_);

    // 초기 Ego 차량 상태 설정
    ego_state_.Global_X_m = map_info_.center_line[0].x + 1.0;
    ego_state_.Global_Y_m = map_info_.center_line[0].y + 1.0;
    ego_state_.Global_Heading_rad = atan2(
        map_info_.center_line[1].y - map_info_.center_line[0].y,
        map_info_.center_line[1].x - map_info_.center_line[0].x);
    ego_state_.speed_mps = 5.0;
}

// 한 프레임 실행
void SimulatorManager::Update() {
    VehicleState_t stLocalCurrentEgoState = {0};
    
    // 02_ 행동 계획
    BehaviorPlanning(&map_info_,  &ego_state_, &behavior_info_);

    // 03_ 경로 계획 및 차량 제어
    stLocalCurrentEgoState.FrontWhlAng_rad = ego_state_.FrontWhlAng_rad;
    stLocalCurrentEgoState.speed_mps = ego_state_.speed_mps;
    stLocalCurrentEgoState.Global_Heading_rad = 0.0; // Local
    stLocalCurrentEgoState.Global_X_m = 0.0; // Local
    stLocalCurrentEgoState.Global_Y_m = 0.0; // Local

    PlanningAndControl(&behavior_info_, &stLocalCurrentEgoState, &planning_info_, &control_info_);

    // 04_ 차량 상태 업데이트
    VehicleStateUpdate(&control_info_, &ego_state_);

    // 프레임 증가
    current_frame_++;
}

// 현재 프레임 출력
void SimulatorManager::PrintFrame() const {
    std::cout << "[Frame " << current_frame_ << "] "
              << "X: " << ego_state_.Global_X_m
              << ", Y: " << ego_state_.Global_Y_m
              << ", Heading: " << ego_state_.Global_Heading_rad
              << std::endl;
}
