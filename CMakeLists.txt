cmake_minimum_required(VERSION 3.16)
project(SnakeGameUsingSFML)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.0
)
FetchContent_MakeAvailable(SFML)

add_executable(SnakeGame
    main.cpp
    Board.hpp
    Food.hpp
    Snake.hpp
    Utils.hpp
)

target_link_libraries(SnakeGame PRIVATE
    SFML::System
    SFML::Window
    SFML::Graphics
)

add_custom_command(TARGET SnakeGame POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/assets
            $<TARGET_FILE_DIR:SnakeGame>/assets
)
