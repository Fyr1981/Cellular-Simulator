#pragma once
#include "CellularSimulator/Core/Command.h"

namespace CellularSimulator
{
namespace Core
{

/**
 * @class PhotosynthesisCommand
 * @brief A command that allows a cell to gain energy.
 */
class PhotosynthesisCommand : public Command
{
public:
    PhotosynthesisCommand(int32_t Energy);
    /**
    * @brief Executes the photosynthesis command to generate energy
    * 
    * Adds a fixed amount of energy (20 units) to the executing cell.
    * This simulates photosynthesis or other energy generation mechanisms
    * in the cellular automaton. The energy is added directly to the
    * cell's current energy reserves without any preconditions.
    * 
    * @param Sim Reference to the simulator environment (unused)
    * @param Agent Reference to the cell executing this command
    * 
    * @note Always adds exactly 20 energy units
    * @note No maximum energy limit is enforced by this command
    * @note Represents a basic energy production mechanism
    */
    void Execute(Simulator& Sim, Cell& Agent) override;

private:
    int32_t EnergyGain = 15;
};
} // namespace Core
} // namespace CellularSimulator