#pragma once

#include "CellularSimulator/Core/Simulator.h"
#include <memory>

namespace CellularSimulator
{
namespace App
{
class Simulator;

class Application
{
public:
    Application();
    ~Application();
    
    void Run();

private:
    void Update();
    void Draw();

    int32_t WindowWidth = 1280;
    int32_t WindowHeight = 720;
    int32_t CellSize = 5;

    std::unique_ptr<Core::Simulator> Sim;
};
} // namespace App
} // namespace CellularSimulator