// Based on this tutorial : https://www.youtube.com/watch?v=UAlYELsxYfs&t=5s
// For SDL_image : https://416rehman.medium.com/setup-sdl2-image-for-clion-using-cmake-82affc3b6f7a

#include "PFS/Game.h"

int main(int argc, char **argv) {


    Game *game = Game::GetInstance();

    game->Init(480, 480);
    game->Run();
    game->Quit();

    return 0;
}
