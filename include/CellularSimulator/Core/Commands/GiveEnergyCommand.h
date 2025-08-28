#pragma once
#include "CellularSimulator/Core/Command.h"

namespace CellularSimulator
{
namespace Core
{


class GiveEnergyCommand : public Command
{
public:
    GiveEnergyCommand(int32_t GiveAmount);
    
    void Execute(Simulator& Sim, Cell& Agent) override;

private:
    /**
    * @brief Amount of energy to give to the target cell
    */
    int32_t EnergyToGive = 20;
};
}
}