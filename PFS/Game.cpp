//
// Created by Toudonou on 5/22/2024.
//

#include "Game.h"

#include <SDL.h>

#include "InputManager.h"
#include "Level.h"
#include "RendererManager.h"
#include "TextureManager.h"

Game *Game::s_instance = nullptr;

// For singleton
Game *Game::GetInstance() {
    if (s_instance == nullptr) s_instance = new Game();
    return s_instance;
}

// For initialization
void Game::Init(const int windowWidth, const int windowHeight) {
    if (m_isInitialize) {
        SDL_Log("Attempt to initialize the game engine more than once");
        return;
    }

    m_width = windowWidth;
    m_height = windowHeight;

    // Init everythings in SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        SDL_Log("Error: Couldn't initialize SDL = %s", SDL_GetError());
        Quit();
    }

    // Create the window.
    m_window = SDL_CreateWindow("Path Finding", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                m_width, m_height, 0);
    if (m_window == nullptr) {
        SDL_Log("Error: Couldn't create the window = %s", SDL_GetError());
        Quit();
    }

    // Create a renderer for GPU accele rated drawing.
    m_render = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (m_render == nullptr) {
        SDL_Log("Error: Couldn't create the renderer = %s", SDL_GetError());
        Quit();
    }
    m_isInitialize = true;
    m_isRunning = true;

    TextureManager::GetInstance()->Init(m_render);
    // Initialize the texture manager before the renderer manager
    RendererManager::GetInstance()->Init(m_render);
    InputManager::GetInstance()->Init();
}

void Game::Run() {
    if (m_isInitialize == false) {
        SDL_Log("The game must be initialized");
        return;
    }

    int nbrTile = (m_width < m_height ? m_width : m_height) / 48;
    nbrTile -= 1 - nbrTile % 2;

    const auto level = new Level(nbrTile, {m_width / 2 - (nbrTile * 48) / 2, m_height / 2 - (nbrTile * 48) / 2});

    // Game loop
    while (m_isRunning) {
        level->Update();

        if (InputManager::GetInstance()->QuitEvent()) m_isRunning = false;
        RendererManager::GetInstance()->Update();
        InputManager::GetInstance()->Update();
    }

    delete level;
}

SDL_Renderer *Game::GetRenderer() const {
    if (m_isInitialize == false) {
        SDL_Log("The game must be initialized");
        return nullptr;
    }
    return m_render;
}

// For cleaning up everythings
void Game::Quit() {
    m_isRunning = false;
    m_isInitialize = false;

    InputManager::GetInstance()->Quit();
    // Quit the renderer manager before the texture manager
    RendererManager::GetInstance()->Quit();
    TextureManager::GetInstance()->Quit();

    // Free allocated elements
    SDL_DestroyRenderer(m_render);
    SDL_DestroyWindow(m_window);

    // Clean up.
    SDL_Quit();
}

Game::~Game() {
    delete s_instance;
}
