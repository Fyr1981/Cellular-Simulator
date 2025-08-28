cmake_minimum_required(VERSION 3.15)
project(CellularSimulator LANGUAGES CXX)

include(FetchContent)
FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG 5.5
)

FetchContent_MakeAvailable(raylib)

FetchContent_Declare(
    nlohmann_json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.11.2
)

FetchContent_MakeAvailable(nlohmann_json)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(APP_HEADERS
    include/CellularSimulator/App/Application.h
    include/CellularSimulator/App/RenderData.h
    include/CellularSimulator/App/Config.h
    include/CellularSimulator/App/ConfigLoader.h
)

set(APP_SOURCES
    src/App/Application.cpp
    src/App/ConfigLoader.cpp
)

set(CORE_HEADERS
    include/CellularSimulator/Core/Cell.h
    include/CellularSimulator/Core/GridTile.h
    include/CellularSimulator/Core/Simulator.h
    include/CellularSimulator/Core/CellSimulatorTypes.h
    include/CellularSimulator/Core/Command.h
    include/CellularSimulator/Core/CommandManager.h
    include/CellularSimulator/Core/CommandRegistry.h
    include/CellularSimulator/Core/StringInterner.h
    include/CellularSimulator/Core/Commands/DeathCommand.h
    include/CellularSimulator/Core/Commands/DefendCommand.h
    include/CellularSimulator/Core/Commands/SkipIfCommand.h
    include/CellularSimulator/Core/Commands/GiveEnergyCommand.h
    include/CellularSimulator/Core/Commands/IdleCommand.h
    include/CellularSimulator/Core/Commands/PhotosynthesisCommand.h
    include/CellularSimulator/Core/Commands/MoveForwardCommand.h
    include/CellularSimulator/Core/Commands/TurnRightCommand.h
    include/CellularSimulator/Core/Commands/TurnLeftCommand.h
    include/CellularSimulator/Core/Commands/EatForwardCommand.h
    include/CellularSimulator/Core/Commands/DivideCommand.h
)

set(CORE_SOURCES
    src/Core/Cell.cpp
    src/Core/GridTile.cpp
    src/Core/Simulator.cpp
    src/Core/CommandManager.cpp
    src/Core/StringInterner.cpp
    src/Core/Command.cpp
    src/Core/Commands/DeathCommand.cpp
    src/Core/Commands/DefendCommand.cpp
    src/Core/Commands/SkipIfCommand.cpp
    src/Core/Commands/GiveEnergyCommand.cpp
    src/Core/Commands/IdleCommand.cpp
    src/Core/Commands/PhotosynthesisCommand.cpp
    src/Core/Commands/MoveForwardCommand.cpp
    src/Core/Commands/TurnRightCommand.cpp
    src/Core/Commands/TurnLeftCommand.cpp
    src/Core/Commands/EatForwardCommand.cpp
    src/Core/Commands/DivideCommand.cpp
)

add_executable(CellularSimulator src/main.cpp)

add_custom_command(
    TARGET CellularSimulator POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_SOURCE_DIR}/config.json"
            "$<TARGET_FILE_DIR:CellularSimulator>/config.json"
    COMMENT "Copying config.json to output directory..."
)

target_sources(CellularSimulator
    PRIVATE
        ${APP_HEADERS}
        ${APP_SOURCES}
        ${CORE_HEADERS}
        ${CORE_SOURCES}
)

target_link_libraries(CellularSimulator
    PRIVATE
        raylib
        nlohmann_json::nlohmann_json
)

target_include_directories(CellularSimulator PRIVATE ${PROJECT_SOURCE_DIR}/include)

message(STATUS "'${PROJECT_NAME}' project has been built successfully!")

find_package(Doxygen)
if(DOXYGEN_FOUND)
    add_custom_target(doxygen-docs
        COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_SOURCE_DIR}/Doxyfile
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        COMMENT "Generating API documentation with Doxygen..."
        VERBATIM
    )
    set_target_properties(doxygen-docs PROPERTIES FOLDER "Documentation")
    message(STATUS "Doxygen target 'doxygen-docs' has been added.")
endif()
