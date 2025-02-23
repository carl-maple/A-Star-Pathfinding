#include "AStarWorker.h"
#include "AStarMap.h"
#include "AStarOpenList.h"
#include "AStarNodeList.h"
#include "AStarUtils.h"

#include "iostream"

AStarWorker::AStarWorker(const AStarMap* const InMap)
    :Map(InMap)
{
    const SVector2Di& MapSize = InMap->GetMapSize();
    NodeList = std::make_unique<AStarNodeList>(MapSize.x * MapSize.y, this);
    OpenList = std::make_unique<AStarOpenList>(MapSize.x * MapSize.y, this);
}

bool AStarWorker::FindPathAsync(const SVector2Di& InStartPos, const SVector2Di& InGoalPos)
{
    StartPos = InStartPos;
    GoalPos = InGoalPos;

    NodeList->Reset();
    OpenList->Reset();
       
    Result = std::async(std::launch::async, &AStarWorker::DoWork, this);

    return true;
}

bool AStarWorker::FindPath(const SVector2Di& InStartPos, const SVector2Di& InGoalPos)
{
    StartPos = InStartPos;
    GoalPos = InGoalPos;

    NodeList->Reset();
    OpenList->Reset();

    return DoWork();
}

bool AStarWorker::DoWork()
{
    const uint32 StartGridIndex = Map->GetGridIndex(StartPos);

    OpenList->Add(StartGridIndex, 0.f);
    while (OpenList->GetNumberOfItems() != 0)
    {
        const uint32 FirstGridIndex = OpenList->GetFirst().GridIndex;

        // Check if we are at our goal
        if (FirstGridIndex == Map->GetGridIndex(GoalPos))
        {
            return true;
        }

        // Add each neighbour node to the open list
        OpenList->PopulateNeighbours(FirstGridIndex);

        // We are done with this node so we remove it
        OpenList->PopFirst();
    }

    return false;
}



uint32 AStarWorker::GetResult(std::vector<uint32>& OutPath)
{
    if (Result.valid() && Result.get())
    {
        const uint32 GoalGridIndex = Map->GetGridIndex(GoalPos);
        return AStarUtils::FillPath(GoalGridIndex, NodeList, OutPath);
    }
    else if(Result.valid() == false)
    {
        const uint32 GoalGridIndex = Map->GetGridIndex(GoalPos);
        return AStarUtils::FillPath(GoalGridIndex, NodeList, OutPath);
    }
    else
    {
        return 0;
    }
}