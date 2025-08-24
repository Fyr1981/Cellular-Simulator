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
    void UpdateFromBuffer(SimulationState& Other) noexcept
    {
        Tiles.swap(Other.Tiles);
        Inspector = Other.Inspector;
    }
};

}  // namespace App
}  // namespace CellularSimulator