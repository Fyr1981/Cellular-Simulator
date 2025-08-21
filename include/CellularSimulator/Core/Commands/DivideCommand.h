#pragma once
#include "CellularSimulator/Core/Command.h"

namespace CellularSimulator
{
namespace Core
{

/**
 * @class DivideCommand
 * @brief Spawn a new agent on the next empty tile. It gets a half of the agent's energy and probably a gene mutation.
 */
class DivideCommand : public Command
{
public:
    void Execute(Simulator& Sim, Cell& Agent) override;
};
} // namespace Core
} // namespace CellularSimulator