#include <SDL2/SDL.h>
#include "../bus/membus.h"
#include "../cartridge/Cartridge.h"
#include "../CPU/CPU.h"

int main(int argc, char* argv[])
{

    SDL_Window* window = nullptr;
    bool done = false;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        SDL_Log("SDL could not initialize! SDL_Error: %s", SDL_GetError());
        return 1;
    }

    window = SDL_CreateWindow(
        "Emulator",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        640,
        480,
        SDL_WINDOW_OPENGL
    );

    if (window == nullptr)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR,
                     "Could not create window: %s",
                     SDL_GetError());
        SDL_Quit();
        return 1;
    }
    
    membus mem;
    mem.loadCartridge("../../ROMs/03-op sp,hl.gb");
    CPU cpu(&mem);
    
    while (!done)
    {
        SDL_Event event;
    
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                done = true;
            }
        }

        /*
        Create a membus
        Call bus.loadCartridge("path/to/rom.gb")
        Create a CPU(&bus)
        In the game loop, call cpu.step() some number of times per frame (roughly 17556 times per frame at 60fps for a DMG)
        */
        for(int i = 0; i < 17556; i++){
           cpu.step();

        }
       
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}