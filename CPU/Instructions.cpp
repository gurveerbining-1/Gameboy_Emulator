#include "Instructions.h"



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


void op_nop(CPU& cpu) {
    // nothing 
}

void initHandlerTable(std::array<Handler, 256>& table) {
    table[0x00] = op_nop;
}