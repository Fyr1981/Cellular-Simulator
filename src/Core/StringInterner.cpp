#include "CellularSimulator/Core/StringInterner.h"
#include <functional>

using namespace CellularSimulator::Core;

StringInterner& StringInterner::GetInstance()
{
    static StringInterner Instance;
    return Instance;
}

size_t StringInterner::Intern(std::string_view String)
{
    auto it = StringToHash.find(std::string(String));
    if (it != StringToHash.end())
    {
        return it->second;
    }
    size_t Hash = HashToString.size();
    
    std::string NewString(String);
    StringToHash[NewString] = Hash;
    HashToString[Hash] = NewString;
    return Hash;
}

std::string_view StringInterner::Resolve(size_t Hash) const
{
    const auto it = HashToString.find(Hash);
    if (it != HashToString.end())
    {
        return it->second;
    }
    return "UNKNOWN_HASH";
}