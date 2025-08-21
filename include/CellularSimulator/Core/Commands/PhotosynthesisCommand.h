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
    void Execute(Simulator& Sim, Cell& Agent) override;
};
} // namespace Core
} // namespace CellularSimulator