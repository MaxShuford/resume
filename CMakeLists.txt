cmake_minimum_required(VERSION 3.27)
project(vaporwave_desktop LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(desktop src/main.cpp)
target_compile_options(desktop PRIVATE -Wall -Wextra -Wpedantic)

if(EMSCRIPTEN)
  # Emscripten ships its own SDL2 port; -sUSE_SDL=2 pulls it in.
  target_compile_options(desktop PRIVATE -sUSE_SDL=2)
  target_link_options(desktop PRIVATE
    -sUSE_SDL=2
    -sMIN_WEBGL_VERSION=2   # WebGL2 == OpenGL ES 3.0
    -sMAX_WEBGL_VERSION=2)
  # Emit desktop.html + desktop.js + desktop.wasm
  set_target_properties(desktop PROPERTIES SUFFIX ".html")
else()
  find_package(SDL2 REQUIRED)
  find_package(OpenGL REQUIRED COMPONENTS GLES3)
  target_link_libraries(desktop PRIVATE SDL2::SDL2 OpenGL::GLES3)
endif()
