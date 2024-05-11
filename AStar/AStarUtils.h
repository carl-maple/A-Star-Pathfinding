#pragma once

#include "Types.h"

#include "memory"
#include "vector"

class AStarNodeList;
class AStarMap;
class AStarWorker;

namespace AStarUtils
{
	int32 FillPath(const uint16 FirstGridIndex
		, const std::unique_ptr<AStarNodeList>& InNodeList
		, std::vector<uint16>& OutPath);

	void PrintResult(const int32 PathLength
		, const std::unique_ptr<AStarMap>& InMap
		, const std::unique_ptr<AStarWorker>& InWorker
		, const std::vector<uint16>& InPath, std::vector<char> InPathDrawMap);
};

