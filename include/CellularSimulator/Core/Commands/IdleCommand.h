#pragma once
#include "CellularSimulator/Core/Command.h"

namespace CellularSimulator
{
namespace Core
{

/**
 * @class IdleCommand
 * @brief A command that does nothing.
 */
class IdleCommand : public Command
{
public:
    /**
    * @brief Executes the idle command (no operation)
    * 
    * This command performs no actions when executed. It serves as a placeholder
    * or "do nothing" instruction in the cellular automaton's command set.
    * The agent remains in its current state without any changes to position,
    * direction, or energy.
    * 
    * @param Sim Reference to the simulator environment (unused)
    * @param Agent Reference to the cell executing this command (unused)
    * 
    * @note This is an intentionally empty implementation
    * @note Useful for genetic algorithms where some genes should have no effect
    */
    void Execute(Simulator& Sim, Cell& Agent) override;

};
} // namespace Core
} // namespace CellularSimulator