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
        condition_code::CD_Z,
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

void op_inc_r16(CPU& cpu, const Instruction& inst){
    uint16_t value = cpu.getReg16(inst.reg_1);
    value++;
    cpu.setReg16(inst.reg_1, value);
}

void initHandlerTable(std::array<Handler, 256>& table) {
    table.fill(op_unimplemented);
    table[0x00] = op_nop;
    table[0x01] = op_ld_r16_imm16;
    table[0x02] = op_ld_mr_r;
    table[0x03] = op_inc_r16;
}