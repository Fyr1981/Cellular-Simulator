#pragma once

namespace CellularSimulator
{
namespace Core
{

/**
 * @enum EDirection
 * @brief Enumerates the directions that a cell can face and do actions in.
 */
enum class EDirection
{
    North, // Positive Y axis
    East, // Positive X axis
    South, // Negative Y axis
    West, // Negative X axis
    None
};

} // namespace Core
} // namespace CellularSimulator