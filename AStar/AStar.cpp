#include <iostream>
#include <array>
#include <algorithm>
#include <memory>

#include "Types.h"
#include "AStarMap.h"
#include "AStar.h"
#include "AStarUtils.h"
#include "AStarWorker.h"

void PrintResult(int32 PathLength, AStarMap* Map
    , const std::unique_ptr<AStarWorker>& Worker, uint16* Path
    , char* Temp)
{
    if (PathLength > 0)
    {
        const uint16 StartGridIndex = Map->GetGridIndex(Worker->GetStartPos());
        const uint16 GoalGridIndex = Map->GetGridIndex(Worker->GetGoalPos());

        std::cout << "StartGridIndex: " << StartGridIndex << std::endl;
        std::cout << "GoalGridIndex: " << GoalGridIndex << std::endl;

        for (int32 PathIndex = PathLength - 1; PathIndex >= 0; PathIndex--)
        {
            if (StartGridIndex == Path[PathIndex])
            {
                Temp[Path[PathIndex]] = 'S';
            }
            else if (GoalGridIndex == Path[PathIndex])
            {
                Temp[Path[PathIndex]] = 'G';
            }
            else
            {
                Temp[Path[PathIndex]] = '*';
            }
        }

        AStarMap::PrintMap(Temp, Map->GetMapSize().x, Map->GetMapSize().y);
    }
    else
    {
        const uint16 StartGridIndex = Map->GetGridIndex(Worker->GetStartPos());
        const uint16 GoalGridIndex = Map->GetGridIndex(Worker->GetGoalPos());

        std::cout << "StartGridIndex: " << StartGridIndex << std::endl;
        std::cout << "GoalGridIndex: " << GoalGridIndex << std::endl;

        Temp[StartGridIndex] = 'S';
        Temp[GoalGridIndex] = 'G';

        AStarMap::PrintMap(Temp, Map->GetMapSize().x, Map->GetMapSize().y);

        std::cout << "Failed to find" << std::endl;
    }

    std::cout << std::endl;
}

int main()
{
    constexpr uint16 MAPSIZEX = 10;
    constexpr uint16 MAPSIZEY = 10;

    char* InputMap = new char[MAPSIZEX * MAPSIZEY]
    {
        '0', '1', '0', '0', '0', '0', '1', '0', '0', '0',
        '0', '1', '0', '1', '0', '0', '1', '0', '1', '0',
        '0', '0', '0', '1', '0', '0', '0', '0', '1', '0',
        '1', '1', '1', '1', '0', '1', '1', '1', '1', '0',
        '0', '0', '0', '0', '0', '0', '0', '0', '0', '0',
        '0', '1', '0', '0', '0', '0', '1', '0', '0', '0',
        '0', '1', '0', '1', '0', '0', '1', '0', '1', '0',
        '0', '0', '0', '1', '0', '0', '0', '0', '1', '0',
        '1', '1', '1', '1', '0', '1', '1', '1', '1', '0',
        '0', '0', '0', '0', '0', '0', '0', '0', '0', '0',
    };

    uint16* Path = new uint16[MAPSIZEX * MAPSIZEY];
    int32 PathLength = 0;

    char* PathDrawMap = new char[MAPSIZEX * MAPSIZEY];
    std::copy(InputMap, InputMap + MAPSIZEX * MAPSIZEY, PathDrawMap);
    
    AStarMap* Map = new AStarMap(InputMap, MAPSIZEX, MAPSIZEY);
    
    bool RunSingle = false;
    if (RunSingle)
    {
        std::unique_ptr<AStarWorker> Worker = std::make_unique<AStarWorker>(Map);
        Worker->FindPath(Map->GetGridPosition(96), Map->GetGridPosition(72));
        PathLength = Worker->GetResult(Path);
        PrintResult(PathLength, Map, Worker, Path, PathDrawMap);
    }
    else
    {
        constexpr uint16 NUM_OF_WORKERS = 4;
        std::array< std::unique_ptr<AStarWorker>, NUM_OF_WORKERS> Workers;
        std::generate(
            std::begin(Workers),
            std::end(Workers),
            [Map]() { return std::make_unique<AStarWorker>(Map); }
        );

        for (const auto& Worker : Workers)
        {
            Worker->FindPath(Map->GetGridPosition(Map->GetRandomValidGridIndex())
                , Map->GetGridPosition(Map->GetRandomValidGridIndex()));
        }

        for (const auto& Worker : Workers)
        {
            std::cout << std::endl;

            PathLength = Worker->GetResult(Path);
            std::copy(InputMap, InputMap + MAPSIZEX * MAPSIZEY, PathDrawMap);

            PrintResult(PathLength, Map, Worker, Path, PathDrawMap);
        } 
    }

    delete[] Path;
    delete[] PathDrawMap;
    delete Map;
}
