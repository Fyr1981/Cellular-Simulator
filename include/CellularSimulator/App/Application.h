#pragma once

#include <memory>
#include <mutex>
#include <optional>

#include "raylib.h"
#include "CellularSimulator/Core/Simulator.h"
#include "RenderData.h"

struct Color;
struct Camera2D;

class CellularSimulator::Core::GridTile;
class CellularSimulator::Core::Simulator;

namespace CellularSimulator
{
namespace App
{

/**
 * @class Application
 * @brief Manages the main application loop, rendering, and user input for the cellular simulator.
*/
class Application
{
public:
    Application();
    ~Application();

    Application(const Application&) = delete;
    Application& operator=(const Application&) = delete;

    /**
     * @brief Starts the main application loop, handling rendering and input.
    */
    void Run();

private:
    void UpdateLoop();
    void RenderLoop();

    void ProcessInput();
    void Draw();

    static Color GetTileColor(const Core::GridTile* Tile);
    static Color GetCellColor(const Core::Cell* InCell);

    int32_t WindowWidth = 1280;
    int32_t WindowHeight = 720;
    int32_t TileSize = 10;
    Camera2D WorldCamera{};

    std::atomic<bool> bIsPaused = false;
    std::atomic<int32_t> UpdatesPerSecond = 10;
    int32_t FramesPerSecond = 30;

    std::unique_ptr<Core::Simulator> Sim;
    
    SimulationState SimState;  
    SimulationState RenderState;
    SimulationState SharedState;
    std::mutex SharedStateMutex;

    std::thread UpdateThread;
    std::atomic<bool> bIsRunning;

    std::pair<int32_t, int32_t> InspectingPos = {0, 0};
    std::atomic<bool> bInputUpdated = false;
    std::mutex InputMutex;
};
} // namespace App
} // namespace CellularSimulator