#include "CellularSimulator/Core/CommandManager.h"
#include "CellularSimulator/Core/Command.h"
#include "CellularSimulator/Core/StringInterner.h"

using namespace CellularSimulator::Core;

Command* CommandManager::GetCommand(size_t CommandNameHash)
{
    auto& Registry = GetRegistry();
    auto it = Registry.find(CommandNameHash);
    if (it != Registry.end())
    {
        return it->second.get();
    }
    return nullptr;
}

void CommandManager::RegisterCommand(std::string_view CommandName, std::unique_ptr<Command> CommandInstance)
{
    size_t Hash = StringInterner::GetInstance().Intern(CommandName);
    if (GetRegistry().find(Hash) == GetRegistry().end())
    {
        GetRegistry()[Hash] = std::move(CommandInstance);
    }
}

std::vector<size_t> CommandManager::GetRegisteredCommandNamesHashes()
{
    std::vector<std::size_t> Hashes;
    Hashes.reserve(GetRegistry().size());
    for (const auto& pair : GetRegistry())
    {
        Hashes.push_back(pair.first);
    }
    return Hashes;
}

CommandManager::FactoryMap& CommandManager::GetRegistry()
{
    static FactoryMap Registry;
    return Registry;
}