#include <iostream>

#include "../00_Common/CommonTypes.hpp"

#include "BehaviorPlanning.hpp"

// Function Declaration
static void BPOutputPreprocessing(const MapInfo* pstLMDoutput, BehaviorInfo_t* pstBPoutput);



// Functino Definition
void BehaviorPlanning(const MapInfo* pstLMDoutput, BehaviorInfo_t* pstBPoutput)
{
    // Input Processing

    // Core

    // Output Processing
    BPOutputPreprocessing(pstLMDoutput, pstBPoutput);
}

static void BPInputPreprocessing()
{

}

static void BPOutputPreprocessing(const MapInfo* pstLMDoutput, BehaviorInfo_t* pstBPoutput)
{
    pstBPoutput->stEgoLaneInfo.center_line = pstLMDoutput->center_line;
    pstBPoutput->stEgoLaneInfo.left_lane = pstLMDoutput->left_lane;
    pstBPoutput->stEgoLaneInfo.right_lane = pstLMDoutput->right_lane;

    std::cout << "BehaviroPlanner: 행동 계획 성공!" << std::endl;
}