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

    if (addr == 0xFF44) return 0x90;
    
    if(testMode){
        return memory[addr];
    }

    if(addr <= 0x7FFF) {
        value = cartridge.read(addr);
    } else {
        value = memory[addr];
    }

    //printf("READ %04X -> %02X\n", addr, value);

    return value;

}
void membus::write(uint16_t addr, uint8_t value){
    if(addr == 0xFF01 || addr == 0xFF02){
        std::cout << "SERIAL WRITE addr: 0x"
                  << std::hex << addr
                  << " value: 0x"
                  << (int)value
                  << std::endl;
    }

    memory[addr] = value;

    if(addr == 0xFF02 && (value & 0x80)){
        std::cout << "OUTPUT: "
                  << static_cast<char>(memory[0xFF01])
                  << std::flush;
    }

}

// Use this to write and test each opcode to test things as instructions are implemented
void membus::loadTestProgram(const std::vector<uint8_t>& program){
    testMode = true;
    std::copy(program.begin(), program.end(), &memory[0x100]);
}
