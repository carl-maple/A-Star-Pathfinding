#include "AStarWorker.h"
#include "AStarMap.h"
#include "AStarOpenList.h"
#include "AStarNodeList.h"


#include "AStarUtils.h"

AStarWorker::AStarWorker(const AStarMap* const InMap)
    :Map(InMap)
{
    const SVector2Di& MapSize = InMap->GetMapSize();
    NodeList = std::make_unique<AStarNodeList>(MapSize.x * MapSize.y);
    OpenList = std::make_unique<AStarOpenList>(MapSize.x * MapSize.y, NodeList.get());
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
        if (FirstGridIndex == Map->GetGridIndex(GoalPos))
        {
            return true;
        }

        NodeList->PopulateNeighbours(FirstGridIndex, OpenList.get(), Map, GoalPos);
        NodeList->CloseNode(FirstGridIndex);
        OpenList->PopFirst();
    }

    return false;
}



int32 AStarWorker::GetResult(uint16* OutPath)
{
    if (Result.get())
    {
        const uint16 GoalGridIndex = Map->GetGridIndex(GoalPos);
        return AStarUtils::FillPath(GoalGridIndex, NodeList.get(), OutPath);
    }
    else
    {
        return 0;
    }
    
}