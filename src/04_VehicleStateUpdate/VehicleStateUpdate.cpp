#include "00_Common/CommonTypes.hpp"
#include "KinematicBicycleModel.hpp"


void VehicleStateUpdate(const ControlResults_t *pstControlInfo, VehicleState_t *pstEgoState)
{
    const double dt = 0.1; // 시간 간격 (100ms)

    // 모델 기반 업데이트 (추후 Localization 코드 추가해도 됨, 혹은 다른 모델 추가해도 됨)
    KinematicBicycleModel vehicle; // 차량 휠베이스 설정 (예: 2.5m)

    vehicle.Update(pstEgoState, pstControlInfo->stStrCmd_rad, pstControlInfo->stAccelCmd_mps2, dt);
}