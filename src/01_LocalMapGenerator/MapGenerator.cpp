#include <iostream>

#include "../00_Common/CommonTypes.hpp"

#include "LoadMapData.hpp"
#include "MapGenerator.hpp"

void MapGenerator(MapInfo* pstLMGOutput)
{
    LoadMapData stLoadMapData;

    // CSV 파일 경로 설정
    std::string csv_file_path = "Data/mapdata/Straight_and_Arc_Lane_Data.csv";

    // LocalMapGenerator 객체 생성
    LocalMapGenerator local_map_gen(csv_file_path);

    // 지도 데이터 로드
    local_map_gen.LoadMap(stLoadMapData);


    // 출력 신호 저장
    pstLMGOutput->center_line = stLoadMapData.center_line;
    pstLMGOutput->left_lane = stLoadMapData.left_lane;
    pstLMGOutput->right_lane = stLoadMapData.right_lane;
}


