#pragma once
#include <cstdint>

namespace CellularSimulator
{
namespace Core
{

/**
 * @class Cell
 * @brief Represents the state of a single living organism.
 *
 * This class is a data container for the properties of a cell,
 * such as its energy or genes. It is not aware of its position or color.
 * The existence of a Cell object implies it is "alive".
 */
class Cell
{
public:
    /**
     * @brief Constructs a cell.
     * @param InX The x-coordinate of the cell.
     * @param InY The y-coordinate of the cell.
     */
    Cell(int32_t InX, int32_t InY);

    /**
     * @brief Updates the internal state of the cell for one simulation step.
     * @note This is a placeholder for future logic like energy consumption.
     */
    void Update();

    /**
     * @brief Gets the x-coordinate of the cell.
     * @return The x-coordinate of the cell.
     */
    [[nodiscard]] int32_t GetX() const;

    /**
     * @brief Gets the y-coordinate of the cell.
     * @return The y-coordinate of the cell.
     */
    [[nodiscard]] int32_t GetY() const;

private:
    int32_t X;
    int32_t Y;
};
} // namespace Core
} // namespace CellularSimulator