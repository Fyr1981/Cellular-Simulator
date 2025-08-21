#include "CellularSimulator/Core/Commands/DivideCommand.h"
#include <cstdint>
#include <random>
#include "CellularSimulator/Core/Cell.h"
#include "CellularSimulator/Core/CellSimulatorTypes.h"
#include "CellularSimulator/Core/CommandRegistry.h"
#include "CellularSimulator/Core/Simulator.h"

using namespace CellularSimulator::Core;

void DivideCommand::Execute(Simulator& Sim, Cell& Agent)
{
    const EDirection Direction = Agent.GetDirection();
    int32_t NextX;
    int32_t NextY;
    GetForwardXY(Direction, NextX, NextY, Agent.GetX(), Agent.GetY());
    if (!Sim.IsTileValidAndEmpty(NextX, NextY)) return;
    std::vector<std::string> NewGenome;
    Agent.GetGenome(NewGenome);
    std::mt19937 Rng(std::random_device{}());
    std::uniform_real_distribution<float> MutationChance(0.0f, 1.0f);
    if (MutationChance(Rng) < 0.05f)
    {
        const auto AvailableCommands = CommandFactory::GetRegisteredCommandNames();
        if (!AvailableCommands.empty())
        {
            std::uniform_int_distribution<size_t> CmdIndex(0, AvailableCommands.size() - 1);
            std::uniform_int_distribution<size_t> GeneIndex(0, NewGenome.size() - 1);

            NewGenome[GeneIndex(Rng)] = AvailableCommands[CmdIndex(Rng)];
        }
    }
    Sim.SpawnCell(NextX, NextY, Agent.GetDirection(), NewGenome, Agent.GetEnergy() / 2.f);
    Agent.ConsumeEnergy(Agent.GetEnergy() / 2.f);
}

namespace
{
const CommandRegistrar Registrar("Divide", MakeCommandCreator<DivideCommand>());
}