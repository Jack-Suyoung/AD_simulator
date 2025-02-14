#ifndef LOADMAPDATA_H
#define LOADMAPDATA_H

#include <vector>
#include <string>


// 좌표 구조체
struct Point {
    double x, y;
};

// MapData 클래스 정의
class MapData {
public:
    MapData() = default; // 기본 생성자
    bool LoadMapData(const std::string& filename); // CSV 데이터 로드
    void PrintMapData() const; // 데이터 출력

private:
    std::vector<Point> center_line; // 차로 중앙
    std::vector<Point> left_lane;   // 좌측 차선
    std::vector<Point> right_lane;  // 우측 차선
};

#endif