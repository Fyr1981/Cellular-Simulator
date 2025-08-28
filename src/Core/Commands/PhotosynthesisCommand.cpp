#include "CellularSimulator/Core/Commands/PhotosynthesisCommand.h"
#include "CellularSimulator/Core/Cell.h"
#include "CellularSimulator/Core/CommandRegistry.h"

using namespace CellularSimulator::Core;

void PhotosynthesisCommand::Execute(Simulator& Sim, Cell& Agent)
{
    Command::Execute(Sim, Agent);
    Agent.AddEnergy(15);
}

namespace
{
const CommandRegistrar<PhotosynthesisCommand> Registrar("Photosynthesis", GREEN);
}