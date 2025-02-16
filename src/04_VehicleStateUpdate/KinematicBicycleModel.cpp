#include "KinematicBicycleModel.hpp"
#include <cmath>

KinematicBicycleModel::KinematicBicycleModel(double wheelbase)
    : x_(0.0), y_(0.0), heading_(0.0), velocity_(0.0), wheelbase_(wheelbase) {}

void KinematicBicycleModel::Update(double steering, double acceleration, double dt) {
    // Kinematic Bicycle Model 방정식 적용
    double beta = atan(0.5 * tan(steering)); // 단순 모델의 slip angle 보정

    x_ += velocity_ * cos(heading_ + beta) * dt;
    y_ += velocity_ * sin(heading_ + beta) * dt;
    heading_ += (velocity_ / wheelbase_) * tan(steering) * dt;
    velocity_ += acceleration * dt;
}

void KinematicBicycleModel::PrintState() const {
    std::cout << "X: " << x_ << ", Y: " << y_ 
              << ", Heading: " << heading_ << " rad, Velocity: " 
              << velocity_ << " mps" << std::endl;
}
