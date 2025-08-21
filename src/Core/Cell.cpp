#include <utility>
#include "CellularSimulator/Core/Cell.h"

using namespace CellularSimulator::Core;

Cell::Cell(int32_t InX, int32_t InY, EDirection InDirection, std::vector<size_t> InGenome, float InEnergy, bool InInObjectPool)
{
    Initialize(InX, InY, InDirection, std::move(InGenome), InEnergy, InInObjectPool);
}

void Cell::Initialize(int32_t InX, int32_t InY, EDirection InDirection, std::vector<size_t> InGenome, float InEnergy, bool InInObjectPool)
{
    SetX(InX);
    SetY(InY);
    SetDirection(InDirection);
    SetGenome(std::move(InGenome));
    SetEnergy(InEnergy);
    SetInObjectPool(InInObjectPool);
}

size_t Cell::DecideNextCommand()
{
    if (Genome.empty()) return 0;
    size_t CommandHash = Genome[GenomePointer];
    GenomePointer++;
    if (GenomePointer >= Genome.size())
    {
        GenomePointer = 0;
    }
    return CommandHash;
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

bool Cell::IsInObjectPool() const
{
    return bInsideObjectPool;
}

void Cell::GetGenome(std::vector<size_t>& OutGenome) const
{
    OutGenome = Genome;
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

void Cell::SetGenome(std::vector<size_t> InGenome)
{
    Genome = std::move(InGenome);
}

void Cell::SetInObjectPool(bool bInObjectPool)
{
    bInsideObjectPool = bInObjectPool;
}