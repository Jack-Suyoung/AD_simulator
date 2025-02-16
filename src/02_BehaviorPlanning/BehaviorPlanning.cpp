#include <iostream>

#include "../01_LocalMapGenerator/LocalMapGeneratorInterface.hpp"

#include "BehaviorPlanningInterface.hpp"

// Function Declaration
static void BPOutputPreprocessing(const LocalMapData* pstLMDoutput, BehaviorInfo_t* pstBPoutput);



// Functino Definition
void BehaviorPlanning(const LocalMapData* pstLMDoutput, BehaviorInfo_t* pstBPoutput)
{
    // Input Processing

    // Core

    // Output Processing
    BPOutputPreprocessing(pstLMDoutput, pstBPoutput);
}

static void BPInputPreprocessing()
{

}

static void BPOutputPreprocessing(const LocalMapData* pstLMDoutput, BehaviorInfo_t* pstBPoutput)
{
    pstBPoutput->stEgoLaneInfo.center_line = pstLMDoutput->center_line;
    pstBPoutput->stEgoLaneInfo.left_lane = pstLMDoutput->left_lane;
    pstBPoutput->stEgoLaneInfo.right_lane = pstLMDoutput->right_lane;
}