#pragma once
#include <cstdint>
#include <vector>

#include "CellSimulatorTypes.h"
#include <raylib.h>

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
     * @brief Default constructor for creating an empty cell in the object pool.
     */
    Cell();

    /**
     * @brief Constructs a cell with the specified parameters.
     * @param InX The x-coordinate of the cell.
     * @param InY The y-coordinate of the cell.
     * @param InDirection The direction of the cell.
     * @param InGenome The genome of the cell.
     * @param InEnergy The energy of the cell.
     * @param InInObjectPool Whether the cell is in the object pool or active in the simulation.
     * @note The color of the cell will be automatically calculated based on its genome.
     */
    Cell(int32_t InX, int32_t InY, EDirection InDirection, std::vector<size_t> InGenome, int32_t InEnergy, bool InInObjectPool);

    /**
     * @brief Constructs a cell with the specified parameters.
     * @param InX The x-coordinate of the cell.
     * @param InY The y-coordinate of the cell.
     * @param InDirection The direction of the cell.
     * @param InGenome The genome of the cell.
     * @param InEnergy The energy of the cell.
     * @param InInObjectPool Whether the cell is in the object pool or active in the simulation.
     * @param InColor The color of the cell for rendering purposes.
     */
    Cell(int32_t InX, int32_t InY, EDirection InDirection, std::vector<size_t> InGenome, int32_t InEnergy, bool InInObjectPool,
        Color InColor);

    /**
     * @brief Initializes the cell with all the parameters.
     * @param InX The x-coordinate of the cell.
     * @param InY The y-coordinate of the cell.
     * @param InDirection The direction of the cell.
     * @param InGenome The genome of the cell.
     * @param InEnergy The energy of the cell.
     * @param InInObjectPool Whether the cell is in the object pool or active in the simulation.
     * @param InColor The color of the cell for rendering purposes.
     * @note The color of the cell will be automatically calculated based on its genome.
     */
    void Initialize(int32_t InX, int32_t InY, EDirection InDirection, std::vector<size_t> InGenome, int32_t InEnergy, bool InInObjectPool);

    /**
     * @brief Initializes the cell with all the parameters.
     * @param InX The x-coordinate of the cell.
     * @param InY The y-coordinate of the cell.
     * @param InDirection The direction of the cell.
     * @param InGenome The genome of the cell.
     * @param InEnergy The energy of the cell.
     * @param InInObjectPool Whether the cell is in the object pool or active in the simulation.
     * @param InColor The color of the cell for rendering purposes.
     */
    void Initialize(
        int32_t InX, int32_t InY, EDirection InDirection, std::vector<size_t> InGenome, int32_t InEnergy, bool InInObjectPool,
        Color InColor);

    /**
     * @brief Decides the next command for the cell.
     * @return The name of the current command from the genome or "None" if the genome is empty.
     */
    size_t DecideNextCommand();

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
    [[nodiscard]] int32_t GetEnergy() const;

    /**
     * @brief Checks if the energy of the cell is positive so the cell is alive.
     * @return True if the cell is alive, false otherwise.
     */
    [[nodiscard]] bool IsAlive() const;

    /**
     * @brief Checks if the cell is in the object pool.
     * @return True if the cell is in the object pool, false otherwise.
     */
    [[nodiscard]] bool IsInObjectPool() const;

    /**
     * @brief Gets the genome of the cell.
     * @return The genome of the cell.
     */
    [[nodiscard]] const std::vector<size_t>& GetGenome() const;

    /**
     * @brief Gets the color of the cell for rendering purposes.
     * @return The color of the cell.
     */
    [[nodiscard]] Color GetColor() const;

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
    void AddEnergy(int32_t Amount);

    /**
     * @brief Consumes energy from the cell. If the cell is defending, it will not consume energy and will remove the defending flag.
     * @param Amount The amount of energy to consume.
     */
    void ConsumeEnergy(int32_t Amount);

    /**
    * @brief Consumes energy from the cell ignoring the defending amount.
    * @param Amount The amount of energy to consume.
    */
    void ConsumeEnergyIgnoreDefendings(int32_t Amount);

    /**
     * @brief Sets the energy of the cell. It also can remove the defending flag if the energy is less than the current energy.
     * @param InEnergy The energy of the cell.
     */
    void SetEnergy(int32_t InEnergy);

    /**
     * @brief Sets the genome of the cell.
     * @param InGenome The genome of the cell.
     */
    void SetGenome(std::vector<size_t> InGenome);

    /**
     * @brief Set cell in object pool flag.
     * @param bInObjectPool Cell in object pool flag.
     */
    void SetInObjectPool(bool bInObjectPool);

    /**
     * @brief Sets the color of the cell for rendering purposes.
     * @param InColor The color to set.
     */
    void SetColor(Color InColor);

    /**
     * @brief Moves the gene pointer to the next command.
     */
    void MoveToNextCommand();

    /**
     * @brief Adds defendings to the cell which protects it from energy consumption.
     * @param Amount The amount of defendings to add.
     */
    void AddDefendings(int32_t Amount);

    bool IsExecutedThisStep() const;
    void SetExecutedThisStep(bool bInExecuted);

private:
    void CalculateColor();

    int32_t X = 0;
    int32_t Y = 0;
    EDirection Direction = EDirection::North;
    int32_t Energy = 0;
    int32_t MaxEnergy = 100.0f;
    int32_t Defences = 0;
    int32_t MaxDefences = 8;
    std::vector<size_t> Genome;
    size_t GenomePointer = 0;
    bool bInsideObjectPool = true;
    Color CellColor = DARKGRAY;

    bool bExecutedThisStep = false;
};
} // namespace Core
} // namespace CellularSimulator