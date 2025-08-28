#include "CellularSimulator/Core/Commands/PhotosynthesisCommand.h"
#include "CellularSimulator/Core/Command.h"
#include "CellularSimulator/App/Config.h"
#include "CellularSimulator/App/ConfigLoader.h"
#include "CellularSimulator/Core/Cell.h"
#include "CellularSimulator/Core/CommandRegistry.h"

using namespace CellularSimulator::Core;

PhotosynthesisCommand::PhotosynthesisCommand(int32_t Energy): EnergyGain(Energy)
{
}

void PhotosynthesisCommand::Execute(Simulator& Sim, Cell& Agent)
{
    Command::Execute(Sim, Agent);
    Agent.AddEnergy(EnergyGain);
}

namespace
{
struct PhotosynthesisRegistrar
{
    PhotosynthesisRegistrar()
    {
        auto CommandInstance = std::make_unique<PhotosynthesisCommand>(
            CellularSimulator::App::ConfigLoader::GetConfig().PhotosynthesisEnergyGain);
        CommandManager::RegisterCommand("Photosynthesis", std::move(CommandInstance), GREEN);
    }
};

const PhotosynthesisRegistrar Registrar;
}