#include "AStarNodeList.h"
#include "AStarNode.h"
#include "AStarMap.h"
#include "AStarOpenList.h"
#include "AStarWorker.h"

#include <cmath>

AStarNodeList::AStarNodeList(const uint32 InSize, const AStarWorker* const InWorkerOwner)
	: NumberOfItems(InSize)
	, WorkerOwner(InWorkerOwner)
{
	List.resize(InSize);
}

const AStarNode& AStarNodeList::GetAStarNode(const uint32 InGridIndex) const
{
	return List[InGridIndex];
}

float AStarNodeList::ManhattanDistance(const SVector2Di& InCurrent, const SVector2Di& InGoal) const
{
	const int32 DeltaX = std::abs(InCurrent.x - InGoal.x);
	const int32 DeltaY = std::abs(InCurrent.y - InGoal.y);
	return 1.f * (DeltaX + DeltaY);
}

bool AStarNodeList::Populate(const uint32 InGridIndex, const uint32 InParentIndex)
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

void AStarNodeList::CloseNode(const uint32 InGridIndex)
{
	List[InGridIndex].State = EAStarNodeState::CLOSED;
}

void AStarNodeList::Reset()
{
	for (AStarNode& Node : List)
	{
		Node.Reset();
	}
}
