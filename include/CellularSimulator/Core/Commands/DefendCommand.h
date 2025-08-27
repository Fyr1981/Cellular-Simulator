#pragma once
#include "CellularSimulator/Core/Command.h"

namespace CellularSimulator
{
namespace Core
{
class DefendCommand : public Command
{
    
public:
    void Execute(Simulator& Sim, Cell& Agent) override;
};
} // namespace Core
} // namespace CellularSimulator