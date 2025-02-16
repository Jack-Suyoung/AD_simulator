#ifndef SIMULATOR_MANAGER_HPP
#define SIMULATOR_MANAGER_HPP


class SimulatorManager {
public:
    // 생성자
    SimulatorManager();

    // 프레임을 증가시키는 함수
    void Update();

    // 현재 프레임을 반환하는 함수
    int GetCurrentFrame() const;

    // 시뮬레이터를 초기화하는 함수
    void Reset();

    // 현재 프레임을 출력하는 함수
    void PrintFrame() const;

private:
    int current_frame_; // 현재 프레임 저장 변수
};

#endif // SIMULATOR_MANAGER_HPP
