#pragma once

#include <memory>
#include "raylib.h"
#include "CellularSimulator/Core/Simulator.h"

struct Color; 
struct Camera2D;

class CellularSimulator::Core::GridTile;
class CellularSimulator::Core::Simulator;

namespace CellularSimulator
{
namespace App
{

class Application
{
public:
    Application();
    ~Application();
    
    void Run();

private:
    void ProcessInput();
    void Update();
    void Draw();
    
    static Color GetTileColor(const Core::GridTile* Tile);
    static Color GetCellColor(const Core::Cell* InCell);

    int32_t WindowWidth = 1280;
    int32_t WindowHeight = 720;
    int32_t CellSize = 10;

    bool bIsPaused = false;
    int32_t UpdatesPerSecond = 10;
    int32_t MaxUpdatesPerFrame = 50;
    float TimeSinceLastUpdate = 0.0;

    Camera2D WorldCamera;

    std::unique_ptr<Core::Simulator> Sim;
};
} // namespace App
} // namespace CellularSimulator