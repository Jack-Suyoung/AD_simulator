#include "KinematicBicycleModel.hpp"
#include <cmath>

KinematicBicycleModel::KinematicBicycleModel(double speed_mps, double wheelbase)
    : local_x_(0.0), local_y_(0.0), local_heading_(0.0),
      velocity_(speed_mps), wheelbase_(wheelbase) {}

// 로컬 좌표계에서 차량 상태 업데이트
void KinematicBicycleModel::UpdateLocal(double steering, double acceleration, double dt) {
    double beta = atan(0.5 * tan(steering)); // Slip angle 보정

    local_x_ += velocity_ * cos(local_heading_ + beta) * dt;
    local_y_ += velocity_ * sin(local_heading_ + beta) * dt;
    local_heading_ += (velocity_ / wheelbase_) * tan(steering) * dt;
    velocity_ += acceleration * dt;
}

// 로컬 상태 출력
void KinematicBicycleModel::PrintLocalState() const {
    std::cout << "Local -> X: " << local_x_ << ", Y: " << local_y_ 
              << ", Heading: " << local_heading_ << " rad, Velocity: " 
              << velocity_ << " mps" << std::endl;
}
