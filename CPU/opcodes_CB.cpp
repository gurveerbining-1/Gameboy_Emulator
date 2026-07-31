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
}

void op_cb_unimplemented(CPU& cpu, const Instruction& inst)
{
    printf("Unimplemented opcode: 0xCB%02X\n", cpu.current_opcode);
}

void op_rlc(CPU& cpu, const Instruction& inst)
{   
    uint8_t original;

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
    uint8_t original;

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
    uint8_t original;
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
    uint8_t original;
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
    uint8_t original;
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
    uint8_t original;
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
    uint8_t original;
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
    uint8_t original;
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
}