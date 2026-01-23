// Created by Pawel Pajor on 23/01/2026. All rights reserved.

#define WIN32_LEAN_AND_MEAN

#include <SDL3/SDL.h>
#include <Windows.h>

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

  if (!SDL_Init(SDL_INIT_VIDEO)) {
    MessageBoxA(nullptr, SDL_GetError(), "SDL_Init failed",
                MB_OK | MB_ICONERROR);
    return 1;
  }

  SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Hello",
                           "Hello from SDL3!", nullptr);

  SDL_Quit();
  return 0;
}
