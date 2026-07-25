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
    
  //  for (int i = 0x100; i < 0x120; i++) {
  //      printf("ROM[%04X] = %02X\n", i, rom_data[i]);
  //  }

}

void Cartridge::parseHeader(){
    cartridge_type = rom_data[0x147];
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
    if (addr >= rom_data.size()) {
        std::cerr << "ROM OOB READ: " << addr << std::endl;
        return 0xFF;
    }
    return rom_data[addr];

}