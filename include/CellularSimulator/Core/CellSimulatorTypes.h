#pragma once

namespace CellularSimulator
{
namespace Core
{

/**
 * @enum EGeneCommand
 * @brief Enumerates the commands that can be executed by a cell.
 */
enum class EGeneCommand
{
    Idle, // Do nothing
    Photosynthesis, // Add energy to the cell
    MoveForward, // Move the cell forward
    TurnRight, // Turn the cell to the right by 90 degrees
    TurnLeft, // Turn the cell to the left by 90 degrees
    Divide // Divide the cell into two new cells, new cell is placed next to the parent
};

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

/**
 * @struct Action
 * @brief Struct that represents an action that cell will execute.
 * @details Contains the command to execute and the direction in which the cell will do it.
 */
struct Action
{
    // The command to execute
    EGeneCommand Command = EGeneCommand::Idle;
    // The direction in which the cell will do the command
    EDirection Direction = EDirection::None;
};

} // namespace Core
} // namespace CellularSimulator