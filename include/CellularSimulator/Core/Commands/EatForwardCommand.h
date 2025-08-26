#pragma once
#include "CellularSimulator/Core/Command.h"

namespace CellularSimulator
{
namespace Core
{

/**
 * @class EatForwardCommand
 * @brief Take energy from the cell in the direction the agent is facing
 */
class EatForwardCommand : public Command
{
public:
    /**
    * @brief Executes the eat forward command to steal energy from target cell
    * 
    * Attempts to consume energy from a cell located in the forward direction.
    * The command steals up to 20 energy units from the target cell and adds
    * the stolen energy to the executing agent. The actual amount stolen is
    * limited by the victim's available energy.
    * 
    * @param Sim Reference to the simulator environment
    * @param Agent Reference to the cell executing this command
    * 
    * @note Operation fails silently if no cell exists in the forward direction
    * @note Maximum energy steal per execution is 20 units
    * @note Victim's energy is reduced by the amount stolen
    */
    void Execute(Simulator& Sim, Cell& Agent) override;
};

} // namespace Core
} // namespace CellularSimulator