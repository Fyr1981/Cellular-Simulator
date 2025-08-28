#include "CellularSimulator/Core/Command.h"

#include "CellularSimulator/Core/Cell.h"

using namespace CellularSimulator::Core;

void Command::Execute(Simulator& Sim, Cell& Agent)
{
    Agent.ConsumeEnergyIgnoreDefendings(EnergyCost);
}