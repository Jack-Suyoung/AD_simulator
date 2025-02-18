#include <vector>
#include <cmath>
#include <vector>

#include "CommonTypes.hpp"
#include "CommonFunc.hpp"

int FindClosestWaypoint(const std::vector<Point>& waypoints, double ego_x, double ego_y) {
    int closest_index = 0;
    double min_distance = std::numeric_limits<double>::max();

    // Linear Search
    for (size_t i = 0; i < waypoints.size(); ++i) {
        double dx = ego_x - waypoints[i].x;
        double dy = ego_y - waypoints[i].y;
        double distance = std::sqrt(dx * dx + dy * dy);

        if (distance < min_distance) {
            min_distance = distance;
            closest_index = static_cast<int>(i);
        }
        else{
            // Do Nothing
        }
    }
    return closest_index;
}