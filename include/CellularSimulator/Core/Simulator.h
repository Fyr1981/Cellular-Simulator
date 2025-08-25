#pragma once
#include <list>
#include <vector>
#include <cstdint>
#include <random>

#include "CommandManager.h"

namespace CellularSimulator::Core
{
enum class EDirection;
}

namespace CellularSimulator
{
namespace Core
{
class GridTile;
class Cell;

/**
 * @class Simulator
 * @brief Manages all simulation agents (Cells) and the world grid (GridTiles).
 */
class Simulator
{
public:
    /**
     * @brief Construct the simulator with a grid of the specified size.
     * @param InWidth The width of the grid.
     * @param InHeight The height of the grid.
     */
    explicit Simulator(int32_t InWidth, int32_t InHeight);

    /**
     * @brief Advances the entire simulation by one step.
     */
    void Update();

    /**
     * @brief Clears the grid and populates it with a random distribution of cells.
     * @param Density The probability (0.0 to 1.0) for any tile to contain a cell.
     */
    void Randomize(float Density);

    /**
     * @brief Provides read-only access to a specific tile on the grid.
     * @param X The x-coordinate of the tile.
     * @param Y The y-coordinate of the tile.
     * @return A const pointer to the Tile, or nullptr if coordinates are out of bounds.
     */
    [[nodiscard]] GridTile* GetTile(int32_t X, int32_t Y);

    /**
     * @brief Gets the width of the simulation grid.
     * @return The grid width.
     */
    [[nodiscard]] int32_t GetWidth() const;

    /**
     * @brief Gets the height of the simulation grid.
     * @return The grid height.
     */
    [[nodiscard]] int32_t GetHeight() const;

    /**
     * @brief Checks if the specified tile is valid and empty.
     * @param X The x-coordinate of the tile.
     * @param Y The y-coordinate of the tile.
     * @return True if the tile is valid and empty, false otherwise.
     */
    [[nodiscard]] bool IsTileValidAndEmpty(int32_t X, int32_t Y) const;

    /**
     * @brief Moves a cell to a new location if the tile is valid and empty.
     * @param Agent The cell to move.
     * @param NewX The new x-coordinate of the cell.
     * @param NewY The new y-coordinate of the cell.
     */
    void MoveCell(Cell* Agent, int32_t NewX, int32_t NewY);

    /**
     * @brief Spawns a new cell at the specified location.
     * @param X The x-coordinate of the cell.
     * @param Y The y-coordinate of the cell.
     * @param Direction The initial direction of the cell.
     * @param Genome The genome of the cell.
     * @param Energy The initial energy of the cell.
     * @return A pointer to the newly spawned cell, or nullptr if the tile is not valid or occupied.
     */
    Cell* SpawnCell(int32_t X, int32_t Y, EDirection Direction, std::vector<size_t> Genome, float Energy);

    /**
     * @brief Returns a reference to the random number generator used by the simulator.
     * @return A reference to the random number generator.
     */
    std::mt19937& GetRNG();

    /**
     * @brief Returns the number of active cells in the simulation.
     * @return The number of active cells.
     */
    size_t GetActiveCellCount() const { return ActiveCellCount; }

    /**
     * @brief Returns a pointer to the cell at the specified index.
     * @param Index The index of the cell.
     * @return A pointer to the cell, or nullptr if the index is out of bounds.
     */
    Cell* GetActiveCellByIndex(size_t Index);

private:
    int32_t Width = 256;
    int32_t Height = 256;
    std::vector<GridTile> Grid;
    std::vector<Cell> CellPool;
    size_t ActiveCellCount = 0;

    CommandManager CmdManager;

    int32_t GenomeLength = 16;

    std::mt19937 RandomGenerator;
};
} // namespace Core
} // namespace CellularSimulator