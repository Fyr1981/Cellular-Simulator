#include "CellularSimulator/Core/Commands/TurnRightCommand.h"
#include "CellularSimulator/Core/Cell.h"
#include "CellularSimulator/Core/CommandRegistry.h"

using namespace CellularSimulator::Core;

void TurnRightCommand::Execute(Simulator& Sim, Cell& Agent)
{
    Agent.SetDirection(TurnRight(Agent.GetDirection()));
}

namespace
{
const CommandRegistrar<TurnRightCommand> Registrar("TurnRight");
}