#include "CPU.h"


CPU::CPU(){
    reset();
    initHandlerTable(handler_table);
    initInstructionTable(instruction_table);
}

CPU::CPU(membus* b) : bus(b){
    reset();
    initHandlerTable(handler_table);
    initInstructionTable(instruction_table);
}

void CPU::reset(){
    //  initial state of all registers
    reg.A = 0x01;
    reg.F = 0xB0;
    reg.B = 0x00;
    reg.C = 0x13;
    reg.D = 0x00;
    reg.E = 0xD8;
    reg.H = 0x01;
    reg.L = 0x4D;

    reg.PC = 0x0100; // if I choose to emulate the boot rom then PC = PC = 0x0000
    reg.SP = 0xFFFE;
    
}
   
void CPU::handle_interrupts(){
    
}

void CPU::step(){
    
    handle_interrupts();
    uint8_t opcode = fetch();
    execute_opcode(opcode);
    
}

uint8_t CPU::fetch(){
    uint8_t opcode = bus->read(reg.PC);
    reg.PC++;
    return opcode;
}

uint16_t CPU::fetch16(){
    /*
    The Game Boy is little-endian, meaning the low byte comes first in memory. 
    */
    uint8_t low = (bus->read(reg.PC)); // low byte is read first
    reg.PC++;
    uint8_t high = bus->read(reg.PC); // then the high byte is read
    reg.PC++;

    return ((high << 8) | low);

}

uint8_t CPU::update_cycles(uint8_t cycles){

}

void CPU::setReg16(reg_type target_reg, uint16_t value){
    /*
    setReg16 receives an enum value telling it which register pair
    setReg16 receives a 16-bit value to store
    setReg16 needs to split that 16-bit value into two 8-bit registers
    */

    // since value is a 16 bit value it has to be split into two 8-bit registers

    uint8_t high = (value >> 8) & 0xFF;
    uint8_t low = (value & 0xFF);
    
    switch(target_reg){
        case(reg_type::R_AF):
            reg.A = high;
            reg.F = (low & 0xF0); // lower bits of F are always 0
            break;
        
        case(reg_type::R_BC):
            reg.B = high;
            reg.C = low;
            break;
        
        case(reg_type::R_DE):
            reg.D = high;
            reg.E = low;
            break;
        
        case(reg_type::R_HL):
            reg.H = high;
            reg.L = low;
            break;

        case(reg_type::R_SP):
            reg.SP = value;
            break;

        case(reg_type::R_PC):
            reg.PC = value;
            break;
        
        default:
            std::cout << ("Invalid 16 bit register") << std::endl;
            break;
    }
}

void CPU::setReg8(reg_type target_reg, uint8_t value){
    switch(target_reg){
        case(reg_type::R_A):
            reg.A = value;
            break;

        case(reg_type::R_B):
            reg.B = value;
            break;
        
        case(reg_type::R_C):
            reg.C = value;
            break;

        case(reg_type::R_D):
            reg.D = value;
            break;
        
        case(reg_type::R_E):
            reg.E = value;
            break;
        
        case(reg_type::R_F):
            reg.F = value & 0xF0;
            break;
        
        case(reg_type::R_H):
            reg.H = value;
            break;
        
        case(reg_type::R_L):
            reg.L = value;
            break;
    }   
}

uint16_t CPU::getReg16(reg_type inst_reg){
    switch(inst_reg){
        case(reg_type::R_AF):
           return this->reg.A << 8 | (this->reg.F & 0xF0);
        
        case(reg_type::R_BC):
           return this->reg.B << 8 | this->reg.C;
        
        case(reg_type::R_DE):
           return this->reg.D << 8 | this->reg.E;
        
        case(reg_type::R_HL):
           return this->reg.H << 8 | this->reg.L;
        
        case(reg_type::R_SP):
           return this->reg.SP;

        case(reg_type::R_PC):
           return this->reg.PC;

        default:
            return 0;
    } 
}

uint8_t CPU::getReg8(reg_type inst_reg){
    switch(inst_reg){
        case(reg_type::R_A):
            return this->reg.A;
            break;
       
        case(reg_type::R_B):
            return this->reg.B;
            break;
        
        case(reg_type::R_C):
            return this->reg.C;
            break;

        case(reg_type::R_D):
            return this->reg.D;
            break;
        
        case(reg_type::R_E):
            return this->reg.E;
            break;
        
        case(reg_type::R_F):
            return this->reg.F;
            break;
        
        case(reg_type::R_H):
            return this->reg.H;
            break;
        
        case(reg_type::R_L):
            return this->reg.L;
            break;
        
    }
}

void CPU::execute_opcode(uint8_t opcode){
    const Instruction currentInst = instruction_table[opcode];
    const Handler currentHandler = handler_table[opcode];
    currentHandler(*this, currentInst);
    //update_cycles();
    
    //instructionTable tells you what an instruction is, but execute_opcode still has no idea what to do with it.

    /* this is how I did chip8 instruction set but this can be much better than a giant switch statement 
    probably try to implement each instruction in Instructions.cpp with classes like an add instruction class
    which inherits from the general instruction class
    Instruction i;
    switch(opcode){
        case 0x00:
            i.instruction_type = mnemonic::IN_NOP;
            i.address_mode = addrmode::AM_NOP;
            i.cond_code = condition_code::CD_NONE;
            i.cycles += 1;
            i.length = 1;
            i.operand_1 = operand_type::NONE;
            i.operand_2 = operand_type::NONE;
            break;
    }

    Instead of a switch statement, build a fixed array of 256 Instruction descriptors (one per opcode), 
    then a separate array of 256 function pointers (or std::functions) that maps each opcode to its handler. 
    execute_opcode becomes a two-line function: look up the descriptor, call the handler. No switch, no if-chains. 
    This is how many well-regarded emulators are structured, and it's the most idiomatic C++ approach here. 
    The table itself becomes almost self-documenting.

    */
}