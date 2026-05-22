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
*/

#include <cstdint>
class membus{
    public:
        uint8_t read(uint16_t addr);
        void write(uint16_t addr, uint8_t value);
    private:
        //Cartridge cartridge;
        uint8_t memory[65536]; //opcodes

        bool bootROM(); 
};