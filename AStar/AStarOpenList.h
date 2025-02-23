#pragma once

#include "Types.h"
#include "Vector2Di.h"

#include <vector>

class AStarWorker;

struct OpenListItem
{
	OpenListItem(uint32 InGridIndex, float InCost) : GridIndex(InGridIndex), Cost(InCost) {}

	uint32 GridIndex;
	float Cost;
};

// Keeps track of all open nodes and sorts them based on cost
// The first index of the list is 1. This to make sorting easier.
class AStarOpenList
{
public:
	AStarOpenList(const uint32 InOpenListBufferSize, const AStarWorker* const InWorkerOwner);

	void Add(const uint32 InGridIndex, float InCost);
	void PopFirst();

	const OpenListItem& GetFirst() const { return OpenList[1]; }

	void PopulateNeighbours(const uint32 InGridIndex);

	uint32 GetNumberOfItems() const { return NumberOfItems; }

	void Reset() { NumberOfItems = 0; }
private:

	std::vector<OpenListItem> OpenList;
	uint32 NumberOfItems = 0;
	const AStarWorker* const WorkerOwner;
};