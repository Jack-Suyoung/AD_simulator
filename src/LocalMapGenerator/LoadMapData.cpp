#include "LoadMapData.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>

bool MapData::LoadMapData(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "파일을 열 수 없습니다: " << filename << std::endl;
        return false;
    }

    std::string line;
    bool is_first_line = true; // 첫 번째 줄을 확인하기 위한 변수

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string value;
        std::vector<double> row;

        // 첫 줄이 헤더인지 확인
        if (is_first_line) {
            is_first_line = false;
            if (!std::isdigit(line[0]) && line[0] != '-') { // 숫자가 아니라면 헤더로 간주하고 스킵
                continue;
            }
        }

        while (std::getline(ss, value, ',')) {
            try {
                row.push_back(std::stod(value)); // 숫자로 변환
            } catch (const std::invalid_argument& e) {
                std::cerr << "잘못된 데이터 감지 (변환 실패): " << value << std::endl;
                row.push_back(0.0); // 기본값 설정 (예외 발생 시 0.0 저장)
            } catch (const std::out_of_range& e) {
                std::cerr << "숫자 범위 초과: " << value << std::endl;
                row.push_back(0.0); // 기본값 설정
            }
        }

        if (row.size() == 6) {
            center_line.push_back({row[0], row[1]});
            left_lane.push_back({row[2], row[3]});
            right_lane.push_back({row[4], row[5]});
        } else {
            std::cerr << "잘못된 형식의 데이터가 포함됨: " << line << std::endl;
        }
    }

    file.close();
    return true;
}

// 데이터 출력 함수 구현
void MapData::PrintMapData() const {
    std::cout << "로드된 맵 데이터:" << std::endl;
    for (size_t i = 0; i < center_line.size(); ++i) {
        std::cout << "Center: (" << center_line[i].x << ", " << center_line[i].y << ") | "
                  << "Left: (" << left_lane[i].x << ", " << left_lane[i].y << ") | "
                  << "Right: (" << right_lane[i].x << ", " << right_lane[i].y << ")" << std::endl;
    }
}
