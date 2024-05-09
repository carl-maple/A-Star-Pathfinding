#pragma once

#include "Types.h"

class AStarNodeList;

namespace AStarUtils
{
	int32 FillPath(const uint16 FirstGridIndex, const AStarNodeList* const InNodeList, uint16* OutPath);
};

