#include "CellularSimulator/Core/Commands/MoveForwardCommand.h"
#include <cstdint>
#include "CellularSimulator/Core/Cell.h"
#include "CellularSimulator/Core/CellSimulatorTypes.h"
#include "CellularSimulator/Core/CommandRegistry.h"
#include "CellularSimulator/Core/Simulator.h"

using namespace CellularSimulator::Core;

void MoveForwardCommand::Execute(Simulator& Sim, Cell& Agent)
{
    const int32_t CurrentX = Agent.GetX();
    const int32_t CurrentY = Agent.GetY();
    const EDirection Direction = Agent.GetDirection();

    int32_t NextX = CurrentX;
    int32_t NextY = CurrentY;

    switch (Direction)
    {
        case EDirection::North: NextY--;
            break;
        case EDirection::East: NextX++;
            break;
        case EDirection::South: NextY++;
            break;
        case EDirection::West: NextX--;
            break;
        case EDirection::None: break;
    }
    if (Sim.IsTileValidAndEmpty(NextX, NextY))
    {
        Sim.MoveCell(&Agent, NextX, NextY);
    }
}

namespace
{
const CommandRegistrar Registrar("MoveForward", MakeCommandCreator<MoveForwardCommand>());
}