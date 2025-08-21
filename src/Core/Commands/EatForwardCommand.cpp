#include "CellularSimulator/Core/Commands/EatForwardCommand.h"
#include "CellularSimulator/Core/Cell.h"
#include "CellularSimulator/Core/CommandRegistry.h"
#include "CellularSimulator/Core/GridTile.h"
#include "CellularSimulator/Core/Simulator.h"

using namespace CellularSimulator::Core;

void EatForwardCommand::Execute(Simulator& Sim, Cell& Agent)
{
    int32_t NextX, NextY;
    GetForwardXY(Agent.GetDirection(), NextX, NextY, Agent.GetX(), Agent.GetY());
    GridTile* TargetTile = Sim.GetTile(NextX, NextY);
    if (!TargetTile || !TargetTile->HasCell()) return;
    Cell* Victim = TargetTile->GetCell();
    if (!Victim) return;
    const float EnergySteal = std::min(20.f, Victim->GetEnergy());
    Victim->ConsumeEnergy(EnergySteal);
    Agent.AddEnergy(EnergySteal);
}

namespace
{
const CommandRegistrar<EatForwardCommand> Registrar("EatForward");
}