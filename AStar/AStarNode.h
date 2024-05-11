#pragma once

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
	constexpr uint16 INVALID_INDEX = std::numeric_limits<uint16>::max();
}

struct AStarNode
{
	float Cost = -1;
	EAStarNodeState State = EAStarNodeState::NONE;
	uint16 Parent = NStarNodeDefs::INVALID_INDEX;
};

