#include "Instructions.h"
#include "CPU.h"

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

void op_dec_r8(CPU& cpu, const Instruction& inst){
    uint8_t original = cpu.getReg8(inst.reg_1); // keep the original value to compute the half carry flag
    uint8_t result = original - 1;
    cpu.setReg8(inst.reg_1, result);

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
} 