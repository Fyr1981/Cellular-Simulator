#include <utility>

#include "CellularSimulator/Core/Cell.h"

using namespace CellularSimulator::Core;

Cell::Cell(int32_t InX, int32_t InY, EDirection InDirection, std::vector<std::string> InGenome, float InEnergy) :
    X(InX),
    Y(InY),
    Direction(InDirection),
    Genome(std::move(InGenome))
{
    SetEnergy(InEnergy);
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

float Cell::GetEnergy() const
{
    return Energy;
}

bool Cell::IsAlive() const
{
    return Energy > 0.0f;
}

void Cell::SetX(int32_t InX)
{
    X = InX;
}

void Cell::SetY(int32_t InY)
{
    Y = InY;
}

void Cell::SetDirection(EDirection InDirection)
{
    Direction = InDirection;
}

void Cell::AddEnergy(float Amount)
{
    if (Amount < 0.0f) return;
    Energy = std::min(MaxEnergy, Energy + Amount);
}

void Cell::ConsumeEnergy(float Amount)
{
    if (Amount < 0.0f) return;
    Energy = std::max(0.0f, Energy - Amount);
}

void Cell::SetEnergy(float InEnergy)
{
    Energy = std::max(0.0f, std::min(MaxEnergy, InEnergy));
}