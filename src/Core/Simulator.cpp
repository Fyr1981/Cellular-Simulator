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
}

void Simulator::Update()
{
    std::vector<Cell*> AgentPtrs;
    AgentPtrs.reserve(AllCells.size());
    for (auto& Agent : AllCells)
    {
        AgentPtrs.push_back(&Agent);
    }

    struct ActionRequest
    {
        Cell* Agent;
        std::string_view CommandName;
    };
    std::vector<ActionRequest> Requests(AgentPtrs.size());

    std::transform(std::execution::par, AgentPtrs.begin(), AgentPtrs.end(), Requests.begin(),
        [](Cell* Agent) -> ActionRequest { return {Agent, Agent->DecideNextCommand()}; });

    for (const auto& Request : Requests)
    {
        Cell* Agent = Request.Agent;
        Command* Cmd = CmdManager.GetCommand(Request.CommandName);
        if (Cmd)
        {
            Cmd->Execute(*this, *Agent);
        }
    }

    std::for_each(std::execution::par, AgentPtrs.begin(), AgentPtrs.end(), [](Cell* Agent) { Agent->ConsumeEnergy(1.0f); });

    for (auto it = AllCells.begin(); it != AllCells.end();)
    {
        if (!it->IsAlive())
        {
            GetTile(it->GetX(), it->GetY())->SetCell(nullptr);
            it = AllCells.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void Simulator::Randomize(float Density)
{
    AllCells.clear();
    for (auto& tile : Grid)
    {
        tile.SetCell(nullptr);
    }
    const std::vector<std::string> AvailableCommands = CommandManager::GetRegisteredCommandNames();
    if (AvailableCommands.empty()) return;

    std::mt19937 Rng(std::random_device{}());
    std::uniform_real_distribution<float> Dist(0.0f, 1.0f);
    std::uniform_int_distribution<size_t> CommandIndexDist(0, AvailableCommands.size() - 1);

    for (int32_t Y = 0; Y < Height; ++Y)
    {
        for (int32_t X = 0; X < Width; ++X)
        {
            if (Dist(Rng) < Density)
            {
                std::vector<std::string> RandomGenome;
                RandomGenome.reserve(GenomeLength);
                for (int i = 0; i < GenomeLength; ++i)
                {
                    RandomGenome.push_back(AvailableCommands[CommandIndexDist(Rng)]);
                }
                SpawnCell(X, Y, EDirection::North, std::move(RandomGenome), 50);
            }
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

Cell* Simulator::SpawnCell(int32_t X, int32_t Y, EDirection Direction, std::vector<std::string> Genome, float Energy)
{
    if (!IsTileValidAndEmpty(X, Y)) return nullptr;
    Cell* NewCell = new Cell(X, Y, Direction, std::move(Genome), Energy);
    GetTile(X, Y)->SetCell(NewCell);
    AllCells.push_back(*NewCell);
    return NewCell;
}