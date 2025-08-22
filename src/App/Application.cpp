#include "CellularSimulator/App/Application.h"
#include "CellularSimulator/Core/GridTile.h"
#include "CellularSimulator/Core/Cell.h"
#include <iostream>
#include <string>
#include <thread>
#include "raylib.h"
#include "raymath.h"
#include "CellularSimulator/Core/StringInterner.h"

using namespace CellularSimulator::App;

Application::Application()
{
    InitWindow(WindowWidth, WindowHeight, "Cellular Simulator");
    SetTargetFPS(60);

    int32_t SimWidth = 400;
    int32_t SimHeight = 300;
    Sim = std::make_unique<Core::Simulator>(SimWidth, SimHeight);
    Sim->Randomize(0.5f);
    const float WorldWidthPx = static_cast<float>(SimWidth * CellSize);
    const float WorldHeightPx = static_cast<float>(SimHeight * CellSize);

    const float XRatio = static_cast<float>(WindowWidth) / WorldWidthPx;
    const float YRatio = static_cast<float>(WindowHeight) / WorldHeightPx;

    const float InitialZoom = std::min(XRatio, YRatio);

    WorldCamera.offset = {
        static_cast<float>(WindowWidth) / 2.0f,
        static_cast<float>(WindowHeight) / 2.0f
    };
    WorldCamera.rotation = 0.0f;
    WorldCamera.zoom = InitialZoom;
    WorldCamera.target = {
        WorldWidthPx / 2.0f,
        WorldHeightPx / 2.0f
    };
    Core::StringInterner::GetInstance().InitializeGeneColors();
};

Application::~Application()
{
    CloseWindow();
}

void Application::Run()
{
    while (!WindowShouldClose())
    {
        ProcessInput();
        Update();
        Draw();
    }
}

void Application::ProcessInput()
{
    if (IsKeyPressed(KEY_SPACE))
    {
        bIsPaused = !bIsPaused;
    }

    if (IsKeyPressed(KEY_RIGHT)) UpdatesPerSecond += 5;
    if (IsKeyPressed(KEY_LEFT)) UpdatesPerSecond -= 5;
    if (UpdatesPerSecond < 0) UpdatesPerSecond = 0;

    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
    {
        Vector2 MouseDelta = GetMouseDelta();
        MouseDelta = Vector2Scale(MouseDelta, -1.0f / WorldCamera.zoom);
        WorldCamera.target = Vector2Add(WorldCamera.target, MouseDelta);
    }

    float WheelMove = GetMouseWheelMove();
    if (WheelMove)
    {
        Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), WorldCamera);
        WorldCamera.offset = GetMousePosition();
        WorldCamera.target = mouseWorldPos;
        const float ZoomIncrement = 0.125f;
        WorldCamera.zoom += (WheelMove * ZoomIncrement);
        if (WorldCamera.zoom < ZoomIncrement) WorldCamera.zoom = ZoomIncrement;
    }
}

void Application::Update()
{
    if (bIsPaused) return;

    TimeSinceLastUpdate += GetFrameTime();
    float TimeBetweenUpdates = 1.0 / UpdatesPerSecond;
    int32_t UpdatesThisFrame = 0;
    while (TimeSinceLastUpdate >= TimeBetweenUpdates && UpdatesThisFrame < MaxUpdatesPerFrame)
    {
        Sim->Update();
        TimeSinceLastUpdate -= TimeBetweenUpdates;
        UpdatesThisFrame++;
    }
}

void Application::Draw()
{
    BeginDrawing();
    ClearBackground(DARKGRAY);
    BeginMode2D(WorldCamera);

    for (int32_t y = 0; y < Sim->GetHeight(); ++y)
    {
        for (int32_t x = 0; x < Sim->GetWidth(); ++x)
        {
            const Core::GridTile* Tile = Sim->GetTile(x, y);
            DrawRectangle(x * CellSize, y * CellSize, CellSize, CellSize, GetTileColor(Tile));
        }
    }
    EndMode2D();

    std::string statusText = bIsPaused ? "PAUSED" : "RUNNING";
    statusText += " | UPS: " + std::to_string(UpdatesPerSecond);
    DrawText(statusText.c_str(), 10, 10, 20, LIME);

    EndDrawing();
}

Color Application::GetTileColor(const Core::GridTile* Tile)
{
    if (!Tile) return BLACK;
    return GetCellColor(Tile->GetCell());
}

size_t HashVector(const std::vector<size_t>& vec)
{
    size_t seed = vec.size();
    for (size_t h : vec)
    {
        seed ^= h + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }
    return seed;
}

Color Application::GetCellColor(const Core::Cell* InCell)
{
    if (!InCell) return WHITE;
    std::vector<size_t> Genome = InCell->GetGenome();
    const size_t GenomeSize = Genome.size();
    if (GenomeSize == 0) return DARKGRAY;
    float TotalR = 0, TotalG = 0, TotalB = 0;
    for (size_t i = 0; i < GenomeSize; ++i)
    {
        size_t GeneHash = Genome[i];
        float Weight = 1.0f - (static_cast<float>(i) / GenomeSize);
        Color GeneColor = Core::StringInterner::GetInstance().GetGeneColor(GeneHash);
        TotalR += GeneColor.r * Weight;
        TotalG += GeneColor.g * Weight;
        TotalB += GeneColor.b * Weight;
    }
    unsigned char FinalR = static_cast<unsigned char>(TotalR / GenomeSize);
    unsigned char FinalG = static_cast<unsigned char>(TotalG / GenomeSize);
    unsigned char FinalB = static_cast<unsigned char>(TotalB / GenomeSize);
    return {FinalR, FinalG, FinalB, 255};
}