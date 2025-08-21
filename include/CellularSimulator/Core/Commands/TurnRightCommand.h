#pragma once
#include "CellularSimulator/Core/Command.h"

namespace CellularSimulator
{
namespace Core
{

/**
 * @class TurnRightCommand
 * @brief Turn the agent 90 degrees to the right
 */
class TurnRightCommand : public Command
{
public:
    void Execute(Simulator& Sim, Cell& Agent) override;
};

} // namespace Core
} // namespace CellularSimulator