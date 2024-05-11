#pragma once

#include "Types.h"
#include "Vector2Di.h"

#include <vector>

class AStarWorker;

// Keeps track of all open nodes and sorts them based on cost
// The first index of the list is 1. This to make sorting easier.
class AStarOpenList
{
public:
	AStarOpenList(const uint32 InOpenListBufferSize, const AStarWorker* const InWorkerOwner);

	void Add(const uint16 InGridIndex);
	void PopFirst();

	uint16 GetFirst() const { return OpenList[1]; }
	
	void PopulateNeighbours(const uint16 InGridIndex, const SVector2Di& InGoalPos);

	uint32 GetNumberOfItems() const { return NumberOfItems; }
private:
	std::vector<uint16> OpenList;
	uint32 NumberOfItems = 0;
	const AStarWorker* const WorkerOwner;
};

