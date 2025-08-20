#include "CellularSimulator/App/Application.h"
#include "CellularSimulator/Core/GridTile.h"
#include "CellularSimulator/Core/Cell.h"
#include <iostream>
#include <thread>
#include "raylib.h"

using namespace CellularSimulator::App;

Application::Application()
{
    InitWindow(WindowWidth, WindowHeight, "Cellular Simulator");
    SetTargetFPS(60);
    int32_t SimWidth = WindowWidth / CellSize;
    int32_t SimHeight = WindowHeight / CellSize;
    Sim = std::make_unique<Core::Simulator>(SimWidth, SimHeight);
    Sim->Randomize(0.5f);
}

Application::~Application()
{
    CloseWindow();
}

void Application::Run()
{
    while (!WindowShouldClose())
    {
        Update();
        Draw();
    }
}

void Application::Update()
{
    Sim->Update();
}

void Application::Draw()
{
    BeginDrawing();
    ClearBackground(RAYWHITE);
    
    for (int32_t y = 0; y < Sim->GetHeight(); ++y)
    {
        for (int32_t x = 0; x < Sim->GetWidth(); ++x)
        {
            const Core::GridTile* tile = Sim->GetTile(x, y);
            if (tile && tile->HasCell())
            {
                DrawRectangle(x * CellSize, y * CellSize, CellSize, CellSize, BLACK);
            }
        }
    }
    DrawFPS(10, 10);

    EndDrawing();
}