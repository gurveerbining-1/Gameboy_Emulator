#include "Instructions.h"
#include "CPU.h"
#include <bitset>

Instruction CB_invalidInstruction = {
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

void initCBInstructionTable(std::array<Instruction, 256>& table){
    table.fill(CB_invalidInstruction);
    table[0x00] = {
        mnemonic::IN_RLC,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_B,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };
    
    table[0x01] = {
        mnemonic::IN_RLC,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_C,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };
    
    table[0x02] = {
        mnemonic::IN_RLC,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_D,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x03] = {
        mnemonic::IN_RLC,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_E,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x04] = {
        mnemonic::IN_RLC,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_H,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x05] = {
        mnemonic::IN_RLC,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_L,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x06] = {
        mnemonic::IN_RLC,
        addrmode::AM_MR,
        operand_type::MEM_R,
        operand_type::NONE,
        reg_type::R_HL,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        16
    };

    table[0x07] = {
        mnemonic::IN_RLC,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_A,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x08] = {
        mnemonic::IN_RRC,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_B,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };
   
    table[0x09] = {
        mnemonic::IN_RRC,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_C,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x0A] = {
        mnemonic::IN_RRC,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_D,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x0B] = {
        mnemonic::IN_RRC,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_E,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x0C] = {
        mnemonic::IN_RRC,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_H,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x0D] = {
        mnemonic::IN_RRC,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_L,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x0E] = {
        mnemonic::IN_RRC,
        addrmode::AM_MR,
        operand_type::MEM_R,
        operand_type::NONE,
        reg_type::R_HL,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        16
    };
    
    table[0x0F] = {
        mnemonic::IN_RRC,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_A,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x10] = {
        mnemonic::IN_RL,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_B,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x11] = {
        mnemonic::IN_RL,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_C,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x12] = {
        mnemonic::IN_RL,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_D,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x13] = {
        mnemonic::IN_RL,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_E,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x14] = {
        mnemonic::IN_RL,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_H,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x15] = {
        mnemonic::IN_RL,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_L,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x16] = {
        mnemonic::IN_RL,
        addrmode::AM_MR,
        operand_type::MEM_R,
        operand_type::NONE,
        reg_type::R_HL,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        16
    };

    table[0x17] = {
        mnemonic::IN_RL,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_A,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x18] = {
        mnemonic::IN_RR,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_B,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x19] = {
        mnemonic::IN_RR,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_C,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x1A] = {
        mnemonic::IN_RR,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_D,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x1B] = {
        mnemonic::IN_RR,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_E,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x1C] = {
        mnemonic::IN_RR,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_H,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x1D] = {
        mnemonic::IN_RR,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_L,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x1E] = {       
        mnemonic::IN_RR,
        addrmode::AM_MR,
        operand_type::MEM_R,
        operand_type::NONE,
        reg_type::R_HL,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        16
    };
    
    table[0x1F] = {
        mnemonic::IN_RR,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_A,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x20] = {
        mnemonic::IN_SLA,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_B,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x21] = {
        mnemonic::IN_SLA,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_C,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x22] = {
        mnemonic::IN_SLA,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_D,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x23] = {
        mnemonic::IN_SLA,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_E,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x24] = {
        mnemonic::IN_SLA,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_H,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x25] = {
        mnemonic::IN_SLA,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_L,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x26] = {
        mnemonic::IN_SLA,
        addrmode::AM_MR,
        operand_type::MEM_R,
        operand_type::NONE,
        reg_type::R_HL,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        16
    };

    table[0x27] = {
        mnemonic::IN_SLA,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_A,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x28] = {
        mnemonic::IN_SRA,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_B,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x29] = {
        mnemonic::IN_SRA,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_C,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x2A] = {
        mnemonic::IN_SRA,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_D,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x2B] = {
        mnemonic::IN_SRA,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_E,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x2C] = {
        mnemonic::IN_SRA,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_H,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x2D] = {
        mnemonic::IN_SRA,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_L,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x2E] = {
        mnemonic::IN_SRA,
        addrmode::AM_MR,
        operand_type::MEM_R,
        operand_type::NONE,
        reg_type::R_HL,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        16
    };

    table[0x2F] = {
        mnemonic::IN_SRA,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_A,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x30] = {
        mnemonic::IN_SWAP,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_B,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x31] = {
        mnemonic::IN_SWAP,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_C,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x32] = {
        mnemonic::IN_SWAP,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_D,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x33] = {
        mnemonic::IN_SWAP,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_E,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x34] = {
        mnemonic::IN_SWAP,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_H,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x35] = {
        mnemonic::IN_SWAP,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_L,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x36] = {
        mnemonic::IN_SWAP,
        addrmode::AM_MR,
        operand_type::MEM_R,
        operand_type::NONE,
        reg_type::R_HL,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        16
    };

    table[0x37] = {
        mnemonic::IN_SWAP,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_A,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x38] = {
        mnemonic::IN_SRL,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_B,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x39] = {
        mnemonic::IN_SRL,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_C,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x3A] = {
        mnemonic::IN_SRL,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_D,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x3B] = {
        mnemonic::IN_SRL,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_E,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x3C] = {
        mnemonic::IN_SRL,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_H,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x3D] = {
        mnemonic::IN_SRL,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_L,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x3E] = {
        mnemonic::IN_SRL,
        addrmode::AM_MR,
        operand_type::MEM_R,
        operand_type::NONE,
        reg_type::R_HL,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        16
    };

    table[0x3F] = {
        mnemonic::IN_SRL,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_A,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x40] = {
        mnemonic::IN_BIT,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_B,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x41] = {
        mnemonic::IN_BIT,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_C,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x42] = {
        mnemonic::IN_BIT,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_D,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x43] = {
        mnemonic::IN_BIT,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_E,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x44] = {
        mnemonic::IN_BIT,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_H,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x45] = {
        mnemonic::IN_BIT,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_L,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x46] = {
        mnemonic::IN_BIT,
        addrmode::AM_MR,
        operand_type::MEM_R,
        operand_type::NONE,
        reg_type::R_HL,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        12
    };

    table[0x47] = {
        mnemonic::IN_BIT,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_A,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x48] = {
        mnemonic::IN_BIT,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_B,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x49] = {
        mnemonic::IN_BIT,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_C,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x4A] = {
        mnemonic::IN_BIT,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_D,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x4B] = {
        mnemonic::IN_BIT,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_E,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x4C] = {
        mnemonic::IN_BIT,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_H,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x4D] = {
        mnemonic::IN_BIT,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_L,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x4E] = {
        mnemonic::IN_BIT,
        addrmode::AM_MR,
        operand_type::MEM_R,
        operand_type::NONE,
        reg_type::R_HL,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        12
    };

    table[0x4F] = {
        mnemonic::IN_BIT,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_A,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x50] = {
        mnemonic::IN_BIT,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_B,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x51] = {
        mnemonic::IN_BIT,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_C,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x52] = {
        mnemonic::IN_BIT,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_D,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x53] = {
        mnemonic::IN_BIT,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_E,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x54] = {
        mnemonic::IN_BIT,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_H,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x55] = {
        mnemonic::IN_BIT,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_L,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x56] = {
        mnemonic::IN_BIT,
        addrmode::AM_MR,
        operand_type::MEM_R,
        operand_type::NONE,
        reg_type::R_HL,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        12
    };

    table[0x57] = {
        mnemonic::IN_BIT,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_A,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x58] = {
        mnemonic::IN_BIT,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_B,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x59] = {
        mnemonic::IN_BIT,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_C,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x5A] = {
        mnemonic::IN_BIT,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_D,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x5B] = {
        mnemonic::IN_BIT,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_E,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x5C] = {
        mnemonic::IN_BIT,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_H,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x5D] = {
        mnemonic::IN_BIT,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_L,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x5E] = {
        mnemonic::IN_BIT,
        addrmode::AM_MR,
        operand_type::MEM_R,
        operand_type::NONE,
        reg_type::R_HL,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        12
    };

    table[0x5F] = {
        mnemonic::IN_BIT,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_A,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x60] = {
        mnemonic::IN_BIT,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_B,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x61] = {
        mnemonic::IN_BIT,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_C,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x62] = {
        mnemonic::IN_BIT,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_D,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x63] = {
        mnemonic::IN_BIT,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_E,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x64] = {
        mnemonic::IN_BIT,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_H,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x65] = {
        mnemonic::IN_BIT,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_L,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x66] = {
        mnemonic::IN_BIT,
        addrmode::AM_MR,
        operand_type::MEM_R,
        operand_type::NONE,
        reg_type::R_HL,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        12
    };

    table[0x67] = {
        mnemonic::IN_BIT,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_A,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x68] = {
        mnemonic::IN_BIT,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_B,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x69] = {
        mnemonic::IN_BIT,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_C,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x6A] = {
        mnemonic::IN_BIT,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_D,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x6B] = {
        mnemonic::IN_BIT,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_E,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x6C] = {
        mnemonic::IN_BIT,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_H,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x6D] = {
        mnemonic::IN_BIT,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_L,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x6E] = {
        mnemonic::IN_BIT,
        addrmode::AM_MR,
        operand_type::MEM_R,
        operand_type::NONE,
        reg_type::R_HL,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        12
    };

    table[0x6F] = {
        mnemonic::IN_BIT,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_A,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x70] = {
        mnemonic::IN_BIT,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_B,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x71] = {
        mnemonic::IN_BIT,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_C,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x72] = {
        mnemonic::IN_BIT,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_D,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x73] = {
        mnemonic::IN_BIT,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_E,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x74] = {
        mnemonic::IN_BIT,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_H,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x75] = {
        mnemonic::IN_BIT,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_L,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x76] = {
        mnemonic::IN_BIT,
        addrmode::AM_MR,
        operand_type::MEM_R,
        operand_type::NONE,
        reg_type::R_HL,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        12
    };

    table[0x77] = {
        mnemonic::IN_BIT,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_A,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x78] = {
        mnemonic::IN_BIT,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_B,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x79] = {
        mnemonic::IN_BIT,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_C,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x7A] = {
        mnemonic::IN_BIT,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_D,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x7B] = {
        mnemonic::IN_BIT,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_E,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x7C] = {
        mnemonic::IN_BIT,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_H,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x7D] = {
        mnemonic::IN_BIT,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_L,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x7E] = {
        mnemonic::IN_BIT,
        addrmode::AM_MR,
        operand_type::MEM_R,
        operand_type::NONE,
        reg_type::R_HL,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        12
    };

    table[0x7F] = {
        mnemonic::IN_BIT,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_A,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x80] = {
        mnemonic::IN_RES,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_B,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x81] = {
        mnemonic::IN_RES,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_C,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x82] = {
        mnemonic::IN_RES,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_D,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x83] = {
        mnemonic::IN_RES,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_E,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x84] = {
        mnemonic::IN_RES,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_H,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x85] = {
        mnemonic::IN_RES,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_L,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x86] = {
        mnemonic::IN_RES,
        addrmode::AM_MR,
        operand_type::MEM_R,
        operand_type::NONE,
        reg_type::R_HL,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        16
    };

    table[0x87] = {
        mnemonic::IN_RES,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_A,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x88] = {
        mnemonic::IN_RES,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_B,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x89] = {
        mnemonic::IN_RES,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_C,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x8A] = {
        mnemonic::IN_RES,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_D,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x8B] = {
        mnemonic::IN_RES,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_E,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x8C] = {
        mnemonic::IN_RES,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_H,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x8D] = {
        mnemonic::IN_RES,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_L,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x8E] = {
        mnemonic::IN_RES,
        addrmode::AM_MR,
        operand_type::MEM_R,
        operand_type::NONE,
        reg_type::R_HL,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        16
    };

    table[0x8F] = {
        mnemonic::IN_RES,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_A,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x90] = {
        mnemonic::IN_RES,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_B,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x91] = {
        mnemonic::IN_RES,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_C,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x92] = {
        mnemonic::IN_RES,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_D,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x93] = {
        mnemonic::IN_RES,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_E,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x94] = {
        mnemonic::IN_RES,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_H,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x95] = {
        mnemonic::IN_RES,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_L,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x96] = {
        mnemonic::IN_RES,
        addrmode::AM_MR,
        operand_type::MEM_R,
        operand_type::NONE,
        reg_type::R_HL,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        16
    };

    table[0x97] = {
        mnemonic::IN_RES,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_A,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x98] = {
        mnemonic::IN_RES,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_B,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x99] = {
        mnemonic::IN_RES,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_C,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x9A] = {
        mnemonic::IN_RES,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_D,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x9B] = {
        mnemonic::IN_RES,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_E,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x9C] = {
        mnemonic::IN_RES,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_H,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x9D] = {
        mnemonic::IN_RES,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_L,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0x9E] = {
        mnemonic::IN_RES,
        addrmode::AM_MR,
        operand_type::MEM_R,
        operand_type::NONE,
        reg_type::R_HL,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        16
    };

    table[0x9F] = {
        mnemonic::IN_RES,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_A,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0xA0] = {
        mnemonic::IN_RES,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_B,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0xA1] = {
        mnemonic::IN_RES,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_C,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0xA2] = {
        mnemonic::IN_RES,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_D,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0xA3] = {
        mnemonic::IN_RES,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_E,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0xA4] = {
        mnemonic::IN_RES,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_H,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0xA5] = {
        mnemonic::IN_RES,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_L,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0xA6] = {
        mnemonic::IN_RES,
        addrmode::AM_MR,
        operand_type::MEM_R,
        operand_type::NONE,
        reg_type::R_HL,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        16
    };

    table[0xA7] = {
        mnemonic::IN_RES,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_A,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0xA8] = {
        mnemonic::IN_RES,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_B,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0xA9] = {
        mnemonic::IN_RES,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_C,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0xAA] = {
        mnemonic::IN_RES,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_D,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0xAB] = {
        mnemonic::IN_RES,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_E,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0xAC] = {
        mnemonic::IN_RES,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_H,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0xAD] = {
        mnemonic::IN_RES,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_L,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0xAE] = {
        mnemonic::IN_RES,
        addrmode::AM_MR,
        operand_type::MEM_R,
        operand_type::NONE,
        reg_type::R_HL,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        16
    };

    table[0xAF] = {
        mnemonic::IN_RES,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_A,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0xB0] = {
        mnemonic::IN_RES,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_B,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0xB1] = {
        mnemonic::IN_RES,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_C,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0xB2] = {
        mnemonic::IN_RES,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_D,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0xB3] = {
        mnemonic::IN_RES,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_E,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0xB4] = {
        mnemonic::IN_RES,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_H,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0xB5] = {
        mnemonic::IN_RES,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_L,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0xB6] = {
        mnemonic::IN_RES,
        addrmode::AM_MR,
        operand_type::MEM_R,
        operand_type::NONE,
        reg_type::R_HL,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        16
    };

    table[0xB7] = {
        mnemonic::IN_RES,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_A,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0xB8] = {
        mnemonic::IN_RES,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_B,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0xB9] = {
        mnemonic::IN_RES,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_C,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0xBA] = {
        mnemonic::IN_RES,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_D,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0xBB] = {
        mnemonic::IN_RES,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_E,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0xBC] = {
        mnemonic::IN_RES,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_H,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0xBD] = {
        mnemonic::IN_RES,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_L,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0xBE] = {
        mnemonic::IN_RES,
        addrmode::AM_MR,
        operand_type::MEM_R,
        operand_type::NONE,
        reg_type::R_HL,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        16
    };

    table[0xBF] = {
        mnemonic::IN_RES,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_A,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };
    
    table[0xC0] = {
        mnemonic::IN_SET,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_B,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0xC1] = {
        mnemonic::IN_SET,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_C,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0xC2] = {
        mnemonic::IN_SET,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_D,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0xC3] = {
        mnemonic::IN_SET,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_E,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0xC4] = {
        mnemonic::IN_SET,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_H,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0xC5] = {
        mnemonic::IN_SET,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_L,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0xC6] = {
        mnemonic::IN_SET,
        addrmode::AM_MR,
        operand_type::MEM_R,
        operand_type::NONE,
        reg_type::R_HL,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        16
    };

    table[0xC7] = {
        mnemonic::IN_SET,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_A,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0xC8] = {
        mnemonic::IN_SET,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_B,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0xC9] = {
        mnemonic::IN_SET,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_C,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0xCA] = {
        mnemonic::IN_SET,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_D,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0xCB] = {
        mnemonic::IN_SET,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_E,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0xCC] = {
        mnemonic::IN_SET,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_H,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0xCD] = {
        mnemonic::IN_SET,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_L,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0xCE] = {
        mnemonic::IN_SET,
        addrmode::AM_MR,
        operand_type::MEM_R,
        operand_type::NONE,
        reg_type::R_HL,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        16
    };

    table[0xCF] = {
        mnemonic::IN_SET,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_A,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0xD0] = {
        mnemonic::IN_SET,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_B,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0xD1] = {
        mnemonic::IN_SET,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_C,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0xD2] = {
        mnemonic::IN_SET,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_D,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0xD3] = {
        mnemonic::IN_SET,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_E,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0xD4] = {
        mnemonic::IN_SET,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_H,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0xD5] = {
        mnemonic::IN_SET,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_L,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0xD6] = {
        mnemonic::IN_SET,
        addrmode::AM_MR,
        operand_type::MEM_R,
        operand_type::NONE,
        reg_type::R_HL,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        16
    };

    table[0xD7] = {
        mnemonic::IN_SET,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_A,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0xD8] = {
        mnemonic::IN_SET,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_B,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0xD9] = {
        mnemonic::IN_SET,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_C,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0xDA] = {
        mnemonic::IN_SET,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_D,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0xDB] = {
        mnemonic::IN_SET,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_E,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0xDC] = {
        mnemonic::IN_SET,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_H,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0xDD] = {
        mnemonic::IN_SET,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_L,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0xDE] = {
        mnemonic::IN_SET,
        addrmode::AM_MR,
        operand_type::MEM_R,
        operand_type::NONE,
        reg_type::R_HL,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        16
    };

    table[0xDF] = {
        mnemonic::IN_SET,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_A,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0xE0] = {
        mnemonic::IN_SET,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_B,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0xE1] = {
        mnemonic::IN_SET,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_C,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0xE2] = {
        mnemonic::IN_SET,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_D,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0xE3] = {
        mnemonic::IN_SET,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_E,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0xE4] = {
        mnemonic::IN_SET,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_H,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0xE5] = {
        mnemonic::IN_SET,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_L,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0xE6] = {
        mnemonic::IN_SET,
        addrmode::AM_MR,
        operand_type::MEM_R,
        operand_type::NONE,
        reg_type::R_HL,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        16
    };

    table[0xE7] = {
        mnemonic::IN_SET,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_A,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0xE8] = {
        mnemonic::IN_SET,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_B,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0xE9] = {
        mnemonic::IN_SET,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_C,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0xEA] = {
        mnemonic::IN_SET,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_D,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0xEB] = {
        mnemonic::IN_SET,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_E,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0xEC] = {
        mnemonic::IN_SET,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_H,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0xED] = {
        mnemonic::IN_SET,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_L,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0xEE] = {
        mnemonic::IN_SET,
        addrmode::AM_MR,
        operand_type::MEM_R,
        operand_type::NONE,
        reg_type::R_HL,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        16
    };

    table[0xEF] = {
        mnemonic::IN_SET,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_A,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0xF0] = {
        mnemonic::IN_SET,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_B,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0xF1] = {
        mnemonic::IN_SET,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_C,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0xF2] = {
        mnemonic::IN_SET,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_D,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0xF3] = {
        mnemonic::IN_SET,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_E,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0xF4] = {
        mnemonic::IN_SET,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_H,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0xF5] = {
        mnemonic::IN_SET,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_L,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0xF6] = {
        mnemonic::IN_SET,
        addrmode::AM_MR,
        operand_type::MEM_R,
        operand_type::NONE,
        reg_type::R_HL,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        16
    };

    table[0xF7] = {
        mnemonic::IN_SET,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_A,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0xF8] = {
        mnemonic::IN_SET,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_B,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0xF9] = {
        mnemonic::IN_SET,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_C,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0xFA] = {
        mnemonic::IN_SET,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_D,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0xFB] = {
        mnemonic::IN_SET,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_E,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0xFC] = {
        mnemonic::IN_SET,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_H,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0xFD] = {
        mnemonic::IN_SET,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_L,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };

    table[0xFE] = {
        mnemonic::IN_SET,
        addrmode::AM_MR,
        operand_type::MEM_R,
        operand_type::NONE,
        reg_type::R_HL,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        16
    };

    table[0xFF] = {
        mnemonic::IN_SET,
        addrmode::AM_R,
        operand_type::R8,
        operand_type::NONE,
        reg_type::R_A,
        reg_type::R_NONE,
        condition_code::CD_NONE,
        2,
        8
    };
}

void op_cb_unimplemented(CPU& cpu, const Instruction& inst)
{
    printf("Unimplemented opcode: 0xCB%02X\n", cpu.current_opcode);
}

void op_rlc(CPU& cpu, const Instruction& inst)
{   
    uint8_t original = 0;

    if(inst.address_mode == addrmode::AM_R){
        original = cpu.getReg8(inst.reg_1);
        uint8_t bit = (original >> 7) & 1; // isolate the 7th bit
        uint8_t rotated = (original << 1) | bit; // shift the bits left by one and set bit 0 equal to the 7th bit
        cpu.setReg8(inst.reg_1, rotated);

        cpu.setFlag(Flag::Z, rotated == 0);
        cpu.setFlag(Flag::N, false);
        cpu.setFlag(Flag::H, false);
        cpu.setFlag(Flag::C, bit); // set the carry flag to the 7th bit
    }
    else if(inst.address_mode == addrmode::AM_MR){
        uint16_t addr = cpu.getReg16(inst.reg_1);
        original = cpu.read(addr);
        uint8_t bit = (original >> 7) & 1; // isolate the 7th bit
        uint8_t rotated = (original << 1) | bit; // shift the bits left by one and set bit 0 equal to the 7th bit
        cpu.write(addr, rotated);

        cpu.setFlag(Flag::Z, rotated == 0);
        cpu.setFlag(Flag::N, false);
        cpu.setFlag(Flag::H, false);
        cpu.setFlag(Flag::C, bit); // set the carry flag to the 7th bit
    }
}

void op_rrc(CPU& cpu, const Instruction& inst)
{   
    uint8_t original = 0;

    if(inst.address_mode == addrmode::AM_R){
        original = cpu.getReg8(inst.reg_1);
        uint8_t bit = (original) & 0x01; // old bit 0
        uint8_t rotated = (original >> 1) | (bit << 7); // shift bits right by one and put old bit 0 into bit 7
        cpu.setReg8(inst.reg_1, rotated);

        cpu.setFlag(Flag::Z, rotated == 0);
        cpu.setFlag(Flag::N, false);
        cpu.setFlag(Flag::H, false);
        cpu.setFlag(Flag::C, bit); // set the carry flag to the 0th bit
    }
    else if(inst.address_mode == addrmode::AM_MR){
        uint16_t addr = cpu.getReg16(inst.reg_1);
        original = cpu.read(addr);
        uint8_t bit = (original) & 0x01; // old bit 0
        uint8_t rotated = (original >> 1) | (bit << 7); // shift bits right by one and put old bit 0 into bit 7
        cpu.write(addr, rotated);

        cpu.setFlag(Flag::Z, rotated == 0);
        cpu.setFlag(Flag::N, false);
        cpu.setFlag(Flag::H, false);
        cpu.setFlag(Flag::C, bit); // set the carry flag to the 0th bit
    }
}

void op_rl(CPU& cpu, const Instruction& inst){
    uint8_t original = 0;
    if(inst.address_mode == addrmode::AM_R){
        original = cpu.getReg8(inst.reg_1);
        uint8_t old_carry = cpu.getFlag(Flag::C); 
        uint8_t new_carry = (original >> 7) & 1; 
        uint8_t rotated = (original << 1) | old_carry;
        
        cpu.setReg8(inst.reg_1, rotated);
        cpu.setFlag(Flag::Z, rotated == 0);
        cpu.setFlag(Flag::N, false);
        cpu.setFlag(Flag::H, false);
        cpu.setFlag(Flag::C, new_carry); 
    }
    else if(inst.address_mode == addrmode::AM_MR){
        uint16_t addr = cpu.getReg16(inst.reg_1);
        original = cpu.read(addr);
        uint8_t old_carry = cpu.getFlag(Flag::C); 
        uint8_t new_carry = (original >> 7) & 1; 
        uint8_t rotated = (original << 1) | old_carry;
        
        cpu.write(addr, rotated);
        cpu.setFlag(Flag::Z, rotated == 0);
        cpu.setFlag(Flag::N, false);
        cpu.setFlag(Flag::H, false);
        cpu.setFlag(Flag::C, new_carry); 
    }
}

void op_rr(CPU& cpu, const Instruction& inst){
    uint8_t original = 0;
    if(inst.address_mode == addrmode::AM_R){
        original = cpu.getReg8(inst.reg_1);
        uint8_t old_carry = cpu.getFlag(Flag::C);
        uint8_t new_carry = (original) & 1;
        uint8_t rotated = (original >> 1) | (old_carry << 7);
        
        cpu.setReg8(inst.reg_1, rotated);
        cpu.setFlag(Flag::Z, rotated == 0);
        cpu.setFlag(Flag::N, false);
        cpu.setFlag(Flag::H, false);
        cpu.setFlag(Flag::C, new_carry); 
    }
    else if(inst.address_mode == addrmode::AM_MR){
        uint16_t addr = cpu.getReg16(inst.reg_1);
        original = cpu.read(addr);
        uint8_t old_carry = cpu.getFlag(Flag::C);
        uint8_t new_carry = (original) & 1;
        uint8_t rotated = (original >> 1) | (old_carry << 7);
        
        cpu.write(addr, rotated);
        cpu.setFlag(Flag::Z, rotated == 0);
        cpu.setFlag(Flag::N, false);
        cpu.setFlag(Flag::H, false);
        cpu.setFlag(Flag::C, new_carry); 
    }
}

void op_sla(CPU& cpu, const Instruction& inst){
    uint8_t original = 0;
    if(inst.address_mode == addrmode::AM_R){
        original = cpu.getReg8(inst.reg_1);
        uint8_t new_carry = (original >> 7) & 1; // isolate 7th bit
        uint8_t shifted = (original << 1); 
        
        cpu.setReg8(inst.reg_1, shifted);
        cpu.setFlag(Flag::Z, shifted == 0);
        cpu.setFlag(Flag::N, false);
        cpu.setFlag(Flag::H, false);
        cpu.setFlag(Flag::C, new_carry); 
    }
    else if(inst.address_mode == addrmode::AM_MR){
        uint16_t addr = cpu.getReg16(inst.reg_1);
        original = cpu.read(addr);
        uint8_t new_carry = (original >> 7) & 1; // isolate 7th bit
        uint8_t shifted = (original << 1); 
        
        cpu.write(addr, shifted);
        cpu.setFlag(Flag::Z, shifted == 0);
        cpu.setFlag(Flag::N, false);
        cpu.setFlag(Flag::H, false);
        cpu.setFlag(Flag::C, new_carry); 
    }
}

void op_sra(CPU& cpu, const Instruction& inst){
    uint8_t original = 0;
    if(inst.address_mode == addrmode::AM_R){
        original = cpu.getReg8(inst.reg_1);
        uint8_t new_carry = (original) & 1; // isolate 0th bit
        uint8_t msb = original & 0x80;  // preserve bit 7
        uint8_t shifted = (original >> 1) | msb; 
        
        cpu.setReg8(inst.reg_1, shifted);
        cpu.setFlag(Flag::Z, shifted == 0);
        cpu.setFlag(Flag::N, false);
        cpu.setFlag(Flag::H, false);
        cpu.setFlag(Flag::C, new_carry); 
    }
    else if(inst.address_mode == addrmode::AM_MR){
        uint16_t addr = cpu.getReg16(inst.reg_1);
        original = cpu.read(addr);
        uint8_t new_carry = (original) & 1; // isolate 0th bit
        uint8_t msb = original & 0x80;  // preserve bit 7
        uint8_t shifted = (original >> 1) | msb; 

        cpu.write(addr, shifted);
        cpu.setFlag(Flag::Z, shifted == 0);
        cpu.setFlag(Flag::N, false);
        cpu.setFlag(Flag::H, false);
        cpu.setFlag(Flag::C, new_carry); 
    }
}

void op_swap(CPU& cpu, const Instruction& inst){
    uint8_t original = 0;
    if(inst.address_mode == addrmode::AM_R){
        original = cpu.getReg8(inst.reg_1);
        uint8_t swapped = (original >> 4) | (original << 4); 
        
        cpu.setReg8(inst.reg_1, swapped);
        cpu.setFlag(Flag::Z, swapped == 0);
        cpu.setFlag(Flag::N, false);
        cpu.setFlag(Flag::H, false);
        cpu.setFlag(Flag::C, false); 
    }
    else if(inst.address_mode == addrmode::AM_MR){
        uint16_t addr = cpu.getReg16(inst.reg_1);
        original = cpu.read(addr);
        uint8_t swapped = (original >> 4) | (original << 4); 
        
        cpu.write(addr, swapped);
        cpu.setFlag(Flag::Z, swapped == 0);
        cpu.setFlag(Flag::N, false);
        cpu.setFlag(Flag::H, false);
        cpu.setFlag(Flag::C, false);   
    }
}

void op_srl(CPU& cpu, const Instruction& inst){
    uint8_t original = 0;
    if(inst.address_mode == addrmode::AM_R){
        original = cpu.getReg8(inst.reg_1);
        uint8_t new_carry = (original) & 1; // isolate 0th bit
        uint8_t shifted = (original >> 1); 
        
        cpu.setReg8(inst.reg_1, shifted);
        cpu.setFlag(Flag::Z, shifted == 0);
        cpu.setFlag(Flag::N, false);
        cpu.setFlag(Flag::H, false);
        cpu.setFlag(Flag::C, new_carry); 
    }
    else if(inst.address_mode == addrmode::AM_MR){
        uint16_t addr = cpu.getReg16(inst.reg_1);
        original = cpu.read(addr);
        uint8_t new_carry = (original) & 1; // isolate 0th bit
        uint8_t shifted = (original >> 1); 

        cpu.write(addr, shifted);
        cpu.setFlag(Flag::Z, shifted == 0);
        cpu.setFlag(Flag::N, false);
        cpu.setFlag(Flag::H, false);
        cpu.setFlag(Flag::C, new_carry); 
    }
}

void op_bit(CPU& cpu, const Instruction& inst){
    uint8_t value = 0;

    if(inst.address_mode == addrmode::AM_R){
        value = cpu.getReg8(inst.reg_1);
    }
    else if(inst.address_mode == addrmode::AM_MR){ 
        value = cpu.read(cpu.getReg16(inst.reg_1));
    }

    uint8_t bit = (cpu.current_opcode >> 3) & 0x07; // which BIT operation? this isolates the bit and tells us

    cpu.setFlag(Flag::Z, ((value >> bit) & 1) == 0); // Is the bit at position bit inside value equal to 0?
    cpu.setFlag(Flag::N, false);
    cpu.setFlag(Flag::H, true);
}

void op_res(CPU& cpu, const Instruction& inst){
    uint8_t value = 0;

    if(inst.address_mode == addrmode::AM_R){
        value = cpu.getReg8(inst.reg_1);
        uint8_t bit = (cpu.current_opcode >> 3) & 0x07; // which BIT operation? this isolates the bit and tells us
        value &= ~(1 << bit); // reset the bit
        cpu.setReg8(inst.reg_1, value); // write the value back
    }
    else if(inst.address_mode == addrmode::AM_MR){ 
        uint16_t addr = cpu.getReg16(inst.reg_1);
        value = cpu.read(addr);
        uint8_t bit = (cpu.current_opcode >> 3) & 0x07; // which BIT operation? this isolates the bit and tells us
        value &= ~(1 << bit); // reset the bit
        cpu.write(addr, value);
    }
}

void op_set(CPU& cpu, const Instruction& inst){
    uint8_t value = 0;

    if(inst.address_mode == addrmode::AM_R){
        value = cpu.getReg8(inst.reg_1);
        uint8_t bit = (cpu.current_opcode >> 3) & 0x07; // which BIT operation? this isolates the bit and tells us
        value |= (1 << bit); // set the bit
        cpu.setReg8(inst.reg_1, value); // write the value back
    }
    else if(inst.address_mode == addrmode::AM_MR){ 
        uint16_t addr = cpu.getReg16(inst.reg_1);
        value = cpu.read(addr);
        uint8_t bit = (cpu.current_opcode >> 3) & 0x07; // which BIT operation? this isolates the bit and tells us
        value |= (1 << bit); // set the bit
        cpu.write(addr, value);
    }
}

void initCBHandlerTable(std::array<Handler, 256>& table) {
    table.fill(op_cb_unimplemented);
    table[0x00] = op_rlc;
    table[0x01] = op_rlc;
    table[0x02] = op_rlc;
    table[0x03] = op_rlc;
    table[0x04] = op_rlc;
    table[0x05] = op_rlc;
    table[0x06] = op_rlc;
    table[0x07] = op_rlc;
    table[0x08] = op_rrc;
    table[0x09] = op_rrc;
    table[0x0A] = op_rrc;
    table[0x0B] = op_rrc;
    table[0x0C] = op_rrc;
    table[0x0D] = op_rrc;
    table[0x0E] = op_rrc;
    table[0x0F] = op_rrc;

    table[0x10] = op_rl;
    table[0x11] = op_rl;
    table[0x12] = op_rl;
    table[0x13] = op_rl;
    table[0x14] = op_rl;
    table[0x15] = op_rl;
    table[0x16] = op_rl;
    table[0x17] = op_rl;
    table[0x18] = op_rr;
    table[0x19] = op_rr;
    table[0x1A] = op_rr;
    table[0x1B] = op_rr;
    table[0x1C] = op_rr;
    table[0x1D] = op_rr;
    table[0x1E] = op_rr;
    table[0x1F] = op_rr;

    table[0x20] = op_sla;
    table[0x21] = op_sla;
    table[0x22] = op_sla;
    table[0x23] = op_sla;
    table[0x24] = op_sla;
    table[0x25] = op_sla;
    table[0x26] = op_sla;
    table[0x27] = op_sla; 
    table[0x28] = op_sra; 
    table[0x29] = op_sra; 
    table[0x2A] = op_sra; 
    table[0x2B] = op_sra; 
    table[0x2C] = op_sra; 
    table[0x2D] = op_sra; 
    table[0x2E] = op_sra; 
    table[0x2F] = op_sra; 

    table[0x30] = op_swap;
    table[0x31] = op_swap;
    table[0x32] = op_swap;
    table[0x33] = op_swap;
    table[0x34] = op_swap;
    table[0x35] = op_swap;
    table[0x36] = op_swap;
    table[0x37] = op_swap;
    table[0x38] = op_srl;
    table[0x39] = op_srl;
    table[0x3A] = op_srl;
    table[0x3B] = op_srl;
    table[0x3C] = op_srl;
    table[0x3D] = op_srl;
    table[0x3E] = op_srl;
    table[0x3F] = op_srl;

    table[0x40] = op_bit;
    table[0x41] = op_bit;
    table[0x42] = op_bit;
    table[0x43] = op_bit;
    table[0x44] = op_bit;
    table[0x45] = op_bit;
    table[0x46] = op_bit;
    table[0x47] = op_bit;
    table[0x48] = op_bit;
    table[0x49] = op_bit;
    table[0x4A] = op_bit;
    table[0x4B] = op_bit;
    table[0x4C] = op_bit;
    table[0x4D] = op_bit;
    table[0x4E] = op_bit;
    table[0x4F] = op_bit;
    
    table[0x50] = op_bit;
    table[0x51] = op_bit;
    table[0x52] = op_bit;
    table[0x53] = op_bit;
    table[0x54] = op_bit;
    table[0x55] = op_bit;
    table[0x56] = op_bit;
    table[0x57] = op_bit;
    table[0x58] = op_bit;
    table[0x59] = op_bit;
    table[0x5A] = op_bit;
    table[0x5B] = op_bit;
    table[0x5C] = op_bit;
    table[0x5D] = op_bit;
    table[0x5E] = op_bit;
    table[0x5F] = op_bit;
    
    table[0x60] = op_bit;
    table[0x61] = op_bit;
    table[0x62] = op_bit;
    table[0x63] = op_bit;
    table[0x64] = op_bit;
    table[0x65] = op_bit;
    table[0x66] = op_bit;
    table[0x67] = op_bit;
    table[0x68] = op_bit;
    table[0x69] = op_bit;
    table[0x6A] = op_bit;
    table[0x6B] = op_bit;
    table[0x6C] = op_bit;
    table[0x6D] = op_bit;
    table[0x6E] = op_bit;
    table[0x6F] = op_bit;

    table[0x70] = op_bit;
    table[0x71] = op_bit;
    table[0x72] = op_bit;
    table[0x73] = op_bit;
    table[0x74] = op_bit;
    table[0x75] = op_bit;
    table[0x76] = op_bit;
    table[0x77] = op_bit;
    table[0x78] = op_bit;
    table[0x79] = op_bit;
    table[0x7A] = op_bit;
    table[0x7B] = op_bit;
    table[0x7C] = op_bit;
    table[0x7D] = op_bit;
    table[0x7E] = op_bit;
    table[0x7F] = op_bit;

    table[0x80] = op_res;
    table[0x81] = op_res;
    table[0x82] = op_res;
    table[0x83] = op_res;
    table[0x84] = op_res;
    table[0x85] = op_res;
    table[0x86] = op_res;
    table[0x87] = op_res;
    table[0x88] = op_res;
    table[0x89] = op_res;
    table[0x8A] = op_res;
    table[0x8B] = op_res;
    table[0x8C] = op_res;
    table[0x8D] = op_res;
    table[0x8E] = op_res;
    table[0x8F] = op_res;

    table[0x90] = op_res;
    table[0x91] = op_res;
    table[0x92] = op_res;
    table[0x93] = op_res;
    table[0x94] = op_res;
    table[0x95] = op_res;
    table[0x96] = op_res;
    table[0x97] = op_res;
    table[0x98] = op_res;
    table[0x99] = op_res;
    table[0x9A] = op_res;
    table[0x9B] = op_res;
    table[0x9C] = op_res;
    table[0x9D] = op_res;
    table[0x9E] = op_res;
    table[0x9F] = op_res;

    table[0xA0] = op_res;
    table[0xA1] = op_res;
    table[0xA2] = op_res;
    table[0xA3] = op_res;
    table[0xA4] = op_res;
    table[0xA5] = op_res;
    table[0xA6] = op_res;
    table[0xA7] = op_res;
    table[0xA8] = op_res;
    table[0xA9] = op_res;
    table[0xAA] = op_res;
    table[0xAB] = op_res;
    table[0xAC] = op_res;
    table[0xAD] = op_res;
    table[0xAE] = op_res;
    table[0xAF] = op_res;

    table[0xB0] = op_res;
    table[0xB1] = op_res;
    table[0xB2] = op_res;
    table[0xB3] = op_res;
    table[0xB4] = op_res;
    table[0xB5] = op_res;
    table[0xB6] = op_res;
    table[0xB7] = op_res;
    table[0xB8] = op_res;
    table[0xB9] = op_res;
    table[0xBA] = op_res;
    table[0xBB] = op_res;
    table[0xBC] = op_res;
    table[0xBD] = op_res;
    table[0xBE] = op_res;
    table[0xBF] = op_res;

    table[0xC0] = op_set;
    table[0xC1] = op_set;
    table[0xC2] = op_set;
    table[0xC3] = op_set;
    table[0xC4] = op_set;
    table[0xC5] = op_set;
    table[0xC6] = op_set;
    table[0xC7] = op_set;
    table[0xC8] = op_set;
    table[0xC9] = op_set;
    table[0xCA] = op_set;
    table[0xCB] = op_set;
    table[0xCC] = op_set;
    table[0xCD] = op_set;
    table[0xCE] = op_set;
    table[0xCF] = op_set;

    table[0xD0] = op_set;
    table[0xD1] = op_set;
    table[0xD2] = op_set;
    table[0xD3] = op_set;
    table[0xD4] = op_set;
    table[0xD5] = op_set;
    table[0xD6] = op_set;
    table[0xD7] = op_set;
    table[0xD8] = op_set;
    table[0xD9] = op_set;
    table[0xDA] = op_set;
    table[0xDB] = op_set;
    table[0xDC] = op_set;
    table[0xDD] = op_set;
    table[0xDE] = op_set;
    table[0xDF] = op_set;

    table[0xE0] = op_set;
    table[0xE1] = op_set;
    table[0xE2] = op_set;
    table[0xE3] = op_set;
    table[0xE4] = op_set;
    table[0xE5] = op_set;
    table[0xE6] = op_set;
    table[0xE7] = op_set;
    table[0xE8] = op_set;
    table[0xE9] = op_set;
    table[0xEA] = op_set;
    table[0xEB] = op_set;
    table[0xEC] = op_set;
    table[0xED] = op_set;
    table[0xEE] = op_set;
    table[0xEF] = op_set;

    table[0xF0] = op_set;
    table[0xF1] = op_set;
    table[0xF2] = op_set;
    table[0xF3] = op_set;
    table[0xF4] = op_set;
    table[0xF5] = op_set;
    table[0xF6] = op_set;
    table[0xF7] = op_set;
    table[0xF8] = op_set;
    table[0xF9] = op_set;
    table[0xFA] = op_set;
    table[0xFB] = op_set;
    table[0xFC] = op_set;
    table[0xFD] = op_set;
    table[0xFE] = op_set;
    table[0xFF] = op_set;
}