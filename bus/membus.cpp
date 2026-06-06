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

    if (addr <= 0x7FFF) {
        value = cartridge.read(addr);
    } else {
        value = memory[addr];
    }

    printf("READ %04X -> %02X\n", addr, value);

    return value;

}
void membus::write(uint16_t addr, uint8_t value){
    memory[addr] = value;
}
