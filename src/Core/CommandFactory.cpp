#include "CellularSimulator/Core/CommandFactory.h"
#include "CellularSimulator/Core/Command.h"

using namespace CellularSimulator::Core;

std::unique_ptr<Command> CommandFactory::CreateCommand(std::string_view CommandName)
{
    auto& Registry = GetRegistry();
    auto it = Registry.find(std::string(CommandName));
    if (it != Registry.end())
    {
        return it->second();
    }
    return nullptr;
}

void CommandFactory::RegisterCommand(std::string_view CommandName, std::function<std::unique_ptr<Command>()> CreateFn)
{
    if (GetRegistry().find(std::string(CommandName)) == GetRegistry().end())
    {
        GetRegistry()[std::string(CommandName)] = std::move(CreateFn);
    }
}

std::vector<std::string> CommandFactory::GetRegisteredCommandNames()
{
    std::vector<std::string> names;
    names.reserve(GetRegistry().size());
    for (const auto& pair : GetRegistry())
    {
        names.push_back(pair.first);
    }
    return names;
}

CommandFactory::FactoryMap& CommandFactory::GetRegistry()
{
    static FactoryMap Registry;
    return Registry;
}