#include "CellularSimulator/Core/Simulator.h"
#include <execution>
#include <random>
#include "CellularSimulator/Core/GridTile.h"
#include "CellularSimulator/Core/Cell.h"
#include "CellularSimulator/Core/Command.h"

using namespace CellularSimulator::Core;

Simulator::Simulator(int32_t InWidth, int32_t InHeight) : Width(InWidth), Height(InHeight)
{
    Grid.resize(static_cast<size_t>(Width) * Height);
    const size_t MaxPopulation = static_cast<size_t>(Width) * Height;
    CellPool.resize(MaxPopulation);
}

void Simulator::Update()
{
    for (auto& Tile : Grid)
    {
        Tile.SetCell(nullptr);
    }
    for (size_t i = 0; i < ActiveCellCount; ++i)
    {
        Cell& cell = CellPool[i];
        GetTile(cell.GetX(), cell.GetY())->SetCell(&cell);
    }

    struct ActionRequest
    {
        Cell* Agent;
        size_t CommandNameHash;
    };

    auto FirstCellIt = CellPool.begin();
    auto LastCellIt = CellPool.begin() + ActiveCellCount;

    std::vector<ActionRequest> Requests(ActiveCellCount);
    std::transform(std::execution::par, CellPool.begin(), LastCellIt, Requests.begin(),
        [](Cell& Agent) -> ActionRequest { return {&Agent, Agent.DecideNextCommand()}; });

    for (const auto& Request : Requests)
    {
        Cell* Agent = Request.Agent;
        Command* Cmd = CommandManager::GetCommand(Request.CommandNameHash);
        if (Cmd)
        {
            Cmd->Execute(*this, *Agent);
        }
    }

    std::for_each(std::execution::par, FirstCellIt, LastCellIt, [](Cell& Agent) { Agent.ConsumeEnergy(10.0f); });

    for (size_t i = 0; i < ActiveCellCount; ++i)
    {
        if (CellPool[i].GetEnergy() <= 0.0f)
        {
            CellPool[i].SetInObjectPool(true);
        }
    }
    auto FirstDead = std::partition(CellPool.begin(), CellPool.begin() + ActiveCellCount, [](const Cell& c) { return c.IsAlive(); });
    ActiveCellCount = std::distance(CellPool.begin(), FirstDead);
}

void Simulator::Randomize(float Density)
{
    for (auto& Tile : Grid)
    {
        Tile.SetCell(nullptr);
    }
    const std::vector<size_t> AvailableCommands = CommandManager::GetRegisteredCommandNamesHashes();
    if (AvailableCommands.empty()) return;
    std::mt19937 Rng = GetRNG();
    std::uniform_real_distribution<float> Dist(0.0f, 1.0f);
    std::uniform_int_distribution<size_t> CommandIndexDist(0, AvailableCommands.size() - 1);
    for (int32_t Y = 0; Y < Height; ++Y)
    {
        for (int32_t X = 0; X < Width; ++X)
        {
            if (Dist(Rng) > Density) continue;
            std::vector<std::size_t> RandomGenome;
            RandomGenome.reserve(GenomeLength);
            for (int i = 0; i < GenomeLength; ++i)
            {
                RandomGenome.push_back(AvailableCommands[CommandIndexDist(Rng)]);
            }
            SpawnCell(X, Y, EDirection::North, std::move(RandomGenome), 50);
        }
    }
}

GridTile* Simulator::GetTile(int32_t X, int32_t Y)
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

bool Simulator::IsTileValidAndEmpty(int32_t X, int32_t Y) const
{
    if (X < 0 || X >= Width || Y < 0 || Y >= Height) return false;
    const GridTile* Tile = &Grid[static_cast<size_t>(Y) * Width + X];
    return Tile->GetCell() == nullptr;
}

void Simulator::MoveCell(Cell* Agent, int32_t NewX, int32_t NewY)
{
    if (!IsTileValidAndEmpty(NewX, NewY)) return;

    GridTile* OldTile = &Grid[static_cast<size_t>(Agent->GetY()) * Width + Agent->GetX()];
    OldTile->SetCell(nullptr);

    GridTile* NewTile = &Grid[static_cast<size_t>(NewY) * Width + NewX];
    NewTile->SetCell(Agent);
    Agent->SetX(NewX);
    Agent->SetY(NewY);
}

Cell* Simulator::SpawnCell(int32_t X, int32_t Y, EDirection Direction, std::vector<size_t> Genome, float Energy)
{
    if (!IsTileValidAndEmpty(X, Y) || ActiveCellCount >= CellPool.size()) return nullptr;
    Cell& NewCell = CellPool[ActiveCellCount];
    GetTile(X, Y)->SetCell(&NewCell);
    NewCell.Initialize(X, Y, Direction, std::move(Genome), Energy, false);
    ++ActiveCellCount;
    return &NewCell;
}

std::mt19937& Simulator::GetRNG()
{
    return RandomGenerator;
}
