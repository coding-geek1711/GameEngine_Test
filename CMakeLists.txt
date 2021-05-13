cmake_minimum_required(VERSION 3.0.0)
project(Game_Engine_Test VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(Game_Engine_Test main.cpp)

find_package(SFML 2.5
    COMPONENTS
        system window graphics network audio REQUIRED
    )

target_include_directories(
    Game_Engine_Test
    PRIVATE
    "${PROJECT_BINARY_DIR}"
)

target_link_libraries(Game_Engine_Test 
    sfml-graphics 
    sfml-window 
    sfml-system
    sfml-audio
    sfml-network)

file(COPY fonts DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY maps DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
