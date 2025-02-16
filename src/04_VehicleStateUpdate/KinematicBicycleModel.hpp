#ifndef KINEMATIC_BICYCLE_MODEL_HPP
#define KINEMATIC_BICYCLE_MODEL_HPP

#include <iostream>

class KinematicBicycleModel {
public:
    // 생성자
    KinematicBicycleModel(double speed_mps, double wheelbase);

    // 차량 상태 업데이트 (로컬)
    void UpdateLocal(double steering, double acceleration, double dt);

    // 현재 상태 출력
    void PrintLocalState() const;

    // Getter 함수
    double GetLocalX() const { return local_x_; }
    double GetLocalY() const { return local_y_; }
    double GetLocalHeading() const { return local_heading_; }
    double GetVelocity() const { return velocity_; }

private:
    double local_x_, local_y_, local_heading_; // 로컬 좌표
    double velocity_; // 속도
    double wheelbase_; // 휠베이스
};

#endif // KINEMATIC_BICYCLE_MODEL_HPP
