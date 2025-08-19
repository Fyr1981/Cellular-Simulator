#pragma once

namespace CellularSimulator
{
namespace Core
{
class Cell;

/**
 * @class GridTile
 * @brief Represents a single t in the grid.
 *
 * This class is a data container for the properties of a tile
 * that can contain a cell.
 */
class GridTile
{
public:
    GridTile() = default;

    /**
     *  @brief Updates the internal state of the tile for one simulation step.
     */
    void Update();

    /**
     * @brief Checks if the tile contains a cell.
     * @return True if the tile contains a cell, false otherwise.
     */
    [[nodiscard]] bool HasCell() const;

    /**
     * @brief Provides read-write access to the Cell.
     * @return A non-const pointer to the Cell, or nullptr if none exists.
     */
    [[nodiscard]] Cell* GetCell();


    /**
     * @brief Provides read-only access to the Cell.
     * @return A const pointer to the Cell, or nullptr if none exists.
     */
    [[nodiscard]] const Cell* GetCell() const;

    /**
    * @brief Sets or clears the cell pointer for this tile.
    * @param InCell A pointer to the cell that now occupies this tile, or nullptr to clear it.
    * @note This method should only be called by the Simulator which manages cell ownership.
    */
    void SetCell(Cell* InCell);

private:
    Cell* HostedCell = nullptr;
};
} // namespace Core
} // namespace CellularSimulator