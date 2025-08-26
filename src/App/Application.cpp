#include "CellularSimulator/App/Application.h"
#include <chrono>
#include <iomanip>
#include <iostream>
#include "CellularSimulator/App/ConfigLoader.h"
#include "CellularSimulator/Core/GridTile.h"
#include "CellularSimulator/Core/Cell.h"
#include <string>
#include <thread>
#include "raylib.h"
#include "raymath.h"
#include "CellularSimulator/Core/StringInterner.h"

using namespace CellularSimulator::App;

Application::Application()
{
    auto LoadedConfig = ConfigLoader::LoadConfigFromFile("config.json");
    if (LoadedConfig)
    {
        AppConfig = *LoadedConfig;
        std::cout << "CellularSimulator config loaded from config.json" << '\n';
    }
    else
    {
        std::cout << "config.json for CellularSimulator not found or invalid. Using default settings." << '\n';
    }

    const int32_t WindowHeight = AppConfig.WindowHeight;
    const int32_t WindowWidth = AppConfig.WindowWidth;
    InitWindow(WindowWidth, WindowHeight, "Cellular Simulator");
    FramesPerSecond = AppConfig.FramesPerSecond;
    SetTargetFPS(FramesPerSecond);
    unsigned int WindowFlags = FLAG_WINDOW_RESIZABLE;
    SetWindowState(WindowFlags);

    const int32_t SimWidth = AppConfig.SimWidth;
    const int32_t SimHeight = AppConfig.SimHeight;
    int32_t Seed = AppConfig.Seed;
    if (Seed == 0)
    {
        Seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    }
    Sim = std::make_unique<Core::Simulator>(SimWidth, SimHeight, Seed);
    Sim->Randomize(AppConfig.InitialDensity, AppConfig.GenomeLength, AppConfig.InitialEnergy);
    UpdatesPerSecond = AppConfig.UpdatesPerSecond;

    const float WorldWidthPx = static_cast<float>(SimWidth * TileSize);
    const float WorldHeightPx = static_cast<float>(SimHeight * TileSize);

    const float XRatio = static_cast<float>(WindowWidth) / WorldWidthPx;
    const float YRatio = static_cast<float>(WindowHeight) / WorldHeightPx;

    const float InitialZoom = std::min(XRatio, YRatio);

    WorldCamera.offset = {static_cast<float>(WindowWidth) / 2.0f, static_cast<float>(WindowHeight) / 2.0f};
    WorldCamera.rotation = 0.0f;
    WorldCamera.zoom = InitialZoom;
    WorldCamera.target = {WorldWidthPx / 2.0f, WorldHeightPx / 2.0f};

    if(AppConfig.bStartFullscreen)
    {
        ToggleFullscreen();
    }

    bIsRunning = true;
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
    UpdateThread = std::thread(&Application::UpdateLoop, this);
    RenderLoop();
}

void Application::UpdateLoop()
{
    auto LastTime = std::chrono::high_resolution_clock::now();
    double TimeAccumulator = 0.0;

    while (bIsRunning.load())
    {
        auto FrameStartTime = std::chrono::high_resolution_clock::now();

        // Input from main thread
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
                    SimState.Inspector.Genome = Core::StringInterner::GetInstance().ResolveGenome(Cell->GetGenome());
                    SimState.Inspector.bShouldDisplayGenome = true;
                }
            }
            else
            {
                SimState.Inspector.bShouldDisplayGenome = false;
            }
        }

        auto CurrentTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> DeltaTime = CurrentTime - LastTime;
        LastTime = CurrentTime;
        if (!bIsPaused.load())
        {
            TimeAccumulator += DeltaTime.count();
            const double TimeBetweenUpdates = 1.0 / UpdatesPerSecond.load();
            while (TimeAccumulator >= TimeBetweenUpdates)
            {
                Sim->Update();
                TimeAccumulator -= TimeBetweenUpdates;
            }
        }
        else
        {
            TimeAccumulator = 0.f;
        }

        SimState.Tiles.clear();
        SimState.Tiles.reserve(Sim->GetActiveCellCount());
        for (int32_t i = 0; i < Sim->GetWidth(); ++i)
        {
            for (int32_t j = 0; j < Sim->GetHeight(); ++j)
            {
                const Core::GridTile* TileInProcess = Sim->GetTile(i, j);
                if (TileInProcess)
                {
                    SimState.Tiles.push_back({i, j, GetTileColor(TileInProcess)});
                }
            }
        }
        if (UpdatesPerSecond < FramesPerSecond)
        {
            std::lock_guard<std::mutex> Lock(SharedStateMutex);
            SharedState.UpdateFromBuffer(SimState);
        }
        else
        {
            if (SharedStateMutex.try_lock())
            {
                SharedState.UpdateFromBuffer(SimState);
                SharedStateMutex.unlock();
            }
        }
    }
}

void Application::RenderLoop()
{
    while (!WindowShouldClose())
    {
        {
            std::lock_guard<std::mutex> lock(SharedStateMutex);
            RenderState = SharedState;
        }
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
    BeginDrawing();
    ClearBackground(DARKGRAY);
    BeginMode2D(WorldCamera);
    for (const auto& TileData : RenderState.Tiles)
    {
        DrawRectangle(TileData.X * TileSize, TileData.Y * TileSize, TileSize, TileSize, TileData.TileColor);
    }
    EndMode2D();
    if (RenderState.Inspector.bShouldDisplayGenome)
    {
        for (size_t i = 0; i < RenderState.Inspector.Genome.size(); ++i)
        {
            DrawText(RenderState.Inspector.Genome[i].c_str(), 10, 30 + (i * 20), 20, LIME);
        }
    }
    std::string StatusText = bIsPaused.load() ? "PAUSED" : "RUNNING";
    StatusText += " | UPS: " + std::to_string(UpdatesPerSecond.load());
    DrawText(StatusText.c_str(), 10, 10, 20, LIME);
    DrawFPS(GetScreenWidth() - 100, 10);
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
    return InCell->GetColor();
}