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
     * @param InDirection The direction of the cell.
     * @param InGenome The genome of the cell.
     * @param InEnergy The energy of the cell.
     */
    Cell(int32_t InX, int32_t InY, EDirection InDirection, std::vector<std::string> InGenome, float InEnergy);

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

    /**
     * @brief Gets the energy of the cell.
     * @return The energy of the cell.
     */
    [[nodiscard]] float GetEnergy() const;

    /**
     * @brief Checks if the energy of the cell is positive so the cell is alive.
     * @return True if the cell is alive, false otherwise.
     */
    [[nodiscard]] bool IsAlive() const;

    /**
     * @brief Gets the genome of the cell.
     * @param OutGenome The genome of the cell.
     */
    void GetGenome(std::vector<std::string>& OutGenome) const;

    /**
     * @brief Sets the x-coordinate of the cell.
     * @param InX The x-coordinate of the cell.
     */
    void SetX(int32_t InX);

    /**
     * @brief Sets the y-coordinate of the cell.
     * @param InY The y-coordinate of the cell.
     */
    void SetY(int32_t InY);

    /**
     * @brief Sets the direction of the cell.
     * @param InDirection The direction of the cell.
     */
    void SetDirection(EDirection InDirection);

    /**
     * @brief Adds energy to the cell.
     * @param Amount The amount of energy to add.
     */
    void AddEnergy(float Amount);

    /**
     * @brief Consumes energy from the cell.
     * @param Amount The amount of energy to consume.
     */
    void ConsumeEnergy(float Amount);

private:
    void SetEnergy(float InEnergy);
    
    int32_t X;
    int32_t Y;
    EDirection Direction;
    float Energy;
    std::vector<std::string> Genome;
    size_t GenomePointer = 0;
    float MaxEnergy = 100.0f;
};
} // namespace Core
} // namespace CellularSimulator