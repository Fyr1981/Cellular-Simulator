#pragma once
#include "CellularSimulator/Core/Command.h"

namespace CellularSimulator
{
namespace Core
{

/**
 * @class TurnLeftCommand
 * @brief Turn the agent 90 degrees to the left
 */
class TurnLeftCommand : public Command
{
public:
    /**
    * @brief Executes the turn left command to rotate the cell counterclockwise
    * 
    * Rotates the cell's facing direction 90 degrees to the left (counterclockwise).
    * This changes the cell's orientation which affects the direction for subsequent
    * movement, eating, and division commands. The rotation is instantaneous and
    * does not consume energy or require any preconditions.
    * 
    * @param Sim Reference to the simulator environment (unused)
    * @param Agent Reference to the cell executing this command
    * 
    * @note Rotation is always exactly 90 degrees counterclockwise
    * @note No energy cost is associated with turning
    * @note Affects the forward direction for other directional commands
    */
    void Execute(Simulator& Sim, Cell& Agent) override;
};

} // namespace Core
} // namespace CellularSimulator