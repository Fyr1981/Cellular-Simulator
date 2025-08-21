#pragma once
#include <string>
#include <string_view>
#include <unordered_map>

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
    
    static StringInterner& GetInstance();
    
    size_t Intern(std::string_view String);
    std::string_view Resolve(size_t Hash) const;

private:
    StringInterner() = default;

    std::unordered_map<std::string, size_t> StringToHash;
    std::unordered_map<size_t, std::string> HashToString;
};
} // namespace Core
} // namespace CellularSimulator