#pragma once
#include <functional>

#include "CellularSimulator/Core/Command.h"

namespace CellularSimulator
{
namespace Core
{

/**
 * @defgroup ConditionalPredicates
 * @brief Predicates that return true if the next command should be skipped
 */

/**
 * @brief A predicate that returns true if the next command should be skipped
 * @ingroup ConditionalPredicates
 */
using SkipPredicate = std::function<bool(const Simulator&, const Cell&)>;

/**
 * @class SkipIfCommand
 * @brief A command that skips the next command if the predicate returns true.
 */
class SkipIfCommand : public Command
{
public:
    /**
     * @brief Construct a new SkipIfCommand object
     * @param Predicate The predicate to use to determine if the next command should be skipped
     */
    SkipIfCommand(SkipPredicate Predicate);

    /**
     * @brief Skip the next command if the predicate returns true by moving the gene pointer to the next command
     * @param Sim The simulator
     * @param Agent The agent to execute the command on
     */
    void Execute(Simulator& Sim, Cell& Agent) override;

private:
    SkipPredicate Condition;
};

} // namespace Core
} // namespace CellularSimulator