#include "CellularSimulator/Core/Simulator.h"
#include <random>
#include "CellularSimulator/Core/GridTile.h"
#include "CellularSimulator/Core/Cell.h"

using namespace CellularSimulator::Core;

Simulator::Simulator(int32_t InWidth, int32_t InHeight) : Width(InWidth), Height(InHeight)
{
    Grid.resize(static_cast<size_t>(Width) * Height);
}

void Simulator::Update()
{
    for (auto& CurrentCell : AllCells)
    {
        CurrentCell.Update();
    }
    for (auto& CurrentTile : Grid)
    {
        CurrentTile.Update();
    }
}

void Simulator::Randomize(float Density)
{
    AllCells.clear();
    for (auto& tile : Grid)
    {
        tile.SetCell(nullptr);
    }
    std::mt19937 Rng(std::random_device{}());
    std::uniform_real_distribution<float> Dist(0.0f, 1.0f);

    for (int32_t Y = 0; Y < Height; ++Y)
    {
        for (int32_t X = 0; X < Width; ++X)
        {
            if (Dist(Rng) < Density)
            {
                AllCells.emplace_back(X, Y);
                Cell* NewCell = &AllCells.back();
                Grid[static_cast<size_t>(Y) * Width + X].SetCell(NewCell);
            }
        }
    }
}

const GridTile* Simulator::GetTile(int32_t X, int32_t Y) const
{
    if (X < 0 || X >= Width || Y < 0 || Y >= Height) return nullptr;
    return &Grid[static_cast<size_t>(Y) * Width + X];
}

int32_t Simulator::GetWidth() const
{
    return Width;
}

int32_t Simulator::GetHeight() const
{
    return Height;
}