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
 * @brief Registers a command with the command factory by its class and name
 * @tparam TCommand Command type to create that must derive from CellularSimulator::Core::Command class
 */
template <typename TCommand>
class CommandRegistrar
{
public:
    /**
     * @brief Constructor for registering a command
     * @param CommandName Name of the command to register
     */
    explicit CommandRegistrar(std::string_view CommandName)
    {
        static_assert(std::is_base_of_v<Command, TCommand>, "TCommand must derive from ICommand");
        CommandManager::RegisterCommand(CommandName, std::make_unique<TCommand>());
    }
};

} // namespace Core
} // namespace CellularSimulator