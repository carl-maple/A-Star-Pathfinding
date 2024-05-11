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
    constexpr uint16 MAPSIZEX = 10;
    constexpr uint16 MAPSIZEY = 10;
    constexpr uint16 NUMBER_OF_NODES = MAPSIZEX * MAPSIZEY;

    const std::vector<char> InputMap = {
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

    std::vector<char> PathDrawMap = InputMap;

    std::vector<uint16> Path(NUMBER_OF_NODES);
    int32 PathLength = 0;

    std::unique_ptr<AStarMap> Map = std::make_unique<AStarMap>(InputMap, MAPSIZEX, MAPSIZEY);
    
    bool RunSingle = true;
    if (RunSingle)
    {
        std::unique_ptr<AStarWorker> Worker = std::make_unique<AStarWorker>(Map.get());
        Worker->FindPath(Map->GetGridPosition(96), Map->GetGridPosition(72));
        PathLength = Worker->GetResult(Path);
        AStarUtils::PrintResult(PathLength, Map, Worker, Path, PathDrawMap);
    }
    else
    {
        constexpr uint16 NUM_OF_WORKERS = 4;
        std::array< std::unique_ptr<AStarWorker>, NUM_OF_WORKERS> Workers;
        std::generate(
            std::begin(Workers),
            std::end(Workers),
            [Map = move(Map)]() { return std::make_unique<AStarWorker>(Map.get()); }
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
            PathDrawMap = InputMap;

            AStarUtils::PrintResult(PathLength, Map, Worker, Path, PathDrawMap);
        } 
    }
}
