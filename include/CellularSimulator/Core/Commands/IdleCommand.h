#pragma once
#include "CellularSimulator/Core/Command.h"

namespace CellularSimulator
{
namespace Core
{

/**
 * @class IdleCommand
 * @brief A command that does nothing.
 */
class IdleCommand : public Command
{
public:
    void Execute(Simulator& Sim, Cell& Agent) override;

};
} // namespace Core
} // namespace CellularSimulator