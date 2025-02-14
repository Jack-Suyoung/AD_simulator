#include <iostream>

#include "LocalMapGenerator/LoadMapData.hpp"

int main() {
    
    // Map Load
    MapData map;
    
    // CSV 파일 경로 설정 (상대 경로)
    std::string csv_file_path = "mapdata/Straight_and_Arc_Lane_Data.csv";
    
    // 맵 데이터 로드
    if (map.LoadMapData(csv_file_path)) {
        std::cout << "맵 데이터 로드 성공!" << std::endl;
        map.PrintMapData(); // 데이터 출력
    } else {
        std::cerr << "맵 데이터를 불러오는 데 실패했습니다." << std::endl;
    }
    
    // Main


    // Viz
    return 0;
}