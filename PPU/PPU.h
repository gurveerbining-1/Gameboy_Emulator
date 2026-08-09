#pragma once
#include <stdint.h>
#include <iostream>
#include <cstring>
#include "../bus/membus.h"
#include "../CPU/CPU.h"

class PPU{
    public:
        PPU(membus* bus);
        void step(uint8_t cycles); // advance PPU by however many cycles
        bool isFrameReady();
        void clearFrameReady();
        uint8_t* getFramebuffer();

    private:
        membus* bus;
        uint8_t current_mode;   // 0, 1, 2, or 3
        uint8_t LY;             // current scanline
        uint16_t cycle_counter; // cycles spent on current scanline
        
        uint8_t framebuffer[160 * 144]; // pixel output
        
        bool frame_ready;
        
        void renderScanline();   // called when Mode 3 completes a line
        void requestInterrupt(uint8_t bit); // sets bit in IF

};

/*
0xFF40 — LCDC (LCD Control): master enable, background enable, sprite enable, tile data addressing mode
0xFF41 — STAT (LCD Status): current mode, interrupt enables for PPU events
0xFF42 — SCY (scroll Y)
0xFF43 — SCX (scroll X)
0xFF44 — LY (current scanline being drawn, 0-153)
0xFF45 — LYC (LY compare, triggers STAT interrupt when LY == LYC)
0xFF47 — BGP (background palette)
0xFF48 — OBP0 (sprite palette 0)
0xFF49 — OBP1 (sprite palette 1)
0x8000–0x9FFF — VRAM (tile data and tile maps)
0xFE00–0xFE9F — OAM (sprite attribute table)

The PPU draws the screen line by line, 144 lines per frame, at 60fps. It doesn't draw the whole screen at once 
it works through a state machine that cycles through four modes for each scanline:

Mode 2 — OAM Scan (80 cycles): finds which sprites appear on this line
Mode 3 — Drawing (172 cycles): actually outputs pixels for this line
Mode 0 — HBlank (204 cycles): rest period after each line
Mode 1 — VBlank (4560 cycles total): 10 "lines" of rest after line 143
*/