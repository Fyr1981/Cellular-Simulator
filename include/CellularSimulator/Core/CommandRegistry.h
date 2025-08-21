#pragma once

#include "CommandFactory.h"
#include <type_traits>
#include <string_view>

namespace CellularSimulator
{
namespace Core
{

/**
 * @brief Creates a command of type TCommand
 * @tparam TCommand Command type to create that must derive from CellularSimulator::Core::Command class
 * @return Creation function
 */
template <typename TCommand>
std::function<std::unique_ptr<Command>()> MakeCommandCreator()
{
    static_assert(std::is_base_of_v<Command, TCommand>, "TCommand must derive from ICommand");
    return []()
    {
        return std::unique_ptr<Command>(new TCommand());
    };
}

/**
 * @class CommandRegistrar
 * @brief Registers a command with the command factory
 */
class CommandRegistrar
{
public:
    /**
     * @brief Constructor for registering a command
     * @param CommandName Name of the command to register
     * @param CreateFn Creation function for the command. Can be created with MakeCommandCreator() template for any command
     */
    CommandRegistrar(std::string_view CommandName, std::function<std::unique_ptr<Command>()> CreateFn)
    {
        CommandFactory::RegisterCommand(CommandName, std::move(CreateFn));
    }
};

} // namespace Core
} // namespace CellularSimulator