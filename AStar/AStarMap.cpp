#include "AStarMap.h"

#include <algorithm>
#include <random>
#include <iostream>

AStarMap::AStarMap(const char* InMap, const int32 InSizeX, const int32 InSizeY)
	: MapSize(InSizeX, InSizeY)
{
	Map = new char[MapSize.x * MapSize.y];
	std::copy(InMap, InMap + MapSize.x * MapSize.y, Map);

	for (size_t i = 0; i < MapSize.x * MapSize.y; i++)
	{
		if (Map[i] == '0')
		{
			ValidPoints.push_back(i);
		}
	}
}

AStarMap::~AStarMap()
{
	delete[] Map;
}

uint16 AStarMap::GetGridIndex(const SVector2Di& InGridPos) const
{
	return InGridPos.x + InGridPos.y * MapSize.y;
}

uint16 AStarMap::GetGridIndex(const int16 InGridPosX, const int16 InGridPosY, const int32 InSizeY)
{
	return InGridPosX + InGridPosY * InSizeY;
}

uint16 AStarMap::GetGridIndex(const int16 InGridPosX, const int16 InGridPosY) const
{
	return GetGridIndex(InGridPosX, InGridPosY, MapSize.y);
}

SVector2Di AStarMap::GetGridPosition(const uint16 InGridIndex) const
{
	const uint8 Row = InGridIndex / MapSize.y;
	const uint8 Column = InGridIndex % MapSize.y;
	return SVector2Di(Column, Row);
}

void AStarMap::GetGridPosition(const uint16 InGridIndex, SVector2Di& OutGridPos) const
{
	OutGridPos.x = InGridIndex / MapSize.y;
	OutGridPos.y = InGridIndex % MapSize.y;
}

bool AStarMap::IsGridPositionValid(const SVector2Di& InGridPos) const
{
	return ((InGridPos.x >= 0 && InGridPos.x < MapSize.x)
		&& (InGridPos.y >= 0 && InGridPos.y < MapSize.y)
		&& Map[GetGridIndex(InGridPos)] == '0');
}

void AStarMap::PrintMap(const char* InMap, const int32 InSizeX, const int32 InSizeY)
{
	for (int16 IndexY = 0; IndexY < InSizeY; IndexY++)
	{
		for (int16 IndexX = 0; IndexX < InSizeX; IndexX++)
		{
			const uint16 GridIndex = GetGridIndex(IndexX, IndexY, InSizeY);
			std::cout << std::string(1, InMap[GridIndex]);
		}

		std::cout << std::endl;
	}
}

uint8 AStarMap::GetValueAtIndex(const uint16 InGridIndex) const
{
	return Map[InGridIndex];
}

uint16 AStarMap::GetRandomValidGridIndex() const
{
	std::random_device RandomDevice;  // a seed source for the random number engine
	std::mt19937 Generator(RandomDevice()); // mersenne_twister_engine seeded with rd()
	std::uniform_int_distribution<int32> Distribution(0, ValidPoints.size() - 1);
	const int32 Index = Distribution(Generator);
	return ValidPoints[Index];
}
