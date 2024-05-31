//
// Created by Toudonou on 5/22/2024.
//

#include "TextureManager.h"

#include <SDL.h>
#include <SDL_image.h>

TextureManager *TextureManager::s_instance = nullptr;

// For singleton
TextureManager *TextureManager::GetInstance() {
    if (s_instance == nullptr) s_instance = new TextureManager();
    return s_instance;
}

// For initialization
void TextureManager::Init(SDL_Renderer *renderer) {
    if(m_isInitialize) {
        SDL_Log("Attempt to initialize the texture manager more than once");
        return;
    }

    if (renderer == nullptr) {
        SDL_Log("The renderer must be not null");
        return;
    }
    m_renderer = renderer;
    m_isInitialize = true;
}

// To get a texture
SDL_Texture *TextureManager::LoadImage(const std::string &file_path) {
    if (m_isInitialize == false) {
        SDL_Log("The texture manager must be initialized");
        return nullptr;
    }

    // The final texture
    SDL_Texture *texture = nullptr;

    // If the texture is all ready loaded
    if (m_textures.contains(file_path)) {
        texture = m_textures[file_path];
    }
    // If not loaded
    else {
        // Create the surface by using the image
        SDL_Surface *loadSurface = IMG_Load(file_path.c_str());
        if (loadSurface == nullptr) {
            SDL_Log("Error: Couldn't load image %s = %s", file_path.c_str(), SDL_GetError());
        } else {
            // Create the texture based on the surface
            texture = SDL_CreateTextureFromSurface(m_renderer, loadSurface);
            // Adding the texture to our textures map
            m_textures.insert(std::make_pair(file_path, texture));
        }
        SDL_FreeSurface(loadSurface);
    }

    return texture;
}

void TextureManager::Quit() {
    m_isInitialize = false;

    for (auto &texture: m_textures) {
        SDL_DestroyTexture(texture.second);
    }
    m_textures.clear();
}
