add_library(console drawer.c drawer.h)

target_include_directories(console PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

