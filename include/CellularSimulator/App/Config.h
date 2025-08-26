#pragma once
#include <cstdint>
#include <string>

namespace CellularSimulator
{
namespace App
{

/**
 * @struct Config
 * @brief Provides application configuration.
 */
struct Config
{
    int32_t WindowWidth = 1280;
    int32_t WindowHeight = 720;
    int32_t FramesPerSecond = 30;
    bool bStartFullscreen = false;

    int32_t SimWidth = 300;
    int32_t SimHeight = 300;
    float InitialDensity = 0.5f;
    int32_t UpdatesPerSecond = 60;

    int32_t Seed = 0;

    int32_t GenomeLength = 16;
    int32_t InitialEnergy = 100;
};

} // namespace App
} // namespace CellularSimulator