#include "CellularSimulator/Core/Commands/PhotosynthesisCommand.h"
#include "CellularSimulator/Core/Cell.h"
#include "CellularSimulator/Core/CommandRegistry.h"

using namespace CellularSimulator::Core;

void PhotosynthesisCommand::Execute(Simulator& Sim, Cell& Agent)
{
    Agent.AddEnergy(20);
}

namespace
{
const CommandRegistrar<PhotosynthesisCommand> Registrar("Photosynthesis", GREEN);
}