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

/**
 * @brief Turns a direction 90 degrees to the right
 * @param Direction The direction to turn from
 * @return The new direction after the turn
 */
inline EDirection TurnRight(EDirection Direction)
{
    switch (Direction)
    {
        case EDirection::North: return EDirection::East;
        case EDirection::East: return EDirection::South;
        case EDirection::South: return EDirection::West;
        case EDirection::West: return EDirection::North;
        case EDirection::None: return EDirection::None;
    }
    return EDirection::None;
}

/**
 * @brief Turns a direction 90 degrees to the left
 * @param Direction The direction to turn from
 * @return The new direction after the turn
 */
inline EDirection TurnLeft(EDirection Direction)
{
    switch (Direction)
    {
        case EDirection::North: return EDirection::West;
        case EDirection::East: return EDirection::North;
        case EDirection::South: return EDirection::East;
        case EDirection::West: return EDirection::South;
        case EDirection::None: return EDirection::None;
    }
    return EDirection::None;
}

inline void GetForwardXY(EDirection Direction, int32_t& OutX, int32_t& OutY, int32_t CurrentX, int32_t CurrentY)
{
    OutX = CurrentX;
    OutY = CurrentY;

    switch (Direction)
    {
        case EDirection::North: OutY--;
        break;
        case EDirection::East: OutX++;
        break;
        case EDirection::South: OutY++;
        break;
        case EDirection::West: OutX--;
        break;
        case EDirection::None: break;
    }
}

} // namespace Core
} // namespace CellularSimulator