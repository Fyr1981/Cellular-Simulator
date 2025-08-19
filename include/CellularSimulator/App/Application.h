#pragma once

#include "CellularSimulator/Core/Simulator.h"
#include <memory>

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
    std::unique_ptr<Core::Simulator> Sim;
};
} // namespace App
} // namespace CellularSimulator