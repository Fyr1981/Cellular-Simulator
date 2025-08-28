#include "CellularSimulator/Core/Commands/DivideCommand.h"
#include <cstdint>
#include <random>
#include <string>

#include "CellularSimulator/Core/Cell.h"
#include "CellularSimulator/Core/CellSimulatorTypes.h"
#include "CellularSimulator/Core/CommandRegistry.h"
#include "CellularSimulator/Core/Simulator.h"

using namespace CellularSimulator::Core;

DivideCommand::DivideCommand(float InMutationChance): MutationChance(InMutationChance)
{
}

void DivideCommand::Execute(Simulator& Sim, Cell& Agent)
{
    Command::Execute(Sim, Agent);
    const int32_t HalfEnergy = Agent.GetEnergy() / 2;
    const EDirection Direction = Agent.GetDirection();
    int32_t NextX;
    int32_t NextY;
    GetForwardXY(Direction, NextX, NextY, Agent.GetX(), Agent.GetY());
    if (!Sim.IsTileValidAndEmpty(NextX, NextY)) return;
    std::vector<size_t> NewGenome = Agent.GetGenome();
    std::uniform_real_distribution<float> Mutation(0.0f, 1.0f);
    std::mt19937& Rng = Sim.GetRNG();
    if (Mutation(Rng) < MutationChance)
    {
        const auto AvailableCommands = CommandManager::GetRegisteredCommandNamesHashes();
        if (!AvailableCommands.empty())
        {
            std::uniform_int_distribution<size_t> CmdIndex(0, AvailableCommands.size() - 1);
            std::uniform_int_distribution<size_t> GeneIndex(0, NewGenome.size() - 1);
            NewGenome[GeneIndex(Rng)] = AvailableCommands[CmdIndex(Rng)];
        }
        Sim.SpawnCell(NextX, NextY, Agent.GetDirection(), NewGenome, HalfEnergy);
    }
    else
    {
        Sim.SpawnCell(NextX, NextY, Agent.GetDirection(), NewGenome, HalfEnergy, Agent.GetColor());
    }
    Agent.ConsumeEnergyIgnoreDefendings(HalfEnergy);
}

namespace
{
struct DivideRegistrar
{
    DivideRegistrar()
    {
        for (float MutationChance = 0.0f; MutationChance <= 1.0f; MutationChance += 0.05f)
        {
            std::string CommandName = "DivideWithMutationChance: " + std::to_string(MutationChance);
            auto CommandInstance = std::make_unique<DivideCommand>(MutationChance);
            CommandManager::RegisterCommand(CommandName, std::move(CommandInstance), GOLD);
        }
    }
};

const DivideRegistrar Registrar;
}