cmake_minimum_required(VERSION 3.10.0)

project(matches_engine
    LANGUAGES C
    VERSION 1.0.0
    DESCRIPTION "Matches game engine library"
)

# Create library
add_library(${PROJECT_NAME} STATIC
    src/matches.c
)

# Install library and its header files
install(TARGETS ${PROJECT_NAME} DESTINATION lib)
install(FILES src/matches.h DESTINATION include/${PROJECT_NAME})
