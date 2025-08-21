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
    void Execute(Simulator& Sim, Cell& Agent) override;
};
} // namespace Core
} // namespace CellularSimulator