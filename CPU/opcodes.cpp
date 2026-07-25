#include "Instructions.h"
#include "CPU.h"
#include <bitset>

Instruction invalidInstruction = {
    mnemonic::IN_INVALID,
    addrmode::AM_IMP,
    operand_type::NONE,
    operand_type::NONE,
    reg_type::R_NONE,
    reg_type::R_NONE,
    condition_code::CD_NONE,
    1,
    0
};

void initInstructionTable(std::array<Instruction, 256>& table){
    table.fill(invalidInstruction);
    table[0x00] = {
        mnemonic::IN_NOP,
        addrmode::AM_IMP,
        operand_type::NONE,
        operand_type::NONE,
        reg_type::R_NONE,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        1,
        4
    };

    table[0x01] = {
        mnemonic::IN_LD,
        addrmode::AM_R_D16,
        operand_type::R16,
        operand_type::IMM16,
        reg_type::R_BC,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        3,
        12
    };
    
    table[0x02] = {
        mnemonic::IN_LD,
        addrmode::AM_MR_R,
        operand_type::MEM_R,
        operand_type::R8,
        reg_type::R_BC,
        reg_type::R_A,
        condition_code::CD_NONE,
        1,
        8
    };

    table[0x03] = {
        mnemonic::IN_INC,
        addrmode::AM_R,
        operand_type::R16,
        operand_type::NONE,
        reg_type::R_BC,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        1,
        8
    };

    table[0x04] = {
        mnemonic::IN_INC,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_B,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        1,
        4
    };

    table[0x05] = {
        mnemonic::IN_DEC,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_B,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        1,
        4
    };

    table[0x06] = {
        mnemonic::IN_LD,
        addrmode::AM_R_D8,
        operand_type::R8,
        operand_type::IMM8,
        reg_type::R_B,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x07] = {
        mnemonic::IN_RLCA,
        addrmode::AM_IMP,
        operand_type::NONE,
        operand_type::NONE,
        reg_type::R_NONE,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        1,
        4
    };

    table[0x08] = {
        mnemonic::IN_LD,
        addrmode::AM_A16_R,
        operand_type::MEM_A16,
        operand_type::R16,
        reg_type::R_NONE,
        reg_type::R_SP,
        condition_code::CD_NONE,
        3,
        20
    };

    table[0x09] = {
        mnemonic::IN_ADD,
        addrmode::AM_R_R,
        operand_type::R16,
        operand_type::R16,
        reg_type::R_HL,
        reg_type::R_BC,
        condition_code::CD_NONE,
        1,
        8
    };

    table[0x0A] = {
        mnemonic::IN_LD,
        addrmode::AM_R_MR,
        operand_type::R8,
        operand_type::MEM_R,
        reg_type::R_A,
        reg_type::R_BC,
        condition_code::CD_NONE,
        1,
        8
    };

    table[0x0B] = {
        mnemonic::IN_DEC,
        addrmode::AM_R,
        operand_type::R16,
        operand_type::NONE,
        reg_type::R_BC,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        1,
        8
    };

    table[0x0C] = {
        mnemonic::IN_INC,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_C,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        1,
        4
    };

    table[0x0D] = {
        mnemonic::IN_DEC,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_C,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        1,
        4
    };

    table[0x0E] = {
        mnemonic::IN_LD,
        addrmode::AM_R_D8,
        operand_type::R8,
        operand_type::IMM8,
        reg_type::R_C,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x0F] = {
        mnemonic::IN_RRCA,
        addrmode::AM_IMP,
        operand_type::NONE,
        operand_type::NONE,
        reg_type::R_NONE,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        1,
        4
    };

    table[0x10] = {
        mnemonic::IN_STOP,
        addrmode::AM_IMP,
        operand_type::NONE,
        operand_type::NONE,
        reg_type::R_NONE,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        2
    };

    table[0x11] = {
        mnemonic::IN_LD,
        addrmode::AM_R_D16,
        operand_type::R16,
        operand_type::IMM16,
        reg_type::R_DE,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        3,
        12        
    };

    table[0x12] = {
        mnemonic::IN_LD,
        addrmode::AM_MR_R,
        operand_type::MEM_R,
        operand_type::R8,
        reg_type::R_DE,
        reg_type::R_A,
        condition_code::CD_NONE,
        1,
        8
    };

    table[0x13] = {
        mnemonic::IN_INC,
        addrmode::AM_R,
        operand_type::R16,
        operand_type::NONE,
        reg_type::R_DE,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        1,
        8
    };

    table[0x14] = {
        mnemonic::IN_INC,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_D,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        1,
        4
    };

    table[0x15] = {
        mnemonic::IN_DEC,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_D,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        1,
        4
    };

    table[0x16] = {
        mnemonic::IN_LD,
        addrmode::AM_R_D8,
        operand_type::R8,
        operand_type::IMM8,
        reg_type::R_D,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x17] = {
        mnemonic::IN_RLA,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_A,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        1,
        4
    };

    table[0x18] = {
        mnemonic::IN_JR,
        addrmode::AM_D8,
        operand_type::IMM8,
        operand_type::NONE,
        reg_type::R_NONE,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        12
    };

    table[0x19] = {
        mnemonic::IN_ADD,
        addrmode::AM_R_R,
        operand_type::R16,
        operand_type::R16,
        reg_type::R_HL,
        reg_type::R_DE,
        condition_code::CD_NONE,
        1,
        8
    };

    table[0x1A] = {
        mnemonic::IN_LD,
        addrmode::AM_R_MR,
        operand_type::R8,
        operand_type::MEM_R,
        reg_type::R_A,
        reg_type::R_DE,
        condition_code::CD_NONE,
        1,
        8
    };

    table[0x1B] = {
        mnemonic::IN_DEC,
        addrmode::AM_R,
        operand_type::R16,
        operand_type::NONE,
        reg_type::R_DE,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        1,
        8
    };

    table[0x1C] = {
        mnemonic::IN_INC,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_E,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        1,
        4
    };

    table[0x1D] = {
        mnemonic::IN_DEC,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_E,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        1,
        4
    };

    table[0x1E] = {
        mnemonic::IN_LD,
        addrmode::AM_R_D8,
        operand_type::R8,
        operand_type::IMM8,
        reg_type::R_E,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x1F] = {
        mnemonic::IN_RRA,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_A,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        1,
        4
    };

    table[0x20] = {
        mnemonic::IN_JR,
        addrmode::AM_D8,
        operand_type::IMM8,
        operand_type::NONE,
        reg_type::R_NONE,
        reg_type::R_NONE,
        condition_code::CD_NZ,
        2,
        8  // not-taken cycles, handler adds 4 more when taken
    };

    table[0x21] = {
        mnemonic::IN_LD,
        addrmode::AM_R_D16,
        operand_type::R16,
        operand_type::IMM16,
        reg_type::R_HL,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        3,
        12        
    };

    table[0x22] = {
        mnemonic::IN_LD,
        addrmode::AM_HLI_R,
        operand_type::HL_INC,
        operand_type::R8,
        reg_type::R_HL,
        reg_type::R_A,
        condition_code::CD_NONE,
        1,
        8
    };

    table[0x23] = {
        mnemonic::IN_INC,
        addrmode::AM_R,
        operand_type::R16,
        operand_type::NONE,
        reg_type::R_HL,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        1,
        8
    };

    table[0x24] = {
        mnemonic::IN_INC,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_H,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        1,
        4
    };

    table[0x25] = {
        mnemonic::IN_DEC,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_H,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        1,
        4
    };

    table[0x26] = {
        mnemonic::IN_LD,
        addrmode::AM_R_D8,
        operand_type::R8,
        operand_type::IMM8,
        reg_type::R_H,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x27] = {
        mnemonic::IN_DAA,
        addrmode::AM_IMP,
        operand_type::NONE,
        operand_type::NONE,
        reg_type::R_NONE,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        1,
        4
    };

    table[0x28] = {
        mnemonic::IN_JR,
        addrmode::AM_D8,
        operand_type::IMM8,
        operand_type::NONE,
        reg_type::R_NONE,
        reg_type::R_NONE,
        condition_code::CD_Z,
        2,
        8  // not-taken cycles, handler adds 4 more when taken
    };

    table[0x29] = {
        mnemonic::IN_ADD,
        addrmode::AM_R_R,
        operand_type::R16,
        operand_type::R16,
        reg_type::R_HL,
        reg_type::R_HL,
        condition_code::CD_NONE,
        1,
        8
    };

    table[0x2A] = {
        mnemonic::IN_LD,
        addrmode::AM_R_HLI,
        operand_type::R8,
        operand_type::HL_INC,
        reg_type::R_A,
        reg_type::R_HL,
        condition_code::CD_NONE,
        1,
        8
    };

    table[0x2B] = {
        mnemonic::IN_DEC,
        addrmode::AM_R,
        operand_type::R16,
        operand_type::NONE,
        reg_type::R_HL,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        1,
        8
    };

    table[0x2C] = {
        mnemonic::IN_INC,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_L,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        1,
        4  
    };

    table[0x2D] = {
        mnemonic::IN_DEC,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_L,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        1,
        4  
    };

    table[0x2E] = {
        mnemonic::IN_LD,
        addrmode::AM_R_D8,
        operand_type::R8,
        operand_type::IMM8,
        reg_type::R_L,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x2F] = {
        mnemonic::IN_CPL,
        addrmode::AM_IMP,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_A,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        1,
        4
    };

    table[0x30] = {
        mnemonic::IN_JR,
        addrmode::AM_D8,
        operand_type::IMM8,
        operand_type::NONE,
        reg_type::R_NONE,
        reg_type::R_NONE,
        condition_code::CD_NC,
        2,
        8  // not-taken cycles, handler adds 4 more when taken
    };

    table[0x31] = {
        mnemonic::IN_LD,
        addrmode::AM_R_D16,
        operand_type::R16,
        operand_type::IMM16,
        reg_type::R_SP,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        3,
        12        
    };

    table[0x32] = {
        mnemonic::IN_LD,
        addrmode::AM_HLD_R,
        operand_type::HL_DEC,
        operand_type::R8,
        reg_type::R_HL,
        reg_type::R_A,
        condition_code::CD_NONE,
        1,
        8
    };

    table[0x33] = {
        mnemonic::IN_INC,
        addrmode::AM_R,
        operand_type::R16,
        operand_type::NONE,
        reg_type::R_SP,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        1,
        8     
    };

    table[0x34] = {
        mnemonic::IN_INC,
        addrmode::AM_MR,
        operand_type::MEM_R,
        operand_type::NONE,
        reg_type::R_HL,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        1,
        12
    };

    table[0x35] = {
        mnemonic::IN_DEC,
        addrmode::AM_MR,
        operand_type::MEM_R,
        operand_type::NONE,
        reg_type::R_HL,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        1,
        12
    };

    table[0x36] = {
        mnemonic::IN_LD,
        addrmode::AM_MR_D8,
        operand_type::MEM_R,
        operand_type::IMM8,
        reg_type::R_HL,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        12
    };

    table[0x37] = {
        mnemonic::IN_SCF,
        addrmode::AM_IMP,
        operand_type::NONE,
        operand_type::NONE,
        reg_type::R_NONE,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        1,
        4
    };

    table[0x38] = {
        mnemonic::IN_JR,
        addrmode::AM_D8,
        operand_type::IMM8,
        operand_type::NONE,
        reg_type::R_NONE,
        reg_type::R_NONE,
        condition_code::CD_C,
        2,
        8  // not-taken cycles, handler adds 4 more when taken
    };

    table[0x39] = {
        mnemonic::IN_ADD,
        addrmode::AM_R_R,
        operand_type::R16,
        operand_type::R16,
        reg_type::R_HL,
        reg_type::R_SP,
        condition_code::CD_NONE,
        1,
        8
    };

    table[0x3A] = {
        mnemonic::IN_LD,
        addrmode::AM_R_HLD,
        operand_type::R8,
        operand_type::HL_DEC,
        reg_type::R_A,
        reg_type::R_HL,
        condition_code::CD_NONE,
        1,
        8
    };

    table[0x3B] = {
        mnemonic::IN_DEC,
        addrmode::AM_R,
        operand_type::R16,
        operand_type::NONE,
        reg_type::R_SP,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        1,
        8
    };

    table[0x3C] = {
        mnemonic::IN_INC,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_A,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        1,
        4  
    };

    table[0x3D] = {
        mnemonic::IN_DEC,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_A,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        1,
        4  
    };

    table[0x3E] = {
        mnemonic::IN_LD,
        addrmode::AM_R_D8,
        operand_type::R8,
        operand_type::IMM8,
        reg_type::R_A,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x3F] = {
        mnemonic::IN_CCF,
        addrmode::AM_IMP,
        operand_type::NONE,
        operand_type::NONE,
        reg_type::R_NONE,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        1,
        4
    };

    table[0x40] = {
        mnemonic::IN_LD,
        addrmode::AM_R_R,
        operand_type::R8,
        operand_type::R8,
        reg_type::R_B,
        reg_type::R_B,
        condition_code::CD_NONE,
        1,
        4
    };

    table[0x41] = {
        mnemonic::IN_LD,
        addrmode::AM_R_R,
        operand_type::R8,
        operand_type::R8,
        reg_type::R_B,
        reg_type::R_C,
        condition_code::CD_NONE,
        1,
        4
    };

    table[0x42] = {
        mnemonic::IN_LD,
        addrmode::AM_R_R,
        operand_type::R8,
        operand_type::R8,
        reg_type::R_B,
        reg_type::R_D,
        condition_code::CD_NONE,
        1,
        4
    };
    
    table[0x43] = {
        mnemonic::IN_LD,
        addrmode::AM_R_R,
        operand_type::R8,
        operand_type::R8,
        reg_type::R_B,
        reg_type::R_E,
        condition_code::CD_NONE,
        1,
        4
    };

    table[0x44] = {
        mnemonic::IN_LD,
        addrmode::AM_R_R,
        operand_type::R8,
        operand_type::R8,
        reg_type::R_B,
        reg_type::R_H,
        condition_code::CD_NONE,
        1,
        4
    };

    table[0x45] = {
        mnemonic::IN_LD,
        addrmode::AM_R_R,
        operand_type::R8,
        operand_type::R8,
        reg_type::R_B,
        reg_type::R_L,
        condition_code::CD_NONE,
        1,
        4
    };

    table[0x46] = {
        mnemonic::IN_LD,
        addrmode::AM_R_MR,
        operand_type::R8,
        operand_type::MEM_R,
        reg_type::R_B,
        reg_type::R_HL,
        condition_code::CD_NONE,
        1,
        8
    };

    table[0x47] = {
        mnemonic::IN_LD,
        addrmode::AM_R_R,
        operand_type::R8,
        operand_type::R8,
        reg_type::R_B,
        reg_type::R_A,
        condition_code::CD_NONE,
        1,
        4
    };

    table[0x48] = {
        mnemonic::IN_LD,
        addrmode::AM_R_R,
        operand_type::R8,
        operand_type::R8,
        reg_type::R_C,
        reg_type::R_B,
        condition_code::CD_NONE,
        1,
        4
    };
    
    table[0x49] = {
        mnemonic::IN_LD,
        addrmode::AM_R_R,
        operand_type::R8,
        operand_type::R8,
        reg_type::R_C,
        reg_type::R_C,
        condition_code::CD_NONE,
        1,
        4
    };

    table[0x4A] = {
        mnemonic::IN_LD,
        addrmode::AM_R_R,
        operand_type::R8,
        operand_type::R8,
        reg_type::R_C,
        reg_type::R_D,
        condition_code::CD_NONE,
        1,
        4
    };
    
    table[0x4B] = {
        mnemonic::IN_LD,
        addrmode::AM_R_R,
        operand_type::R8,
        operand_type::R8,
        reg_type::R_C,
        reg_type::R_E,
        condition_code::CD_NONE,
        1,
        4
    };

    table[0x4C] = {
        mnemonic::IN_LD,
        addrmode::AM_R_R,
        operand_type::R8,
        operand_type::R8,
        reg_type::R_C,
        reg_type::R_H,
        condition_code::CD_NONE,
        1,
        4
    };

    table[0x4D] = {
        mnemonic::IN_LD,
        addrmode::AM_R_R,
        operand_type::R8,
        operand_type::R8,
        reg_type::R_C,
        reg_type::R_L,
        condition_code::CD_NONE,
        1,
        4
    };

    table[0x4E] = {
        mnemonic::IN_LD,
        addrmode::AM_R_MR,
        operand_type::R8,
        operand_type::MEM_R,
        reg_type::R_C,
        reg_type::R_HL,
        condition_code::CD_NONE,
        1,
        8
    };

    table[0x4F] = {
        mnemonic::IN_LD,
        addrmode::AM_R_R,
        operand_type::R8,
        operand_type::R8,
        reg_type::R_C,
        reg_type::R_A,
        condition_code::CD_NONE,
        1,
        4
    };
    
    table[0x50] = {
        mnemonic::IN_LD,
        addrmode::AM_R_R,
        operand_type::R8,
        operand_type::R8,
        reg_type::R_D,
        reg_type::R_B,
        condition_code::CD_NONE,
        1,
        4
    };
    
    table[0x51] = {
        mnemonic::IN_LD,
        addrmode::AM_R_R,
        operand_type::R8,
        operand_type::R8,
        reg_type::R_D,
        reg_type::R_C,
        condition_code::CD_NONE,
        1,
        4
    };
    
    table[0x52] = {
        mnemonic::IN_LD,
        addrmode::AM_R_R,
        operand_type::R8,
        operand_type::R8,
        reg_type::R_D,
        reg_type::R_D,
        condition_code::CD_NONE,
        1,
        4
    };

    table[0x53] = {
        mnemonic::IN_LD,
        addrmode::AM_R_R,
        operand_type::R8,
        operand_type::R8,
        reg_type::R_D,
        reg_type::R_E,
        condition_code::CD_NONE,
        1,
        4
    };

    table[0x54] = {
        mnemonic::IN_LD,
        addrmode::AM_R_R,
        operand_type::R8,
        operand_type::R8,
        reg_type::R_D,
        reg_type::R_H,
        condition_code::CD_NONE,
        1,
        4
    };

    table[0x55] = {
        mnemonic::IN_LD,
        addrmode::AM_R_R,
        operand_type::R8,
        operand_type::R8,
        reg_type::R_D,
        reg_type::R_L,
        condition_code::CD_NONE,
        1,
        4
    };

    table[0x56] = {
        mnemonic::IN_LD,
        addrmode::AM_R_MR,
        operand_type::R8,
        operand_type::MEM_R,
        reg_type::R_D,
        reg_type::R_HL,
        condition_code::CD_NONE,
        1,
        8
    };

    table[0x57] = {
        mnemonic::IN_LD,
        addrmode::AM_R_R,
        operand_type::R8,
        operand_type::R8,
        reg_type::R_D,
        reg_type::R_A,
        condition_code::CD_NONE,
        1,
        4
    };

    table[0x58] = {
        mnemonic::IN_LD,
        addrmode::AM_R_R,
        operand_type::R8,
        operand_type::R8,
        reg_type::R_E,
        reg_type::R_B,
        condition_code::CD_NONE,
        1,
        4
    };

    table[0x59] = {
        mnemonic::IN_LD,
        addrmode::AM_R_R,
        operand_type::R8,
        operand_type::R8,
        reg_type::R_E,
        reg_type::R_C,
        condition_code::CD_NONE,
        1,
        4
    };

    table[0x5A] = {
        mnemonic::IN_LD,
        addrmode::AM_R_R,
        operand_type::R8,
        operand_type::R8,
        reg_type::R_E,
        reg_type::R_D,
        condition_code::CD_NONE,
        1,
        4
    };

    table[0x5B] = {
        mnemonic::IN_LD,
        addrmode::AM_R_R,
        operand_type::R8,
        operand_type::R8,
        reg_type::R_E,
        reg_type::R_E,
        condition_code::CD_NONE,
        1,
        4
    };

    table[0x5C] = {
        mnemonic::IN_LD,
        addrmode::AM_R_R,
        operand_type::R8,
        operand_type::R8,
        reg_type::R_E,
        reg_type::R_H,
        condition_code::CD_NONE,
        1,
        4
    };

    table[0x5D] = {
        mnemonic::IN_LD,
        addrmode::AM_R_R,
        operand_type::R8,
        operand_type::R8,
        reg_type::R_E,
        reg_type::R_L,
        condition_code::CD_NONE,
        1,
        4
    };

    table[0x5E] = {
        mnemonic::IN_LD,
        addrmode::AM_R_MR,
        operand_type::R8,
        operand_type::MEM_R,
        reg_type::R_E,
        reg_type::R_HL,
        condition_code::CD_NONE,
        1,
        8
    };

    table[0x5F] = {
        mnemonic::IN_LD,
        addrmode::AM_R_R,
        operand_type::R8,
        operand_type::R8,
        reg_type::R_E,
        reg_type::R_A,
        condition_code::CD_NONE,
        1,
        4
    };

    table[0x60] = {
        mnemonic::IN_LD,
        addrmode::AM_R_R,
        operand_type::R8,
        operand_type::R8,
        reg_type::R_H,
        reg_type::R_B,
        condition_code::CD_NONE,
        1,
        4
    };
    
    table[0x61] = {
        mnemonic::IN_LD,
        addrmode::AM_R_R,
        operand_type::R8,
        operand_type::R8,
        reg_type::R_H,
        reg_type::R_C,
        condition_code::CD_NONE,
        1,
        4
    };
    
    table[0x62] = {
        mnemonic::IN_LD,
        addrmode::AM_R_R,
        operand_type::R8,
        operand_type::R8,
        reg_type::R_H,
        reg_type::R_D,
        condition_code::CD_NONE,
        1,
        4
    };

    table[0x63] = {
        mnemonic::IN_LD,
        addrmode::AM_R_R,
        operand_type::R8,
        operand_type::R8,
        reg_type::R_H,
        reg_type::R_E,
        condition_code::CD_NONE,
        1,
        4
    };

    table[0x64] = {
        mnemonic::IN_LD,
        addrmode::AM_R_R,
        operand_type::R8,
        operand_type::R8,
        reg_type::R_H,
        reg_type::R_H,
        condition_code::CD_NONE,
        1,
        4
    };

    table[0x65] = {
        mnemonic::IN_LD,
        addrmode::AM_R_R,
        operand_type::R8,
        operand_type::R8,
        reg_type::R_H,
        reg_type::R_L,
        condition_code::CD_NONE,
        1,
        4
    };

    table[0x66] = {
        mnemonic::IN_LD,
        addrmode::AM_R_MR,
        operand_type::R8,
        operand_type::MEM_R,
        reg_type::R_H,
        reg_type::R_HL,
        condition_code::CD_NONE,
        1,
        8
    };

    table[0x67] = {
        mnemonic::IN_LD,
        addrmode::AM_R_R,
        operand_type::R8,
        operand_type::R8,
        reg_type::R_H,
        reg_type::R_A,
        condition_code::CD_NONE,
        1,
        4
    };

    table[0x68] = {
        mnemonic::IN_LD,
        addrmode::AM_R_R,
        operand_type::R8,
        operand_type::R8,
        reg_type::R_L,
        reg_type::R_B,
        condition_code::CD_NONE,
        1,
        4
    };

    table[0x69] = {
        mnemonic::IN_LD,
        addrmode::AM_R_R,
        operand_type::R8,
        operand_type::R8,
        reg_type::R_L,
        reg_type::R_C,
        condition_code::CD_NONE,
        1,
        4
    };

    table[0x6A] = {
        mnemonic::IN_LD,
        addrmode::AM_R_R,
        operand_type::R8,
        operand_type::R8,
        reg_type::R_L,
        reg_type::R_D,
        condition_code::CD_NONE,
        1,
        4
    };

    table[0x6B] = {
        mnemonic::IN_LD,
        addrmode::AM_R_R,
        operand_type::R8,
        operand_type::R8,
        reg_type::R_L,
        reg_type::R_E,
        condition_code::CD_NONE,
        1,
        4
    };

    table[0x6C] = {
        mnemonic::IN_LD,
        addrmode::AM_R_R,
        operand_type::R8,
        operand_type::R8,
        reg_type::R_L,
        reg_type::R_H,
        condition_code::CD_NONE,
        1,
        4
    };

    table[0x6D] = {
        mnemonic::IN_LD,
        addrmode::AM_R_R,
        operand_type::R8,
        operand_type::R8,
        reg_type::R_L,
        reg_type::R_L,
        condition_code::CD_NONE,
        1,
        4
    };

    table[0x6E] = {
        mnemonic::IN_LD,
        addrmode::AM_R_MR,
        operand_type::R8,
        operand_type::MEM_R,
        reg_type::R_L,
        reg_type::R_HL,
        condition_code::CD_NONE,
        1,
        8
    };

    table[0x6F] = {
        mnemonic::IN_LD,
        addrmode::AM_R_R,
        operand_type::R8,
        operand_type::R8,
        reg_type::R_L,
        reg_type::R_A,
        condition_code::CD_NONE,
        1,
        4
    };

    table[0x70] = {
        mnemonic::IN_LD,
        addrmode::AM_MR_R,
        operand_type::MEM_R,
        operand_type::R8,
        reg_type::R_HL,
        reg_type::R_B,
        condition_code::CD_NONE,
        1,
        8
    };

    table[0x71] = {
        mnemonic::IN_LD,
        addrmode::AM_MR_R,
        operand_type::MEM_R,
        operand_type::R8,
        reg_type::R_HL,
        reg_type::R_C,
        condition_code::CD_NONE,
        1,
        8
    };
    
    table[0x72] = {
        mnemonic::IN_LD,
        addrmode::AM_MR_R,
        operand_type::MEM_R,
        operand_type::R8,
        reg_type::R_HL,
        reg_type::R_D,
        condition_code::CD_NONE,
        1,
        8
    };

    table[0x73] = {
        mnemonic::IN_LD,
        addrmode::AM_MR_R,
        operand_type::MEM_R,
        operand_type::R8,
        reg_type::R_HL,
        reg_type::R_E,
        condition_code::CD_NONE,
        1,
        8
    };

    table[0x74] = {
        mnemonic::IN_LD,
        addrmode::AM_MR_R,
        operand_type::MEM_R,
        operand_type::R8,
        reg_type::R_HL,
        reg_type::R_H,
        condition_code::CD_NONE,
        1,
        8
    };

    table[0x75] = {
        mnemonic::IN_LD,
        addrmode::AM_MR_R,
        operand_type::MEM_R,
        operand_type::R8,
        reg_type::R_HL,
        reg_type::R_L,
        condition_code::CD_NONE,
        1,
        8
    };

    table[0x76] = {
        mnemonic::IN_HALT,
        addrmode::AM_IMP,
        operand_type::NONE,
        operand_type::NONE,
        reg_type::R_NONE,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        1,
        4
    };

    table[0x77] = {
        mnemonic::IN_LD,
        addrmode::AM_MR_R,
        operand_type::MEM_R,
        operand_type::R8,
        reg_type::R_HL,
        reg_type::R_A,
        condition_code::CD_NONE,
        1,
        8
    };

    table[0x78] = {
        mnemonic::IN_LD,
        addrmode::AM_R_R,
        operand_type::R8,
        operand_type::R8,
        reg_type::R_A,
        reg_type::R_B,
        condition_code::CD_NONE,
        1,
        4
    }; 

    table[0x79] = {
        mnemonic::IN_LD,
        addrmode::AM_R_R,
        operand_type::R8,
        operand_type::R8,
        reg_type::R_A,
        reg_type::R_C,
        condition_code::CD_NONE,
        1,
        4
    }; 

    table[0x7A] = {
        mnemonic::IN_LD,
        addrmode::AM_R_R,
        operand_type::R8,
        operand_type::R8,
        reg_type::R_A,
        reg_type::R_D,
        condition_code::CD_NONE,
        1,
        4
    }; 

    table[0x7B] = {
        mnemonic::IN_LD,
        addrmode::AM_R_R,
        operand_type::R8,
        operand_type::R8,
        reg_type::R_A,
        reg_type::R_E,
        condition_code::CD_NONE,
        1,
        4
    }; 

    table[0x7C] = {
        mnemonic::IN_LD,
        addrmode::AM_R_R,
        operand_type::R8,
        operand_type::R8,
        reg_type::R_A,
        reg_type::R_H,
        condition_code::CD_NONE,
        1,
        4
    }; 

    table[0x7D] = {
        mnemonic::IN_LD,
        addrmode::AM_R_R,
        operand_type::R8,
        operand_type::R8,
        reg_type::R_A,
        reg_type::R_L,
        condition_code::CD_NONE,
        1,
        4
    }; 

    table[0x7E] = {
        mnemonic::IN_LD,
        addrmode::AM_R_MR,
        operand_type::R8,
        operand_type::MEM_R,
        reg_type::R_A,
        reg_type::R_HL,
        condition_code::CD_NONE,
        1,
        8
    };

    table[0x7F] = {
        mnemonic::IN_LD,
        addrmode::AM_R_R,
        operand_type::R8,
        operand_type::R8,
        reg_type::R_A,
        reg_type::R_A,
        condition_code::CD_NONE,
        1,
        4
    }; 

    table[0x80] = {
        mnemonic::IN_ADD,
        addrmode::AM_R_R,
        operand_type::R8,
        operand_type::R8,
        reg_type::R_A,
        reg_type::R_B,
        condition_code::CD_NONE,
        1,
        4
    };

    table[0x81] = {
        mnemonic::IN_ADD,
        addrmode::AM_R_R,
        operand_type::R8,
        operand_type::R8,
        reg_type::R_A,
        reg_type::R_C,
        condition_code::CD_NONE,
        1,
        4
    };

    table[0x82] = {
        mnemonic::IN_ADD,
        addrmode::AM_R_R,
        operand_type::R8,
        operand_type::R8,
        reg_type::R_A,
        reg_type::R_D,
        condition_code::CD_NONE,
        1,
        4
    };

    table[0x83] = {
        mnemonic::IN_ADD,
        addrmode::AM_R_R,
        operand_type::R8,
        operand_type::R8,
        reg_type::R_A,
        reg_type::R_E,
        condition_code::CD_NONE,
        1,
        4
    };

    table[0x84] = {
        mnemonic::IN_ADD,
        addrmode::AM_R_R,
        operand_type::R8,
        operand_type::R8,
        reg_type::R_A,
        reg_type::R_H,
        condition_code::CD_NONE,
        1,
        4
    };

    table[0x85] = {
        mnemonic::IN_ADD,
        addrmode::AM_R_R,
        operand_type::R8,
        operand_type::R8,
        reg_type::R_A,
        reg_type::R_L,
        condition_code::CD_NONE,
        1,
        4
    };

    table[0x86] = {
        mnemonic::IN_ADD,
        addrmode::AM_R_MR,
        operand_type::R8,
        operand_type::MEM_R,
        reg_type::R_A,
        reg_type::R_HL,
        condition_code::CD_NONE,
        1,
        8
    };

    table[0x87] = {
        mnemonic::IN_ADD,
        addrmode::AM_R_R,
        operand_type::R8,
        operand_type::R8,
        reg_type::R_A,
        reg_type::R_A,
        condition_code::CD_NONE,
        1,
        4
    };

    table[0x88] = {
        mnemonic::IN_ADC,
        addrmode::AM_R_R,
        operand_type::R8,
        operand_type::R8,
        reg_type::R_A,
        reg_type::R_B,
        condition_code::CD_NONE,
        1,
        4
    };

    table[0x89] = {
        mnemonic::IN_ADC,
        addrmode::AM_R_R,
        operand_type::R8,
        operand_type::R8,
        reg_type::R_A,
        reg_type::R_C,
        condition_code::CD_NONE,
        1,
        4
    };

    table[0x8A] = {
        mnemonic::IN_ADC,
        addrmode::AM_R_R,
        operand_type::R8,
        operand_type::R8,
        reg_type::R_A,
        reg_type::R_D,
        condition_code::CD_NONE,
        1,
        4
    };

    table[0x8B] = {
        mnemonic::IN_ADC,
        addrmode::AM_R_R,
        operand_type::R8,
        operand_type::R8,
        reg_type::R_A,
        reg_type::R_E,
        condition_code::CD_NONE,
        1,
        4
    };

    table[0x8C] = {
        mnemonic::IN_ADC,
        addrmode::AM_R_R,
        operand_type::R8,
        operand_type::R8,
        reg_type::R_A,
        reg_type::R_H,
        condition_code::CD_NONE,
        1,
        4
    };

    table[0x8D] = {
        mnemonic::IN_ADC,
        addrmode::AM_R_R,
        operand_type::R8,
        operand_type::R8,
        reg_type::R_A,
        reg_type::R_L,
        condition_code::CD_NONE,
        1,
        4
    };

    table[0x8E] = {
        mnemonic::IN_ADC,
        addrmode::AM_R_MR,
        operand_type::R8,
        operand_type::MEM_R,
        reg_type::R_A,
        reg_type::R_HL,
        condition_code::CD_NONE,
        1,
        8
    };

    table[0x8F] = {
        mnemonic::IN_ADC,
        addrmode::AM_R_R,
        operand_type::R8,
        operand_type::R8,
        reg_type::R_A,
        reg_type::R_A,
        condition_code::CD_NONE,
        1,
        4
    };


}

void op_unimplemented(CPU& cpu, const Instruction& inst)
{
    printf("Unimplemented opcode: 0x%02X\n", cpu.current_opcode);
}

void op_nop(CPU& cpu, const Instruction& inst) {
    // nothing 
}

// DONT FORGET TO COMBINE ALL THESE LOAD FUNCTIONS (AND ALL OTHER RELATED FUNCTIONS) TOGETHER
// these are all separate for now to make debugging a bit easier

void op_ld_r16_imm16(CPU& cpu, const Instruction& inst){
    if(inst.address_mode == addrmode::AM_R_D16){
        // load immediate 16 bit value into register
        uint16_t value = cpu.fetch16(); // imm16 value
        cpu.setReg16(inst.reg_1, value); // write to register
    }
}

void op_ld_mr_r(CPU& cpu, const Instruction& inst){
    if(inst.address_mode == addrmode::AM_MR_R){
        // load value of register into address of the target register
        cpu.write(cpu.getReg16(inst.reg_1), cpu.getReg8(inst.reg_2));
    }
}

void op_ld_r8_imm8(CPU& cpu, const Instruction& inst){
    if(inst.address_mode == addrmode::AM_R_D8){
        // load immediate 8 bit value into register
        uint8_t value = cpu.fetch(); // imm8 value
        cpu.setReg8(inst.reg_1, value); // write to register
    }
}

void op_ld_r8_r8(CPU& cpu, const Instruction& inst){
    if(inst.address_mode == addrmode::AM_R_R){
        // load register value into register
        uint8_t value = cpu.getReg8(inst.reg_2);
        cpu.setReg8(inst.reg_1, value); // write to register
    }
}

void op_ld_mr_imm8(CPU& cpu, const Instruction& inst){
    if(inst.address_mode == addrmode::AM_MR_D8){
        // load immediate 8 bit value into memory register
        uint16_t addr = cpu.getReg16(inst.reg_1);
        uint8_t value = cpu.fetch(); // imm8 value

        cpu.write(addr, value); // write to register
    }
}

void op_ld_a16_r(CPU& cpu, const Instruction& inst){
    if(inst.address_mode == addrmode::AM_A16_R){
        uint16_t value = cpu.getReg16(inst.reg_2);
        uint16_t addr = cpu.fetch16();
        cpu.write(addr, value & 0xFF); // writes the lower byte of SP to the imm16 bit address (0xFF is the mask that isolates the lower byte)
        cpu.write(addr + 1, value >> 8); // writes the upper byte of SP to imm16 + 1 address (shift the bits 8 to the right to isolate the upper byte)
    }
}

void op_ld_r_mr(CPU& cpu, const Instruction& inst){
    if(inst.address_mode == addrmode::AM_R_MR){
        uint16_t addr = cpu.getReg16(inst.reg_2);
        uint8_t value = cpu.read(addr);

        cpu.setReg8(inst.reg_1, value);
    }
}

void op_inc_r16(CPU& cpu, const Instruction& inst){
    uint16_t value = cpu.getReg16(inst.reg_1);
    value++;
    cpu.setReg16(inst.reg_1, value);
}

void op_dec_r16(CPU& cpu, const Instruction& inst){
    uint16_t value = cpu.getReg16(inst.reg_1);
    value--;
    cpu.setReg16(inst.reg_1, value);
}

void op_inc_r8(CPU& cpu, const Instruction& inst){
    uint8_t original = cpu.getReg8(inst.reg_1); // keep the original value to compute the half carry flag
    uint8_t result = original + 1;
    cpu.setReg8(inst.reg_1, result);

    // flag logic
    cpu.setFlag(Flag::Z, result == 0);
    cpu.setFlag(Flag::N, false);
    cpu.setFlag(Flag::H, (original & 0x0F) == 0x0F);
}

void op_inc_mr(CPU& cpu, const Instruction& inst){
    uint16_t addr = cpu.getReg16(inst.reg_1);
    uint8_t original = cpu.read(addr);
    uint8_t result = original + 1;    
    cpu.write(addr, result);
    
    // flag logic
    cpu.setFlag(Flag::Z, result == 0);
    cpu.setFlag(Flag::N, false);
    cpu.setFlag(Flag::H, (original & 0x0F) == 0x0F);
}

void op_dec_r8(CPU& cpu, const Instruction& inst){
    uint8_t original = cpu.getReg8(inst.reg_1); // keep the original value to compute the half carry flag
    uint8_t result = original - 1;
    cpu.setReg8(inst.reg_1, result);

    // flag logic
    cpu.setFlag(Flag::Z, result == 0);
    cpu.setFlag(Flag::N, true);
    cpu.setFlag(Flag::H, (original & 0x0F) == 0);
}

void op_dec_mr(CPU& cpu, const Instruction& inst){
    uint16_t addr = cpu.getReg16(inst.reg_1);
    uint8_t original = cpu.read(addr);    
    uint8_t result = original - 1;
    cpu.write(addr, result);

    // flag logic
    cpu.setFlag(Flag::Z, result == 0);
    cpu.setFlag(Flag::N, true);
    cpu.setFlag(Flag::H, (original & 0x0F) == 0);
}

void op_rlca(CPU& cpu, const Instruction& inst){
    /*
    Rotate the contents of register A to the left. That is, the contents of bit 0 are copied to bit 1, 
    and the previous contents of bit 1 (before the copy operation) are copied to bit 2. 
    The same operation is repeated in sequence for the rest of the register.
    The contents of bit 7 are placed in both the CY flag and bit 0 of register A.
    */
    uint8_t original = cpu.getReg8(reg_type::R_A);  // original value stored in register A before rotation
    uint8_t bit = (original >> 7) & 1; // isolate the 7th bit
    uint8_t rotated = (original << 1) | bit; // shift the bits left by one and set bit 0 equal to the 7th bit
    cpu.setReg8(reg_type::R_A, rotated);

    cpu.setFlag(Flag::C, bit); // set the carry flag to the 7th bit
    cpu.setFlag(Flag::Z, false);
    cpu.setFlag(Flag::N, false);
    cpu.setFlag(Flag::H, false);
}

void op_add_r16_r16(CPU& cpu, const Instruction& inst){
    if(inst.address_mode == addrmode::AM_R_R){
        uint16_t value = cpu.getReg16(inst.reg_2);
        uint16_t original = cpu.getReg16(inst.reg_1);
        bool carry = (original + value) > 0xFFFF;
        bool halfCarry = ((original & 0x0FFF) + (value & 0x0FFF)) > 0x0FFF;
        cpu.setReg16(inst.reg_1, original + value);

        cpu.setFlag(Flag::N, false);
        cpu.setFlag(Flag::H, halfCarry);
        cpu.setFlag(Flag::C, carry);
    }
}

void op_rrca(CPU& cpu, const Instruction& inst){
    /*
    Rotate the contents of register A to the right. That is, the contents of bit 7 are copied to bit 6,
    and the previous contents of bit 6 (before the copy) are copied to bit 5. 
    The same operation is repeated in sequence for the rest of the register. 
    The contents of bit 0 are placed in both the CY flag and bit 7 of register A.
    */
    uint8_t original = cpu.getReg8(reg_type::R_A);  // original value stored in register A before rotation
    uint8_t bit = (original) & 0x01; // old bit 0
    uint8_t rotated = (original >> 1) | (bit << 7); // shift the bits left by one and set bit 0 equal to the 7th bit
    cpu.setReg8(reg_type::R_A, rotated);

    cpu.setFlag(Flag::C, bit); // set the carry flag to the 0th bit
    cpu.setFlag(Flag::Z, false);
    cpu.setFlag(Flag::N, false);
    cpu.setFlag(Flag::H, false);
}

void op_stop(CPU& cpu, const Instruction& inst){
    // partial implementation for now
    cpu.fetch();
    cpu.stopped = true;
}

void op_rla(CPU& cpu, const Instruction& inst){
    /*
    Rotate the contents of register A to the left, through the carry (CY) flag. 
    That is, the contents of bit 0 are copied to bit 1, and the previous contents of bit 1 (before the copy operation) 
    are copied to bit 2. The same operation is repeated in sequence for the rest of the register. 
    The previous contents of the carry flag are copied to bit 0.
    */

    uint8_t a = cpu.getReg8(reg_type::R_A);
    uint8_t old_carry = cpu.getFlag(Flag::C); 
    uint8_t new_carry = (a >> 7) & 1; 
    uint8_t rotated = (a << 1) | old_carry;
    
    cpu.setReg8(reg_type::R_A, rotated);
    cpu.setFlag(Flag::C, new_carry); 
    cpu.setFlag(Flag::Z, false);
    cpu.setFlag(Flag::N, false);
    cpu.setFlag(Flag::H, false);
}

void op_jr_s8(CPU& cpu, const Instruction& inst){
    // Jump s8 steps (s8 steps means: a signed 8-bit number of steps.) from the currect address in PC
    int8_t offset = static_cast<int8_t>(cpu.fetch()); // needs to be signed because the offset byte is -2
    uint16_t pc = cpu.getReg16(reg_type::R_PC);
    cpu.setReg16(reg_type::R_PC, pc + offset);
}

void op_rra(CPU& cpu, const Instruction& inst){
    /*
    Rotate the contents of register A to the right, through the carry (CY) flag. 
    That is, the contents of bit 7 are copied to bit 6, and the previous contents of bit 6 (before the copy) are copied to bit 5. 
    The same operation is repeated in sequence for the rest of the register. 
    The previous contents of the carry flag are copied to bit 7.
    */
    uint8_t a = cpu.getReg8(reg_type::R_A);
    uint8_t old_carry = cpu.getFlag(Flag::C);
    uint8_t new_carry = (a) & 1;
    uint8_t rotated = (a >> 1) | (old_carry << 7);

    cpu.setReg8(reg_type::R_A, rotated);
    cpu.setFlag(Flag::C, new_carry);
    cpu.setFlag(Flag::Z, false);
    cpu.setFlag(Flag::N, false);
    cpu.setFlag(Flag::H, false);
}

void op_jr_conditional(CPU& cpu, const Instruction& inst){
    int8_t offset = static_cast<int8_t>(cpu.fetch()); 
    bool condition = false;
    switch(inst.cond_code){
        case condition_code::CD_NZ: condition = !cpu.getFlag(Flag::Z); break;
        case condition_code::CD_Z:  condition =  cpu.getFlag(Flag::Z); break;
        case condition_code::CD_NC: condition = !cpu.getFlag(Flag::C); break;
        case condition_code::CD_C:  condition =  cpu.getFlag(Flag::C); break;
        default: break;
    }

    if(condition){
        uint16_t pc = cpu.getReg16(reg_type::R_PC);
        cpu.setReg16(reg_type::R_PC, pc + offset);
        cpu.update_cycles(4); // add 4 more cycles since the conditional branch is taken (12 clock cycles total)
    }
}

void op_ld_hl_inc_dec_r(CPU& cpu, const Instruction& inst){
    uint16_t hl = cpu.getReg16(inst.reg_1);
    cpu.write(cpu.getReg16(inst.reg_1), cpu.getReg8(inst.reg_2));

    if(inst.operand_1 == operand_type::HL_INC){
        // increment
        hl++;
    }
    else if(inst.operand_1 == operand_type::HL_DEC){
        // decrement
        hl--;
    }
    cpu.setReg16(inst.reg_1, hl);
}

void op_ld_r_hl_inc_dec(CPU& cpu, const Instruction& inst){
    uint16_t hl = cpu.getReg16(inst.reg_2);
    uint8_t value = cpu.read(hl);

    cpu.setReg8(inst.reg_1, value);

    if(inst.operand_2 == operand_type::HL_INC){
        // increment
        hl++;
    }
    else if(inst.operand_2 == operand_type::HL_DEC){
        // decrement
        hl--;
    }
    cpu.setReg16(inst.reg_2, hl);
}

void op_daa(CPU& cpu, const Instruction& inst){
    uint8_t a = cpu.getReg8(reg_type::R_A);
    uint8_t correction = 0;
    bool setCarry = false;

    if (!cpu.getFlag(Flag::N)) {
        // after addition
        if (cpu.getFlag(Flag::H) || (a & 0x0F) > 9)
            correction |= 0x06;
        if (cpu.getFlag(Flag::C) || a > 0x99) {
            correction |= 0x60;
            setCarry = true;
        }
        a += correction;
    } else {
        // after subtraction
        if (cpu.getFlag(Flag::H))
            correction |= 0x06;
        if (cpu.getFlag(Flag::C)) {
            correction |= 0x60;
            setCarry = true;
        }
        a -= correction;
    }

    cpu.setReg8(reg_type::R_A, a);
    cpu.setFlag(Flag::Z, a == 0);
    cpu.setFlag(Flag::H, false);
    cpu.setFlag(Flag::C, setCarry);
}

void op_cpl(CPU& cpu, const Instruction& inst){
    uint8_t a = cpu.getReg8(reg_type::R_A);
    cpu.setReg8(reg_type::R_A, static_cast<uint8_t>(~a));
    
    cpu.setFlag(Flag::N, true);
    cpu.setFlag(Flag::H, true);
}

void op_scf(CPU& cpu, const Instruction& inst){
    cpu.setFlag(Flag::N, false);
    cpu.setFlag(Flag::H, false);
    cpu.setFlag(Flag::C, true);
}

void op_ccf(CPU& cpu, const Instruction& inst){
    cpu.setFlag(Flag::N, false);
    cpu.setFlag(Flag::H, false);
    cpu.setFlag(Flag::C, !cpu.getFlag(Flag::C));
}

void op_halt(CPU& cpu, const Instruction& inst){
    // partial implementation for now
    cpu.halted = true;
}

void op_add(CPU& cpu, const Instruction& inst){
    uint8_t op1;
    uint8_t op2;

    if(inst.address_mode == addrmode::AM_R_R){
        op1 = cpu.getReg8(inst.reg_1);
        op2 = cpu.getReg8(inst.reg_2);
    }
    else if(inst.address_mode == addrmode::AM_R_MR){
        op1 = cpu.getReg8(inst.reg_1);
        uint16_t addr = cpu.getReg16(inst.reg_2);
        op2 = cpu.read(addr);
    }
    uint16_t result = op1 + op2;
    cpu.setReg8(inst.reg_1, static_cast<uint8_t>(result));

    cpu.setFlag(Flag::Z, (result & 0xFF) == 0); // did the 8 bit result become zero? (& 0xFF is used to isolate the 8 bits that are actually stored) 
    cpu.setFlag(Flag::N, false);  
    cpu.setFlag(Flag::H, ((op1 & 0xF) + (op2 & 0xF)) > 0xF); // was there a carry from bit 3 to 4? are the lower 4 bits of op 1 and op 2 added greater than 1111 (0xF)?
    cpu.setFlag(Flag::C, result > 0xFF); // if the result exceeds the largest 8 bit number 0xFF (255) then C is true  
}

void op_adc(CPU& cpu, const Instruction& inst){
    uint8_t op1;
    uint8_t op2;

    if(inst.address_mode == addrmode::AM_R_R){
        op1 = cpu.getReg8(inst.reg_1);
        op2 = cpu.getReg8(inst.reg_2);
    }
    else if(inst.address_mode == addrmode::AM_R_MR){
        op1 = cpu.getReg8(inst.reg_1);
        uint16_t addr = cpu.getReg16(inst.reg_2);
        op2 = cpu.read(addr);
    }
    uint8_t carry = cpu.getFlag(Flag::C);
    uint16_t result = op1 + op2 + carry;
    cpu.setReg8(inst.reg_1, static_cast<uint8_t>(result));

    cpu.setFlag(Flag::Z, (result & 0xFF) == 0); // did the 8 bit result become zero? (& 0xFF is used to isolate the 8 bits that are actually stored) 
    cpu.setFlag(Flag::N, false);  
    cpu.setFlag(Flag::H, ((op1 & 0xF) + (op2 & 0xF) + carry) > 0xF); // was there a carry from bit 3 to 4? are the lower 4 bits of op 1, op 2 and carry added greater than 1111 (0xF)?
    cpu.setFlag(Flag::C, result > 0xFF); // if the result exceeds the largest 8 bit number 0xFF (255) then C is true  
}


void initHandlerTable(std::array<Handler, 256>& table) {
    table.fill(op_unimplemented);
    table[0x00] = op_nop;
    table[0x01] = op_ld_r16_imm16;
    table[0x02] = op_ld_mr_r;
    table[0x03] = op_inc_r16;
    table[0x04] = op_inc_r8;
    table[0x05] = op_dec_r8;
    table[0x06] = op_ld_r8_imm8;
    table[0x07] = op_rlca;
    table[0x08] = op_ld_a16_r;
    table[0x09] = op_add_r16_r16;
    table[0x0A] = op_ld_r_mr;
    table[0x0B] = op_dec_r16;
    table[0x0C] = op_inc_r8;
    table[0x0D] = op_dec_r8;
    table[0x0E] = op_ld_r8_imm8;
    table[0x0F] = op_rrca;
    
    table[0x10] = op_stop; // remember that this is not done, don't need it for now though
    table[0x11] = op_ld_r16_imm16;
    table[0x12] = op_ld_mr_r;
    table[0x13] = op_inc_r16;
    table[0x14] = op_inc_r8;
    table[0x15] = op_dec_r8;
    table[0x16] = op_ld_r8_imm8;
    table[0x17] = op_rla;
    table[0x18] = op_jr_s8;
    table[0x19] = op_add_r16_r16;
    table[0x1A] = op_ld_r_mr;
    table[0x1B] = op_dec_r16;
    table[0x1C] = op_inc_r8;
    table[0x1D] = op_dec_r8;
    table[0x1E] = op_ld_r8_imm8;
    table[0x1F] = op_rra;
    
    table[0x20] = op_jr_conditional;
    table[0x21] = op_ld_r16_imm16;
    table[0x22] = op_ld_hl_inc_dec_r;
    table[0x23] = op_inc_r16;
    table[0x24] = op_inc_r8;
    table[0x25] = op_dec_r8;
    table[0x26] = op_ld_r8_imm8;
    table[0x27] = op_daa;
    table[0x28] = op_jr_conditional;
    table[0x29] = op_add_r16_r16;
    table[0x2A] = op_ld_r_hl_inc_dec;
    table[0x2B] = op_dec_r16;
    table[0x2C] = op_inc_r8;
    table[0x2D] = op_dec_r8;
    table[0x2E] = op_ld_r8_imm8;
    table[0x2F] = op_cpl;
    
    table[0x30] = op_jr_conditional;
    table[0x31] = op_ld_r16_imm16;
    table[0x32] = op_ld_hl_inc_dec_r;
    table[0x33] = op_inc_r16;
    table[0x34] = op_inc_mr;
    table[0x35] = op_dec_mr;
    table[0x36] = op_ld_mr_imm8;
    table[0x37] = op_scf;
    table[0x38] = op_jr_conditional;
    table[0x39] = op_add_r16_r16;
    table[0x3A] = op_ld_r_hl_inc_dec;
    table[0x3B] = op_dec_r16;
    table[0x3C] = op_inc_r8;
    table[0x3D] = op_dec_r8;
    table[0x3E] = op_ld_r8_imm8;
    table[0x3F] = op_ccf;
    
    table[0x40] = op_ld_r8_r8;
    table[0x41] = op_ld_r8_r8; 
    table[0x42] = op_ld_r8_r8;
    table[0x43] = op_ld_r8_r8;
    table[0x44] = op_ld_r8_r8;
    table[0x45] = op_ld_r8_r8;
    table[0x46] = op_ld_r_mr;
    table[0x47] = op_ld_r8_r8;
    table[0x48] = op_ld_r8_r8;
    table[0x49] = op_ld_r8_r8;
    table[0x4A] = op_ld_r8_r8;
    table[0x4B] = op_ld_r8_r8;
    table[0x4C] = op_ld_r8_r8;
    table[0x4D] = op_ld_r8_r8;
    table[0x4E] = op_ld_r_mr;
    table[0x4F] = op_ld_r8_r8;
    
    table[0x50] = op_ld_r8_r8;
    table[0x51] = op_ld_r8_r8;
    table[0x52] = op_ld_r8_r8;
    table[0x53] = op_ld_r8_r8;
    table[0x54] = op_ld_r8_r8;
    table[0x55] = op_ld_r8_r8;
    table[0x56] = op_ld_r_mr;
    table[0x57] = op_ld_r8_r8;
    table[0x58] = op_ld_r8_r8;
    table[0x59] = op_ld_r8_r8;
    table[0x5A] = op_ld_r8_r8;
    table[0x5B] = op_ld_r8_r8;
    table[0x5C] = op_ld_r8_r8;
    table[0x5D] = op_ld_r8_r8;
    table[0x5E] = op_ld_r_mr;
    table[0x5F] = op_ld_r8_r8;
    
    table[0x60] = op_ld_r8_r8;
    table[0x61] = op_ld_r8_r8;
    table[0x62] = op_ld_r8_r8;
    table[0x63] = op_ld_r8_r8;
    table[0x64] = op_ld_r8_r8;
    table[0x65] = op_ld_r8_r8;
    table[0x66] = op_ld_r_mr;
    table[0x67] = op_ld_r8_r8;
    table[0x68] = op_ld_r8_r8;
    table[0x69] = op_ld_r8_r8;
    table[0x6A] = op_ld_r8_r8;
    table[0x6B] = op_ld_r8_r8;
    table[0x6C] = op_ld_r8_r8;
    table[0x6D] = op_ld_r8_r8;
    table[0x6E] = op_ld_r_mr;
    table[0x6F] = op_ld_r8_r8;

    table[0x70] = op_ld_mr_r;
    table[0x71] = op_ld_mr_r;
    table[0x72] = op_ld_mr_r;
    table[0x73] = op_ld_mr_r;
    table[0x74] = op_ld_mr_r;
    table[0x75] = op_ld_mr_r;
    table[0x76] = op_halt; // remember that this is not done, need to implement interrupts first. This instruction is important.
    table[0x77] = op_ld_mr_r;
    table[0x78] = op_ld_r8_r8;
    table[0x79] = op_ld_r8_r8;
    table[0x7A] = op_ld_r8_r8;
    table[0x7B] = op_ld_r8_r8;
    table[0x7C] = op_ld_r8_r8;
    table[0x7D] = op_ld_r8_r8;
    table[0x7E] = op_ld_r_mr;
    table[0x7F] = op_ld_r8_r8;
    
    table[0x80] = op_add;
    table[0x81] = op_add;
    table[0x82] = op_add;
    table[0x83] = op_add;
    table[0x84] = op_add;
    table[0x85] = op_add;
    table[0x86] = op_add;
    table[0x87] = op_add;
    table[0x88] = op_adc;
    table[0x89] = op_adc;
    table[0x8A] = op_adc;
    table[0x8B] = op_adc;
    table[0x8C] = op_adc;
    table[0x8D] = op_adc;
    table[0x8E] = op_adc;
    table[0x8F] = op_adc;
}