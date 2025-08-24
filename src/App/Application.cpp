#include "CellularSimulator/App/Application.h"
#include <chrono>
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
    int32_t SimWidth = 300;
    int32_t SimHeight = 300;
    Sim = std::make_unique<Core::Simulator>(300, 300);
    Sim->Randomize(0.5f);

    const float WorldWidthPx = static_cast<float>(SimWidth * TileSize);
    const float WorldHeightPx = static_cast<float>(SimHeight * TileSize);

    const float XRatio = static_cast<float>(WindowWidth) / WorldWidthPx;
    const float YRatio = static_cast<float>(WindowHeight) / WorldHeightPx;

    const float InitialZoom = std::min(XRatio, YRatio);

    WorldCamera.offset = {static_cast<float>(WindowWidth) / 2.0f, static_cast<float>(WindowHeight) / 2.0f};
    WorldCamera.rotation = 0.0f;
    WorldCamera.zoom = InitialZoom;
    WorldCamera.target = {WorldWidthPx / 2.0f, WorldHeightPx / 2.0f};

    Core::StringInterner::GetInstance().InitializeGeneColors();

    bIsRunning = true;
    UpdateThread = std::thread(&Application::UpdateLoop, this);
};

Application::~Application()
{
    bIsRunning = false;
    if (UpdateThread.joinable())
    {
        UpdateThread.join();
    }
    CloseWindow();
}

void Application::Run()
{
    RenderLoop();
}

void Application::UpdateLoop()
{
    using namespace std::chrono;

    auto LastTime = high_resolution_clock::now();
    double TimeAccumulator = 0.0;

    while (bIsRunning.load())
    {
        if (bInputUpdated.load())
        {
            std::pair<int32_t, int32_t> InspectingAt;
            {
                std::lock_guard<std::mutex> Lock(InputMutex);
                InspectingAt = InspectingPos;
            }
            bInputUpdated.store(false);
            const Core::GridTile* Tile = Sim->GetTile(InspectingAt.first, InspectingAt.second);
            if (Tile)
            {
                const Core::Cell* Cell = Tile->GetCell();
                if (Cell)
                {
                    BackState.Inspector.Genome = Core::StringInterner::GetInstance().ResolveGenome(Cell->GetGenome());
                    BackState.Inspector.bShouldDisplayGenome = true;
                }
            }
            else
            {
                BackState.Inspector.bShouldDisplayGenome = false;
            }
        }

        auto CurrentTime = high_resolution_clock::now();
        duration<double> DeltaTime = CurrentTime - LastTime;
        LastTime = CurrentTime;
        if (bIsPaused.load())
        {
            std::this_thread::sleep_for(milliseconds(10));
            continue;
        }
        TimeAccumulator += DeltaTime.count();
        const double TimeBetweenUpdates = 1.0 / UpdatesPerSecond.load();
        while (TimeAccumulator >= TimeBetweenUpdates)
        {
            Sim->Update();
            TimeAccumulator -= TimeBetweenUpdates;
        }
        BackState.Tiles.clear();
        BackState.Tiles.reserve(Sim->GetActiveCellCount());
        for (int32_t i = 0; i < Sim->GetWidth(); ++i)
        {
            for (int32_t j = 0; j < Sim->GetHeight(); ++j)
            {
                const Core::GridTile* TileInProcess = Sim->GetTile(i, j);
                if (TileInProcess)
                {
                    BackState.Tiles.push_back({i, j, GetTileColor(TileInProcess)});
                }
            }
        }
        {
            std::lock_guard<std::mutex> Lock(StateMutex);
            FrontState.UpdateFromBuffer(BackState);
        }

        std::this_thread::sleep_for(milliseconds(1));
    }
}

void Application::RenderLoop()
{
    while (!WindowShouldClose())
    {
        ProcessInput();
        Draw();
    }
}

void Application::ProcessInput()
{
    // Fullscreen
    if (IsKeyPressed(KEY_F11))
    {
        ToggleFullscreen();
    }
    // Pause
    if (IsKeyPressed(KEY_SPACE))
    {
        bIsPaused = !bIsPaused;
    }
    // Simulation speed
    if (IsKeyPressed(KEY_RIGHT)) UpdatesPerSecond += 5;
    if (IsKeyPressed(KEY_LEFT)) UpdatesPerSecond -= 5;
    if (UpdatesPerSecond < 0) UpdatesPerSecond = 0;
    // Camera movement
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
    {
        Vector2 MouseDelta = GetMouseDelta();
        MouseDelta = Vector2Scale(MouseDelta, -1.0f / WorldCamera.zoom);
        WorldCamera.target = Vector2Add(WorldCamera.target, MouseDelta);
    }
    // Camera zoom
    const float WheelMove = GetMouseWheelMove();
    if (WheelMove)
    {
        Vector2 MouseWorldPos = GetScreenToWorld2D(GetMousePosition(), WorldCamera);
        WorldCamera.offset = GetMousePosition();
        WorldCamera.target = MouseWorldPos;
        const float ZoomIncrement = 0.125f;
        WorldCamera.zoom += (WheelMove * ZoomIncrement);
        if (WorldCamera.zoom < ZoomIncrement) WorldCamera.zoom = ZoomIncrement;
    }
    if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
    {
        const Vector2 MouseScreenPos = GetMousePosition();
        const Vector2 MouseWorldPos = GetScreenToWorld2D(MouseScreenPos, WorldCamera);
        const int32_t TileX = static_cast<int32_t>(MouseWorldPos.x / TileSize);
        const int32_t TileY = static_cast<int32_t>(MouseWorldPos.y / TileSize);
        {
            std::lock_guard<std::mutex> Lock(InputMutex);
            InspectingPos = {TileX, TileY};
        }
        bInputUpdated.store(true);
    }
}

void Application::Draw()
{
    SimulationState StateToDraw;
    {
        std::lock_guard<std::mutex> Lock(StateMutex);
        StateToDraw = FrontState;
    }

    BeginDrawing();
    ClearBackground(DARKGRAY);
    BeginMode2D(WorldCamera);

    for (const auto& TileData : StateToDraw.Tiles)
    {
        DrawRectangle(TileData.X * TileSize, TileData.Y * TileSize, TileSize, TileSize, TileData.TileColor);
    }

    EndMode2D();

    if (StateToDraw.Inspector.bShouldDisplayGenome)
    {
        for (size_t i = 0; i < StateToDraw.Inspector.Genome.size(); ++i)
        {
            DrawText(StateToDraw.Inspector.Genome[i].c_str(), 10, 30 + (i * 20), 20, LIME);
        }
    }

    std::string StatusText = bIsPaused.load() ? "PAUSED" : "RUNNING";
    StatusText += " | UPS: " + std::to_string(UpdatesPerSecond.load());
    DrawText(StatusText.c_str(), 10, 10, 20, LIME);
    DrawFPS(WindowWidth - 100, 10);
    EndDrawing();
}

Color Application::GetTileColor(const Core::GridTile* Tile)
{
    if (!Tile) return BLACK;
    return GetCellColor(Tile->GetCell());
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