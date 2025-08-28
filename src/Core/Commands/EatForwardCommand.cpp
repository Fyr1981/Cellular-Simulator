#include "CellularSimulator/Core/Commands/EatForwardCommand.h"

#include <string>

#include "CellularSimulator/Core/Cell.h"
#include "CellularSimulator/Core/CommandRegistry.h"
#include "CellularSimulator/Core/GridTile.h"
#include "CellularSimulator/Core/Simulator.h"

using namespace CellularSimulator::Core;

EatForwardCommand::EatForwardCommand(int32_t EnergyToSteal): EnergySteal(EnergyToSteal)
{
    EnergyCost = EnergySteal / 2;
}

void EatForwardCommand::Execute(Simulator& Sim, Cell& Agent)
{
    Command::Execute(Sim, Agent);
    int32_t NextX, NextY;
    GetForwardXY(Agent.GetDirection(), NextX, NextY, Agent.GetX(), Agent.GetY());
    GridTile* TargetTile = Sim.GetTile(NextX, NextY);
    if (!TargetTile || !TargetTile->HasCell()) return;
    Cell* Victim = TargetTile->GetCell();
    if (!Victim) return;
    const int32_t Steal = std::min(EnergySteal, Victim->GetEnergy());
    Victim->ConsumeEnergy(Steal);
    Agent.AddEnergy(Steal);
}

namespace
{
struct EatForwardRegistrar
{
    EatForwardRegistrar()
    {
        for (int32_t i = 1; i <= 100; ++i)
        {
            std::string CommandName = "EatForward: " + std::to_string(i);
            auto CommandInstance = std::make_unique<EatForwardCommand>(i);
            CommandManager::RegisterCommand(CommandName, std::move(CommandInstance), RED);
        }
    }
};

const EatForwardRegistrar Registrar;
}