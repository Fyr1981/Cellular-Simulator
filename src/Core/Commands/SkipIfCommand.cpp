#include "CellularSimulator/Core/Commands/SkipIfCommand.h"

#include <string>

#include "CellularSimulator/Core/Cell.h"
#include "CellularSimulator/Core/CommandManager.h"
#include "CellularSimulator/Core/GridTile.h"
#include "CellularSimulator/Core/Simulator.h"

using namespace CellularSimulator::Core;


SkipIfCommand::SkipIfCommand(SkipPredicate Predicate): Condition(Predicate)
{
}

void SkipIfCommand::Execute(Simulator& Sim, Cell& Agent)
{
    if (Condition)
    {
        if (Condition(Sim, Agent))
        {
            Agent.MoveToNextCommand();
        }
    }
}

bool IsCellAhead(Simulator& Sim, Cell& Agent)
{
    int32_t NextX, NextY;
    GetForwardXY(Agent.GetDirection(), NextX, NextY, Agent.GetX(), Agent.GetY());
    const auto* Tile = Sim.GetTile(NextX, NextY);
    return Tile && Tile->HasCell();
}

bool IsNoCellAhead(Simulator& Sim, Cell& Agent)
{
    return !IsCellAhead(Sim, Agent);
}

auto CreateEnergyPredicate(int32_t Threshold, bool bSkipIfAbove)
{
    return [Threshold, bSkipIfAbove](Simulator& Sim, Cell& Agent) -> bool
    {
        if (bSkipIfAbove)
        {
            return Agent.GetEnergy() > Threshold;
        }
        return Agent.GetEnergy() < Threshold;
    };
}

auto CreateColorPredicate(int32_t Threshold, bool bSkipIfAbove)
{
    return [Threshold, bSkipIfAbove](Simulator& Sim, Cell& Agent) -> bool
    {
        int32_t NextX, NextY;
        GetForwardXY(Agent.GetDirection(), NextX, NextY, Agent.GetX(), Agent.GetY());
        const auto* Tile = Sim.GetTile(NextX, NextY);
        if (!Tile || !Tile->HasCell()) return false;
        const Cell* Victim = Tile->GetCell();
        if (!Victim) return false;
        const Color VictimColor = Victim->GetColor();
        const Color AgentColor = Agent.GetColor();
        const int32_t Diff = std::abs(VictimColor.a - AgentColor.a) + std::abs(VictimColor.r - AgentColor.r) +
                             std::abs(VictimColor.g - AgentColor.g) + std::abs(VictimColor.b - AgentColor.b);
        return bSkipIfAbove ? Diff > Threshold : Diff < Threshold;
    };
}

namespace
{
struct ConditionalCommandRegistrar
{
    ConditionalCommandRegistrar()
    {
        // Cell Ahead
        CommandManager::RegisterCommand(std::string("SkipIf_CellAhead"), std::make_unique<SkipIfCommand>(IsCellAhead), SKYBLUE);
        CommandManager::RegisterCommand(std::string("SkipIf_NoCellAhead"), std::make_unique<SkipIfCommand>(IsNoCellAhead), DARKBLUE);

        // Energy
        for (int32_t EnergyLevel = 0; EnergyLevel < 100; EnergyLevel += 10)
        {
            std::string NameAbove = "SkipIf_EnergyAbove_" + std::to_string(EnergyLevel);
            SkipPredicate PredicateAbove = CreateEnergyPredicate(EnergyLevel, true);
            CommandManager::RegisterCommand(NameAbove, std::make_unique<SkipIfCommand>(PredicateAbove), BLACK);

            std::string NameBelow = "SkipIf_EnergyBelow_" + std::to_string(EnergyLevel);
            SkipPredicate PredicateBelow = CreateEnergyPredicate(EnergyLevel, false);
            CommandManager::RegisterCommand(NameBelow, std::make_unique<SkipIfCommand>(PredicateBelow), WHITE);
        }

        // Color
        for (int32_t ColorLevel = 1; ColorLevel < 256*4; ColorLevel *= 2)
        {
            std::string NameAbove = "SkipIf_ColorDifferenceAbove_" + std::to_string(ColorLevel);
            SkipPredicate PredicateAbove = CreateColorPredicate(ColorLevel, true);
            CommandManager::RegisterCommand(NameAbove, std::make_unique<SkipIfCommand>(PredicateAbove), BROWN);

            std::string NameBelow = "SkipIf_ColorDifferenceBelow_" + std::to_string(ColorLevel);
            SkipPredicate PredicateBelow = CreateColorPredicate(ColorLevel, false);
            CommandManager::RegisterCommand(NameBelow, std::make_unique<SkipIfCommand>(PredicateBelow), BROWN);
        }
    }
};

const ConditionalCommandRegistrar Registrar;
}