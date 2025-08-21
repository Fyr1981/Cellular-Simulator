#include "CellularSimulator/Core/CommandManager.h"
#include "CellularSimulator/Core/Command.h"

using namespace CellularSimulator::Core;

Command* CommandManager::GetCommand(std::string_view CommandName)
{
    auto& registry = GetRegistry();
    auto it = registry.find(std::string(CommandName));
    if (it != registry.end())
    {
        return it->second.get();
    }
    return nullptr;
}

void CommandManager::RegisterCommand(std::string_view CommandName, std::unique_ptr<Command> CommandInstance)
{
    if (GetRegistry().find(std::string(CommandName)) == GetRegistry().end())
    {
        GetRegistry()[std::string(CommandName)] = std::move(CommandInstance);
    }
}

std::vector<std::string> CommandManager::GetRegisteredCommandNames()
{
    std::vector<std::string> names;
    names.reserve(GetRegistry().size());
    for (const auto& pair : GetRegistry())
    {
        names.push_back(pair.first);
    }
    return names;
}

CommandManager::FactoryMap& CommandManager::GetRegistry()
{
    static FactoryMap Registry;
    return Registry;
}