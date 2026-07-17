#include "membus.h"
#include "../cartridge/Cartridge.h"

void membus::loadCartridge(const std::string& path){
    cartridge.load(path);
    
}   

uint8_t membus::read(uint16_t addr){
    /*
     if addr is 0x0000–0x7FFF, delegate to cartridge.read(addr). Otherwise fall through to flat memory array for RAM regions.
    */
    uint8_t value;

    if(testMode){
        return memory[addr];
    }

    if(addr <= 0x7FFF) {
        value = cartridge.read(addr);
    } else {
        value = memory[addr];
    }

    printf("READ %04X -> %02X\n", addr, value);

    return value;

}
void membus::write(uint16_t addr, uint8_t value){
    memory[addr] = value;

/*
    Many of Blargg's tests print their results through the Game Boy's serial port instead of the screen. 
    Specifically, they write to:

    SB (0xFF01) - Serial transfer data
    SC (0xFF02) - Serial control*/

    if (addr == 0xFF02 && value == 0x81){
        std::cout << (char)memory[0xFF01];
    }
}

// Use this to write and test each opcode to test things as instructions are implemented
void membus::loadTestProgram(const std::vector<uint8_t>& program){
    std::copy(program.begin(), program.end(), &memory[0x100]);
}
