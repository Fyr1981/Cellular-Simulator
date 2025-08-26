# Cellular Simulator

[![Language](https://img.shields.io/badge/Language-C%2B%2B17-blue.svg)](https://isocpp.org/)
[![License](https://img.shields.io/badge/License-MIT-green.svg)](LICENSE)
[![Platform](https://img.shields.io/badge/Platform-Windows-informational.svg)]()

A high-performance, multithreaded artificial life simulation built from scratch in modern C++. Watch simple rules give rise to complex, evolving ecosystems.

![Simulation Showcase GIF](showcase.gif)

## Key Features

- **Massively Parallel Engine:** The core simulation loop is heavily parallelized using C++17 Parallel STL, capable of handling millions of agents at hundreds of updates per second.
- **Genetic Evolution:** Agents (cells) are driven by a genome that defines their behavior. The `Divide` command includes a mutation chance, allowing for emergent strategies and evolution.
- **Complex Agent Behavior:** Cells can perform actions like Photosynthesis, Movement (turning, moving forward), Eating other cells, and Division.
- **Data-Oriented High-Performance Design:** Utilizes advanced patterns like Object Pooling, String Interning, and lock-free parallel algorithms to maximize performance.
- **Interactive Experience:**
    - Fully interactive 2D camera with smooth panning and zooming.
    - Simulation controls (pause/resume, speed adjustment).
    - Cell Inspector UI to view the genome and state of any cell in real-time.
- **Configurable:** All simulation parameters can be tweaked in an external `config.json` file.

## Tech Stack

- **Language:** C++17
- **Build System:** CMake
- **Graphics & Input:** RayLib
- **Configuration:** nlohmann/json
- **Concurrency:** C++17 Parallel STL, `std::thread`, `std::mutex`, `std::atomic`

## Building and Running

### Prerequisites
- A C++17 compliant compiler (e.g., MSVC, GCC, Clang)
- CMake (version 3.16 or higher)
- Git

### Build Steps

```bash
# 1. Clone the repository
git clone https://github.com/your-username/CellularSimulator.git
cd CellularSimulator

# 2. Configure the project using CMake (dependencies will be fetched automatically)
cmake -S . -B build

# 3. Build the project
# For multi-config generators (like Visual Studio), specify the config
cmake --build build --config Release

# 4. Run the application
# The executable will be in the build/Release directory
./build/Release/CellularSimulator.exe
```

### Configuration
The simulation can be customized by editing the config.json file located in the root directory. This file is automatically copied to the build output directory.

Example config.json:
```json
{
  "window": {
    "width": 1920,
    "height": 1080,
    "fullscreen": true,
    "fps": 60
  },
  "simulation": {
    "width": 300,
    "height": 300,
    "density": 0.5,
    "ups": 10,
    "seed": 0,
    "max_update_time": 0.1
  },
  "cell": {
    "genome_length": 16,
    "initial_energy": 100.0
  }
}
```

### Controls
- LMB + Drag: Pan Camera
- Mouse Wheel: Zoom Camera
- RMB Click: Select a cell to inspect
- Spacebar: Pause / Resume simulation
- Left/Right Arrow: Decrease / Increase simulation speed (UPS)
- F11: Toggle Fullscreen