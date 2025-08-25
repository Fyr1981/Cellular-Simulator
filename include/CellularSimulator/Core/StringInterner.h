#pragma once
#include <map>
#include <string>
#include <string_view>
#include <unordered_map>

#include "raylib.h"

namespace CellularSimulator
{
namespace Core
{

/**
 * @class StringInterner
 * @brief Provides string interning functionality for optimization
 */
class StringInterner
{
public:
    StringInterner(const StringInterner&) = delete;
    StringInterner& operator=(const StringInterner&) = delete;

    /**
     * @brief Initializes the gene color map. Should be called once at the start
     */
    void InitializeGeneColors();
    /**
     * @brief Retrieves the singleton instance
     * @return The singleton instance
     */
    static StringInterner& GetInstance();

    /**
     * @brief Interns a string and returns its hash value
     * @param String The string to intern
     * @return The hash value of the interned string
     */
    size_t Intern(std::string_view String);

    /**
     * @brief Resolves a hash value to its original string
     * @param Hash The hash value to resolve
     * @return The original string associated with the hash value
     */
    std::string_view Resolve(size_t Hash) const;

    /**
     * @brief Resolves a vector of hash values to their original strings
     * @param Genome The vector of hash values to resolve
     * @return The vector of original strings associated with the hash values
     */
    std::vector<std::string> ResolveGenome(const std::vector<size_t>& Genome) const;

    /**
     * @brief Retrieves the color associated with a gene hash value
     * @param Hash The hash value of the gene
     * @return The color associated with the gene hash value
     */
    Color GetGeneColor(size_t Hash) const;

private:
    StringInterner() = default;
    std::unordered_map<std::string, size_t> StringToHash;
    std::unordered_map<size_t, std::string> HashToString;
    std::map<size_t, Color> GeneColorMap;
    Color DefaultColor = BLACK;
};
} // namespace Core
} // namespace CellularSimulator