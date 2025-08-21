#pragma once

#include "CommandFactory.h"
#include <type_traits>
#include <string_view>

namespace CellularSimulator
{
namespace Core
{

template <typename TCommand>
std::function<std::unique_ptr<Command>()> MakeCommandCreator()
{
    static_assert(std::is_base_of_v<Command, TCommand>, "TCommand must derive from ICommand");
    return []()
    {
        return std::unique_ptr<Command>(new TCommand());
    };
}

class CommandRegistrar
{
public:
    CommandRegistrar(std::string_view CommandName, std::function<std::unique_ptr<Command>()> CreateFn)
    {
        CommandFactory::RegisterCommand(CommandName, std::move(CreateFn));
    }
};

} // namespace Core
} // namespace CellularSimulator