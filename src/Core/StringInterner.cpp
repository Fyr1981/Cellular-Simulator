#include "CellularSimulator/Core/StringInterner.h"
#include <functional>
#include <map>
#include "raylib.h"

using namespace CellularSimulator::Core;

void StringInterner::InitializeGeneColors()
{
    GeneColorMap[Intern("Photosynthesis")] = LIME;
    GeneColorMap[Intern("MoveForward")] = BLUE;
    GeneColorMap[Intern("EatForward")] = RED;
    GeneColorMap[Intern("TurnRight")] = WHITE;
    GeneColorMap[Intern("TurnLeft")] = WHITE;
    GeneColorMap[Intern("Divide")] = GOLD;
    GeneColorMap[Intern("Idle")] = GRAY;
}

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

std::vector<std::string> StringInterner::ResolveGenome(const std::vector<size_t>& Genome) const
{
    std::vector<std::string> ResolvedGenome(Genome.size());
    for (size_t i = 0; i < Genome.size(); ++i)
    {
        ResolvedGenome[i] = Resolve(Genome[i]);
    }
    return ResolvedGenome;
}

Color StringInterner::GetGeneColor(size_t Hash) const
{
    if (GeneColorMap.find(Hash) != GeneColorMap.end()) return GeneColorMap.at(Hash);
    return DefaultColor;
}