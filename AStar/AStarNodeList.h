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
	AStarNodeList(const uint32 InSize, const AStarWorker* const InWorkerOwner);

	const AStarNode& GetAStarNode(const uint32 InGridIndex) const;

	bool Populate(const uint32 InGridIndex, const uint32 InGoalIndex);

	void CloseNode(const uint32 InGridIndex);

	void Reset();

private:
	float ManhattanDistance(const SVector2Di& InCurrent, const SVector2Di& InGoal) const;

	std::vector<AStarNode> List;
	uint32 NumberOfItems;
	const AStarWorker* const WorkerOwner;
};
