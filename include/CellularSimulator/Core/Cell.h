#pragma once
#include <cstdint>
#include <string>
#include <vector>

#include "CellSimulatorTypes.h"

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
    Cell(int32_t InX, int32_t InY, EDirection InDirection, std::vector<std::string> InGenome);

    /**
     * @brief Decides the next command for the cell.
     * @return The name of the current command from the genome or "None" if the genome is empty.
     */
    std::string DecideNextCommand();

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

    /**
     * @brief Gets the direction of the cell.
     * @return The direction of the cell.
     */
    [[nodiscard]] EDirection GetDirection() const;

private:
    int32_t X;
    int32_t Y;
    EDirection Direction;
    std::vector<std::string> Genome;
    size_t GenomePointer = 0;
};
} // namespace Core
} // namespace CellularSimulator