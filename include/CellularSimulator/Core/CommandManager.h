#pragma once
#include <memory>
#include <unordered_map>
#include <functional>
#include <string>
#include <string_view>

namespace CellularSimulator
{
namespace Core
{
enum class EGeneCommand;
class Command;

/**
 * @class CommandManager
 * @brief Owns a registry of commands and provides access to them.
 */
class CommandManager
{
public:
    CommandManager() = default;

    /**
     * @brief Provides access to a command by name.
     * @param CommandNameHash The hash of the command name.
     * @return A pointer to the created command.
     */
    static Command* GetCommand(size_t CommandNameHash);

    /**
     * @brief Registers a command with the factory.
     * @param CommandName The name of the command.
     * @param CommandInstance Pointer to the created command.
     */
    static void RegisterCommand(std::string_view CommandName, std::unique_ptr<Command> CommandInstance);

    /**
     * @brief Gets the names of all registered commands.
     * @return A vector of command names.
     */
    static std::vector<size_t> GetRegisteredCommandNamesHashes();

private:
    using FactoryMap = std::unordered_map<size_t, std::unique_ptr<Command>>;
    static FactoryMap& GetRegistry();
};

} // namespace Core
} // namespace CellularSimulator