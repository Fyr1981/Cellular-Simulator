#include "CellularSimulator/Core/Commands/TurnLeftCommand.h"
#include "CellularSimulator/Core/Cell.h"
#include "CellularSimulator/Core/CommandRegistry.h"

using namespace CellularSimulator::Core;

void TurnLeftCommand::Execute(Simulator& Sim, Cell& Agent)
{
    Agent.SetDirection(TurnLeft(Agent.GetDirection()));
}

namespace
{
const CommandRegistrar Registrar("TurnLeft", MakeCommandCreator<TurnLeftCommand>());
}