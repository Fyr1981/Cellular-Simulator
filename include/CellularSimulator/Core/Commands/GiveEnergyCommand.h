#pragma once
#include "CellularSimulator/Core/Command.h"

namespace CellularSimulator
{
namespace Core
{

/**
 * @class GiveEnergyCommand
 * @brief Give energy to the cell in the direction the agent is facing
 */
class GiveEnergyCommand : public Command
{
public:
    /**
     * @brief Construct a new Give Energy Command object
     * @param GiveAmount Amount of energy to give to the target cell
     */
    GiveEnergyCommand(int32_t GiveAmount);

    /**
     * @brief Execute the command giving energy to the cell in the direction the agent is facing
     * @param Sim Simulator instance
     * @param Agent Agent instance
     */
    void Execute(Simulator& Sim, Cell& Agent) override;

private:
    /**
    * @brief Amount of energy to give to the target cell
    */
    int32_t EnergyToGive = 20;
};
}
}