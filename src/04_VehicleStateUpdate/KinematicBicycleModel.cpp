#include <cmath>

#include "../00_Common/CommonTypes.hpp"
#include "../00_Common/CommonFunc.hpp"

#include "KinematicBicycleModel.hpp"

// 기본 생성자 구현
KinematicBicycleModel::KinematicBicycleModel() {
    // 초기화할 멤버 변수가 없으면 비워둘 수 있음
}

void KinematicBicycleModel::Update(VehicleState_t *pstEgoState, double steering, double acceleration, double dt) {
    //double beta = atan(0.5 * tan(steering)); // Slip angle 보정

    pstEgoState->Global_X_m += pstEgoState->speed_mps * cos(pstEgoState->Global_Heading_rad) * dt;
    pstEgoState->Global_Y_m += pstEgoState->speed_mps  * sin(pstEgoState->Global_Heading_rad) * dt;
    pstEgoState->Global_Heading_rad += (pstEgoState->speed_mps / pstEgoState->WheelBase_m) * tan(steering) * dt;
    pstEgoState->FrontWhlAng_rad = steering;
    pstEgoState->speed_mps += acceleration * dt;
}

