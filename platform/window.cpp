#include <SDL2/SDL.h>
#include "../bus/membus.h"
#include "../cartridge/Cartridge.h"
#include "../CPU/CPU.h"
#include "../PPU/PPU.h"
#include "../timer/timer.h"
#include "../input/Joypad.h"

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
    Joypad jpad(&mem);   // joypad gets bus pointer for interrupt requests
    mem.setJoypad(&jpad);// bus gets joypad pointer for routing
    uint32_t last_frame_cycles = 0;
    const double FRAME_DURATION_MS = (70224.0 / 4194304.0) * 1000.0; // ~16.7427 ms, real DMG frame time, number of clock cycles in one frame: 70224, gameboy clock speed: 4,194,304 Hz, multiply by 1000 to convert seconds to milliseconds
    double next_frame_due = SDL_GetTicks();

    
    while (!done)
    {
        SDL_Event event;
    
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                done = true;
            }
            
            if (event.type == SDL_KEYDOWN && !event.key.repeat)
            {
                switch (event.key.keysym.sym)
                {
                    case SDLK_RIGHT:
                        jpad.buttonPress(Joypad::BTN_RIGHT);
                        break;

                    case SDLK_LEFT:
                        jpad.buttonPress(Joypad::BTN_LEFT);
                        break;

                    case SDLK_UP:
                        jpad.buttonPress(Joypad::BTN_UP);
                        break;

                    case SDLK_DOWN:
                        jpad.buttonPress(Joypad::BTN_DOWN);
                        break;

                    case SDLK_z:
                        jpad.buttonPress(Joypad::BTN_A);
                        break;

                    case SDLK_x:
                        jpad.buttonPress(Joypad::BTN_B);
                        break;

                    case SDLK_c:
                        jpad.buttonPress(Joypad::BTN_START);
                        break;

                    case SDLK_v:
                        jpad.buttonPress(Joypad::BTN_SELECT);
                        break;
                }
            }

            if (event.type == SDL_KEYUP)
            {
                switch (event.key.keysym.sym)
                {
                    case SDLK_RIGHT:
                        jpad.buttonRelease(Joypad::BTN_RIGHT);
                        break;

                    case SDLK_LEFT:
                        jpad.buttonRelease(Joypad::BTN_LEFT);
                        break;

                    case SDLK_UP:
                        jpad.buttonRelease(Joypad::BTN_UP);
                        break;

                    case SDLK_DOWN:
                        jpad.buttonRelease(Joypad::BTN_DOWN);
                        break;

                    case SDLK_z:
                        jpad.buttonRelease(Joypad::BTN_A);
                        break;

                    case SDLK_x:
                        jpad.buttonRelease(Joypad::BTN_B);
                        break;

                    case SDLK_c:
                        jpad.buttonRelease(Joypad::BTN_START);
                        break;

                    case SDLK_v:
                        jpad.buttonRelease(Joypad::BTN_SELECT);
                        break;
                    }
                }
        }

        uint32_t frame_cycles = 0;

        while (frame_cycles < 70224) {
            uint8_t cycles = cpu.getLastCycles();
            cpu.step();
            ppu.step(cycles);
            tmr.step(cycles);
            frame_cycles += cycles;
            
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

        next_frame_due += FRAME_DURATION_MS;
        double now = SDL_GetTicks();
        if (now < next_frame_due) {
            SDL_Delay(static_cast<Uint32>(next_frame_due - now));
        } else {
            next_frame_due = now; // fell behind (e.g. a slow frame) — resync instead of bursting to catch up
        }
       
    }
    mem.saveCartridge();
    SDL_DestroyTexture(texture);
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer); 
    SDL_Quit();

    return 0;
}