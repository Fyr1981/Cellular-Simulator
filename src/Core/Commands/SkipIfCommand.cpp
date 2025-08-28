#include "CellularSimulator/Core/Commands/SkipIfCommand.h"

#include <string>

#include "CellularSimulator/Core/Cell.h"
#include "CellularSimulator/Core/CommandManager.h"
#include "CellularSimulator/Core/GridTile.h"
#include "CellularSimulator/Core/Simulator.h"

using namespace CellularSimulator::Core;


SkipIfCommand::SkipIfCommand(SkipPredicate Predicate): Condition(std::move(Predicate))
{
}

void SkipIfCommand::Execute(Simulator& Sim, Cell& Agent)
{
    Command::Execute(Sim, Agent);
    if (Condition)
    {
        if (Condition(Sim, Agent))
        {
            Agent.MoveToNextCommand();
        }
    }
}

/**
 * @brief Checks if there is a cell in front of the agent
 * @ingroup ConditionalPredicates
 */
bool IsCellAhead(const Simulator& Sim, const Cell& Agent)
{
    int32_t NextX, NextY;
    GetForwardXY(Agent.GetDirection(), NextX, NextY, Agent.GetX(), Agent.GetY());
    const auto* Tile = Sim.GetTile(NextX, NextY);
    return Tile && Tile->HasCell();
}

/**
 * @brief Checks if there is no cell in front of the agent
 * @ingroup ConditionalPredicates
 */
bool IsNoCellAhead(const Simulator& Sim, const Cell& Agent)
{
    return !IsCellAhead(Sim, Agent);
}

/**
 * @brief Creates a predicate that checks if the agent's energy is above or below a threshold
 * @ingroup ConditionalPredicates
 */
auto CreateEnergyPredicate(int32_t Threshold, bool bSkipIfAbove)
{
    return [Threshold, bSkipIfAbove](const Simulator& Sim, const Cell& Agent) -> bool
    {
        if (bSkipIfAbove)
        {
            return Agent.GetEnergy() > Threshold;
        }
        return Agent.GetEnergy() < Threshold;
    };
}

/**
 * @brief Creates a predicate that checks if the agent's color is above or below a threshold
 * @ingroup ConditionalPredicates
 */
auto CreateColorPredicate(int32_t Threshold, bool bSkipIfAbove)
{
    return [Threshold, bSkipIfAbove](const Simulator& Sim, const Cell& Agent) -> bool
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

/**
 * @brief Checks if the agent is looking north
 * @ingroup ConditionalPredicates
 */
bool IsLookingNorth(const Simulator& Sim, const Cell& Agent)
{
    return Agent.GetDirection() == EDirection::North;
}

/**
 * @brief Checks if the agent is not looking north
 * @ingroup ConditionalPredicates
 */
bool IsNotLookingNorth(const Simulator& Sim, const Cell& Agent)
{
    return Agent.GetDirection() != EDirection::North;
}

/**
 * @brief Checks if the agent is looking east
 * @ingroup ConditionalPredicates
 */
bool IsLookingEast(const Simulator& Sim, const Cell& Agent)
{
    return Agent.GetDirection() == EDirection::East;
}

/**
 * @brief Checks if the agent is not looking east
 * @ingroup ConditionalPredicates
 */
bool IsNotLookingEast(const Simulator& Sim, const Cell& Agent)
{
    return Agent.GetDirection() != EDirection::East;
}

/**
 * @brief Checks if the agent is looking south
 * @ingroup ConditionalPredicates
 */
bool IsLookingSouth(const Simulator& Sim, const Cell& Agent)
{
    return Agent.GetDirection() == EDirection::South;
}

/**
 * @brief Checks if the agent is not looking south
 * @ingroup ConditionalPredicates
 */
bool IsNotLookingSouth(const Simulator& Sim, const Cell& Agent)
{
    return Agent.GetDirection() != EDirection::South;
}

/**
 * @brief Checks if the agent is looking west
 * @ingroup ConditionalPredicates
 */
bool IsLookingWest(const Simulator& Sim, const Cell& Agent)
{
    return Agent.GetDirection() == EDirection::West;
}

/**
 * @brief Checks if the agent is not looking west
 * @ingroup ConditionalPredicates
 */
bool IsNotLookingWest(const Simulator& Sim, const Cell& Agent)
{
    return Agent.GetDirection() != EDirection::West;
}

namespace
{
struct ConditionalCommandRegistrar
{
    ConditionalCommandRegistrar()
    {
        // Cell Ahead
        CommandManager::RegisterCommand(std::string("SkipIf: CellAhead"), std::make_unique<SkipIfCommand>(IsCellAhead), SKYBLUE);
        CommandManager::RegisterCommand(std::string("SkipIf: NoCellAhead"), std::make_unique<SkipIfCommand>(IsNoCellAhead), DARKBLUE);

        // Energy
        for (int32_t EnergyLevel = 0; EnergyLevel <= 100; EnergyLevel += 1)
        {
            std::string NameAbove = "SkipIf: EnergyAbove: " + std::to_string(EnergyLevel);
            SkipPredicate PredicateAbove = CreateEnergyPredicate(EnergyLevel, true);
            CommandManager::RegisterCommand(NameAbove, std::make_unique<SkipIfCommand>(PredicateAbove), BLACK);

            std::string NameBelow = "SkipIf: EnergyBelow: " + std::to_string(EnergyLevel);
            SkipPredicate PredicateBelow = CreateEnergyPredicate(EnergyLevel, false);
            CommandManager::RegisterCommand(NameBelow, std::make_unique<SkipIfCommand>(PredicateBelow), WHITE);
        }

        // Color
        for (int32_t ColorLevel = 1; ColorLevel < 256 * 4; ColorLevel *= 2)
        {
            std::string NameAbove = "SkipIf: ColorDifferenceAbove: " + std::to_string(ColorLevel);
            SkipPredicate PredicateAbove = CreateColorPredicate(ColorLevel, true);
            CommandManager::RegisterCommand(NameAbove, std::make_unique<SkipIfCommand>(PredicateAbove), BROWN);

            std::string NameBelow = "SkipIf: ColorDifferenceBelow: " + std::to_string(ColorLevel);
            SkipPredicate PredicateBelow = CreateColorPredicate(ColorLevel, false);
            CommandManager::RegisterCommand(NameBelow, std::make_unique<SkipIfCommand>(PredicateBelow), BROWN);
        }

        // Directions
        CommandManager::RegisterCommand(std::string("SkipIf: LookingNorth"), std::make_unique<SkipIfCommand>(IsLookingNorth), ORANGE);
        CommandManager::RegisterCommand(std::string("SkipIf: NotLookingNorth"), std::make_unique<SkipIfCommand>(IsNotLookingNorth), ORANGE);
        CommandManager::RegisterCommand(std::string("SkipIf: LookingEast"), std::make_unique<SkipIfCommand>(IsLookingEast), ORANGE);
        CommandManager::RegisterCommand(std::string("SkipIf: NotLookingEast"), std::make_unique<SkipIfCommand>(IsNotLookingEast), ORANGE);
        CommandManager::RegisterCommand(std::string("SkipIf: LookingSouth"), std::make_unique<SkipIfCommand>(IsLookingSouth), ORANGE);
        CommandManager::RegisterCommand(std::string("SkipIf: NotLookingSouth"), std::make_unique<SkipIfCommand>(IsNotLookingSouth), ORANGE);
        CommandManager::RegisterCommand(std::string("SkipIf: LookingWest"), std::make_unique<SkipIfCommand>(IsLookingWest), ORANGE);
        CommandManager::RegisterCommand(std::string("SkipIf: NotLookingWest"), std::make_unique<SkipIfCommand>(IsNotLookingWest), ORANGE);
    }
};

const ConditionalCommandRegistrar Registrar;
}