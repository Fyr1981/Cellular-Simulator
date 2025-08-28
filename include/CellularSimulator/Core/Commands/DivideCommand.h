#pragma once
#include "CellularSimulator/Core/Command.h"

namespace CellularSimulator
{
namespace Core
{

/**
 * @class DivideCommand
 * @brief Spawn a new agent on the next empty tile. It gets a half of the agent's energy and probably a gene mutation.
 */
class DivideCommand : public Command
{
public:
    /**
     * @brief Construct a new Divide Command object with a mutation chance. With this mutation chance
     * one of the genes can be replaced with an any available command.
     * @param InMutationChance Mutation chance for the offspring cell
     */
    DivideCommand(double InMutationChance);
    
    /**
     * @brief Executes the divide command to create offspring cell
     * 
     * Creates a new cell in the forward direction with half of the parent's energy.
     * The offspring inherits the parent's genome with a 5% chance of random mutation.
     * If mutation occurs, one random gene is replaced with a random available command.
     * The parent cell loses half of its energy in the process.
     * 
     * @param Sim Reference to the simulator environment
     * @param Agent Reference to the cell executing this command
     * 
     * @note Operation fails silently if the target tile is invalid or occupied
     * @note Mutation rate is fixed at 5% (0.05f)
     * @note Energy is split equally between parent and offspring
     */
    void Execute(Simulator& Sim, Cell& Agent) override;

private:
    double MutationChance;
};

}  // namespace Core
}  // namespace CellularSimulator