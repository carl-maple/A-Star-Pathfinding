#pragma once

#include "Types.h"
#include "AStarDefs.h"
#include "Vector2Di.h"

#include <vector>
#include <random>

constexpr SVector2Di NeighbourDirections[NAStarDefs::NUM_OF_NEIGHBOURS] = { SVector2Di(-1, 0), SVector2Di(1, 0), SVector2Di(0, -1), SVector2Di(0, 1) };

// Keeps track of the map
// Handles converstion between GridIndex -> GridPos and vice vers.
class AStarMap
{
public:
	AStarMap(const std::vector<char>& InMap, const uint32 InSizeX, const uint32 InSizeY);

	uint8 GetValueAtIndex(const uint16 InGridIndex) const;

	uint32 GetRandomValidGridIndex() const;

	void GetRandomValidStartAndEndGridIndex(uint32& OutStartGridIndex, uint32& OutEndGridIndex) const;

	uint32 GetGridIndex(const SVector2Di& InGridPos) const;
	static uint32 GetGridIndex(const int16 InGridPosX, const int16 InGridPosY, const uint32 InSizeY);
	uint32 GetGridIndex(const int16 InGridPosX, const int16 InGridPosY) const;

	SVector2Di GetGridPosition(const uint32 InGridIndex) const;
	void GetGridPosition(const uint32 InGridIndex, SVector2Di& OutGridPos) const;

	bool IsGridPositionValid(const SVector2Di& InGridPos) const;

	static void PrintMap(const std::vector<char> InPathDrawMap
		, const uint32 InSizeX, const uint32 InSizeY);

	static void WriteMapToFile(std::ofstream& InFile, const std::vector<char> InPathDrawMap, const uint32 InSizeX, const uint32 InSizeY);

	const SVector2Di& GetMapSize() const { return MapSize; }
	
private:
	SVector2Di MapSize;

	std::vector<char> Map;

	std::vector<uint32> ValidPoints;
};

