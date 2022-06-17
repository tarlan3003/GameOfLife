cmake_minimum_required(VERSION 3.0)
cmake_policy(SET CMP0076 NEW)

project(gameOfLife LANGUAGES C)


add_subdirectory(game_sdl)
add_subdirectory(game)	
add_subdirectory(console)

set (SRC1 main_sdl.c)
set (SRC2 main.c)

add_executable(${PROJECT_NAME} "")
target_sources(${PROJECT_NAME} PUBLIC ${SRC2})
target_link_libraries(${PROJECT_NAME} PUBLIC game console) 
install(TARGETS ${PROJECT_NAME})


set(SDL gameOfLife_SDL)
add_executable(${SDL} "")
target_sources(${SDL} PUBLIC ${SRC1})
target_link_libraries(${SDL} PUBLIC game_sdl) 
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
target_link_libraries(${SDL} PUBLIC game_sdl ${SDL2_LIBRARIES})
install(TARGETS ${SDL})


set(TEST_PROJECT test_pract1)
add_executable(${TEST_PROJECT} "")
target_sources(${TEST_PROJECT} PUBLIC ctest.c)
target_link_libraries(${TEST_PROJECT} PUBLIC game cunit)  
#install(TARGETS ${TEST_PROJECT})

enable_testing()
add_test(NAME "MyCunitTest" COMMAND ${TEST_PROJECT})