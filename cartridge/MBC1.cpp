#include "MBC1.h"

MBC1::MBC1() : ram_data(4 * 8192), ram_enabled(false), rom_bank(1), upper_bits(0), banking_mode(0), current_ram_bank(0){
    // initialize ram_data, allocate 32kb space for now, ram size is in the header at 0x0149
}

void MBC1::load(const std::string& path){
    Cartridge::load(path);  // call base first, populates rom_data, sets sav_path
    
    // NOW rom_data is populated, safe to read header
    uint8_t ram_size_code = rom_data[0x0149];
    size_t ram_size = 0;
    switch(ram_size_code){
        case 0x00: ram_size = 0;       break;
        case 0x01: ram_size = 2048;    break;
        case 0x02: ram_size = 8192;    break;
        case 0x03: ram_size = 32768;   break;
        case 0x04: ram_size = 131072;  break;
    }
    ram_data.resize(ram_size, 0xFF);
    
    // load save file if it exists
    std::ifstream sav(sav_path, std::ios::binary);
    if(sav && !ram_data.empty()){
        sav.read(reinterpret_cast<char*>(ram_data.data()), ram_data.size());
    }

}

void MBC1::save(){
    if(ram_data.empty()) return;
    std::ofstream sav(sav_path, std::ios::binary);
    sav.write(reinterpret_cast<char*>(ram_data.data()), ram_data.size());
}

uint8_t MBC1::read(uint16_t addr){
    if(addr <= 0x3FFF){
        /*
        Always bank 0. But in RAM banking mode (mode 1), the upper_bits actually affect which physical bank appears here too
        this is a MBC1 quirk. For simplicity implement mode 0 first.
        */
        if(banking_mode == 0 ){
            return rom_data[addr]; // bank 0 always fixed
        }
        
        uint32_t offset = (upper_bits << 5) * 0x4000 + addr;
        if(offset >= rom_data.size()) return 0xFF;
        return rom_data[offset];
        
    }
    else if(addr <= 0x7FFF){
        /*
        The switchable bank. Compute the effective bank number from rom_bank and upper_bits, offset into rom_data
        */
        return rom_data[(((upper_bits << 5) | rom_bank) * 0x4000) + (addr - 0x4000)];
    }
    else if(addr >= 0xA000 && addr <= 0xBFFF){
        /*
        External RAM. Only valid when ram_enabled is true.
        Mode 0: RAM bank 0.
        Mode 1: upper_bits selects RAM bank 0-3.
        */
        if (!ram_enabled)
            return 0xFF;
        
        if(banking_mode == 0){
            return ram_data[addr - 0xA000];
        }
        
        size_t index = (upper_bits * 0x2000) + (addr - 0xA000);
        return ram_data[index];
    }

    return 0xFF;
}

void MBC1::writeRegister(uint16_t addr, uint8_t value){
    if(addr <= 0x1FFF){
        /*
        RAM enable/disable. If the lower 4 bits of the written value equal 0x0A, RAM is enabled. 
        Any other value disables it. The game does this before reading/writing save data.        
        */
        if((value & 0x0F) == 0x0A){
            ram_enabled = true;
        }
        else{
            ram_enabled = false;
        }

    }
    else if(addr <= 0x3FFF){
        /*
        Select which ROM bank appears in the 0x4000-0x7FFF window. Only the lower 5 bits matter. 
        If the result is 0, treat it as 1 (bank 0 can never appear in the upper window).
        */
        rom_bank = value & 0x1F;
        if (rom_bank == 0){
            rom_bank = 1;
        }
    }
    else if(addr <= 0x5FFF){
        /*
        The 2-bit upper_bits register. In ROM banking mode these become bits 5-6 of the ROM bank number, 
        extending it to 7 bits total. In RAM banking mode they select which 8KB RAM bank is visible.
        */
        upper_bits = (value & 0x03);
    }
    else if(addr <= 0x7FFF){
        /*
        Mode select. Bit 0 of the value sets banking_mode. 0 = ROM banking mode, 1 = RAM banking mode.
        */
        banking_mode = (value & 1);
    }
    else if(addr >= 0xA000 && addr <= 0xBFFF){
        /*
        External RAM. Only valid when ram_enabled is true. Bank selected by current_ram_bank (which is set by upper_bits in RAM banking mode)
        */
        if(!ram_enabled){
            return;
        }

        if(banking_mode == 0){
            ram_data[addr - 0xA000] = value;
        }
        else{ // mode 1
            ram_data[(upper_bits * 0x2000) + (addr - 0xA000)] = value;
        }
    }
}

