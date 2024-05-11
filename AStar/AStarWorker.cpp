#include "AStarWorker.h"
#include "AStarMap.h"
#include "AStarOpenList.h"
#include "AStarNodeList.h"
#include "AStarUtils.h"

AStarWorker::AStarWorker(const AStarMap* const InMap)
    :Map(InMap)
{
    const SVector2Di& MapSize = InMap->GetMapSize();
    NodeList = std::make_unique<AStarNodeList>(MapSize.x * MapSize.y, this);
    OpenList = std::make_unique<AStarOpenList>(MapSize.x * MapSize.y, this);
}

bool AStarWorker::FindPath(const SVector2Di& InStartPos, const SVector2Di& InGoalPos)
{
    StartPos = InStartPos;
    GoalPos = InGoalPos;
       
    Result = std::async(std::launch::async, &AStarWorker::DoWork, this);

    return true;
}

bool AStarWorker::DoWork()
{
    const uint16 StartGridIndex = Map->GetGridIndex(StartPos);

    OpenList->Add(StartGridIndex);
    while (OpenList->GetNumberOfItems() != 0)
    {
        const uint16 FirstGridIndex = OpenList->GetFirst();

        // Check if we are at our goal
        if (FirstGridIndex == Map->GetGridIndex(GoalPos))
        {
            return true;
        }

        // Add each neighbour node to the open list
        OpenList->PopulateNeighbours(FirstGridIndex, GoalPos);

        // We are done with this node so we remove it
        OpenList->PopFirst();
    }

    return false;
}



int32 AStarWorker::GetResult(std::vector<uint16>& OutPath)
{
    if (Result.get())
    {
        const uint16 GoalGridIndex = Map->GetGridIndex(GoalPos);
        return AStarUtils::FillPath(GoalGridIndex, NodeList, OutPath);
    }
    else
    {
        return 0;
    }
}