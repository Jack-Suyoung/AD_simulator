#ifndef LOCAL_MAP_GENERATOR_H
#define LOCAL_MAP_GENERATOR_H

#include "LocalMapGeneratorInterface.hpp"
#include "LoadMapData.hpp" // MapData 클래스를 사용

    
class LocalMapGenerator
{
public:
    LocalMapGenerator(const std::string& map_file);
    bool LoadMap(LocalMapData& output_map);

private:
    std::string map_file_path;
};

#endif // LOCAL_MAP_GENERATOR_H
