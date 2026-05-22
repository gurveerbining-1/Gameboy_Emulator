#include "membus.h"

uint8_t membus::read(uint16_t addr){
    //cartrige->read(addr)
    return memory[addr];
}
void membus::write(uint16_t addr, uint8_t value){
    
}