#include "AStarUtils.h"
#include "AStarDefs.h"
#include "AStarNodeList.h"
#include "AStarMap.h"
#include "AStarWorker.h"

#include "vector"
#include "iostream"

int32 AStarUtils::FillPath(const uint16 FirstGridIndex
    , const std::unique_ptr<AStarNodeList>& InNodeList, std::vector<uint16>& OutPath)
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

void AStarUtils::PrintResult(const int32 PathLength, const std::unique_ptr<AStarMap>& InMap
    , const std::unique_ptr<AStarWorker>& InWorker, const std::vector<uint16>& InPath
    , std::vector<char> InPathDrawMap)
{
    if (PathLength > 0)
    {
        const uint16 StartGridIndex = InMap->GetGridIndex(InWorker->GetStartPos());
        const uint16 GoalGridIndex = InMap->GetGridIndex(InWorker->GetGoalPos());

        std::cout << "StartGridIndex: " << StartGridIndex << std::endl;
        std::cout << "GoalGridIndex: " << GoalGridIndex << std::endl;

        for (int32 PathIndex = PathLength - 1; PathIndex >= 0; PathIndex--)
        {
            if (StartGridIndex == InPath[PathIndex])
            {
                InPathDrawMap[InPath[PathIndex]] = 'S';
            }
            else if (GoalGridIndex == InPath[PathIndex])
            {
                InPathDrawMap[InPath[PathIndex]] = 'G';
            }
            else
            {
                InPathDrawMap[InPath[PathIndex]] = '*';
            }
        }

        AStarMap::PrintMap(InPathDrawMap, InMap->GetMapSize().x, InMap->GetMapSize().y);
    }
    else
    {
        const uint16 StartGridIndex = InMap->GetGridIndex(InWorker->GetStartPos());
        const uint16 GoalGridIndex = InMap->GetGridIndex(InWorker->GetGoalPos());

        std::cout << "StartGridIndex: " << StartGridIndex << std::endl;
        std::cout << "GoalGridIndex: " << GoalGridIndex << std::endl;

        InPathDrawMap[StartGridIndex] = 'S';
        InPathDrawMap[GoalGridIndex] = 'G';

        AStarMap::PrintMap(InPathDrawMap, InMap->GetMapSize().x, InMap->GetMapSize().y);

        std::cout << "Failed to find" << std::endl;
    }

    std::cout << std::endl;
}