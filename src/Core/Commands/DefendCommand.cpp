#include "CellularSimulator/Core/Commands/DefendCommand.h"
#include <string>
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
        for (int32_t i = 1; i <= 4; ++i)
        {
            std::string CommandName = "Defend: " + std::to_string(i);
            auto CommandInstance = std::make_unique<DefendCommand>(i * 10, i);
            CommandManager::RegisterCommand(CommandName, std::move(CommandInstance), GRAY);
        }
    }
};

const DefendRegistrar Registrar;
}