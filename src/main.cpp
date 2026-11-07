#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#include <SDL.h>
#include <GLES3/gl3.h>
#include <iostream>

int main(int argc, char* argv[]) {
    // Setup SDL2 env.
    if (SDL_Init(SDL_INIT_VIDEO) != 0){
        std::printf("%s", SDL_GetError());
        return 1;
    }

    
}  