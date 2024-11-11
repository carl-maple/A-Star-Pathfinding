#pragma once

#include "Types.h"
#include "Vector2Di.h"
#include "AStarNodeList.h"
#include "AStarOpenList.h"

#include <memory>
#include <future>

class AStarMap;

// Takes requests and asynchronously finds a path
class AStarWorker
{
public:

	AStarWorker(const AStarMap* const InMap);

	bool FindPathAsync(const SVector2Di& InStartPos, const SVector2Di& InGoalPos);
	bool FindPath(const SVector2Di& InStartPos, const SVector2Di& InGoalPos);

	uint32 GetResult(std::vector<uint32>& OutPath);

	const SVector2Di& GetStartPos() const { return StartPos; }
	const SVector2Di& GetGoalPos() const { return GoalPos; }

	const std::unique_ptr<AStarOpenList>& GetOpenList() const { return OpenList; }
	const std::unique_ptr<AStarNodeList>& GetNodeList() const { return NodeList; }

	const AStarMap* const GetMap() const { return Map; }

private:
	bool DoWork();

	const AStarMap* const Map;

	std::unique_ptr<AStarOpenList> OpenList;
	std::unique_ptr<AStarNodeList> NodeList;

	SVector2Di StartPos;
	SVector2Di GoalPos;

	std::future<bool> Result;
};

