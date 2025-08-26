#pragma once
#include "CellularSimulator/Core/Command.h"

namespace CellularSimulator
{
namespace Core
{

/**
 * @class MoveForwardCommand
 * @brief Move the agent forward by one cell by looking at the direction it is facing
 */
class MoveForwardCommand : public Command
{
public:
    /**
 * @brief Executes the move forward command to relocate the cell
 * 
 * Attempts to move the cell one tile forward in the direction it is currently
 * facing. The movement only occurs if the target tile is valid (within bounds)
 * and empty (no other cell occupies it). If the target tile is occupied or
 * invalid, the command fails silently and the cell remains in place.
 * 
 * @param Sim Reference to the simulator environment
 * @param Agent Reference to the cell executing this command
 * 
 * @note Operation fails silently if target tile is invalid or occupied
 * @note Cell direction determines the forward movement vector
 * @note No energy cost is associated with movement
 */
    void Execute(Simulator& Sim, Cell& Agent) override;
};
} // namespace Core
} // namespace CellularSimulator