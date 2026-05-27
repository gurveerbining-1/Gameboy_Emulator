#include "Instructions.h"
#include "CPU.h"


void initInstructionTable(std::array<Instruction, 256>& table){
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
        reg_type::R_NONE,
        condition_code::CD_NONE,
        1,
        8
    };
}


void op_nop(CPU& cpu, Instruction& inst) {
    // nothing 
}

void op_ld_r16_imm16(CPU& cpu, Instruction& inst){
    if(inst.address_mode == addrmode::AM_R_D16){
        // load immediate 16 bit value into register
        uint16_t value = cpu.fetch16(); // imm16 value
        cpu.setReg16(inst.reg_1, value); // write to register
    }
}

void op_ld_mr_r(CPU& cpu, Instruction& inst){
    if(inst.address_mode == addrmode::AM_MR_R){
        // load value of register into address of the target register
        // to do this: Add a public write(uint16_t addr, uint8_t val) on CPU that calls bus->write
    }
}

void initHandlerTable(std::array<Handler, 256>& table) {
    table[0x00] = op_nop;
    table[0x01] = op_ld_r16_imm16;
}