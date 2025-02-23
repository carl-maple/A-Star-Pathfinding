#pragma once

#ifdef NEW_ASTAR_IMPL


#include <limits>
#include "vector"

#include "Types.h"
#include "AStarDefs.h"

enum class EAStarNodeState : uint8
{
	NONE,
	OPEN,
	CLOSED
};

namespace NStarNodeDefs
{
	constexpr uint32 INVALID_INDEX = std::numeric_limits<uint32>::max();
}

struct AStarNode
{
	AStarNode(const uint32 InSize);
	void Reset();

	std::vector<float> Cost;
	std::vector<EAStarNodeState> State;
	std::vector<uint32> Parent;
};

#else

#include <limits>

#include "Types.h"
#include "AStarDefs.h"

enum class EAStarNodeState
{
	NONE,
	OPEN,
	CLOSED
};

namespace NStarNodeDefs
{
	constexpr uint32 INVALID_INDEX = std::numeric_limits<uint32>::max();
}

struct AStarNode
{
	void Reset()
	{
		Cost = -1;
		State = EAStarNodeState::NONE;
		Parent = NStarNodeDefs::INVALID_INDEX;
	}

	float Cost = -1;
	EAStarNodeState State = EAStarNodeState::NONE;
	uint32 Parent = NStarNodeDefs::INVALID_INDEX;
};


#endif