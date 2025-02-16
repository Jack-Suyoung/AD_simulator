

#include "00_Common/CommonTypes.hpp"
#include "KinematicBicycleModel.hpp"

void VehicleStateUpdate(const ControlResults_t *pstControlInfo, VehicleState_t *pstEgoState)
{
    KinematicBicycleModel vehicle(2.5); // 차량 휠베이스 설정 (예: 2.5m)

    const double dt = 0.1; // 시간 간격 (100ms)

    vehicle.Update(pstControlInfo->stStrCmd, pstControlInfo->stAccelCmd, dt);

    vehicle.PrintState();
}