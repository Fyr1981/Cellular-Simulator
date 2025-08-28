#pragma once
#include "CellularSimulator/Core/Command.h"

namespace CellularSimulator
{
namespace Core
{

/**
 * @class DefendCommand
 * @brief Defend against incoming energy consumption for a specified number of steps.
 * @note Some Energy consumption commands will ignore the defense using Cell::ConsumeEnergyIgnoreDefense()
 * @note depending on the config and hardcode.
 */
class DefendCommand : public Command
{
public:
    /**
     * @brief Construct a new Defend Command object
     * @param Cost Energy cost of the command
     * @param InNumDefendings Number of steps to defend
     */
    DefendCommand(int32_t Cost, int32_t InNumDefendings);

    /**
     * @brief Adds the number of defendings to the cell
     * @param Sim The simulator
     * @param Agent The cell to defend
     */
    void Execute(Simulator& Sim, Cell& Agent) override;

private:
    int32_t NumDefendings;
};
} // namespace Core
} // namespace CellularSimulator