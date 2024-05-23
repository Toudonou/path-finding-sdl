//
// Created by Toudonou on 5/22/2024.
//

#ifndef GAME_H
#define GAME_H
#include <SDL_render.h>


class Game {
public:
    // For singleton
    static Game *GetInstance();

    // For initialization
    void Init(int windowWidth, int windowHeight);

    // Run method
    void Run();

    [[nodiscard]] SDL_Renderer *GetRenderer() const;

    // For cleaning up everythings
    void Quit();

private:
    static Game *s_instance;

    int m_width{};
    int m_height{};
    bool m_isInitialize = false;
    bool m_isRunning = false;

    SDL_Window* m_window = nullptr;
    SDL_Renderer *m_render = nullptr;

    Game() = default;

    ~Game();
};




#endif //GAME_H
