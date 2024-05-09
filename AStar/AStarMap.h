#pragma once

#include <vector>
#include <random>

#include "Types.h"
#include "AStarDefs.h"
#include "Vector2Di.h"

constexpr SVector2Di NeighbourDirections[NAStarDefs::NUM_OF_NEIGHBOURS] = { SVector2Di(-1, 0), SVector2Di(1, 0), SVector2Di(0, -1), SVector2Di(0, 1) };

class AStarMap
{
public:
	AStarMap(const char* InMap, const int32 InSizeX, const int32 InSizeY);
	~AStarMap();

	uint8 GetValueAtIndex(const uint16 InGridIndex) const;

	uint16 GetRandomValidGridIndex() const;

	uint16 GetGridIndex(const SVector2Di& InGridPos) const;
	static uint16 GetGridIndex(const int16 InGridPosX, const int16 InGridPosY, const int32 InSizeY);
	uint16 GetGridIndex(const int16 InGridPosX, const int16 InGridPosY) const;

	SVector2Di GetGridPosition(const uint16 InGridIndex) const;
	void GetGridPosition(const uint16 InGridIndex, SVector2Di& OutGridPos) const;

	bool IsGridPositionValid(const SVector2Di& InGridPos) const;

	static void PrintMap(const char* InMap, const int32 InSizeX, const int32 InSizeY);

	const SVector2Di& GetMapSize() const { return MapSize; }
	
private:
	SVector2Di MapSize;

	char* Map = nullptr;

	std::vector<int32> ValidPoints;
};

