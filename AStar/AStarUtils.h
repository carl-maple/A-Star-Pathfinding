#pragma once

#include "Types.h"

#include "memory"
#include "vector"

class AStarNodeList;
class AStarMap;
class AStarWorker;

namespace AStarUtils
{
	uint32 FillPath(const uint32 FirstGridIndex
		, const std::unique_ptr<AStarNodeList>& InNodeList
		, std::vector<uint32>& OutPath);

	void PrintResult(const int32 PathLength
		, const std::unique_ptr<AStarMap>& InMap
		, const std::unique_ptr<AStarWorker>& InWorker
		, const std::vector<uint32>& InPath, std::vector<char> InPathDrawMap);

	void WriteResults(const int32 InPathLength
		, const std::unique_ptr<AStarMap>& InMap
		, const std::unique_ptr<AStarWorker>& InWorker
		, const std::vector<uint32>& InPath, std::vector<char> InPathDrawMap, int32 InCurrentIteration);

	std::vector<char> RandomizeMap(const uint32 InSizeX, const uint32 InSizeY);
};

