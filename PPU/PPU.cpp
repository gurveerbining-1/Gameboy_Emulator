#include "PPU.h"

PPU::PPU(membus* bus) : bus(bus){
    cycle_counter = 0;
    current_mode = 2; // OAM scan by default
    LY = 0;
    memset(framebuffer, 0, sizeof(framebuffer)); 
    frame_ready = false;
}

void PPU::requestInterrupt(uint8_t bit){
    uint8_t interrupt_flags = bus->read(0xFF0F);
    interrupt_flags |= bit; // set bit 0 of the IF register
    bus->write(0xFF0F, interrupt_flags);
    //printf("Interrupt requested: bit %d, IF now %02X\n", bit, interrupt_flags);
}

void PPU::renderScanline(){
/*
Each tile row is 2 bytes. The two bytes together give you 8 pixels — bit 7 of byte 1 and bit 7 of byte 2 
together form the 2-bit color index for pixel 0, bit 6 of each byte for pixel 1, and so on.

So for pixel x within a tile row:

bit_index = 7 - (x % 8)
low_bit = (byte1 >> bit_index) & 1
high_bit = (byte2 >> bit_index) & 1
color_index = (high_bit << 1) | low_bit

Then apply BGP: BGP is a byte where bits 1-0 = color for index 0, 
bits 3-2 = color for index 1, bits 5-4 = color for index 2, bits 7-6 = color for index 3.
*/
    uint8_t LCDC = bus->read(0xFF40);
    
    if(!(LCDC & 0x80)){
        // LCD disabled - reset PPU state
        cycle_counter = 0;
        LY = 0;
        current_mode = 0;
        bus->write(0xFF44, 0);
        return;
    }

    uint8_t SCX = bus->read(0xFF43);
    uint8_t SCY = bus->read(0xFF42);
    uint8_t BGP = bus->read(0xFF47);
    /*
    if(LY == 0){
        printf("LCDC=%02X SCX=%02X SCY=%02X BGP=%02X\n", LCDC, SCX, SCY, BGP);
        
        // sample a few tile map entries
        printf("TileMap[0]=%02X [1]=%02X [2]=%02X\n",
            bus->read(0x9800), bus->read(0x9801), bus->read(0x9802));
        
        // sample tile 0 data
        printf("Tile0: %02X %02X %02X %02X\n",
            bus->read(0x8000), bus->read(0x8001),
            bus->read(0x8002), bus->read(0x8003));
    }
    */

    for (uint8_t x = 0; x < 160; x++)
    {   

        // The background is a 256×256 pixel space. The screen is a 160×144 window into it. SCX and SCY control where that window starts
        uint8_t map_x = (x + SCX) % 256;  // wraps around
        uint8_t map_y = (LY + SCY) % 256;
        
        // The map is 32×32 tiles (32 × 8 = 256 pixels). Dividing by 8 gives tile coordinates
        uint8_t tile_col = map_x / 8;
        uint8_t tile_row = map_y / 8;

        //Look up the tile index in the tile map the tile map starts at 0x9800 (assuming LCDC bit 3 = 0 for now)
        uint16_t tile_map_base = (LCDC & 0x08) ? 0x9C00 : 0x9800;
        uint16_t tile_map_addr = tile_map_base + (tile_row * 32) + tile_col;
        uint8_t tile_index = bus->read(tile_map_addr);

        // Find where that tile's data is, tile data starts at 0x8000. Each tile is 16 bytes (2 bytes × 8 rows)
        uint16_t tile_data_addr;
        if(LCDC & 0x10){
            // bit 4 = 1: unsigned indexing from 0x8000
            tile_data_addr = 0x8000 + (tile_index * 16);
        } else {
            // bit 4 = 0: signed indexing from 0x9000
            int8_t signed_index = static_cast<int8_t>(tile_index);
            tile_data_addr = 0x9000 + (signed_index * 16);
        }
        // Which row and column within the tile?
        uint8_t tile_pixel_x = map_x % 8;  // 0-7, column within tile
        uint8_t tile_pixel_y = map_y % 8;  // 0-7, row within tile

        // Read the two bytes for this tile row each row is 2 bytes. The row offset is tile_pixel_y * 2
        uint8_t byte1 = bus->read(tile_data_addr + tile_pixel_y * 2);
        uint8_t byte2 = bus->read(tile_data_addr + tile_pixel_y * 2 + 1);

        // Extract the 2-bit color index for this pixel, Bit 7 = leftmost pixel, bit 0 = rightmost
        uint8_t bit_index = 7 - tile_pixel_x;
        uint8_t low_bit  = (byte1 >> bit_index) & 1;
        uint8_t high_bit = (byte2 >> bit_index) & 1;
        uint8_t color_index = (high_bit << 1) | low_bit;  // 0-3

        // Apply the palette BGP maps each color index to a shade. Bits 1-0 = shade for index 0, bits 3-2 = shade for index 1, etc
        uint8_t shade = (BGP >> (color_index * 2)) & 0x03;

        framebuffer[LY * 160 + x] = shade; 
    }

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
    }

    if(current_mode == 3 && cycle_counter >= 172){
        current_mode = 0;
        cycle_counter -= 172;
        renderScanline();
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
        }
        else{
            // switch to mode 2
            current_mode = 2;
        }
    }

    if(current_mode == 1 && cycle_counter >= 456){
        cycle_counter = 0;
        LY++;
        bus->write(0xFF44, LY);
                
        if(LY == 154){
            LY = 0;
            //switch to mode 2
            current_mode = 2;
            //present framebuffer to screen
            frame_ready = true;
        }
    }
}