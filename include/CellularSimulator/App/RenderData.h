#pragma once

#include <cstdint>
#include <vector>
#include "raylib.h"

namespace CellularSimulator
{
namespace App
{

/**
 * @struct TileRenderData
 * @brief Represents the rendering data for a single tile in the simulation.
 */
struct TileRenderData
{
    /**
     * @brief The x-coordinate of the tile in the grid.
     */
    int32_t X;
    /**
     * @brief The y-coordinate of the tile in the grid.
     */
    int32_t Y;
    /**
     * @brief The color to render the tile.
     */
    Color TileColor;
};

/**
 * @struct InspectorData
 * @brief Holds data for the inspector panel, including whether to display genome information and the genome itself.
 */
struct InspectorData
{
    /**
     * @brief Indicates whether genome information should be displayed in the inspector.
     */
    bool bShouldDisplayGenome = false;
    /**
     * @brief The genome data to be displayed, represented as a vector of strings.
     */
    std::vector<std::string> Genome;
};

/**
 * @struct SimulationState
 * @brief Encapsulates the entire state of the simulation for rendering purposes, including tile data and inspector information.
 */
struct SimulationState
{
    /**
     * @brief A vector containing the rendering data for all tiles in the simulation.
     */
    std::vector<TileRenderData> Tiles;
    /**
     * @brief The inspector data, including genome display information.
     */
    InspectorData Inspector;
    /**
     * @brief Updates the current simulation state from another instance, swapping tile data and copying inspector information.
     * @param Other The other SimulationState instance to copy data from.
     * @note This method uses swap for the Tiles vector to efficiently transfer ownership of the data.
     */
    void UpdateFromBuffer(SimulationState& Other) noexcept
    {
        Tiles.swap(Other.Tiles);
        Inspector = Other.Inspector;
    }
};

}  // namespace App
}  // namespace CellularSimulator