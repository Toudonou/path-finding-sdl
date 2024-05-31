//
// Created by Toudonou on 5/22/2024.
//

#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H
#include <SDL_render.h>
#include <string>
#include <unordered_map>


class TextureManager {
public:
    // For singleton
    static TextureManager *GetInstance();

    // For initialization
    void Init(SDL_Renderer *renderer);

    // To get a texture
    SDL_Texture *LoadImage(const std::string &file_path);

    // For cleaning up everythings
    void Quit();

private:
    static TextureManager *s_instance;

    bool m_isInitialize = false;

    // To store all the textures
    std::unordered_map<std::string, SDL_Texture *> m_textures = {};

    // To store the renderer of the game
    SDL_Renderer *m_renderer{};

    TextureManager() = default;

    ~TextureManager() = default;
};


#endif //TEXTUREMANAGER_H
