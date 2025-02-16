

#include "00_Common/CommonTypes.hpp"
#include "KinematicBicycleModel.hpp"
#include "GlobalStateUpdater.hpp"

void VehicleStateUpdate(const ControlResults_t *pstControlInfo, VehicleState_t *pstEgoState)
{
    const double dt = 0.1; // 시간 간격 (100ms)

    // 모델 기반 업데이트 (추후 Localization 코드 추가해도 됨, 혹은 다른 모델 추가해도 됨)
    KinematicBicycleModel vehicle(pstEgoState->speed_mps, 3.0); // 차량 휠베이스 설정 (예: 2.5m)

    vehicle.UpdateLocal(pstControlInfo->stStrCmd_rad, pstControlInfo->stAccelCmd_mps2, dt);
    vehicle.PrintLocalState();


    // Global 좌표계 기준 차량 상태 업데이트
    GlobalStateUpdater global_state(pstEgoState->Global_X_m, pstEgoState->Global_Y_m, pstEgoState->Global_Heading_rad);

    global_state.UpdateGlobal(vehicle);
    global_state.PrintGlobalState();


    // 출력
    pstEgoState->Global_X_m += global_state.GetGlobalX();
    pstEgoState->Global_Y_m += global_state.GetGlobalY();
    pstEgoState->Global_Heading_rad += global_state.GetGlobalHeading();
    pstEgoState->FrontWhlAng_rad = pstControlInfo->stStrCmd_rad;
    pstEgoState->speed_mps += (pstControlInfo->stAccelCmd_mps2 * dt);
}