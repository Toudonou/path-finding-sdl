cmake_minimum_required(VERSION 3.14)
project(path_findind_sdl)

set(CMAKE_CXX_STANDARD 20)

# --- SDL2 SETUP ---
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)
set(SDL2_PATH "SDL2/x86_64-w64-mingw32")
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

# Find SDL2_image
set(SDL2_IMAGE_PATH "SDL2_image/x86_64-w64-mingw32")
find_package(SDL2_image REQUIRED)
include_directories(${SDL2_IMAGE_INCLUDE_DIRS})

# Find SDL2_ttf
set(SDL2_TTF_PATH "SDL2_ttf/x86_64-w64-mingw32")
find_package(SDL2_ttf REQUIRED)
include_directories(${SDL2_TTF_INCLUDE_DIRS})

add_executable(${PROJECT_NAME}
        main.cpp
        PFS/Game.cpp
        PFS/Game.h
        PFS/TextureManager.cpp
        PFS/TextureManager.h
        PFS/Sprite.cpp
        PFS/Sprite.h
        PFS/RendererManager.cpp
        PFS/RendererManager.h
        PFS/Tile.cpp
        PFS/Tile.h
        PFS/defines.h
        PFS/Level.cpp
        PFS/Level.h
        PFS/defines.cpp
        PFS/InputManager.cpp
        PFS/InputManager.h
        PFS/Agent.cpp
        PFS/Agent.h
)

# Link spdlog and SDL
target_link_libraries(${PROJECT_NAME} PUBLIC ${SDL2_LIBRARY}  ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES})