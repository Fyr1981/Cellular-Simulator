cmake_minimum_required(VERSION 3.15)
project(CellularSimulator LANGUAGES CXX)

include(FetchContent)
FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG 5.5
)

FetchContent_MakeAvailable(raylib)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(APP_HEADERS
    include/CellularSimulator/App/Application.h
)
set(APP_SOURCES
    src/App/Application.cpp
)

set(CORE_HEADERS
    include/CellularSimulator/Core/Cell.h
    include/CellularSimulator/Core/GridTile.h
    include/CellularSimulator/Core/Simulator.h
    include/CellularSimulator/Core/CellSimulatorTypes.h
    include/CellularSimulator/Core/Command.h
    include/CellularSimulator/Core/CommandFactory.h
    include/CellularSimulator/Core/CommandRegistry.h
)
set(CORE_SOURCES
    src/Core/Cell.cpp
    src/Core/GridTile.cpp
    src/Core/Simulator.cpp
    src/Core/CommandFactory.cpp
)

add_executable(CellularSimulator src/main.cpp)

target_sources(CellularSimulator
    PRIVATE
        ${APP_HEADERS}
        ${APP_SOURCES}
        ${CORE_HEADERS}
        ${CORE_SOURCES}
)

target_link_libraries(CellularSimulator PRIVATE raylib)

target_include_directories(CellularSimulator PRIVATE ${PROJECT_SOURCE_DIR}/include)

message(STATUS "'${PROJECT_NAME}' project has been built successfully!")
