#ifndef LOADMAPDATA_H
#define LOADMAPDATA_H

#include <vector>
#include <string>

#include "../common/CommonTypes.hpp"


// MapData 클래스 정의
class MapData {
public:
    MapData() = default; // 기본 생성자
    bool LoadMapData(const std::string& filename); // CSV 데이터 로드
    void PrintMapData() const; // 데이터 출력

    // Getter 함수 추가 (멤버 변수 직접 접근 방지)
    const std::vector<Point>& GetCenterLine() const {return center_line;}
    const std::vector<Point>& GetLeftLane() const {return left_lane;}
    const std::vector<Point>& GetRightLane() const {return right_lane;}

private:
    std::vector<Point> center_line; // 차로 중앙
    std::vector<Point> left_lane;   // 좌측 차선
    std::vector<Point> right_lane;  // 우측 차선
};

#endif