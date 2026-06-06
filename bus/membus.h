/*
Each operation cycle will:

Fetch the next opcode.
Decode the fetched opcode.
Fetch any extra data required to resolve the operation including extra opcodes and literals.
Record all m-cycles consumed in the operation so that we can block later to adjust our timings.
Execute the opcode.

the fetch is gotten from the memory bus and the memory bus connects what is read from the cartride to the cpu and the 
cpu decodes the bytes and performs instructions based on opcode instruction table

CPU ↔ Memory Bus ↔ Cartridge / RAM / VRAM / IO


Address Range       Hardware
-------------       --------
0000-7FFF           Cartridge ROM
8000-9FFF           VRAM chip
A000-BFFF           Cartridge RAM
C000-DFFF           Work RAM
FF00-FF7F           IO registers

*/
#pragma once
#include <cstdint>
#include <string>
#include "../cartridge/Cartridge.h"

class membus{
    public:
        uint8_t read(uint16_t addr);
        void write(uint16_t addr, uint8_t value);
        void loadCartridge(const std::string& path);

    private:
        Cartridge cartridge;
        uint8_t memory[65536]; 

        bool bootROM(); 
};