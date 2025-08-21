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
    void Execute(Simulator& Sim, Cell& Agent) override;
};

} // namespace Core
} // namespace CellularSimulator