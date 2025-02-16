#include <iostream>
#include "SimulatorManager.hpp"

// 생성자: 초기 프레임을 0으로 설정
SimulatorManager::SimulatorManager() : current_frame_(0) {}

// 프레임을 1 증가시키는 함수
void SimulatorManager::Update() {
    current_frame_++;
}

// 현재 프레임을 반환하는 함수
int SimulatorManager::GetCurrentFrame() const {
    return current_frame_;
}

// 프레임을 초기화하는 함수
void SimulatorManager::Reset() {
    current_frame_ = 0;
}

// 현재 프레임을 출력하는 함수
void SimulatorManager::PrintFrame() const {
    std::cout << "Current Frame: " << current_frame_ << std::endl;
}
