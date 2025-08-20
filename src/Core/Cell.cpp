#include <utility>

#include "CellularSimulator/Core/Cell.h"

using namespace CellularSimulator::Core;

Cell::Cell(int32_t InX, int32_t InY, EDirection InDirection, std::vector<std::string> InGenome):
    X(InX),
    Y(InY),
    Direction(InDirection),
    Genome(std::move(InGenome))
{
}

std::string Cell::DecideNextCommand()
{
    if (Genome.empty()) return "None";
    if (Genome.size() < GenomePointer)
    {
        GenomePointer = 0;
    }
    return Genome[++GenomePointer];
}

int32_t Cell::GetX() const
{
    return X;
}

int32_t Cell::GetY() const
{
    return Y;
}

EDirection Cell::GetDirection() const
{
    return Direction;
}