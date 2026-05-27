#pragma once
#include <stdint.h>
#include <iostream>
#include "Instructions.H"
#include "membus.h"

/*   condition code (2 bits inside the opcode) selects whether a conditional branch is taken, 
*    based on CPU flags, nz (not zero), z (zero), nc (no carry), c (carry)
*/

struct registers{
    // 8-bit registers A F B C D E H L
    // can be combined to create 16-bit registers AF BC DE HL
    uint8_t A;
    uint8_t F;
    uint8_t B;
    uint8_t C;
    uint8_t D;
    uint8_t E;
    uint8_t H;
    uint8_t L;

    // 16-bit register helper functions (add two 8 bit registers)
    uint16_t af() const{
        return (A << 8) | F;
    };

    uint16_t bc() const{
        return (B << 8) | C;
    };

    uint16_t de() const{
        return (D << 8) | E;
    };

    uint16_t hl() const{
        return (H << 8) | L;
    };

    // Program Counter and Stack Pointer
    uint16_t PC;
    uint16_t SP;
};

/*
u16int_t V-Blank = 0x40
u16int_t STAT = 0x48
u16int_t Timer = 0x50
u16int_t Serial = 0x58
u16int_t Joypad = 0x60

bit 0 = VBlank requested
bit 1 = STAT requested
bit 2 = Timer requested
bit 3 = Serial requested
bit 4 = Joypad requested
*/
enum Interrupt : uint8_t {
    INT_VBLANK = 0,
    INT_STAT   = 1,
    INT_TIMER  = 2,
    INT_SERIAL = 3,
    INT_JOYPAD = 4
};

constexpr std::array<uint16_t, 5> interrupt_vectors = {
    0x40,
    0x48,
    0x50,
    0x58,
    0x60
};

class CPU{
    public:
        CPU();
        CPU(membus* b);
        void reset(); // set initial values 
        void step(); // fetch opcode, decode it, then execute instruction and advance cycles
        uint8_t fetch();
        uint16_t fetch16(); // reads two bytes, advances PC twice, assembles little-endian
        void execute_opcode(uint8_t opcode);
        uint8_t update_cycles(uint8_t cycles);
        void setReg16(reg_type, uint16_t);
        uint16_t getReg16(reg_type);
        void setReg8(reg_type, uint8_t);
        uint8_t getReg8(reg_type);

    private:
        void handle_interrupts(); 
        registers reg;
        membus* bus;
        std::array<Instruction, 256> instruction_table;
        std::array<Handler, 256> handler_table;
};