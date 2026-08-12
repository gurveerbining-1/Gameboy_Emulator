#include "PPU.h"

PPU::PPU(membus* bus) : bus(bus){
    cycle_counter = 0;
    current_mode = 2; // OAM scan by default
    LY = 0;
    memset(framebuffer, 0, sizeof(framebuffer)); 
    frame_ready = false;
    OAMscan();
    updateSTAT();
    stat_irq_line = false;
    window_line = 0;
}

void PPU::requestInterrupt(uint8_t bit){
    uint8_t interrupt_flags = bus->read(0xFF0F);
    interrupt_flags |= (1 << bit); // set bit 0 of the IF register
    bus->write(0xFF0F, interrupt_flags);
    //printf("Interrupt requested: bit %d, IF now %02X\n", bit, interrupt_flags);
}

void PPU::updateSTAT(){
    uint8_t stat = bus->read(0xFF41);   // read STAT register
    uint8_t enables = stat & 0x78;      // bits 3-6: interrupt-source enables, ROM-owned, basically ROM decides which STAT events it wants to receieve interrupts for

    uint8_t LYC_reg = bus->read(0xFF45);
    bool coincidence = (LY == LYC_reg); // Bit 2 of the LCD status register (STAT at 0xFF41). It becomes 1 when the current video scanline (LY at 0xFF44) matches the comparison value (LYC at 0xFF45), and 0 when they do not match

    stat = 0x80 | enables | (current_mode & 0x03);
    if(coincidence) stat |= 0x04; 

    bus->write(0xFF41, stat);

    bool line = (coincidence       && ((enables >> 6) & 1)) ||  // LYC=LY
                (current_mode == 0 && ((enables >> 3) & 1)) ||  // HBlank
                (current_mode == 1 && ((enables >> 4) & 1)) ||  // VBlank
                (current_mode == 2 && ((enables >> 5) & 1));    // OAM

    if(line && !stat_irq_line){
        requestInterrupt(INT_STAT);
    }
    stat_irq_line = line; // edge-triggered, so this won't refire every call while held true
}

void PPU::OAMscan(){
    current_scanline_sprites.clear();
    
    uint8_t LCDC = bus->read(0xFF40);

    // Sprite height: 8 or 16 pixels
    uint8_t sprite_height = (LCDC & 0x04) ? 16 : 8;

    // Check all 40 sprites in OAM
    for (int i = 0; i < 40; i++)
    {
        uint16_t addr = 0xFE00 + (i * 4);

        uint8_t y = bus->read(addr);
        uint8_t x = bus->read(addr + 1);
        uint8_t tile = bus->read(addr + 2);
        uint8_t attributes = bus->read(addr + 3);

        // OAM Y position is screen Y + 16
        int sprite_top = static_cast<int>(y) - 16;
        int sprite_bottom = sprite_top + sprite_height;

        // Is this sprite visible on the current scanline?
        if (LY >= sprite_top && LY < sprite_bottom)
        {
            Sprite sprite;
            sprite.y = y;
            sprite.x = x;
            sprite.tile = tile;
            sprite.attributes = attributes;
            sprite.oam_index = i;

            current_scanline_sprites.push_back(sprite);

            // Game Boy limit: max 10 sprites per scanline
            if (current_scanline_sprites.size() == 10)
                break;
        }
    }
}

void PPU::renderScanline(){
    uint8_t LCDC = bus->read(0xFF40);

    if(!(LCDC & 0x80)){
        cycle_counter = 0;
        LY = 0;
        current_mode = 0;
        bus->write(0xFF44, 0);
        return;
    }

    uint8_t bg_pixels[160] = {};       // final shaded color 0-3
    uint8_t bg_indices[160] = {};      // raw color index 0-3 BEFORE palette (needed for priority)
    bool    window_pixels[160] = {};   // whether window covers this pixel
    uint8_t win_pixels[160] = {};      // window shade
    uint8_t sprite_pixels[160] = {};   // sprite shade (0 = no sprite / transparent)
    uint8_t sprite_attrs[160] = {};    // sprite attribute byte (for priority flags)
    bool    sprite_exists[160] = {};   // did any sprite cover this pixel    

    renderBackground(bg_pixels, bg_indices);

    renderWindow(win_pixels, window_pixels);


    renderSprites(sprite_pixels, sprite_attrs, sprite_exists);

    
    compositeLayers(bg_pixels, bg_indices,
                    win_pixels, window_pixels,
                    sprite_pixels, sprite_attrs, sprite_exists);

}

void PPU::clearFrameReady(){
    frame_ready = false;
}


bool PPU::isFrameReady(){
    return frame_ready;
}

uint8_t* PPU::getFramebuffer(){
    return framebuffer;
}

void PPU::step(uint8_t cycles){
    cycle_counter += cycles;

    if(current_mode == 2 && cycle_counter >= 80){
        // switch to mode 3
        current_mode = 3;
        cycle_counter -= 80;
        updateSTAT();
    }

    if(current_mode == 3 && cycle_counter >= 172){
        current_mode = 0;
        cycle_counter -= 172;
        renderScanline();
        updateSTAT();    
    }
    
    if(current_mode == 0 && cycle_counter >= 204){
        cycle_counter -= 204;
        LY++;
        bus->write(0xFF44, LY);

        if(LY == 144){
            // switch to mode 1
            current_mode = 1;
            // request VBLANK interrupt
            requestInterrupt(INT_VBLANK);
            //window_line = 0;
        }
        else{
            // switch to mode 2
            current_mode = 2;
            OAMscan();
        }
        updateSTAT();
    }

    if(current_mode == 1 && cycle_counter >= 456){
        cycle_counter = 0;
        LY++;
        bus->write(0xFF44, LY);
                
        if(LY == 154){
            LY = 0;
            window_line = 0;
            //switch to mode 2
            OAMscan();
            current_mode = 2;
            //present framebuffer to screen
            frame_ready = true;
        }
        updateSTAT();
    }
}

uint8_t PPU::getTilePixel(uint16_t tile_addr, uint8_t tile_x, uint8_t tile_y){
    // Each row is 2 bytes
    uint16_t row_addr = tile_addr + (tile_y * 2);

    uint8_t low  = bus->read(row_addr);
    uint8_t high = bus->read(row_addr + 1);

    // Leftmost pixel is bit 7
    uint8_t bit = 7 - tile_x;

    uint8_t low_bit  = (low  >> bit) & 1;
    uint8_t high_bit = (high >> bit) & 1;

    return (high_bit << 1) | low_bit;
}

uint8_t PPU::applyPalette(uint8_t palette_reg, uint8_t colour_index){
    return (palette_reg >> (colour_index * 2)) & 0x03;
}

void PPU::renderBackground(uint8_t* pixels, uint8_t* indices){
    uint8_t LCDC = bus->read(0xFF40);
    uint8_t SCX  = bus->read(0xFF43);
    uint8_t SCY  = bus->read(0xFF42);
    uint8_t BGP  = bus->read(0xFF47);

    bool bg_enabled = LCDC & 0x01;

    for (uint8_t x = 0; x < 160; x++)
    {
        uint8_t bg_colour_index = 0;

        if (bg_enabled)
        {
            // Screen pixel -> position in the 256x256 BG map
            uint8_t map_x = (x + SCX) % 256;
            uint8_t map_y = (LY + SCY) % 256;

            // Which tile in the 32x32 tile map?
            uint8_t tile_col = map_x / 8;
            uint8_t tile_row = map_y / 8;

            // Select BG tile map
            uint16_t tile_map_base =
                (LCDC & 0x08) ? 0x9C00 : 0x9800;

            uint16_t tile_map_addr =
                tile_map_base + (tile_row * 32) + tile_col;

            uint8_t tile_index = bus->read(tile_map_addr);

            // Find tile's data
            uint16_t tile_data_addr;

            if (LCDC & 0x10)
            {
                // $8000 addressing: unsigned tile index
                tile_data_addr = 0x8000 + (tile_index * 16);
            }
            else
            {
                // $8800 addressing: signed tile index
                int8_t signed_index = static_cast<int8_t>(tile_index);
                tile_data_addr = 0x9000 + (signed_index * 16);
            }

            // Position inside the 8x8 tile
            uint8_t tile_x = map_x % 8;
            uint8_t tile_y = map_y % 8;

            // Get raw 2-bit color index
            bg_colour_index = getTilePixel(
                tile_data_addr,
                tile_x,
                tile_y
            );
        }

        // IMPORTANT:
        // Keep the raw index for sprite priority.
        indices[x] = bg_colour_index;

        // Convert raw index through BGP for display.
        pixels[x] = applyPalette(BGP, bg_colour_index);
    }
}

void PPU::renderWindow(uint8_t* pixels, bool* active){
    uint8_t LCDC = bus->read(0xFF40);
    uint8_t BGP  = bus->read(0xFF47);
    uint8_t WX   = bus->read(0xFF4B);
    uint8_t WY   = bus->read(0xFF4A);

    // Window disabled
    if (!(LCDC & 0x20)) // 5th bit of LCDC determines if window is enabled or not
        return;

    for (int x = 0; x < 160; x++) {
        active[x] = false;
    }


    bool window_drawn = false;

    for (uint8_t x = 0; x < 160; x++)
    {
        // Window is only active once LY reaches WY
        // and x reaches WX - 7.
        if (LY < WY || x < (int)WX - 7)
            continue;

        // Window coordinates start at (0, 0) when
        // the window begins drawing.
        uint8_t window_x = x - ((int)WX - 7);
        uint8_t window_y = window_line;

        // Window tile map:
        // LCDC bit 6 = 0 -> $9800
        // LCDC bit 6 = 1 -> $9C00
        uint16_t tile_map_base =
            (LCDC & 0x40) ? 0x9C00 : 0x9800;

        // Find tile in the 32x32 tile map
        uint8_t tile_col = window_x / 8;
        uint8_t tile_row = window_y / 8;

        uint16_t tile_map_addr =
            tile_map_base + (tile_row * 32) + tile_col;

        uint8_t tile_index = bus->read(tile_map_addr);

        // Select tile data addressing mode.
        uint16_t tile_data_addr;

        if (LCDC & 0x10)
        {
            // $8000 addressing: unsigned tile index
            tile_data_addr = 0x8000 + (tile_index * 16);
        }
        else
        {
            // $8800 addressing: signed tile index
            int8_t signed_index =
                static_cast<int8_t>(tile_index);

            tile_data_addr =
                0x9000 + (signed_index * 16);
        }

        // Pixel inside the 8x8 tile
        uint8_t tile_x = window_x % 8;
        uint8_t tile_y = window_y % 8;

        uint8_t colour_index =
            getTilePixel(tile_data_addr, tile_x, tile_y);

        // Apply BGP palette
        pixels[x] = applyPalette(BGP, colour_index);

        // Tell compositor that this pixel belongs to window
        active[x] = true;

        window_drawn = true;
    }

    // Only advance window_line if the window actually appeared
    // on this scanline.
    if (window_drawn)
        window_line++;
}


void PPU::renderSprites(uint8_t* pixels, uint8_t* attrs, bool* exists){
    uint8_t LCDC = bus->read(0xFF40);

    // Sprites disabled
    if (!(LCDC & 0x02))
        return;

    uint8_t OBP0 = bus->read(0xFF48);
    uint8_t OBP1 = bus->read(0xFF49);

    uint8_t sprite_height = (LCDC & 0x04) ? 16 : 8;

    // Keep track of which sprite currently wins at each x.
    int best_x[160];

    for (int x = 0; x < 160; x++) {
        exists[x] = false;
        best_x[x] = 999;
    }

    for (const Sprite& s : current_scanline_sprites)
    {
        int sprite_left = (int)s.x - 8;

        // Row within this sprite for the current scanline
        int row = static_cast<int>(LY) - (static_cast<int>(s.y) - 16);

        // Y flip
        if (s.attributes & 0x40)
            row = (sprite_height - 1) - row;

        // For 8x16 sprites, the bottom bit of the tile number is ignored
        uint8_t tile = s.tile;

        if (sprite_height == 16)
            tile &= 0xFE;

        uint16_t tile_addr = 0x8000 + (tile * 16);

        uint8_t low  = bus->read(tile_addr + row * 2);
        uint8_t high = bus->read(tile_addr + row * 2 + 1);

        for (int col = 0; col < 8; col++)
        {
            int x = sprite_left + col;

            // Sprite is outside the screen
            if (x < 0 || x >= 160)
                continue;

            int pixel_col = col;

            // X flip
            if (s.attributes & 0x20)
                pixel_col = 7 - pixel_col;

            // Game Boy tile pixels are stored MSB first
            int bit = 7 - pixel_col;

            uint8_t low_bit  = (low  >> bit) & 1;
            uint8_t high_bit = (high >> bit) & 1;

            uint8_t color_index = (high_bit << 1) | low_bit;

            // Color 0 is transparent
            if (color_index == 0)
                continue;

            /*
             * Sprite priority:
             
                1. Smaller X wins
                2. If X is equal, lower OAM index wins

                current_scanline_sprites is in OAM order, so if
                we only replace when the new X is strictly smaller,
                the first sprite automatically wins equal-X ties.
             */
            if (!exists[x] ||
                sprite_left < best_x[x])
            {
                exists[x] = true;
                best_x[x] = sprite_left;

                // Save attributes for the compositor
                attrs[x] = s.attributes;

                // Select OBP0 or OBP1
                uint8_t palette =
                    (s.attributes & 0x10) ? OBP1 : OBP0;

                // Convert raw color index to shade
                pixels[x] =
                    (palette >> (color_index * 2)) & 0x03;
            }
        }
    }
}

void PPU::compositeLayers(  uint8_t* bg_pixels, uint8_t* bg_indices,
                            uint8_t* win_pixels, bool* win_active,
                            uint8_t* spr_pixels, uint8_t* spr_attrs, bool* spr_exists){
    
    uint8_t final_write_to_buffer = 0;
    uint8_t bg_index = 0;
    bool behind;
    for(int x = 0; x < 160; x++){
        final_write_to_buffer = bg_pixels[x]; // start with background

        if(win_active[x]){
            final_write_to_buffer = win_pixels[x]; // window overrides background
            bg_index = win_active[x]; // window index used for sprite priority too
        }
        else{
            bg_index = bg_indices[x];
        }

        if(spr_exists[x]){
            behind = (spr_attrs[x] & 0x80) && (bg_index != 0);
            if(!behind){
                final_write_to_buffer = spr_pixels[x]; // sprite wins
            }
        }

        framebuffer[LY * 160 + x] = final_write_to_buffer;
    }    
}

