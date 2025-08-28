#include "CellularSimulator/Core/Commands/DefendCommand.h"
#include <string>
#include "CellularSimulator/App/Config.h"
#include "CellularSimulator/App/ConfigLoader.h"
#include "CellularSimulator/Core/Cell.h"
#include "CellularSimulator/Core/CommandRegistry.h"
#include "CellularSimulator/Core/Commands/DeathCommand.h"

using namespace CellularSimulator::Core;

DefendCommand::DefendCommand(int32_t Cost, int32_t InNumDefendings)
{
    EnergyCost = Cost;
    NumDefendings = InNumDefendings;
}

void DefendCommand::Execute(Simulator& Sim, Cell& Agent)
{
    Command::Execute(Sim, Agent);
    Agent.AddDefendings(NumDefendings);
}

namespace
{
struct DefendRegistrar
{
    DefendRegistrar()
    {
        const int32_t Cost = CellularSimulator::App::ConfigLoader::GetConfig().PerDefendEnergyCost;
        const int32_t MaxValue = CellularSimulator::App::ConfigLoader::GetConfig().MaxDefences;
        for (int32_t i = 1; i <= MaxValue; ++i)
        {
            std::string CommandName = "Defend: " + std::to_string(i);
            auto CommandInstance = std::make_unique<DefendCommand>(i * Cost, i);
            CommandManager::RegisterCommand(CommandName, std::move(CommandInstance), GRAY);
        }
    }
};

const DefendRegistrar Registrar;
}