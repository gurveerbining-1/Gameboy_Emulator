#include <SDL2/SDL.h>
#include "../bus/membus.h"
#include "../cartridge/Cartridge.h"
#include "../CPU/CPU.h"
#include "../PPU/PPU.h"
#include "../timer/timer.h"

int main(int argc, char* argv[])
{

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_Texture* texture = nullptr;
    
    bool done = false;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        SDL_Log("SDL could not initialize! SDL_Error: %s", SDL_GetError());
        return 1;
    }

    window = SDL_CreateWindow(
        "Game Boy",
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

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer){
        SDL_Log("Could not create SDL renderer %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    texture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_RGB24,
        SDL_TEXTUREACCESS_STREAMING,
        160,
        144
    );

    if (!texture)
    {
        SDL_Log("Failed to create texture: %s", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    membus mem;
    mem.loadCartridge("../../ROMs/dmg-acid2.gb");
    CPU cpu(&mem);
    PPU ppu(&mem);
    timer tmr(&mem);     // timer gets bus pointer for interrupt requests
    mem.setTimer(&tmr);  // bus gets timer pointer for register routing
    uint32_t last_frame_cycles = 0;
    
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

        Before building the real PPU, stub it so 02-interrupts.gb can run. In your main loop, after every cpu.step(),
        increment a cycle counter. When it reaches 17556 cycles (one frame), 
        write 0x90 to 0xFF44 (LY) and request a VBlank interrupt by setting bit 0 of IF:
        bus.write(0xFF0F, bus.read(0xFF0F) | 0x01);
        The Game Boy runs at 4,194,304 cycles per second at 60fps, 
        which means one frame is about 70224 cycles. When cycle_count crosses that threshold, 
        fire the VBlank interrupt and reset the counter.
        */
        for (int i = 0; i < 17556; i++) {
            cpu.step();
            ppu.step(cpu.getLastCycles());
            tmr.step(cpu.getLastCycles());
            if(ppu.isFrameReady()){
                // update texture and renderer
                void* pixels;
                int pitch;
                SDL_LockTexture(texture, nullptr, &pixels, &pitch);
                
                uint8_t* dst = static_cast<uint8_t*>(pixels);
                uint8_t* fb = ppu.getFramebuffer();
                
                // convert 0-3 shade values to RGB
                static const uint8_t palette[4][3] = {
                    {255, 255, 255},  // 0 = white
                    {170, 170, 170},  // 1 = light gray
                    {85,  85,  85},   // 2 = dark gray
                    {0,   0,   0}     // 3 = black
                };
                
                // framebuffer stores values 0–3 (the four Game Boy shades). 
                // SDL needs actual RGB bytes. This lookup table converts shade to RGB
                // For every pixel, read the shade from framebuffer, look up its RGB values, 
                // write 3 bytes into the texture memory. i * 3 because each pixel takes 3 bytes (R, G, B).
                for(int i = 0; i < 160 * 144; i++){
                    uint8_t shade = fb[i] & 0x03;
                    dst[i * 3 + 0] = palette[shade][0];
                    dst[i * 3 + 1] = palette[shade][1];
                    dst[i * 3 + 2] = palette[shade][2];
                }
                
                SDL_UnlockTexture(texture);
                SDL_RenderClear(renderer);
                SDL_RenderCopy(renderer, texture, nullptr, nullptr);
                SDL_RenderPresent(renderer);
                

                ppu.clearFrameReady(); // reset
            }
        }
        
        /*
        if (cpu.getCycles() - last_frame_cycles >= 70224)
        {
            last_frame_cycles += 70224;

            mem.write(0xFF44, 144);

            uint8_t IF = mem.read(0xFF0F);
            mem.write(0xFF0F, IF | 0x01);
        }
        */
        
       
    }
    SDL_DestroyTexture(texture);
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer); 
    SDL_Quit();

    return 0;
}