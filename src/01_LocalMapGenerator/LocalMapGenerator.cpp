#include <iostream>

#include "LocalMapGenerator.hpp"

void MapGenerator(LocalMapData* pstLMGOutput)
{
    // CSV 파일 경로 설정
    std::string csv_file_path = "Data/mapdata/Straight_and_Arc_Lane_Data.csv";

    // LocalMapGenerator 객체 생성
    LocalMapGenerator local_map_gen(csv_file_path);

    // 지도 데이터 로드드
    local_map_gen.LoadMap(*pstLMGOutput);
}

LocalMapGenerator::LocalMapGenerator(const std::string& map_file)
    : map_file_path(map_file) {}

bool LocalMapGenerator::LoadMap(LocalMapData& output_map) {
    MapData map_data;

    // CSV 파일에서 지도 데이터를 로드
    if (!map_data.LoadMapData(map_file_path)) {
        std::cerr << "LocalMapGenerator: 지도 데이터 로드 실패!" << std::endl;
        return false;
    }

    // MapData의 데이터를 LocalMapData 구조체로 변환하여 저장
    output_map.center_line = map_data.GetCenterLine();
    output_map.left_lane = map_data.GetLeftLane();
    output_map.right_lane = map_data.GetRightLane();

    std::cout << "LocalMapGenerator: 지도 데이터 로드 성공!" << std::endl;
    return true;
}
