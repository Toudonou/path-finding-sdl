//
// Created by Toudonou on 5/23/2024.
//

#ifndef RENDERER_MANAGER_H
#define RENDERER_MANAGER_H

#include "Sprite.h"
#include <unordered_map>
#include <vector>

class RendererManager {
public:
    static RendererManager *GetInstance();

    void Init(SDL_Renderer *renderer);

    void AddSprite(Sprite *sprite);

    void Update() const;

    void Quit();

private:
    // For singleton
    static RendererManager *s_instance;
    // Store the renderer of the application
    static SDL_Renderer *s_render;

    // To store the sprites pointers : unordered_map is more efficient
    std::unordered_map<std::string, Sprite *> m_sprites;

    // To keep track of the order of the sprites
    std::pmr::vector<std::string> m_sprites_id;

    //
    bool m_isInitialize = false;

    RendererManager() = default;

    ~RendererManager();
};


#endif //RENDERER_MANAGER_H
