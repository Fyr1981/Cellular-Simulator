#pragma once
#include <functional>

#include "CellularSimulator/Core/Command.h"

namespace CellularSimulator
{
namespace Core
{

using SkipPredicate = std::function<bool(Simulator&, Cell&)>;

class SkipIfCommand : public Command
{
public:
    SkipIfCommand(SkipPredicate Predicate);

    void Execute(Simulator& Sim, Cell& Agent) override;

private:
    SkipPredicate Condition;
};

} // namespace Core
} // namespace CellularSimulator