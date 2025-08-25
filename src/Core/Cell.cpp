#include <utility>
#include "CellularSimulator/Core/Cell.h"
#include <CellularSimulator/Core/StringInterner.h>

#include "CellularSimulator/Core/CommandManager.h"

using namespace CellularSimulator::Core;

Cell::Cell(int32_t InX, int32_t InY, EDirection InDirection, std::vector<size_t> InGenome, float InEnergy, bool InInObjectPool)
{
    Initialize(InX, InY, InDirection, std::move(InGenome), InEnergy, InInObjectPool);
}

Cell::Cell(
    int32_t InX, int32_t InY, EDirection InDirection, std::vector<size_t> InGenome, float InEnergy, bool InInObjectPool, Color InColor)
{
    Initialize(InX, InY, InDirection, std::move(InGenome), InEnergy, InInObjectPool, InColor);
}

void CellularSimulator::Core::Cell::Initialize(
    int32_t InX, int32_t InY, EDirection InDirection, std::vector<size_t> InGenome, float InEnergy, bool InInObjectPool)
{
    SetX(InX);
    SetY(InY);
    SetDirection(InDirection);
    SetGenome(std::move(InGenome));
    SetEnergy(InEnergy);
    SetInObjectPool(InInObjectPool);
    CalculateColor();
}

void Cell::Initialize(
    int32_t InX, int32_t InY, EDirection InDirection, std::vector<size_t> InGenome, float InEnergy, bool InInObjectPool, Color InColor)
{
    SetX(InX);
    SetY(InY);
    SetDirection(InDirection);
    SetGenome(std::move(InGenome));
    SetEnergy(InEnergy);
    SetInObjectPool(InInObjectPool);
    SetColor(InColor);
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

const std::vector<size_t>& Cell::GetGenome() const
{
    return Genome;
}

Color Cell::GetColor() const
{
    return CellColor;
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

void CellularSimulator::Core::Cell::SetColor(Color InColor)
{
    CellColor = InColor;
}

void CellularSimulator::Core::Cell::CalculateColor()
{
    const size_t GenomeSize = Genome.size();
    if (GenomeSize == 0)
    {
        CellColor = DARKGRAY;
        return;
    }
    float TotalR = 0, TotalG = 0, TotalB = 0;
    for (size_t i = 0; i < GenomeSize; ++i)
    {
        size_t GeneHash = Genome[i];
        float Weight = 1.0f - (static_cast<float>(i) / GenomeSize);
        Color GeneColor = StringInterner::GetInstance().GetGeneColor(GeneHash);
        TotalR += GeneColor.r * Weight;
        TotalG += GeneColor.g * Weight;
        TotalB += GeneColor.b * Weight;
    }
    unsigned char FinalR = static_cast<unsigned char>(TotalR / GenomeSize);
    unsigned char FinalG = static_cast<unsigned char>(TotalG / GenomeSize);
    unsigned char FinalB = static_cast<unsigned char>(TotalB / GenomeSize);
    CellColor = {FinalR, FinalG, FinalB, 255};
}