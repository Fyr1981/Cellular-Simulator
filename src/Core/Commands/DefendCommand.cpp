#include "CellularSimulator/Core/Commands/DefendCommand.h"
#include "CellularSimulator/Core/Cell.h"
#include "CellularSimulator/Core/CommandRegistry.h"
#include "CellularSimulator/Core/Commands/DeathCommand.h"

using namespace CellularSimulator::Core;

void DefendCommand::Execute(Simulator& Sim, Cell& Agent)
{
    Agent.AddDefendings(2);
}

namespace
{
const CommandRegistrar<DefendCommand> Registrar("Defend", GRAY);
}