#pragma once
#include <stdint.h>
#include <string>
#include <array>

class CPU;

using Handler = void(*)(CPU&);

enum class addrmode{
    AM_R_D16,   // register <- 16-bit immediate value
    AM_R_R,     // register <- register
    AM_R,       // operation uses a single register
    AM_R_D8,    // register <- 8-bit immediate value
    AM_R_MR,    // register <- memory pointed to by register
    AM_R_HLI,   // register <- [HL], then increment HL
    AM_R_HLD,   // register <- [HL], then decrement HL
    AM_HLI_R,   // [HL] <- register, then increment HL 
    AM_HLD_R,   // [HL] <- register, then decrement HL
    AM_R_A8,    // register (A) <- memory[0xFF00 + immediate 8-bit offset]
    AM_A8_R,    // memory[0xFF00 + immediate 8-bit offset] <- register (A)
    AM_HL_SPR,  // HL <- SP + signed 8-bit immediate
    AM_D16,     // immediate 16-bit value from instruction stream
    AM_D8,      // immediate 8-bit value from instruction stream
    AM_IMP,     // no operands, instruction operates implicitly
    AM_MR_R,   // memory pointed to by register <- register
    AM_MR_D8,   // memory pointed to by register <- 8-bit immediate value
    AM_MR,      // memory pointed to by register 
    AM_A16_R,   // memory[16-bit address] <- register (A)
    AM_R_A16    // register (A) <- memory[16-bit address]
};

enum class reg_type{
    R_NONE,
    R_A,
    R_F,
    R_B,
    R_C,
    R_D,
    R_E,
    R_H,
    R_L,
    R_AF,
    R_BC,
    R_DE,
    R_HL,
    R_PC,
    R_SP
};

enum class operand_type {
    NONE,

    R8,     // A, B, C, D, E, H, L
    R16,    // BC, DE, HL, SP

    IMM8,   // d8
    IMM16,  // d16

    MEM_R,  // (HL), (BC), (DE)
    MEM_A16,// (a16)
    MEM_IO8,// (0xFF00 + a8)

    HL_INC, // (HL+)
    HL_DEC, // (HL-)

    SP_R8   // SP + r8 (special case)
};

enum class mnemonic{
    IN_NOP,
    IN_LD,
    IN_INC,
    IN_DEC,
    IN_RLCA,
    IN_ADD,
    IN_RRCA,
    IN_STOP,
    IN_RLA,
    IN_JR,
    IN_RRA,
    IN_DAA,
    IN_CPL,
    IN_SCF,
    IN_CCF,
    IN_HALT,
    IN_ADC,
    IN_SUB,
    IN_SBC,
    IN_AND,
    IN_XOR,
    IN_OR,
    IN_CP,
    IN_POP,
    IN_JP,
    IN_PUSH,
    IN_RET,
    IN_CB,
    IN_CALL,
    IN_RETI,
    IN_LDH,
    IN_JPHL,
    IN_DI,
    IN_EI,
    IN_RST,
    IN_ERR,
    IN_RLC, 
    IN_RRC,
    IN_RL, 
    IN_RR,
    IN_SLA, 
    IN_SRA,
    IN_SWAP, 
    IN_SRL,
    IN_BIT, 
    IN_RES, 
    IN_SET
};

enum class condition_code{
    CD_NONE,
    CD_NZ,
    CD_Z,
    CD_NC,
    CD_C
};

struct Instruction
{   
    
    // Human-readable name, examples: LD, ADD, SUB, JP, CALL, BIT, XOR, INC, DEC
    mnemonic instruction_type;

    // what kind of addressing is used based on source and destination of operation
    addrmode address_mode;

    // instead of having reg_type maybe use an operand_type instead because not every operand is a register
    operand_type operand_1;
    operand_type operand_2;

    // still have register types to know which register is being used if operand is a register
    reg_type reg_1;
    reg_type reg_2;

    // 4 bits in the F register modified based on instruction
    condition_code cond_code;
    
    // Instruction size in bytes
    uint8_t length;

    // CPU cycles
    uint8_t cycles;

}; 

void initInstructionTable(std::array<Instruction, 256>& table);
void initHandlerTable(std::array<Handler, 256>& table);
// use the mnemonic to execute the general functions with appropriate parameters such as handle_ld() with the operands as parameters
// used clock cycles instead of machine cycles, 1 machine cycles = 4 clock cycles

