#include "CellularSimulator/App/ConfigLoader.h"
#include <fstream>

#include "CellularSimulator/App/Config.h"
#include "nlohmann/json.hpp"

using namespace CellularSimulator::App;
using json = nlohmann::json;

std::optional<Config> ConfigLoader::LoadConfigFromFile(const std::string& FilePath)
{
    std::ifstream File(FilePath);
    if (!File.is_open())
    {
        return std::nullopt;
    }
    json Data = json::parse(File, nullptr, false);
    if (Data.is_discarded())
    {
        return std::nullopt;
    }
    Config Cfg;
    if (Data.contains("window"))
    {
        Cfg.WindowWidth = Data["window"].value("width", Cfg.WindowWidth);
        Cfg.WindowHeight = Data["window"].value("height", Cfg.WindowHeight);
        Cfg.FramesPerSecond = Data["window"].value("fps", Cfg.FramesPerSecond);
        Cfg.bStartFullscreen = Data["window"].value("fullscreen", Cfg.bStartFullscreen);
    }
    if (Data.contains("simulation"))
    {
        Cfg.SimWidth = Data["simulation"].value("width", Cfg.SimWidth);
        Cfg.SimHeight = Data["simulation"].value("height", Cfg.SimHeight);
        Cfg.InitialDensity = Data["simulation"].value("density", Cfg.InitialDensity);
        Cfg.UpdatesPerSecond = Data["simulation"].value("ups", Cfg.UpdatesPerSecond);
        Cfg.MaxUpdateTime = Data["simulation"].value("max_update_time", Cfg.MaxUpdateTime);
        Cfg.InitialEnergy = Data["simulation"].value("initial_energy", Cfg.InitialEnergy);
        Cfg.Seed = Data["simulation"].value("seed", Cfg.Seed);
        Cfg.bRandomGenome = Data["simulation"].value("random_genome", Cfg.bRandomGenome);
        Cfg.GenomeLength = Data["simulation"].value("genome_length", Cfg.GenomeLength);
        Cfg.InitialPopulationGenome = Data["simulation"].value("initial_population_genome", Cfg.InitialPopulationGenome);
        Cfg.EnergyConsumption = Data["simulation"].value("energy_consumption", Cfg.EnergyConsumption);
        Cfg.bEnergyConsumptionIgnoreDefence = Data["simulation"].value("energy_consumption_ignore_defence",
            Cfg.bEnergyConsumptionIgnoreDefence);
    }
    return Cfg;
}