#ifndef KINEMATIC_BICYCLE_MODEL_HPP
#define KINEMATIC_BICYCLE_MODEL_HPP

#include <iostream>

class KinematicBicycleModel {
public:
    // 생성자
    KinematicBicycleModel(double wheelbase);

    // 차량 상태 업데이트 함수
    void Update(double steering, double acceleration, double dt);

    // 현재 차량 상태를 출력하는 함수
    void PrintState() const;

    // 차량 상태를 반환하는 함수
    double GetX() const { return x_; }
    double GetY() const { return y_; }
    double GetHeading() const { return heading_; }
    double GetVelocity() const { return velocity_; }
    
private:
    double x_;       // 위치 X
    double y_;       // 위치 Y
    double heading_; // 헤딩 각도 (rad)
    double velocity_; // 속도 (mps)
    double wheelbase_; // 휠베이스
};

#endif // KINEMATIC_BICYCLE_MODEL_HPP
