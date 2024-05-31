//
// Created by Toudonou on 5/23/2024.
//

#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <SDL.h>

#include "defines.h"
#include "SDL_scancode.h"


class InputManager {
public:
    static InputManager *GetInstance();

    void Init();

    // If a key is down (query once)
    [[nodiscard]] bool KeyDown(SDL_Scancode key) const;

    // If a key is maintained
    [[nodiscard]] bool KeyPressed(SDL_Scancode key) const;

    // If a mouse button is maintained
    [[nodiscard]] bool MouseButtonPressed(int button) const;

    // Get the position X position of mouse
    [[nodiscard]] inline int GetMouseX() const { return m_mousePosition.x; }

    // Get the position Y position of mouse
    [[nodiscard]] inline int GetMouseY() const { return m_mousePosition.y; }

    // To update keys registers
    void Update();

    // If quit application event is emit
    [[nodiscard]] bool QuitEvent() const;

    // To quit the input manager
    void Quit();

private:
    static InputManager *s_instance;

    //
    bool m_isInitialize = false;

    // Store all keys actions except keyDown action
    char *m_keys = nullptr;

    // To store keyDown action
    char *m_keysDown = nullptr;

    // Store mouse's buttons
    char m_mouseButtons[4]{};

    // Store mouse position
    Vector2 m_mousePosition{};

    //
    SDL_Event m_event{};

    // Quit application event
    bool s_quitApplication{};

    InputManager() = default;

    ~InputManager();
};


#endif //INPUTMANAGER_H
