#include "CellularSimulator/App/Application.h"
#include "CellularSimulator/Core/GridTile.h"
#include "CellularSimulator/Core/Cell.h"
#include <iostream>
#include <thread>   
#include <chrono>

using namespace CellularSimulator::App;
using namespace CellularSimulator::Core;

Application::Application()
{
    Sim = std::make_unique<Core::Simulator>(10, 10);
}

Application::~Application()
{
}

void PrintGrid(const Simulator& Sim)
{
    for (int32_t Y = 0; Y < Sim.GetHeight(); ++Y)
    {
        for (int32_t X = 0; X < Sim.GetWidth(); ++X)
        {
            const GridTile* Tile = Sim.GetTile(X, Y);
            if (Tile && Tile->HasCell())
            {
                std::cout << "O ";
            }
            else
            {
                std::cout << ". ";
            }
        }
        std::cout << '\n';
    }
    std::cout << "--------------------" << '\n';
}

void Application::Run()
{
    std::cout << "Starting simulation..." << '\n';
    
    Sim->Randomize(0.5f);
    PrintGrid(*Sim);
    
    for (int i = 0; i < 100; ++i)
    {
        Sim->Update();
        PrintGrid(*Sim);
        std::cout << "Step: " << i + 1 << '\n';
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
    
    std::cout << "Simulation finished. Press Enter to exit." << '\n';
    std::cin.get();
}

