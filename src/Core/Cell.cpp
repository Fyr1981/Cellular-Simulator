#include <utility>
#include "CellularSimulator/Core/Cell.h"
#include <CellularSimulator/Core/StringInterner.h>

#include "CellularSimulator/App/Config.h"
#include "CellularSimulator/App/ConfigLoader.h"
#include "CellularSimulator/Core/CommandManager.h"

using namespace CellularSimulator::Core;

Cell::Cell()
{
    MaxDefences = App::ConfigLoader::GetConfig().MaxDefences;
    MaxEnergy = App::ConfigLoader::GetConfig().MaxEnergy;
}

Cell::Cell(int32_t InX, int32_t InY, EDirection InDirection, std::vector<size_t> InGenome, int32_t InEnergy, bool InInObjectPool)
{
    Initialize(InX, InY, InDirection, std::move(InGenome), InEnergy, InInObjectPool);
}

Cell::Cell(
    int32_t InX, int32_t InY, EDirection InDirection, std::vector<size_t> InGenome, int32_t InEnergy, bool InInObjectPool, Color InColor)
{
    Initialize(InX, InY, InDirection, std::move(InGenome), InEnergy, InInObjectPool, InColor);
}

void Cell::Initialize(
    int32_t InX, int32_t InY, EDirection InDirection, std::vector<size_t> InGenome, int32_t InEnergy, bool InInObjectPool)
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
    int32_t InX, int32_t InY, EDirection InDirection, std::vector<size_t> InGenome, int32_t InEnergy, bool InInObjectPool, Color InColor)
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
    MoveToNextCommand();
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

int32_t Cell::GetEnergy() const
{
    return Energy;
}

bool Cell::IsAlive() const
{
    return Energy > 0;
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

void Cell::AddEnergy(int32_t Amount)
{
    SetEnergy(Energy + Amount);
}

void Cell::ConsumeEnergy(int32_t Amount)
{
    if (Amount < 0) return;
    if (Defences > 0)
    {
        Defences--;
        return;
    }
    SetEnergy(Energy - Amount);
}

void Cell::ConsumeEnergyIgnoreDefendings(int32_t Amount)
{
    SetEnergy(Energy - Amount);
}

void Cell::SetEnergy(int32_t InEnergy)
{
    Energy = std::max(0, std::min(MaxEnergy, InEnergy));
}

void Cell::SetGenome(std::vector<size_t> InGenome)
{
    Genome = std::move(InGenome);
}

void Cell::SetInObjectPool(bool bInObjectPool)
{
    bInsideObjectPool = bInObjectPool;
}

void Cell::SetColor(Color InColor)
{
    CellColor = InColor;
}

void Cell::MoveToNextCommand()
{
    GenomePointer++;
    if (GenomePointer >= Genome.size())
    {
        GenomePointer = 0;
    }
}

void Cell::AddDefendings(int32_t Amount)
{
    if (Amount < 0) return;
    Defences += Amount;
    if (Defences > MaxDefences)
    {
        Defences = MaxDefences;
    }
}

bool Cell::IsExecutedThisStep() const
{
    return bExecutedThisStep;
}

void Cell::SetExecutedThisStep(bool bInExecuted)
{
    bExecutedThisStep = bInExecuted;
}

void Cell::CalculateColor()
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