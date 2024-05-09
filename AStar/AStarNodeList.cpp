#include "AStarNodeList.h"
#include "AStarNode.h"
#include "AStarMap.h"
#include "AStarOpenList.h"

#include <cmath>

AStarNodeList::AStarNodeList(const uint16 InSize)
	: NumberOfItems(InSize)
{
	List = new AStarNode[NumberOfItems];
}

AStarNodeList::~AStarNodeList()
{
	delete[] List;
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

void AStarNodeList::PopulateNeighbours(const uint16 InGridIndex, AStarOpenList* InOpenList, const AStarMap* const InMap, const SVector2Di& InGoalPos)
{
	const SVector2Di TempGridPos = InMap->GetGridPosition(InGridIndex);
	SVector2Di TempNeighbourGridPos = SVector2Di();

	for (uint16 NeighbourIndex = 0; NeighbourIndex < NAStarDefs::NUM_OF_NEIGHBOURS; NeighbourIndex++)
	{
		TempNeighbourGridPos = TempGridPos + NeighbourDirections[NeighbourIndex];

		if (InMap->IsGridPositionValid(TempNeighbourGridPos) == false)
		{
			continue;
		}

		const uint16 NeighbourGridIndex = InMap->GetGridIndex(TempNeighbourGridPos);

		if (List[NeighbourGridIndex].State != EAStarNodeState::NONE)
		{
			continue;
		}

		List[NeighbourGridIndex].Neighbours[NeighbourIndex] = NeighbourGridIndex;
		List[NeighbourGridIndex].Cost = ManhattanDistance(TempNeighbourGridPos, InGoalPos);
		List[NeighbourGridIndex].State = EAStarNodeState::OPEN;
		List[NeighbourGridIndex].Parent = InGridIndex;

		InOpenList->Add(NeighbourGridIndex);
	}
}

void AStarNodeList::CloseNode(const uint16 InGridIndex)
{
	List[InGridIndex].State = EAStarNodeState::CLOSED;
}
