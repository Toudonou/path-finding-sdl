//
// Created by Toudonou on 5/23/2024.
//

#ifndef SPRITE_H
#define SPRITE_H


#include <string>
#include <SDL.h>

#include "defines.h"

class Sprite {
public:
    explicit Sprite(const std::string &file_path);

    Sprite(const std::string &file_path, Vector2 position);

    ~Sprite();

    // Set the position of the sprite
    void SetPosition(Vector2 position);

    // Set the image
    void SetTexture(const std::string &file_path);

    // Set the visibility
    void SetVisibility(bool isVisible);

    // Get the position of the sprite
    [[nodiscard]] inline int GetPositionX() const { return m_position.x; }
    [[nodiscard]] inline int GetPositionY() const { return m_position.y; }

    [[nodiscard]] inline std::string GetId() const { return m_id; }

    [[nodiscard]] inline SDL_Texture *GetTexture() const { return m_texture; }

    inline SDL_Rect *GetRect() { return &m_rect; }

    // TODO : scale can be specify

private:
    // Store the renderer of the application
    static SDL_Renderer *s_render;

    // Store the position of the sprite
    Vector2 m_position{};

    // For the identification of the sprite
    std::string m_id;

    // For the visibility of the sprite
    bool m_isVisible = true;

    // Store the texture
    SDL_Texture *m_texture;

    // Store the sprite rectangle for drawing
    SDL_Rect m_rect{};
};


#endif //SPRITE_H
