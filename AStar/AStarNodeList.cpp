#include "AStarNodeList.h"
#include "AStarNode.h"
#include "AStarMap.h"
#include "AStarOpenList.h"
#include "AStarWorker.h"

#include <cmath>

AStarNodeList::AStarNodeList(const uint16 InSize, const AStarWorker* const InWorkerOwner)
	: NumberOfItems(InSize)
	, WorkerOwner(InWorkerOwner)
{
	List.resize(InSize);
}

const AStarNode& AStarNodeList::GetAStarNode(const uint16 InGridIndex) const
{
	return List[InGridIndex];
}

float AStarNodeList::ManhattanDistance(const SVector2Di& InCurrent, const SVector2Di& InGoal) const
{
	const uint8 DeltaX = std::abs(InCurrent.x - InGoal.x);
	const uint8 DeltaY = std::abs(InCurrent.y - InGoal.y);
	return 1.f * (DeltaX + DeltaY);
}

bool AStarNodeList::Populate(const int16 InGridIndex, const int16 InParentIndex)
{
	const AStarMap* const Map = WorkerOwner->GetMap();

	if (List[InGridIndex].State != EAStarNodeState::NONE)
	{
		return false;
	}

	List[InGridIndex].Cost = ManhattanDistance(Map->GetGridPosition(InGridIndex)
		, WorkerOwner->GetGoalPos());
	List[InGridIndex].State = EAStarNodeState::OPEN;
	List[InGridIndex].Parent = InParentIndex;

	return true;
}

void AStarNodeList::CloseNode(const uint16 InGridIndex)
{
	List[InGridIndex].State = EAStarNodeState::CLOSED;
}
