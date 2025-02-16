#include <cmath>
#include <iostream>

#include "KinematicBicycleModel.hpp"
#include "GlobalStateUpdater.hpp"

GlobalStateUpdater::GlobalStateUpdater(double init_x, double init_y, double init_heading)
    : global_x_(init_x), global_y_(init_y), global_heading_(init_heading) {}

// Global 좌표 업데이트
void GlobalStateUpdater::UpdateGlobal(const KinematicBicycleModel& local_state) {
    double local_x = local_state.GetLocalX();
    double local_y = local_state.GetLocalY();
    double local_heading = local_state.GetLocalHeading();

    // 로컬 좌표를 Global 좌표로 변환
    global_x_ += local_x * cos(global_heading_) - local_y * sin(global_heading_);
    global_y_ += local_x * sin(global_heading_) + local_y * cos(global_heading_);
    global_heading_ += local_heading;

    // 로컬 상태 초기화 (새로운 업데이트를 위해)
}

// Global 상태 출력
void GlobalStateUpdater::PrintGlobalState() const {
    std::cout << "Global -> X: " << global_x_ << ", Y: " << global_y_ 
              << ", Heading: " << global_heading_ << " rad" << std::endl;
}
