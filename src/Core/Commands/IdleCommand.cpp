#include "CellularSimulator/Core/Commands/IdleCommand.h"
#include "CellularSimulator/Core/CommandRegistry.h"

using namespace CellularSimulator::Core;

void IdleCommand::Execute(Simulator& Sim, Cell& Agent)
{
}

namespace
{
const CommandRegistrar<IdleCommand> Registrar("Idle");
}