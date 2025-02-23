#include "AStarUtils.h"
#include "AStarDefs.h"
#include "AStarNodeList.h"
#include "AStarMap.h"
#include "AStarWorker.h"

#include "vector"
#include "iostream"

#include <fstream>
#include <string> 

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

        InPathDrawMap[StartGridIndex] = 'S';
        InPathDrawMap[GoalGridIndex] = 'G';

        AStarMap::PrintMap(InPathDrawMap, InMap->GetMapSize().x, InMap->GetMapSize().y);
    }
}

void AStarUtils::WriteResults(const int32 InPathLength, const std::unique_ptr<AStarMap>& InMap
    , const std::unique_ptr<AStarWorker>& InWorker, const std::vector<uint32>& InPath
    , std::vector<char> InPathDrawMap, int32 InCurrentIteration)
{
    if (InPathLength > 0)
    {
        const uint32 StartGridIndex = InMap->GetGridIndex(InWorker->GetStartPos());
        const uint32 GoalGridIndex = InMap->GetGridIndex(InWorker->GetGoalPos());

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

        std::ofstream File;

        File.open("result_" + std::to_string(InCurrentIteration) + ".txt");

        AStarMap::WriteMapToFile(File, InPathDrawMap, InMap->GetMapSize().x, InMap->GetMapSize().y);

        File.close();
    }
}

std::vector<char> AStarUtils::RandomizeMap(const uint32 InSizeX, const uint32 InSizeY)
{
    std::vector<char> Values = { '0', '1', '0', '1', '0' };
    std::vector<char> Map;
    Map.reserve(InSizeX * InSizeY);

    std::random_device RandomDevice;  // a seed source for the random number engine
    std::mt19937 Generator(0); // mersenne_twister_engine seeded with rd()
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

void AStarUtils::GenerateScenarios(const uint32 ScenariosToGenerate, const uint32 InSizeX, const uint32 InSizeY)
{
    for (int i = 0; i < ScenariosToGenerate; ++i)
    {
        const std::vector<char> InputMap = AStarUtils::RandomizeMap(InSizeX, InSizeY);
        std::unique_ptr<AStarMap> Map = std::make_unique<AStarMap>(InputMap, InSizeX, InSizeY);

        uint32 StartGridIndex;
        uint32 EndGridIndex;

        Map->GetRandomValidStartAndEndGridIndex(StartGridIndex, EndGridIndex);

        std::ofstream File;
        File.open("scenario_" + std::to_string(i) + ".txt");

        File << StartGridIndex << " " << EndGridIndex << std::endl;
        AStarMap::WriteMapToFile(File, InputMap, InSizeX, InSizeY);
        File.close();
    }
}

std::vector<char> AStarUtils::ReadScenario(const std::string& InFileName, uint32& OutStartGridIndex, uint32& OutEndGridIndex)
{
    std::ifstream File;
    File.open(InFileName);

    File >> OutStartGridIndex >> OutEndGridIndex;

    std::vector<char> InputMap;
    char c;
    while (File.get(c))
    {
        if (c == '\n')
        {
            continue;
        }

        InputMap.push_back(c);
    }


    File.close();

    return InputMap;
}