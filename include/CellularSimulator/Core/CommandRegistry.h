#pragma once

#include "CommandManager.h"
#include <type_traits>
#include <string_view>

namespace CellularSimulator
{
namespace Core
{

/**
 * @class CommandRegistrar
 * @brief Registers a command in CommandManager with the command factory by its class and name and color
 * @tparam TCommand Command type to create that must derive from CellularSimulator::Core::Command class
 * @note It's a helper class and can be used optionally for registering commands without any construction features
 */
template <typename TCommand>
class CommandRegistrar
{
public:
    /**
     * @brief Constructor for registering a command in CommandManager
     * @param CommandName Name of the command to register
     * @param CommandColor Color of the command to register. Used for cell visualization
     * @note TCommand must derive from CellularSimulator::Core::Command class
     */
    explicit CommandRegistrar(std::string_view CommandName, Color CommandColor)
    {
        static_assert(std::is_base_of_v<Command, TCommand>, "TCommand must derive from ICommand");
        CommandManager::RegisterCommand(CommandName, std::make_unique<TCommand>(), CommandColor);
    }
};

} // namespace Core
} // namespace CellularSimulator