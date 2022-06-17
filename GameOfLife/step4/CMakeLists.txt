cmake_minimum_required(VERSION 3.0)
cmake_policy(SET CMP0076 NEW)

project(gameOfLife LANGUAGES C)


add_subdirectory(game_sdl)

add_executable(${PROJECT_NAME} "")
target_sources(${PROJECT_NAME} PUBLIC main_sdl.c)
target_link_libraries(${PROJECT_NAME} PUBLIC game_sdl) 
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PUBLIC game_sdl ${SDL2_LIBRARIES})
install(TARGETS ${PROJECT_NAME})
