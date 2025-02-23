#include "AStarMap.h"

#include <algorithm>
#include <random>
#include <iostream>
#include <fstream>
#include <string> 

AStarMap::AStarMap(const std::vector<char>& InMap, const uint32 InSizeX, const uint32 InSizeY)
	: MapSize(InSizeX, InSizeY)
	, Map(InMap)
{
	for (uint32 i = 0; i < MapSize.x * MapSize.y; i++)
	{
		if (Map[i] == '0')
		{
			ValidPoints.push_back(i);
		}
	}
}

uint32 AStarMap::GetGridIndex(const SVector2Di& InGridPos) const
{
	return InGridPos.x + InGridPos.y * MapSize.y;
}

uint32 AStarMap::GetGridIndex(const int16 InGridPosX, const int16 InGridPosY, const uint32 InSizeY)
{
	return InGridPosX + InGridPosY * InSizeY;
}

uint32 AStarMap::GetGridIndex(const int16 InGridPosX, const int16 InGridPosY) const
{
	return GetGridIndex(InGridPosX, InGridPosY, MapSize.y);
}

SVector2Di AStarMap::GetGridPosition(const uint32 InGridIndex) const
{
	const uint32 Row = InGridIndex / MapSize.y;
	const uint32 Column = InGridIndex % MapSize.y;
	return SVector2Di(Column, Row);
}

void AStarMap::GetGridPosition(const uint32 InGridIndex, SVector2Di& OutGridPos) const
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

void AStarMap::PrintMap(const std::vector<char> InPathDrawMap
	, const uint32 InSizeX, const uint32 InSizeY)
{
	for (uint32 IndexY = 0; IndexY < InSizeY; IndexY++)
	{
		for (uint32 IndexX = 0; IndexX < InSizeX; IndexX++)
		{
			const uint16 GridIndex = GetGridIndex(IndexX, IndexY, InSizeY);
			//std::cout << std::string(1, InPathDrawMap[GridIndex]);
		}

		//std::cout << std::endl;
	}
}

void AStarMap::WriteMapToFile(std::ofstream& InFile, const std::vector<char> InPathDrawMap
	, const uint32 InSizeX, const uint32 InSizeY)
{
	for (uint32 IndexY = 0; IndexY < InSizeY; IndexY++)
	{
		for (uint32 IndexX = 0; IndexX < InSizeX; IndexX++)
		{
			const uint16 GridIndex = GetGridIndex(IndexX, IndexY, InSizeY);
			InFile << std::string(1, InPathDrawMap[GridIndex]);
		}

		InFile << std::endl;
	}
}

uint8 AStarMap::GetValueAtIndex(const uint16 InGridIndex) const
{
	return Map[InGridIndex];
}

uint32 AStarMap::GetRandomValidGridIndex() const
{
	std::random_device RandomDevice;  // a seed source for the random number engine
	std::mt19937 Generator(RandomDevice()); // mersenne_twister_engine seeded with rd()
	std::uniform_int_distribution<int32> Distribution(0, ValidPoints.size() - 1);
	const int32 Index = Distribution(Generator);
	return ValidPoints[Index];
}

void AStarMap::GetRandomValidStartAndEndGridIndex(uint32& OutStartGridIndex, uint32& OutEndGridIndex) const
{
	std::vector<uint32> TempValidPoints = ValidPoints;
	std::random_device RandomDevice;  // a seed source for the random number engine
	std::shuffle(TempValidPoints.begin(), TempValidPoints.end(), RandomDevice);
	OutStartGridIndex = TempValidPoints[0];
	OutEndGridIndex = TempValidPoints[1];
}
