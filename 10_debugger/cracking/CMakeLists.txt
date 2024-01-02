cmake_minimum_required(VERSION 3.10.0)

# Create new project
project(matches
    LANGUAGES C
    VERSION 1.0.0
    DESCRIPTION "Matches game application"
)

# Create game executable
add_executable(${PROJECT_NAME}
    src/md5/md5-crypt.c
    src/md5/md5.c
    src/game.c
)

# Link Matches engine library
target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/deps/matches_engine/build/include
)
target_link_libraries(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/deps/matches_engine/build/lib/libmatches_engine.a
)
