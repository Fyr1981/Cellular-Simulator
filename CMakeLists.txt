cmake_minimum_required(VERSION 3.15)
project(CellularSimulator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(CellularSimulator
    src/main.cpp
)

target_include_directories(CellularSimulator PRIVATE ${PROJECT_SOURCE_DIR}/include)

message(STATUS "'${PROJECT_NAME}' project has been built successfully!")
