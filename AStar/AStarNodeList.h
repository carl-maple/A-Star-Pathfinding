#pragma once

#include "Types.h"
#include "Vector2Di.h"
#include "AStarNode.h"

#include "vector"

class AStarMap;
class AStarOpenList;
class AStarWorker;

class AStarNodeList
{
public:
	AStarNodeList(const uint16 InSize, const AStarWorker* const InWorkerOwner);

	const AStarNode& GetAStarNode(const uint16 InGridIndex) const;

	bool Populate(const int16 InGridIndex, const int16 InGoalIndex);

	void CloseNode(const uint16 InGridIndex);

private:
	float ManhattanDistance(const SVector2Di& InCurrent, const SVector2Di& InGoal) const;

	std::vector<AStarNode> List;
	uint16 NumberOfItems;
	const AStarWorker* const WorkerOwner;
};

