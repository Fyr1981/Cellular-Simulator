#include "CellularSimulator/Core/Commands/DeathCommand.h"
#include "CellularSimulator/Core/Cell.h"
#include "CellularSimulator/Core/CommandRegistry.h"

using namespace CellularSimulator::Core;

void DeathCommand::Execute(Simulator& Sim, Cell& Agent)
{
    Agent.ConsumeEnergy(100);
}

namespace
{
const CommandRegistrar<DeathCommand> Registrar("Death", BLACK);
}