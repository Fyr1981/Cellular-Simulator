#pragma once

// Forward declarations
namespace CellularSimulator
{
namespace Core
{
class Simulator;
class Cell;
}
}

namespace CellularSimulator
{
namespace Core
{

/**
 * @class Command
 * @brief Base class for commands that can be executed on the simulator for the cell.
 */
class Command
{
public:
    virtual ~Command() = default;

    virtual void Execute(Simulator& Sim, Cell& Agent) = 0;
};
} // namespace Core
} // namespace CellularSimulator