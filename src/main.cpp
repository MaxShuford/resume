#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#include <SDL.h>
#include <GLES3/gl3.h>
#include <cstdio>

struct AppState {
    SDL_Window* window;
    SDL_GLContext ctx;
    bool running;
};

void frame(void* arg) {
    AppState* s = (AppState*)arg;
    SDL_Event event;
    while(SDL_PollEvent(&event)){
        if(event.type == SDL_QUIT){
            s->running = false;
        }
    }

    glClearColor(1.0f, 0.4f, 0.8f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    SDL_GL_SwapWindow(s->window);           
}


int main(int, char**) {
    // Setup SDL2 env.
    if (SDL_Init(SDL_INIT_VIDEO) != 0){
        std::fprintf(stderr, "SDL_Init failed ***BOOM*** %s\n", SDL_GetError());
        return 1;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);

    static AppState state = {nullptr, nullptr, true};

    state.window = SDL_CreateWindow("Max Shufords Resume", 
                                        SDL_WINDOWPOS_CENTERED, 
                                        SDL_WINDOWPOS_CENTERED, 
                                        1280, 720, SDL_WINDOW_OPENGL);

    if(state.window == nullptr) {
        std::fprintf(stderr, "SDL_CreateWindow failed ***BOOM*** %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    state.ctx = SDL_GL_CreateContext(state.window); 
    if(state.ctx == nullptr) {
        std::fprintf(stderr, "SDL_GL_CreateContext failed ***BOOM*** %s\n", SDL_GetError());
        SDL_DestroyWindow(state.window);
        SDL_Quit();
        return 1;
    }

    SDL_GL_SetSwapInterval(1);

    while(state.running){
        
        frame(&state);
        

    }

    SDL_GL_DeleteContext(state.ctx);
    SDL_DestroyWindow(state.window);
    SDL_Quit();
}
