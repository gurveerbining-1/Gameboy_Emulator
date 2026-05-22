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

uint8_t CPU::update_cycles(uint8_t cycles){

}

void CPU::execute_opcode(uint8_t opcode){
    const Instruction currentInst = instruction_table[opcode];
    const Handler currentHandler = handler_table[opcode];
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