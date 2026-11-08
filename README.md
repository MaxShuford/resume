# Vaporwave Desktop Resume

An interactive resume presented as a Windows XP–inspired desktop with a vaporwave aesthetic, written in C++23 and compiled to WebAssembly for the browser.

The project is also a way for me to learn C++, graphics programming and WASM, so it's built up in small steps.

## Vision

- A desktop with draggable windows, a taskbar, a Start menu and desktop icons
- Each resume section opens as an "app": About.txt, a Projects folder, Contact, a music player, and a demo app (ray tracer, particle sim, or an original small game)
- Vaporwave look: pink/cyan gradients, a grid sunset, and a CRT/VHS post-processing shader
- XP-*inspired* window chrome drawn in code. No Microsoft assets (Bliss, logos, bitmaps).
- A plain HTML resume at `/resume.html`, built from the same content, for recruiters, mobile and screen readers

## Stack

| Layer | Choice |
|---|---|
| Language / build | C++23, CMake presets, Ninja |
| Platform | SDL2 (native build; Emscripten's built-in port on the web) |
| Graphics | OpenGL ES 3.0 natively = WebGL2 in the browser |
| Planned | `glm`, `stb_truetype`, `stb_image`, `toml++`, `doctest` |
| Error handling | `std::expected` rather than exceptions (keeps WASM small) |
| Deploy (later) | GitHub Actions + emsdk → GitHub Pages |

The same code builds two ways: **native** for fast iteration and debugging, and **web** (Emscripten) for the deployed site.

## Setup (Ubuntu / WSL)

```bash
sudo apt install build-essential cmake ninja-build pkg-config libsdl2-dev libgles-dev

# Emscripten (installed in ~/emsdk, outside the repo)
git clone https://github.com/emscripten-core/emsdk.git ~/emsdk
cd ~/emsdk && ./emsdk install latest && ./emsdk activate latest
echo 'EMSDK_QUIET=1 source "$HOME/emsdk/emsdk_env.sh"' >> ~/.bashrc
```

Tested with GCC 15.2, CMake 4.2, Ninja 1.13, SDL 2.32 and Emscripten 7.0.

## Build & run

```bash
# Native
cmake --preset native && cmake --build --preset native
./build/native/desktop

# Web
cmake --preset web && cmake --build --preset web
emrun build/web/desktop.html
```

If you configured `web` before `$EMSDK` was set, delete `build/web` and configure again.

## Layout

```
CMakeLists.txt       # what to build; EMSCRIPTEN branch vs native branch
CMakePresets.json    # how to build: `native` (Debug) and `web` (Release, Emscripten toolchain)
src/main.cpp         # entry point
```

Planned: `src/platform/`, `src/gfx/`, `src/wm/`, `src/apps/`, `assets/`, `content/resume.toml`, `tests/`, `web/shell.html`.

## Progress

### Milestone 1: a pink window, native and in the browser
- [x] Toolchain installed (native + emsdk)
- [x] CMake + presets
- [x] **Step 1:** includes (`<SDL.h>`, `<GLES3/gl3.h>`, `<emscripten.h>` guarded by `#ifdef`)
- [ ] **Step 2:** `SDL_Init(SDL_INIT_VIDEO)` with an error check. Builds; still to do: `int main(int, char**)`, `<cstdio>`, `\n`, `fprintf(stderr, ...)`
- [ ] **Step 3:** `SDL_GL_SetAttribute` for ES 3.0 (profile mask, major, minor), *before* creating the window
- [ ] **Step 4:** `SDL_CreateWindow` with `SDL_WINDOW_OPENGL`
- [ ] **Step 5:** `SDL_GL_CreateContext`
- [ ] **Step 6:** frame function: `SDL_PollEvent` → `glClearColor`/`glClear` → `SDL_GL_SwapWindow`
- [ ] **Step 7:** main loop: `while (running)` natively, `emscripten_set_main_loop_arg` on the web (state passed in a struct as `void*`)
- [ ] **Step 8:** cleanup: `SDL_GL_DeleteContext`, `SDL_DestroyWindow`, `SDL_Quit`
- [ ] Bonus: print `glGetString(GL_VERSION)`

### Later milestones
- 2D batched renderer, text via a font atlas
- Window manager: z-order, drag, resize, focus, taskbar, Start menu
- Apps and resume content (`resume.toml`)
- CRT/VHS post-processing shader
- Plain HTML resume fallback
- Deploy to GitHub Pages

## References

- SDL2 wiki (use `/SDL2/` URLs; the default is SDL3): https://wiki.libsdl.org/SDL2/CategoryAPI
- Local headers: `/usr/include/SDL2/`
- Lazy Foo' SDL2 tutorials (setup and event loop): https://lazyfoo.net/tutorials/SDL/
- Emscripten docs: https://emscripten.org/docs/
- cppreference: https://en.cppreference.com/

