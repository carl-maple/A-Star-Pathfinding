#pragma once

#include "Types.h"
#include "Vector2Di.h"
#include "AStarNode.h"

class AStarMap;
class AStarOpenList;

class AStarNodeList
{
public:
	AStarNodeList(const uint16 InSize);
	~AStarNodeList();

	const AStarNode& GetAStarNode(const uint16 InGridIndex) const;

	void PopulateNeighbours(const uint16 InGridIndex, AStarOpenList* InOpenList, const AStarMap* const InMap, const SVector2Di& InGoalPos);

	void CloseNode(const uint16 InGridIndex);

private:
	float ManhattanDistance(const SVector2Di& InCurrent, const SVector2Di& InGoal) const;

	struct AStarNode* List;
	uint16 NumberOfItems;
};

