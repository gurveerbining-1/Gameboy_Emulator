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

    std::cout << "ROM size: " << rom_data.size() << "\n";

    for (int i = 0x100; i < 0x120; i++) {
        printf("ROM[%04X] = %02X\n", i, rom_data[i]);
    }

}

uint8_t Cartridge::read(uint16_t addr){
    if (addr >= rom_data.size()) {
        std::cerr << "ROM OOB READ: " << addr << std::endl;
        return 0xFF;
    }
    return rom_data[addr];

}