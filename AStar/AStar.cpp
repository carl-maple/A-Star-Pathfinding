#include <iostream>
#include <array>
#include <algorithm>
#include <memory>
#include <fstream>
#include <string>
#include <filesystem>
#include <sstream>

#include "Types.h"
#include "AStarMap.h"
#include "AStar.h"
#include "AStarUtils.h"
#include "AStarWorker.h"

#if DEBUG
#include "spdlog/sinks/rotating_file_sink.h"
#endif

void InitLogger()
{
#if DEBUG
    auto MaxSize = 1048576 * 50;
    auto MaxFiles = 3;
#ifdef NEW_ASTAR_IMPL
    auto logger = spdlog::rotating_logger_mt("basic_logger", "logs/new-log.txt", DEBUG, MaxFiles);
#else
    auto logger = spdlog::rotating_logger_mt("basic_logger", "logs/old-log.txt", DEBUG, MaxFiles);
#endif // NEW_ASTAR_IMPL
#endif
}

static const std::vector<char> InputMap = {
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

int main()
{
    InitLogger();

    constexpr uint32 MAPSIZEX = 1000;
    constexpr uint32 MAPSIZEY = 1000;
    constexpr uint32 NUMBER_OF_NODES = (MAPSIZEX * MAPSIZEY);

    constexpr bool PrintOutResults = false;
    constexpr uint32 NumberOfPathfindings = 1000;
    constexpr bool RunSingleThreaded = true;

    constexpr uint32 ScenariosToGenerate = 5;
    constexpr bool GenerateScenario = false;
    constexpr bool RunScenario = true;

    if (GenerateScenario)
    {
        AStarUtils::GenerateScenarios(ScenariosToGenerate, MAPSIZEX, MAPSIZEY);
        return 1;
    }
    if (RunScenario)
    {
        for (int i = 0; i < NumberOfPathfindings; ++i)
        {
            int index = 0;
            std::string FileName = "scenario_" + std::to_string(index) + ".txt";

            while (std::filesystem::exists(FileName))
            {
                uint32 StartGridIndex;
                uint32 EndGridIndex;

                std::vector<char> InputMap = AStarUtils::ReadScenario(FileName, StartGridIndex, EndGridIndex);

                std::vector<char> PathDrawMap = InputMap;

                std::vector<uint32> Path(InputMap.size());
                int32 PathLength = 0;

                std::unique_ptr<AStarMap> Map = std::make_unique<AStarMap>(InputMap, MAPSIZEX, MAPSIZEY);

                std::unique_ptr<AStarWorker> Worker = std::make_unique<AStarWorker>(Map.get());

                bool Result = Worker->FindPath(Map->GetGridPosition(StartGridIndex), Map->GetGridPosition(EndGridIndex));
                if (Result)
                {
                    PathLength = Worker->GetResult(Path);
                    if (PrintOutResults)
                    {
                        AStarUtils::WriteResults(PathLength, Map, Worker, Path, PathDrawMap, index);
                    }
                }

                index++;
                FileName = "scenario_" + std::to_string(index) + ".txt";
            }
        }

        return 1;
    }
    

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
            bool Result = Worker->FindPath(SVector2Di(0,0), SVector2Di(1999, 1999));
            if (Result)
            {
                PathLength = Worker->GetResult(Path);
                if (PrintOutResults)
                {
                    AStarUtils::WriteResults(PathLength, Map, Worker, Path, PathDrawMap, i);
                }
            }
        }
    }
    else
    {
        int32 CurrentResult = 0;

        constexpr uint32 NUM_OF_WORKERS = 4;
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
                PathLength = Worker->GetResult(Path);
                PathDrawMap = InputMap;

                AStarUtils::WriteResults(PathLength, Map, Worker, Path, PathDrawMap, CurrentResult);
                CurrentResult++;
            }
        } 
    }
}