#pragma once

namespace CellularSimulator
{
namespace Core
{
class Simulator;
class Cell;

/**
 * @class Command
 * @brief Base class for commands that can be executed on the simulator for the cell.
 */
class Command
{
public:
    virtual ~Command() = default;

    /**
     * @brief Executes the command on the given simulator for the specified cell.
     * @param Sim The simulator on which the command is executed.
     * @param Agent The cell for which the command is executed.
     */
    virtual void Execute(Simulator& Sim, Cell& Agent) = 0;
};
} // namespace Core
} // namespace CellularSimulator