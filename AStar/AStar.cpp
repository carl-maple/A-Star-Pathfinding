#include <iostream>
#include <array>
#include <algorithm>
#include <memory>

#include "Types.h"
#include "AStarMap.h"
#include "AStar.h"
#include "AStarUtils.h"
#include "AStarWorker.h"


int main()
{
    constexpr uint32 MAPSIZEX = 1000;
    constexpr uint32 MAPSIZEY = 1000;
    constexpr uint32 NUMBER_OF_NODES = (MAPSIZEX * MAPSIZEY) / 2;

    constexpr bool PrintOutResults = false;
    constexpr uint32 NumberOfPathfindings = 100000;
    constexpr bool RunSingleThreaded = false;

    /*
    const std::vector<char> InputMap = {
        '0', '0', '0', '0', '0', '0', '0', '0', '0', '0',
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
    */

    const std::vector<char> InputMap = AStarUtils::RandomizeMap(MAPSIZEX,MAPSIZEY);

    std::vector<char> PathDrawMap = InputMap;

    std::vector<uint32> Path(NUMBER_OF_NODES);
    int32 PathLength = 0;

    std::unique_ptr<AStarMap> Map = std::make_unique<AStarMap>(InputMap, MAPSIZEX, MAPSIZEY);

    uint32 StartGridIndex;
    uint32 EndGridIndex;

    Map->GetRandomValidStartAndEndGridIndex(StartGridIndex, EndGridIndex);
    
    if (RunSingleThreaded)
    {
        std::unique_ptr<AStarWorker> Worker = std::make_unique<AStarWorker>(Map.get());
        for (int32 i = 0; i < NumberOfPathfindings; ++i)
        {
            bool Result = Worker->FindPath(Map->GetGridPosition(StartGridIndex), Map->GetGridPosition(EndGridIndex));
            if (Result)
            {
                if (PrintOutResults)
                {
                    PathLength = Worker->GetResult(Path);
                    AStarUtils::WriteResults(PathLength, Map, Worker, Path, PathDrawMap, i);
                }
            }
        }
    }
    else
    {
        int32 currentResult = 0;

        constexpr uint16 NUM_OF_WORKERS = 4;
        std::array< std::unique_ptr<AStarWorker>, NUM_OF_WORKERS> Workers;
        std::generate(
            std::begin(Workers),
            std::end(Workers),
            [Map = Map.get()]() { return std::make_unique<AStarWorker>(Map); }
        );

        for (const auto& Worker : Workers)
        {
            Worker->FindPathAsync(Map->GetGridPosition(Map->GetRandomValidGridIndex())
                , Map->GetGridPosition(Map->GetRandomValidGridIndex()));
        }

        for (const auto& Worker : Workers)
        {
            if (PrintOutResults)
            {
                std::cout << std::endl;

                PathLength = Worker->GetResult(Path);
                PathDrawMap = InputMap;

                AStarUtils::WriteResults(PathLength, Map, Worker, Path, PathDrawMap, currentResult);
                currentResult++;
            }
        } 
    }
}
