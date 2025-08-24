#pragma once

#include <cstdint>
#include <vector>
#include "raylib.h"


namespace CellularSimulator
{
namespace App
{

struct TileRenderData
{
    int32_t X;
    int32_t Y;
    Color TileColor;
};

struct InspectorData
{
    bool bShouldDisplayGenome = false;
    std::vector<std::string> Genome;
};

struct SimulationState
{
    std::vector<TileRenderData> Tiles;
    InspectorData Inspector;
    void Swap(SimulationState& other) noexcept
    {
        Tiles.swap(other.Tiles);
        std::swap(Inspector, other.Inspector);
    }
};

} // namespace App
} // namespace CellularSimulator