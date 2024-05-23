//
// Created by Toudonou on 5/23/2024.
//

#include <algorithm>

#include "RendererManager.h"
#include "Game.h"
#include "Sprite.h"

RendererManager *RendererManager::s_instance = nullptr;
SDL_Renderer *RendererManager::s_render = nullptr;

RendererManager *RendererManager::GetInstance() {
    if (s_instance == nullptr) s_instance = new RendererManager();
    return s_instance;
}

void RendererManager::Init(SDL_Renderer *renderer) {
    s_render = Game::GetInstance()->GetRenderer();
    m_isInitialize = true;
}

void RendererManager::AddSprite(Sprite *sprite) {
    if (m_isInitialize == false) {
        SDL_Log("The renderer must be initialized");
        return;
    }

    if (sprite == nullptr) {
        SDL_Log("The sprite must be not null");
        return;
    }

    // Check if the sprite is already added to the manager
    if (std::ranges::find(m_sprites_id, sprite->GetId()) == m_sprites_id.end()) {
        m_sprites.insert(std::make_pair(sprite->GetId(), sprite));
        m_sprites_id.push_back(sprite->GetId());
    }
}

void RendererManager::Update() const {
    if (m_isInitialize == false) {
        SDL_Log("The game must be initialized");
        return;
    }

    SDL_RenderClear(s_render);

    for (const auto &sprite_id: m_sprites_id) {
        SDL_RenderCopy(s_render, m_sprites.at(sprite_id)->GetTexture(), nullptr, m_sprites.at(sprite_id)->GetRect());
    }

    SDL_RenderPresent(s_render);
}

void RendererManager::Quit() {
    m_isInitialize = false;
    m_sprites.clear();
    m_sprites_id.clear();
}
