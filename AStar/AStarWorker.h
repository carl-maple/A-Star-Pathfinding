#pragma once

#include "Types.h"
#include "Vector2Di.h"
#include "AStarNodeList.h"
#include "AStarOpenList.h"

#include <memory>
#include <future>

class AStarMap;

class AStarWorker
{
public:

	AStarWorker(const AStarMap* const InMap);

	bool FindPath(const SVector2Di& InStartPos, const SVector2Di& InGoalPos);
	int32 GetResult(uint16* OutPath);

	const SVector2Di& GetStartPos() const { return StartPos; }
	const SVector2Di& GetGoalPos() const { return GoalPos; }

private:
	bool DoWork();

	const AStarMap* const Map;

	std::unique_ptr<AStarOpenList> OpenList;
	std::unique_ptr<AStarNodeList> NodeList;

	SVector2Di StartPos;
	SVector2Di GoalPos;

	std::future<bool> Result;
};
