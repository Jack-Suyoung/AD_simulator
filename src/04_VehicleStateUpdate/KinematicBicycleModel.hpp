#ifndef KINEMATIC_BICYCLE_MODEL_HPP
#define KINEMATIC_BICYCLE_MODEL_HPP

class KinematicBicycleModel {
public:
    // 생성자
    KinematicBicycleModel();

    // 차량 상태 업데이트
    void Update(VehicleState_t *pstEgoState, double steering, double acceleration, double dt);

private:
};


#endif // KINEMATIC_BICYCLE_MODEL_HPP
