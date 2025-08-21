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
 * @class CommandFactory
 * @brief Owns a registry of commands and creates them.
 */
class CommandFactory
{
public:
    CommandFactory() = default;

    /**
     * @brief Creates a command by name.
     * @param CommandName The name of the command.
     * @return A pointer to the created command.
     */
    std::unique_ptr<Command> CreateCommand(std::string_view CommandName);

    /**
     * @brief Registers a command with the factory.
     * @param CommandName The name of the command.
     * @param CreateFn The function that creates the command.
     */
    static void RegisterCommand(std::string_view CommandName, std::function<std::unique_ptr<Command>()> CreateFn);

    /**
     * @brief Gets the names of all registered commands.
     * @return A vector of command names.
     */
    static std::vector<std::string> GetRegisteredCommandNames();
    
private:
    using FactoryMap = std::unordered_map<std::string, std::function<std::unique_ptr<Command>()>>;
    static FactoryMap& GetRegistry();
};

} // namespace Core
} // namespace CellularSimulator