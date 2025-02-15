#ifndef LOCAL_MAP_GENERATOR_INTERFACE_H
#define LOCAL_MAP_GENERATOR_INTERFACE_H

#include <vector>

#include "../00_Common/CommonTypes.hpp"

// 인터페이스에서 사용할 지도 데이터 구조체
struct LocalMapData {
    std::vector<Point> center_line; // 차로 중앙선
    std::vector<Point> left_lane;   // 좌측 차선
    std::vector<Point> right_lane;  // 우측 차선
};

void MapGenerator(LocalMapData* pstLMGOutput);

#endif // LOCAL_MAP_GENERATOR_INTERFACE_H
