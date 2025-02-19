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
    ego_state_.WheelBase_m = 3.0;
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

    // 🔹 Local 좌표 -> Global 좌표 변환 (Visualizer용)
    ConvertLocalToGlobalPath();

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

// 🟢 로컬 좌표 -> 글로벌 좌표 변환 함수 (Visualizer용)
void SimulatorManager::ConvertLocalToGlobalPath() {
    viz_debug_.stPathPlanningGlobal.clear();

    for (const auto& local_point : planning_info_.stLocalPath) {
        Point global_point;
        double cos_theta = cos(-ego_state_.Global_Heading_rad);
        double sin_theta = sin(-ego_state_.Global_Heading_rad);

        global_point.x = ego_state_.Global_X_m + local_point.x * cos_theta - local_point.y * sin_theta;
        global_point.y = ego_state_.Global_Y_m + local_point.x * sin_theta + local_point.y * cos_theta;

        viz_debug_.stPathPlanningGlobal.push_back(global_point);
    }
}