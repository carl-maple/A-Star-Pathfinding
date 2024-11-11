#include "AStarUtils.h"
#include "AStarDefs.h"
#include "AStarNodeList.h"
#include "AStarMap.h"
#include "AStarWorker.h"

#include "vector"
#include "iostream"

uint32 AStarUtils::FillPath(const uint32 FirstGridIndex
    , const std::unique_ptr<AStarNodeList>& InNodeList, std::vector<uint32>& OutPath)
{
    uint32 PathGridIndex = FirstGridIndex;
    int32 PathIndex = 0;

    while (PathGridIndex != NStarNodeDefs::INVALID_INDEX)
    {
        OutPath[PathIndex] = PathGridIndex;
        PathIndex++;
        PathGridIndex = InNodeList->GetAStarNode(PathGridIndex).Parent;
    }

    return PathIndex;
}

void AStarUtils::PrintResult(const int32 InPathLength, const std::unique_ptr<AStarMap>& InMap
    , const std::unique_ptr<AStarWorker>& InWorker, const std::vector<uint32>& InPath
    , std::vector<char> InPathDrawMap)
{
    if (InPathLength > 0)
    {
        const uint32 StartGridIndex = InMap->GetGridIndex(InWorker->GetStartPos());
        const uint32 GoalGridIndex = InMap->GetGridIndex(InWorker->GetGoalPos());

        std::cout << "StartGridIndex: " << StartGridIndex << std::endl;
        std::cout << "GoalGridIndex: " << GoalGridIndex << std::endl;

        for (int32 PathIndex = InPathLength - 1; PathIndex >= 0; PathIndex--)
        {
            if (StartGridIndex == InPath[PathIndex])
            {
                InPathDrawMap[InPath[PathIndex]] = 'S';
            }
            else if (GoalGridIndex == InPath[PathIndex])
            {
                InPathDrawMap[InPath[PathIndex]] = 'G';
            }
            else
            {
                InPathDrawMap[InPath[PathIndex]] = '*';
            }
        }

        AStarMap::PrintMap(InPathDrawMap, InMap->GetMapSize().x, InMap->GetMapSize().y);
    }
    else
    {
        const uint32 StartGridIndex = InMap->GetGridIndex(InWorker->GetStartPos());
        const uint32 GoalGridIndex = InMap->GetGridIndex(InWorker->GetGoalPos());

        std::cout << "StartGridIndex: " << StartGridIndex << std::endl;
        std::cout << "GoalGridIndex: " << GoalGridIndex << std::endl;

        InPathDrawMap[StartGridIndex] = 'S';
        InPathDrawMap[GoalGridIndex] = 'G';

        AStarMap::PrintMap(InPathDrawMap, InMap->GetMapSize().x, InMap->GetMapSize().y);

        std::cout << "Failed to find" << std::endl;
    }

    std::cout << std::endl;
}

void AStarUtils::WriteResults(const int32 InPathLength, const std::unique_ptr<AStarMap>& InMap
    , const std::unique_ptr<AStarWorker>& InWorker, const std::vector<uint32>& InPath
    , std::vector<char> InPathDrawMap, int32 InCurrentIteration)
{
    if (InPathLength > 0)
    {
        const uint32 StartGridIndex = InMap->GetGridIndex(InWorker->GetStartPos());
        const uint32 GoalGridIndex = InMap->GetGridIndex(InWorker->GetGoalPos());
        std::cout << "Iteration: " << InCurrentIteration << std::endl;
        std::cout << "StartGridIndex: " << StartGridIndex << std::endl;
        std::cout << "GoalGridIndex: " << GoalGridIndex << std::endl;

        for (int32 PathIndex = InPathLength - 1; PathIndex >= 0; PathIndex--)
        {
            if (StartGridIndex == InPath[PathIndex])
            {
                InPathDrawMap[InPath[PathIndex]] = 'S';
            }
            else if (GoalGridIndex == InPath[PathIndex])
            {
                InPathDrawMap[InPath[PathIndex]] = 'G';
            }
            else
            {
                InPathDrawMap[InPath[PathIndex]] = '*';
            }
        }

        AStarMap::WriteMapToFile(InPathDrawMap, InMap->GetMapSize().x, InMap->GetMapSize().y, InCurrentIteration);
    }
}

std::vector<char> AStarUtils::RandomizeMap(const uint32 InSizeX, const uint32 InSizeY)
{
    std::vector<char> Values = { '0', '0', '0', '0', '0' };
    std::vector<char> Map;
    Map.reserve(InSizeX * InSizeY);

    std::random_device RandomDevice;  // a seed source for the random number engine
    std::mt19937 Generator(RandomDevice()); // mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<int32> Distribution(0, Values.size() - 1);

    for (uint32 y = 0; y < InSizeY; y++)
    {
        for (uint32 x = 0; x < InSizeX; x++)
        {
            const int32 Index = Distribution(Generator);
            Map.push_back(Values[Index]);
        }
    }
    
    
    return Map;
}