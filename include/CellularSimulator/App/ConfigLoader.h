#pragma once
#include <optional>
#include <string>

namespace CellularSimulator
{
namespace App
{
struct Config;

/**
 * @class ConfigLoader
 * @brief Loads the configuration from a JSON file.
 */
class ConfigLoader
{
public:
    /**
     * @brief Loads the configuration from a JSON file.
     * @param FilePath 
     * @return Config instance if the file was loaded successfully, std::nullopt otherwise.
     */
    static std::optional<Config> LoadConfigFromFile(const std::string& FilePath);
};
} // namespace App
} // namespace CellularSimulator