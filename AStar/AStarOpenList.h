#pragma once

#include "Types.h"

struct AStarNode;
class AStarNodeList;

class AStarOpenList
{
public:
	AStarOpenList(const uint32 InSize, const AStarNodeList* const InNodeList);
	~AStarOpenList();

	void Add(const uint16 InGridIndex);

	uint16 GetFirst() const { return OpenList[1]; }
	void PopFirst();

	uint32 GetNumberOfItems() const { return NumberOfItems; }
private:
	const AStarNodeList* const NodeList = nullptr;

	uint32* OpenList = nullptr;
	uint32 NumberOfItems = 0;

};

