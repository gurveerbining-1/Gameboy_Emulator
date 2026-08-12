#pragma once
#include <stdint.h>
#include <iostream>
#include <cstring>
#include "../bus/membus.h"
#include "../CPU/CPU.h"

struct Sprite
{
    uint8_t y;
    uint8_t x;
    uint8_t tile;
    uint8_t attributes;
    uint8_t oam_index;
};

class PPU{
    public:
        PPU(membus* bus);
        void step(uint8_t cycles); // advance PPU by however many cycles
        bool isFrameReady();
        void clearFrameReady();
        uint8_t* getFramebuffer();
        std::vector<Sprite> current_scanline_sprites;


    private:
        membus* bus;
        uint8_t current_mode;   // 0, 1, 2, or 3
        uint8_t LY;             // current scanline
        uint16_t cycle_counter; // cycles spent on current scanline
        uint8_t framebuffer[160 * 144]; // pixel output
        uint8_t LYC;
        uint8_t STAT;
        uint8_t WX; // window registers WX and WY specify coordinates of the windows top left pixel
        uint8_t WY;
        uint8_t window_line;
        
        bool frame_ready;
        
        void updateSTAT();
        bool stat_irq_line = false;
        void renderScanline();   // called when Mode 3 completes a line
        void OAMscan();            
        void requestInterrupt(uint8_t bit); // sets bit in IF
        void renderBackground(uint8_t* pixels, uint8_t* indices);
        void renderWindow(uint8_t* pixels, bool* active);
        void renderSprites(uint8_t* pixels, uint8_t* attrs, bool* exists);
        void compositeLayers(
            uint8_t* bg_pixels, uint8_t* bg_indices,
            uint8_t* win_pixels, bool* win_active,
            uint8_t* spr_pixels, uint8_t* spr_attrs, bool* spr_exists
        );
        
        // helpers used by multiple layers
        uint8_t getTilePixel(uint16_t tile_addr, uint8_t tile_x, uint8_t tile_y);
        uint8_t applyPalette(uint8_t palette_reg, uint8_t colour_index);


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