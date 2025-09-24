cmake_minimum_required(VERSION 3.10)
project(WindowTest)
find_package(raylib REQUIRED)
add_executable(${PROJECT_NAME} main.c)
target_link_libraries(${PROJECT_NAME} raylib)
target_sources(${PROJECT_NAME} PRIVATE game.c map.c entity.c player.c balloon.c input.c weapon.c entity_list.c balloon_list.c)

if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()

file(COPY assets DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")