#include "CellularSimulator/Core/Commands/GiveEnergyCommand.h"
#include <string>
#include "CellularSimulator/Core/Cell.h"
#include "CellularSimulator/Core/CellSimulatorTypes.h"
#include "CellularSimulator/Core/CommandManager.h"
#include "CellularSimulator/Core/GridTile.h"
#include "CellularSimulator/Core/Simulator.h"

using namespace CellularSimulator::Core;

GiveEnergyCommand::GiveEnergyCommand(int32_t GiveAmount): EnergyToGive(GiveAmount)
{
    EnergyCost = EnergyToGive;
}

void GiveEnergyCommand::Execute(Simulator& Sim, Cell& Agent)
{
    int32_t NextX, NextY;
    GetForwardXY(Agent.GetDirection(), NextX, NextY, Agent.GetX(), Agent.GetY());
    GridTile* TargetTile = Sim.GetTile(NextX, NextY);
    if (!TargetTile || !TargetTile->HasCell()) return;
    Cell* Victim = TargetTile->GetCell();
    if (!Victim) return;
    const int32_t Give = std::min(EnergyToGive, Agent.GetEnergy());
    Victim->AddEnergy(Give);
    Command::Execute(Sim, Agent);
}

namespace
{
struct GiveEnergyRegistrar
{
    GiveEnergyRegistrar()
    {
        for (int32_t i = 1; i <= 100; ++i)
        {
            std::string CommandName = "GiveEnergy: " + std::to_string(i);
            auto CommandInstance = std::make_unique<GiveEnergyCommand>(i);
            CommandManager::RegisterCommand(CommandName, std::move(CommandInstance), YELLOW);
        }
    }
};

const GiveEnergyRegistrar Registrar;
}