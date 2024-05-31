//
// Created by Toudonou on 5/23/2024.
//

#include <ctime>

#include "Sprite.h"

#include "TextureManager.h"


Sprite::Sprite(const std::string &file_path) {
    m_position = {0, 0};

    m_id = randomStringGenerator() + std::to_string(std::time(nullptr));
    m_texture = TextureManager::GetInstance()->LoadImage(file_path);

    m_rect = SDL_Rect(m_position.x, m_position.y, 0, 0);
    if (SDL_QueryTexture(m_texture, nullptr, nullptr, &m_rect.w, &m_rect.h) != 0) {
        SDL_Log("Error when query texture informations = %s", SDL_GetError());
    }
}

Sprite::Sprite(const std::string &file_path, const Vector2 position) {
    m_position = position;

    m_id = randomStringGenerator() + std::to_string(std::time(nullptr));
    m_texture = TextureManager::GetInstance()->LoadImage(file_path);

    m_rect = SDL_Rect(m_position.x, m_position.y, 0, 0);
    if (SDL_QueryTexture(m_texture, nullptr, nullptr, &m_rect.w, &m_rect.h) != 0) {
        SDL_Log("Error when query texture informations = %s", SDL_GetError());
    }
}

Sprite::~Sprite() = default;

void Sprite::SetPosition(const Vector2 position) {
    m_position = position;

    m_rect = SDL_Rect(m_position.x, m_position.y, m_rect.w, m_rect.h);
}

void Sprite::SetTexture(const std::string &file_path) {
    m_texture = TextureManager::GetInstance()->LoadImage(file_path);

    if (SDL_QueryTexture(m_texture, nullptr, nullptr, &m_rect.w, &m_rect.h) != 0) {
        SDL_Log("Error when query texture informations = %s", SDL_GetError());
    }
}

void Sprite::SetVisibility(const bool isVisible) {
    m_isVisible = isVisible;
}
