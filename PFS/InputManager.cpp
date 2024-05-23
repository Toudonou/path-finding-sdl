//
// Created by Toudonou on 5/23/2024.
//

#include "InputManager.h"

InputManager *InputManager::s_instance = nullptr;

InputManager *InputManager::GetInstance() {
    if (s_instance == nullptr) s_instance = new InputManager();
    return s_instance;
}

void InputManager::Init() {
    if (!m_isInitialize) {
        m_keys = static_cast<char *>(malloc(SDL_NUM_SCANCODES * sizeof(char)));
        if (m_keys == nullptr) {
            SDL_Log("Error during Input (keys) manager initialization");
            return;
        }
        memset(m_keys, 0, SDL_NUM_SCANCODES);

        m_keysDown = static_cast<char *>(malloc(SDL_NUM_SCANCODES * sizeof(char)));
        if (m_keysDown == nullptr) {
            SDL_Log("Error during Input (keys) manager initialization");
            return;
        }
        memset(m_keysDown, 0, SDL_NUM_SCANCODES);

        m_isInitialize = true;
    } else {
        SDL_Log("Attempt to initialize input manager more than once");
    }
}

bool InputManager::KeyDown(const SDL_Scancode key) const {
    if (m_isInitialize == false) {
        SDL_Log("The input manager must be initialized");
        return false;
    }

    if (0 <= key && key < SDL_NUM_SCANCODES) {
        SDL_Log("Invalid keyboard key!");
        return false;
    }

    const bool temp = m_keysDown[key];
    m_keysDown[key] = 0;

    return temp;
}

bool InputManager::KeyPressed(const SDL_Scancode key) const {
    if (m_isInitialize == false) {
        SDL_Log("The input manager must be initialized");
        return false;
    }

    if (0 <= key && key < SDL_NUM_SCANCODES) {
        SDL_Log("Invalid keyboard key!");
        return false;
    }

    return m_keys[key];
}

bool InputManager::MouseButtonPressed(const int button) const {
    if (m_isInitialize == false) {
        SDL_Log("The input manager must be initialized");
        return false;
    }

    // Only the left, the right and the middle buttons will be available
    if (1 <= button && button <= 3) {
        SDL_Log("Invalid mouse button!");
        return false;
    }

    return m_mouseButtons[button];
}

void InputManager::Update() {
    if (m_isInitialize == false) {
        SDL_Log("The input manager must be initialized");
        return;
    }

    while (SDL_PollEvent(&m_event)) {
        if (m_event.type == SDL_QUIT) s_quitApplication = true;

        // Updating mouse position
        m_mousePosition = {m_event.motion.x, m_event.motion.y};

        switch (m_event.type) {
            case SDL_KEYDOWN:
                m_keys[m_event.key.keysym.scancode] = 1;
                if (m_keysDown[m_event.key.keysym.scancode] == -1) m_keysDown[m_event.key.keysym.scancode] = 1;
                break;
            case SDL_KEYUP:
                m_keys[m_event.key.keysym.scancode] = 0;
                m_keysDown[m_event.key.keysym.scancode] = -1;
                break;
            case SDL_MOUSEBUTTONDOWN:
                m_mouseButtons[m_event.button.button] = 1;
                break;
            case SDL_MOUSEBUTTONUP:
                m_mouseButtons[m_event.button.button] = 0;
                break;
            default:
                break;
        }
    }
}

bool InputManager::QuitEvent() const {
    return s_quitApplication;
}

void InputManager::Quit() {
    m_isInitialize = false;
}

InputManager::~InputManager() {
    delete s_instance;
    delete m_keys;
    delete m_keysDown;
}
