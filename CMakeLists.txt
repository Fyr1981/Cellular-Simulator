cmake_minimum_required(VERSION 3.15)
project(CellularSimulator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(APP_SOURCES
    src/App/Application.cpp
)

set(CORE_SOURCES
    src/Core/Cell.cpp
    src/Core/GridTile.cpp
    src/Core/Simulator.cpp
)

add_executable(CellularSimulator
    src/main.cpp
    ${APP_SOURCES}
    ${CORE_SOURCES}
)

target_include_directories(CellularSimulator PRIVATE ${PROJECT_SOURCE_DIR}/include)

message(STATUS "'${PROJECT_NAME}' project has been built successfully!")
