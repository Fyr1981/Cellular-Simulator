#include "CellularSimulator/Core/GridTile.h"
#include "CellularSimulator/Core/Cell.h"

using namespace CellularSimulator::Core;

void GridTile::Update()
{
}

bool GridTile::HasCell() const
{
    return HostedCell;
}

Cell* GridTile::GetCell()
{
    return HostedCell;
}

const Cell* GridTile::GetCell() const
{
    return HostedCell;
}

void GridTile::SetCell(Cell* InCell)
{
    HostedCell = InCell;
}