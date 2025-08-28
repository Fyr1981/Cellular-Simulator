#pragma once
#include <cstdint>
#include <string>
#include <vector>

namespace CellularSimulator
{
namespace App
{

/**
 * @struct Config
 * @brief Provides full application configuration.
 */
struct Config
{
    // Window settings
    /**
     * @brief Window width in pixels.
     */
    int32_t WindowWidth = 1280;
    /**
     * @brief Window height in pixels.
     */
    int32_t WindowHeight = 720;
    /**
     * @brief Target frames per second to render.
     */
    int32_t FramesPerSecond = 30;
    /**
     * @brief Whether to start the application in fullscreen mode.
     */
    bool bStartFullscreen = false;

    // Simulation settings
    /**
     * @brief Width of the simulation grid.
     */
    int32_t SimWidth = 300;
    /**
     * @brief Height of the simulation grid.
     */
    int32_t SimHeight = 300;
    /**
     * @brief Initial probability (0.0 to 1.0) for any tile to contain a cell.
     */
    float InitialDensity = 0.5f;
    /**
     * @brief Target updates per second for the simulation.
     */
    int32_t UpdatesPerSecond = 60;
    /**
    * @brief Maximum time (in seconds) allowed for a single update.
    */
    float MaxUpdateTime = 0.25f;
    /**
    * @brief Initial energy for each cell.
    */
    int32_t InitialEnergy = 100;
    /**
    * @brief Seed for random number generation.
    */
    int32_t Seed = 0;
    /**
     * @brief Whether to initialize cells with a random genome.
     */
    bool bRandomGenome = true;
    /**
    * @brief Length of the genome for each cell if initialized with a random genome.
    */
    int32_t GenomeLength = 16;
    /**
     * @brief Genome for the initial population of cells if bRandomGenome is false.
     */
    std::vector<std::string> InitialPopulationGenome;
    /**
     * @brief Energy consumption per cell per update.
     */
    int32_t EnergyConsumption = 10;
    /**
     * @brief Whether to ignore defence when consuming energy every step.
     */
    bool bEnergyConsumptionIgnoreDefence = false;

    // Cell settings
    /**
     * @brief Maximum number of defences a cell can have.
     */
    int32_t MaxDefences = 10;
    /**
     * @brief Maximum energy a cell can have.
     */
    int32_t MaxEnergy = 100;
};

} // namespace App
} // namespace CellularSimulator