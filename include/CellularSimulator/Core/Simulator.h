#pragma once
#include <list>
#include <vector>
#include <cstdint>

#include "CommandFactory.h"

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

    [[nodiscard]] bool IsTileValidAndEmpty(int32_t X, int32_t Y) const;
    void MoveCell(Cell* Agent, int32_t NewX, int32_t NewY);
    Cell* SpawnCell(int32_t X, int32_t Y, EDirection Direction, std::vector<std::string> Genome);

private:
    int32_t Width = 256;
    int32_t Height = 256;
    std::vector<GridTile> Grid;
    std::list<Cell> AllCells;

    CommandFactory CmdFactory;

    int32_t GenomeLength = 16;
};
} // namespace Core
} // namespace CellularSimulator