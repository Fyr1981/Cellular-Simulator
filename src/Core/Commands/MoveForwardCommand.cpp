#include "CellularSimulator/Core/Commands/MoveForwardCommand.h"
#include <cstdint>
#include "CellularSimulator/Core/Cell.h"
#include "CellularSimulator/Core/CellSimulatorTypes.h"
#include "CellularSimulator/Core/CommandRegistry.h"
#include "CellularSimulator/Core/Simulator.h"

using namespace CellularSimulator::Core;

void MoveForwardCommand::Execute(Simulator& Sim, Cell& Agent)
{
    const EDirection Direction = Agent.GetDirection();
    int32_t NextX;
    int32_t NextY;
    GetForwardXY(Direction, NextX, NextY, Agent.GetX(), Agent.GetY());
    if (Sim.IsTileValidAndEmpty(NextX, NextY))
    {
        Sim.MoveCell(&Agent, NextX, NextY);
    }
}

namespace
{
const CommandRegistrar Registrar("MoveForward", MakeCommandCreator<MoveForwardCommand>());
}