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
    void Execute(Simulator& Sim, Cell& Agent) override;
};

} // namespace Core
} // namespace CellularSimulator