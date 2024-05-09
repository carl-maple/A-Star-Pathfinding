#include "AStarUtils.h"
#include "AStarDefs.h"
#include "AStarNodeList.h"

int32 AStarUtils::FillPath(const uint16 FirstGridIndex, const AStarNodeList* const InNodeList, uint16* OutPath)
{
    uint16 PathGridIndex = FirstGridIndex;
    int32 PathIndex = 0;

    while (PathGridIndex != NStarNodeDefs::INVALID_INDEX)
    {
        OutPath[PathIndex] = PathGridIndex;
        PathIndex++;
        PathGridIndex = InNodeList->GetAStarNode(PathGridIndex).Parent;
    }

    return PathIndex;
}