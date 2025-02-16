#ifndef GLOBAL_STATE_UPDATER_HPP
#define GLOBAL_STATE_UPDATER_HPP

class GlobalStateUpdater {
public:
    // 생성자: 초기 위치와 방향 설정
    GlobalStateUpdater(double init_x, double init_y, double init_heading);

    // Global 좌표 업데이트
    void UpdateGlobal(const KinematicBicycleModel& local_state);

    // 현재 Global 상태 출력
    void PrintGlobalState() const;

    // Getter 함수
    double GetGlobalX() const { return global_x_; }
    double GetGlobalY() const { return global_y_; }
    double GetGlobalHeading() const { return global_heading_; }

private:
    double global_x_;       // Global X 좌표
    double global_y_;       // Global Y 좌표
    double global_heading_; // Global 헤딩
};

#endif // GLOBAL_STATE_UPDATER_HPP
