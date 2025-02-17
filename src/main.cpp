#include "00_SimulatorManager/SimulatorManager.hpp"
#include "05_Visualizer/Visualizer.hpp"

int main() {
    // 시뮬레이터 및 비주얼라이저 초기화
    SimulatorManager simulator;
    simulator.Initialize();
    
    Visualizer visualizer;

    // 비주얼라이저 실행 (시뮬레이터와 연동)
    visualizer.Run(simulator);

    return 0;
}
