#include "Cartridge.h"

/*
Cartridge::Cartridge(){
    // read ROM files from /ROMS into memory
    // parse the header after loading
    // MBC logic 
    
}
*/

void Cartridge::load(const std::string &path){
    // use std::ifstream() to read ROM path and read bytes into rom_data vector
    std::ifstream file(path, std::ios::binary);
    
    if (!file) {
        throw std::runtime_error("Failed to open ROM: " + path);
    }

    file.seekg(0, std::ios::end);
    const auto size = static_cast<std::size_t>(file.tellg());
    file.seekg(0, std::ios::beg);

    rom_data.resize(size);
    file.read(reinterpret_cast<char*>(rom_data.data()), size);
    
    parseHeader();

    std::cout << "ROM size: " << rom_data.size() << "\n";
    
}

void Cartridge::parseHeader(){
    cartridge_type = rom_data[0x147];
    //printf("Cartridge type: 0x%02X\n", cartridge_type);
    switch (cartridge_type)
    {
        case 0x00:
            std::cout << "ROM ONLY\n";
            break;

        case 0x01:
        case 0x02:
        case 0x03:
            std::cout << "MBC1\n";
            break;

        case 0x05:
        case 0x06:
            std::cout << "MBC2\n";
            break;

        case 0x0F:
        case 0x10:
        case 0x11:
        case 0x12:
        case 0x13:
            std::cout << "MBC3\n";
            break;

        case 0x19:
        case 0x1A:
        case 0x1B:
        case 0x1C:
        case 0x1D:
        case 0x1E:
            std::cout << "MBC5\n";
            break;

        default:
            std::cerr << "Unsupported cartridge type: 0x"
                      << std::hex
                      << static_cast<int>(cartridge_type)
                      << std::endl;
            break;
    }

}

uint8_t Cartridge::read(uint16_t addr){
    if(addr <= 0x3FFF){
        return rom_data[addr]; // bank 0 always fixed
    }
    else if(addr <= 0x7FFF){
        // switchable bank
        uint32_t offset = current_rom_bank * 0x4000 + (addr - 0x4000);
        if(offset < rom_data.size()) return rom_data[offset];
        return 0xFF;
    }
    return 0xFF;
}

void Cartridge::writeRegister(uint16_t addr, uint8_t value){
    if(addr >= 0x2000 && addr <= 0x3FFF){
        current_rom_bank = value & 0x1F;
        if(current_rom_bank == 0) current_rom_bank = 1;
        printf("MBC1: switched to bank %d\n", current_rom_bank);
    }
}