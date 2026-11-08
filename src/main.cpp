#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#include <SDL.h>
#include <GLES3/gl3.h>
#include <cstdio>

int main(int, char**) {
    // Setup SDL2 env.
    if (SDL_Init(SDL_INIT_VIDEO) != 0){
        std::fprintf(stderr, "SDL_Init failed ***BOOM*** %s\n", SDL_GetError());
        return 1;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);

    SDL_Window *frame = SDL_CreateWindow("Max Shufords Resume", 
                                        SDL_WINDOWPOS_CENTERED, 
                                        SDL_WINDOWPOS_CENTERED, 
                                        1280, 720, SDL_WINDOW_OPENGL);

    if(frame == nullptr) {
        std::fprintf(stderr, "SDL_CreateWindow failed ***BOOM*** %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_GLContext ctx = SDL_GL_CreateContext(frame); 
    if(ctx == nullptr) {
        std::fprintf(stderr, "SDL_GL_CreateContext failed ***BOOM*** %s\n", SDL_GetError());
        SDL_DestroyWindow(frame);
        SDL_Quit();
        return 1;
    }

    
}