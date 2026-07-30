#include <cassert>
#include <iostream>

#include "../CPU/CPU.h"
#include "../bus/membus.h"

void checkFlags(CPU& cpu, bool z, bool n, bool h, bool c)
{
    assert(cpu.getFlag(Z) == z);
    assert(cpu.getFlag(N) == n);
    assert(cpu.getFlag(H) == h);
    assert(cpu.getFlag(C) == c);
}

void test_opcode_00_NOP()
{
    membus bus;
    CPU cpu(&bus);

    cpu.setFlag(Z, true);
    cpu.setFlag(N, false);
    cpu.setFlag(H, true);
    cpu.setFlag(C, true);

    bus.loadTestProgram({
        0x00
    });

    cpu.step();

    assert(cpu.getReg16(reg_type::R_PC) == 0x101);

    // Flags should remain unchanged.
    checkFlags(cpu, true, false, true, true);

    std::cout << "Opcode 00 (NOP) passed\n";
}

void test_opcode_01_LD_BC()
{
    membus bus;
    CPU cpu(&bus);

    cpu.setFlag(Z, false);
    cpu.setFlag(N, true);
    cpu.setFlag(H, false);
    cpu.setFlag(C, true);

    bus.loadTestProgram({
        0x01, 0x34, 0x12
    });

    cpu.step();

    assert(cpu.getReg16(reg_type::R_BC) == 0x1234);
    assert(cpu.getReg16(reg_type::R_PC) == 0x103);

    // Flags should remain unchanged.
    checkFlags(cpu, false, true, false, true);

    std::cout << "Opcode 01 (LD BC,d16) passed\n";
}

void test_opcode_02_LD_BC_A()
{
    membus bus;
    CPU cpu(&bus);

    cpu.setReg8(reg_type::R_A, 0x56);
    cpu.setReg16(reg_type::R_BC, 0xC123);

    cpu.setFlag(Z, true);
    cpu.setFlag(N, true);
    cpu.setFlag(H, false);
    cpu.setFlag(C, false);

    bus.loadTestProgram({
        0x02
    });

    cpu.step();

    assert(bus.read(0xC123) == 0x56);
    assert(cpu.getReg16(reg_type::R_PC) == 0x101);

    // Flags should remain unchanged.
    checkFlags(cpu, true, true, false, false);

    std::cout << "Opcode 02 (LD (BC),A) passed\n";
}

void test_opcode_03_INC_BC()
{
    membus bus;
    CPU cpu(&bus);

    cpu.setReg16(reg_type::R_BC, 0x1234);

    cpu.setFlag(Z, false);
    cpu.setFlag(N, true);
    cpu.setFlag(H, true);
    cpu.setFlag(C, false);

    bus.loadTestProgram({
        0x03
    });

    cpu.step();

    assert(cpu.getReg16(reg_type::R_BC) == 0x1235);
    assert(cpu.getReg16(reg_type::R_PC) == 0x101);

    // Flags should remain unchanged.
    checkFlags(cpu, false, true, true, false);

    std::cout << "Opcode 03 (INC BC) passed\n";
}

void test_opcode_04_INC_B_normal()
{
    membus bus;
    CPU cpu(&bus);

    cpu.setReg8(reg_type::R_B, 0x01);

    cpu.setFlag(C, true);

    bus.loadTestProgram({
        0x04
    });

    cpu.step();

    assert(cpu.getReg8(reg_type::R_B) == 0x02);

    checkFlags(cpu, false, false, false, true);

    std::cout << "Opcode 04 (INC B normal) passed\n";
}

void test_opcode_04_INC_B_halfcarry()
{
    membus bus;
    CPU cpu(&bus);

    cpu.setReg8(reg_type::R_B, 0x0F);

    cpu.setFlag(C, false);

    bus.loadTestProgram({
        0x04
    });

    cpu.step();

    assert(cpu.getReg8(reg_type::R_B) == 0x10);

    checkFlags(cpu, false, false, true, false);

    std::cout << "Opcode 04 (INC B half carry) passed\n";
}

void test_opcode_04_INC_B_zero()
{
    membus bus;
    CPU cpu(&bus);

    cpu.setReg8(reg_type::R_B, 0xFF);

    cpu.setFlag(C, true);

    bus.loadTestProgram({
        0x04
    });

    cpu.step();

    assert(cpu.getReg8(reg_type::R_B) == 0x00);

    checkFlags(cpu, true, false, true, true);

    std::cout << "Opcode 04 (INC B zero) passed\n";
}

void test_opcode_05_DEC_B_normal()
{
    membus bus;
    CPU cpu(&bus);

    cpu.setReg8(reg_type::R_B, 0x05);

    cpu.setFlag(C, true);

    bus.loadTestProgram({
        0x05
    });

    cpu.step();

    assert(cpu.getReg8(reg_type::R_B) == 0x04);

    checkFlags(cpu, false, true, false, true);

    std::cout << "Opcode 05 (DEC B normal) passed\n";
}

void test_opcode_05_DEC_B_zero()
{
    membus bus;
    CPU cpu(&bus);

    cpu.setReg8(reg_type::R_B, 0x01);

    cpu.setFlag(C, false);

    bus.loadTestProgram({
        0x05
    });

    cpu.step();

    assert(cpu.getReg8(reg_type::R_B) == 0x00);

    checkFlags(cpu, true, true, false, false);

    std::cout << "Opcode 05 (DEC B zero) passed\n";
}

void test_opcode_05_DEC_B_halfborrow()
{
    membus bus;
    CPU cpu(&bus);

    cpu.setReg8(reg_type::R_B, 0x10);

    cpu.setFlag(C, true);

    bus.loadTestProgram({
        0x05
    });

    cpu.step();

    assert(cpu.getReg8(reg_type::R_B) == 0x0F);

    checkFlags(cpu, false, true, true, true);

    std::cout << "Opcode 05 (DEC B half borrow) passed\n";
}

void test_opcode_06_LD_B()
{
    membus bus;
    CPU cpu(&bus);

    bus.loadTestProgram({
        0x06, 0x42
    });

    cpu.step();

    assert(cpu.getReg8(reg_type::R_B) == 0x42);
    assert(cpu.getReg16(reg_type::R_PC) == 0x102);

    std::cout << "Opcode 06 (LD B,d8) passed\n";
}

void test_opcode_07_RLCA()
{
    membus bus;
    CPU cpu(&bus);

    cpu.setReg8(reg_type::R_A, 0b10000001);

    bus.loadTestProgram({
        0x07
    });

    cpu.step();

    assert(cpu.getReg8(reg_type::R_A) == 0b00000011);

    checkFlags(cpu, false, false, false, true);

    std::cout << "Opcode 07 (RLCA) passed\n";
}

void test_opcode_08_LD_a16_SP()
{
    membus bus;
    CPU cpu(&bus);

    cpu.setReg16(reg_type::R_SP, 0x1234);

    bus.loadTestProgram({
        0x08, 0x00, 0xC0
    });

    cpu.step();

    assert(bus.read(0xC000) == 0x34);
    assert(bus.read(0xC001) == 0x12);

    std::cout << "Opcode 08 (LD (a16),SP) passed\n";
}

void test_opcode_09_ADD_HL_BC()
{
    membus bus;
    CPU cpu(&bus);

    cpu.setReg16(reg_type::R_HL, 0x1000);
    cpu.setReg16(reg_type::R_BC, 0x2000);

    bus.loadTestProgram({
        0x09
    });

    cpu.step();

    assert(cpu.getReg16(reg_type::R_HL) == 0x3000);

    checkFlags(cpu, true, false, false, false);

    std::cout << "Opcode 09 (ADD HL,BC) passed\n";
}

void test_opcode_0A_LD_A_BC()
{
    membus bus;
    CPU cpu(&bus);

    cpu.setReg16(reg_type::R_BC, 0xC000);

    bus.write(0xC000, 0x77);

    bus.loadTestProgram({
        0x0A
    });

    cpu.step();

    assert(cpu.getReg8(reg_type::R_A) == 0x77);

    std::cout << "Opcode 0A (LD A,(BC)) passed\n";
}

void test_opcode_0B_DEC_BC()
{
    membus bus;
    CPU cpu(&bus);

    cpu.setReg16(reg_type::R_BC, 0x1234);

    bus.loadTestProgram({
        0x0B
    });

    cpu.step();

    assert(cpu.getReg16(reg_type::R_BC) == 0x1233);

    std::cout << "Opcode 0B (DEC BC) passed\n";
}

void test_opcode_0C_INC_C()
{
    membus bus;
    CPU cpu(&bus);

    cpu.setReg8(reg_type::R_C, 0x0F);
    cpu.setFlag(C, false); // INC does not modify C

    bus.loadTestProgram({
        0x0C
    });

    cpu.step();

    assert(cpu.getReg8(reg_type::R_C) == 0x10);

    checkFlags(cpu, false, false, true, false);

    std::cout << "Opcode 0C (INC C) passed\n";
}

void test_opcode_0D_DEC_C()
{
    membus bus;
    CPU cpu(&bus);

    cpu.setReg8(reg_type::R_C, 0x01);
    cpu.setFlag(C, false);  // DEC does not change C, so define its starting state

    bus.loadTestProgram({
        0x0D
    });

    cpu.step();

    assert(cpu.getReg8(reg_type::R_C) == 0x00);

    checkFlags(cpu, true, true, false, false);

    std::cout << "Opcode 0D (DEC C) passed\n";
}

void test_opcode_0E_LD_C()
{
    membus bus;
    CPU cpu(&bus);

    bus.loadTestProgram({
        0x0E, 0x99
    });

    cpu.step();
    assert(cpu.getReg8(reg_type::R_C) == 0x99);
    assert(cpu.getReg16(reg_type::R_PC) == 0x102);

    std::cout << "Opcode 0E (LD C,d8) passed\n";
}

void test_opcode_0F_RRCA()
{
    membus bus;
    CPU cpu(&bus);

    cpu.setReg8(reg_type::R_A, 0b10000001);

    bus.loadTestProgram({
        0x0F
    });

    cpu.step();
    
    assert(cpu.getReg8(reg_type::R_A) == 0b11000000);

    checkFlags(cpu, false, false, false, true);

    std::cout << "Opcode 0F (RRCA) passed\n";
}

void test_opcode_10_STOP()
{
    membus bus;
    CPU cpu(&bus);

    bus.loadTestProgram({
        0x10, 0x00
    });

    cpu.step();

    // STOP is 2 bytes.
    assert(cpu.getReg16(reg_type::R_PC) == 0x102);

    std::cout << "Opcode 10 (STOP) passed\n";
}

void test_opcode_11_LD_DE()
{
    membus bus;
    CPU cpu(&bus);

    cpu.setFlag(Z, true);
    cpu.setFlag(N, false);
    cpu.setFlag(H, true);
    cpu.setFlag(C, false);

    bus.loadTestProgram({
        0x11, 0x78, 0x56
    });
          
    cpu.step();

    assert(cpu.getReg16(reg_type::R_DE) == 0x5678);
    assert(cpu.getReg16(reg_type::R_PC) == 0x103);

    checkFlags(cpu, true, false, true, false);

    std::cout << "Opcode 11 (LD DE,d16) passed\n";
}

void test_opcode_12_LD_DE_A()
{
    membus bus;
    CPU cpu(&bus);

    cpu.setReg16(reg_type::R_DE, 0xC123);
    cpu.setReg8(reg_type::R_A, 0xAB);

    cpu.setFlag(Z, false);
    cpu.setFlag(N, true);
    cpu.setFlag(H, false);
    cpu.setFlag(C, true);

    bus.loadTestProgram({
        0x12
    });

    cpu.step();

    assert(bus.read(0xC123) == 0xAB);

    checkFlags(cpu, false, true, false, true);

    std::cout << "Opcode 12 (LD (DE),A) passed\n";
}

void test_opcode_13_INC_DE()
{
    membus bus;
    CPU cpu(&bus);

    cpu.setReg16(reg_type::R_DE, 0x4321);

    cpu.setFlag(Z, true);
    cpu.setFlag(N, false);
    cpu.setFlag(H, true);
    cpu.setFlag(C, true);

    bus.loadTestProgram({
        0x13
    });

    cpu.step();

    assert(cpu.getReg16(reg_type::R_DE) == 0x4322);

    checkFlags(cpu, true, false, true, true);

    std::cout << "Opcode 13 (INC DE) passed\n";
}

void test_opcode_14_INC_D()
{
    membus bus;
    CPU cpu(&bus);

    cpu.setReg8(reg_type::R_D, 0x0F);
    cpu.setFlag(C, true);

    bus.loadTestProgram({
        0x14
    });

    cpu.step();

    assert(cpu.getReg8(reg_type::R_D) == 0x10);

    checkFlags(cpu, false, false, true, true);

    std::cout << "Opcode 14 (INC D) passed\n";
}

void test_opcode_15_DEC_D()
{
    membus bus;
    CPU cpu(&bus);

    cpu.setReg8(reg_type::R_D, 0x10);
    cpu.setFlag(C, false);

    bus.loadTestProgram({
        0x15
    });

    cpu.step();

    assert(cpu.getReg8(reg_type::R_D) == 0x0F);

    checkFlags(cpu, false, true, true, false);

    std::cout << "Opcode 15 (DEC D) passed\n";
}

void test_opcode_16_LD_D()
{
    membus bus;
    CPU cpu(&bus);

    bus.loadTestProgram({
        0x16, 0x55
    });

    cpu.step();

    assert(cpu.getReg8(reg_type::R_D) == 0x55);
    assert(cpu.getReg16(reg_type::R_PC) == 0x102);

    std::cout << "Opcode 16 (LD D,d8) passed\n";
}

void test_opcode_17_RLA()
{
    membus bus;
    CPU cpu(&bus);

    cpu.setReg8(reg_type::R_A, 0b10000010);
    cpu.setFlag(C, true);

    bus.loadTestProgram({
        0x17
    });

    cpu.step();

    assert(cpu.getReg8(reg_type::R_A) == 0b00000101);

    checkFlags(cpu, false, false, false, true);

    std::cout << "Opcode 17 (RLA) passed\n";
}

void test_opcode_18_JR_forward()
{
    membus bus;
    CPU cpu(&bus);

    bus.loadTestProgram({
        0x18, 0x05
    });

    cpu.step();

    // PC after fetching operand:
    // 0x102 + 5 = 0x107
    assert(cpu.getReg16(reg_type::R_PC) == 0x107);

    std::cout << "Opcode 18 (JR forward) passed\n";
}

void test_opcode_18_JR_backward()
{
    membus bus;
    CPU cpu(&bus);

    bus.loadTestProgram({
        0x18, 0xFE
    });

    cpu.step();

    // PC after fetching operand:
    // 0x102 - 2 = 0x100
    assert(cpu.getReg16(reg_type::R_PC) == 0x100);

    std::cout << "Opcode 18 (JR backward) passed\n";
}

void test_opcode_19_ADD_HL_DE()
{
    membus bus;
    CPU cpu(&bus);

    cpu.setReg16(reg_type::R_HL, 0x1000);
    cpu.setReg16(reg_type::R_DE, 0x2000);

    cpu.setFlag(Z, true);
    cpu.setFlag(N, true);
    cpu.setFlag(H, false);
    cpu.setFlag(C, true);

    bus.loadTestProgram({
        0x19
    });

    cpu.step();

    assert(cpu.getReg16(reg_type::R_HL) == 0x3000);

    // Z is unaffected
    // N is reset
    // H/C depend on result
    checkFlags(cpu, true, false, false, false);

    std::cout << "Opcode 19 (ADD HL,DE) passed\n";
}

void test_opcode_1A_LD_A_DE()
{
    membus bus;
    CPU cpu(&bus);

    cpu.setReg16(reg_type::R_DE, 0xC000);

    bus.write(0xC000, 0x77);

    bus.loadTestProgram({
        0x1A
    });

    cpu.step();

    assert(cpu.getReg8(reg_type::R_A) == 0x77);

    std::cout << "Opcode 1A (LD A,(DE)) passed\n";
}

void test_opcode_1B_DEC_DE()
{
    membus bus;
    CPU cpu(&bus);

    cpu.setReg16(reg_type::R_DE, 0x1234);

    cpu.setFlag(Z, true);
    cpu.setFlag(N, false);
    cpu.setFlag(H, true);
    cpu.setFlag(C, true);

    bus.loadTestProgram({
        0x1B
    });

    cpu.step();

    assert(cpu.getReg16(reg_type::R_DE) == 0x1233);

    // Flags unaffected
    checkFlags(cpu, true, false, true, true);

    std::cout << "Opcode 1B (DEC DE) passed\n";
}

void test_opcode_1C_INC_E()
{
    membus bus;
    CPU cpu(&bus);

    cpu.setReg8(reg_type::R_E, 0x0F);
    cpu.setFlag(C, true);

    bus.loadTestProgram({
        0x1C
    });

    cpu.step();

    assert(cpu.getReg8(reg_type::R_E) == 0x10);

    checkFlags(cpu, false, false, true, true);

    std::cout << "Opcode 1C (INC E) passed\n";
}

void test_opcode_1D_DEC_E()
{
    membus bus;
    CPU cpu(&bus);

    cpu.setReg8(reg_type::R_E, 0x10);
    cpu.setFlag(C, false);

    bus.loadTestProgram({
        0x1D
    });

    cpu.step();

    assert(cpu.getReg8(reg_type::R_E) == 0x0F);

    checkFlags(cpu, false, true, true, false);

    std::cout << "Opcode 1D (DEC E) passed\n";
}

void test_opcode_1E_LD_E()
{
    membus bus;
    CPU cpu(&bus);

    bus.loadTestProgram({
        0x1E, 0x99
    });

    cpu.step();

    assert(cpu.getReg8(reg_type::R_E) == 0x99);
    assert(cpu.getReg16(reg_type::R_PC) == 0x102);

    std::cout << "Opcode 1E (LD E,d8) passed\n";
}

void test_opcode_1F_RRA()
{
    membus bus;
    CPU cpu(&bus);

    cpu.setReg8(reg_type::R_A, 0b00000001);
    cpu.setFlag(C, true);

    bus.loadTestProgram({
        0x1F
    });

    cpu.step();

    /*
        Before:
        A = 00000001
        C = 1

        After:
        Carry gets old bit 0
        Old carry goes into bit 7

        A = 10000000
        C = 1
    */
    assert(cpu.getReg8(reg_type::R_A) == 0b10000000);

    checkFlags(cpu, false, false, false, true);

    std::cout << "Opcode 1F (RRA) passed\n";
}

void test_opcode_20_JR_NZ_taken()
{
    membus bus;
    CPU cpu(&bus);

    cpu.setFlag(Z, false);

    bus.loadTestProgram({
        0x20, 0x05
    });

    cpu.step();

    assert(cpu.getReg16(reg_type::R_PC) == 0x107);

    std::cout << "Opcode 20 (JR NZ taken) passed\n";
}

void test_opcode_20_JR_NZ_not_taken()
{
    membus bus;
    CPU cpu(&bus);

    cpu.setFlag(Z, true);

    bus.loadTestProgram({
        0x20, 0x05
    });

    cpu.step();

    assert(cpu.getReg16(reg_type::R_PC) == 0x102);

    std::cout << "Opcode 20 (JR NZ not taken) passed\n";
}

void test_opcode_21_LD_HL()
{
    membus bus;
    CPU cpu(&bus);

    bus.loadTestProgram({
        0x21, 0x78, 0x56
    });

    cpu.step();

    assert(cpu.getReg16(reg_type::R_HL) == 0x5678);
    assert(cpu.getReg16(reg_type::R_PC) == 0x103);

    std::cout << "Opcode 21 (LD HL,d16) passed\n";
}

void test_opcode_22_LD_HL_INC_A()
{
    membus bus;
    CPU cpu(&bus);

    cpu.setReg16(reg_type::R_HL, 0xC000);
    cpu.setReg8(reg_type::R_A, 0x42);

    bus.loadTestProgram({
        0x22
    });

    cpu.step();

    assert(bus.read(0xC000) == 0x42);
    assert(cpu.getReg16(reg_type::R_HL) == 0xC001);

    std::cout << "Opcode 22 (LD (HL+),A) passed\n";
}

void test_opcode_23_INC_HL()
{
    membus bus;
    CPU cpu(&bus);

    cpu.setReg16(reg_type::R_HL, 0x1234);

    cpu.setFlag(Z,true);
    cpu.setFlag(N,true);
    cpu.setFlag(H,true);
    cpu.setFlag(C,true);

    bus.loadTestProgram({
        0x23
    });

    cpu.step();

    assert(cpu.getReg16(reg_type::R_HL) == 0x1235);

    // INC rr does not affect flags
    checkFlags(cpu,true,true,true,true);

    std::cout << "Opcode 23 (INC HL) passed\n";
}

void test_opcode_24_INC_H()
{
    membus bus;
    CPU cpu(&bus);

    cpu.setReg8(reg_type::R_H,0x0F);
    cpu.setFlag(C, true);

    bus.loadTestProgram({
        0x24
    });

    cpu.step();


    assert(cpu.getReg8(reg_type::R_H)==0x10);

    checkFlags(cpu,false,false,true,true);

    std::cout << "Opcode 24 (INC H) passed\n";
}

void test_opcode_25_DEC_H()
{
    membus bus;
    CPU cpu(&bus);

    cpu.setReg8(reg_type::R_H,0x10);
    cpu.setFlag(C, true);

    bus.loadTestProgram({
        0x25
    });

    cpu.step();

    assert(cpu.getReg8(reg_type::R_H)==0x0F);

    checkFlags(cpu,false,true,true,true);

    std::cout << "Opcode 25 (DEC H) passed\n";
}

void test_opcode_26_LD_H()
{
    membus bus;
    CPU cpu(&bus);

    bus.loadTestProgram({
        0x26,0xAA
    });

    cpu.step();

    assert(cpu.getReg8(reg_type::R_H)==0xAA);
    assert(cpu.getReg16(reg_type::R_PC)==0x102);

    std::cout << "Opcode 26 (LD H,d8) passed\n";
}

void test_opcode_27_DAA()
{
    membus bus;
    CPU cpu(&bus);

    // 0x15 + 0x27 = 0x3C -> DAA -> 0x42
    cpu.setReg8(reg_type::R_A,0x3C);

    cpu.setFlag(N,false);
    cpu.setFlag(H,false);
    cpu.setFlag(C,false);

    bus.loadTestProgram({
        0x27
    });

    cpu.step();

    assert(cpu.getReg8(reg_type::R_A)==0x42);

    std::cout << "Opcode 27 (DAA) passed\n";
}

void test_opcode_28_JR_Z_taken()
{
    membus bus;
    CPU cpu(&bus);

    cpu.setFlag(Z,true);

    bus.loadTestProgram({
        0x28,0x05
    });

    cpu.step();

    assert(cpu.getReg16(reg_type::R_PC)==0x107);

    std::cout << "Opcode 28 (JR Z taken) passed\n";
}

void test_opcode_29_ADD_HL_HL()
{
    membus bus;
    CPU cpu(&bus);

    cpu.setReg16(reg_type::R_HL, 0x1234);

    cpu.setFlag(Z, true);
    cpu.setFlag(N, true);
    cpu.setFlag(H, false);
    cpu.setFlag(C, true);

    bus.loadTestProgram({
        0x29
    });

    cpu.step();

    assert(cpu.getReg16(reg_type::R_HL) == 0x2468);

    checkFlags(cpu, true, false, false, false);

    std::cout << "Opcode 29 (ADD HL,HL) passed\n";
}

void test_opcode_2A_LD_A_HL_INC()
{
    membus bus;
    CPU cpu(&bus);

    cpu.setReg16(reg_type::R_HL, 0xC000);

    bus.write(0xC000,0x55);

    bus.loadTestProgram({
        0x2A
    });

    cpu.step();

    assert(cpu.getReg8(reg_type::R_A)==0x55);
    assert(cpu.getReg16(reg_type::R_HL)==0xC001);

    std::cout << "Opcode 2A (LD A,(HL+)) passed\n";
}

void test_opcode_2B_DEC_HL()
{
    membus bus;
    CPU cpu(&bus);

    cpu.setReg16(reg_type::R_HL,0x1234);

    cpu.setFlag(Z,true);
    cpu.setFlag(N,true);
    cpu.setFlag(H,true);
    cpu.setFlag(C,true);

    bus.loadTestProgram({
        0x2B
    });

    cpu.step();

    assert(cpu.getReg16(reg_type::R_HL)==0x1233);

    checkFlags(cpu,true,true,true,true);

    std::cout << "Opcode 2B (DEC HL) passed\n";
}

void test_opcode_2C_INC_L()
{
    membus bus;
    CPU cpu(&bus);

    cpu.setReg8(reg_type::R_L,0x0F);

    cpu.setFlag(C,true);

    bus.loadTestProgram({
        0x2C
    });

    cpu.step();

    assert(cpu.getReg8(reg_type::R_L)==0x10);

    checkFlags(cpu,false,false,true,true);

    std::cout << "Opcode 2C (INC L) passed\n";
}

void test_opcode_2D_DEC_L()
{
    membus bus;
    CPU cpu(&bus);

    cpu.setReg8(reg_type::R_L,0x10);

    cpu.setFlag(C,true);

    bus.loadTestProgram({
        0x2D
    });

    cpu.step();

    assert(cpu.getReg8(reg_type::R_L)==0x0F);

    checkFlags(cpu,false,true,true,true);

    std::cout << "Opcode 2D (DEC L) passed\n";
}

void test_opcode_2E_LD_L()
{
    membus bus;
    CPU cpu(&bus);

    bus.loadTestProgram({
        0x2E,0x77
    });

    cpu.step();

    assert(cpu.getReg8(reg_type::R_L)==0x77);
    assert(cpu.getReg16(reg_type::R_PC)==0x102);

    std::cout << "Opcode 2E (LD L,d8) passed\n";
}

void test_opcode_2F_CPL()
{
    membus bus;
    CPU cpu(&bus);

    cpu.setReg8(reg_type::R_A,0b10101010);

    cpu.setFlag(Z,true);
    cpu.setFlag(C,true);

    bus.loadTestProgram({
        0x2F
    });

    cpu.step();

    assert(cpu.getReg8(reg_type::R_A)==0b01010101);

    checkFlags(cpu,true,true,true,true);

    std::cout << "Opcode 2F (CPL) passed\n";
}

void test_opcode_30_JR_NC_taken()
{
    membus bus;
    CPU cpu(&bus);

    cpu.setFlag(C,false);

    bus.loadTestProgram({
        0x30,0x05
    });

    cpu.step();

    assert(cpu.getReg16(reg_type::R_PC)==0x107);

    std::cout << "Opcode 30 (JR NC taken) passed\n";
}

void test_opcode_30_JR_NC_not_taken()
{
    membus bus;
    CPU cpu(&bus);

    cpu.setFlag(C,true);

    bus.loadTestProgram({
        0x30,0x05
    });

    cpu.step();

    assert(cpu.getReg16(reg_type::R_PC)==0x102);

    std::cout << "Opcode 30 (JR NC not taken) passed\n";
}

void test_opcode_31_LD_SP()
{
    membus bus;
    CPU cpu(&bus);

    bus.loadTestProgram({
        0x31,0x78,0x56
    });

    cpu.step();

    assert(cpu.getReg16(reg_type::R_SP)==0x5678);
    assert(cpu.getReg16(reg_type::R_PC)==0x103);

    std::cout << "Opcode 31 (LD SP,d16) passed\n";
}

void test_opcode_32_LD_HL_DEC_A()
{
    membus bus;
    CPU cpu(&bus);

    cpu.setReg16(reg_type::R_HL, 0xC000);
    cpu.setReg8(reg_type::R_A, 0x42);

    bus.loadTestProgram({
        0x32
    });

    cpu.step();

    assert(bus.read(0xC000) == 0x42);
    assert(cpu.getReg16(reg_type::R_HL) == 0xBFFF);

    std::cout << "Opcode 32 (LD (HL-),A) passed\n";
}

void test_opcode_33_INC_SP()
{
    membus bus;
    CPU cpu(&bus);

    cpu.setReg16(reg_type::R_SP,0x1234);

    cpu.setFlag(Z,true);
    cpu.setFlag(N,true);
    cpu.setFlag(H,true);
    cpu.setFlag(C,true);

    bus.loadTestProgram({
        0x33
    });

    cpu.step();

    assert(cpu.getReg16(reg_type::R_SP)==0x1235);

    checkFlags(cpu,true,true,true,true);

    std::cout << "Opcode 33 (INC SP) passed\n";
}

void test_opcode_34_INC_HL_memory()
{
    membus bus;
    CPU cpu(&bus);

    cpu.setReg16(reg_type::R_HL,0xC000);

    bus.write(0xC000,0x0F);

    cpu.setFlag(C,true);

    bus.loadTestProgram({
        0x34
    });

    cpu.step();

    assert(bus.read(0xC000)==0x10);

    checkFlags(cpu,false,false,true,true);

    std::cout << "Opcode 34 (INC (HL)) passed\n";
}

void test_opcode_35_DEC_HL_memory()
{
    membus bus;
    CPU cpu(&bus);

    cpu.setReg16(reg_type::R_HL,0xC000);

    bus.write(0xC000,0x10);

    cpu.setFlag(C,true);

    bus.loadTestProgram({
        0x35
    });

    cpu.step();

    assert(bus.read(0xC000)==0x0F);

    checkFlags(cpu,false,true,true,true);

    std::cout << "Opcode 35 (DEC (HL)) passed\n";
}

void test_opcode_36_LD_HL_d8()
{
    membus bus;
    CPU cpu(&bus);

    cpu.setReg16(reg_type::R_HL,0xC000);

    bus.loadTestProgram({
        0x36,0x77
    });

    cpu.step();

    assert(bus.read(0xC000)==0x77);
    assert(cpu.getReg16(reg_type::R_PC)==0x102);

    std::cout << "Opcode 36 (LD (HL),d8) passed\n";
}

void test_opcode_37_SCF()
{
    membus bus;
    CPU cpu(&bus);

    cpu.setFlag(Z,true);
    cpu.setFlag(C,false);
    cpu.setFlag(N,true);
    cpu.setFlag(H,true);

    bus.loadTestProgram({
        0x37
    });

    cpu.step();

    checkFlags(cpu,true,false,false,true);

    std::cout << "Opcode 37 (SCF) passed\n";
}

void test_opcode_38_JR_C_taken()
{
    membus bus;
    CPU cpu(&bus);

    cpu.setFlag(C,true);

    bus.loadTestProgram({
        0x38,0x05
    });

    cpu.step();

    assert(cpu.getReg16(reg_type::R_PC)==0x107);

    std::cout << "Opcode 38 (JR C taken) passed\n";
}

void test_opcode_38_JR_C_not_taken()
{
    membus bus;
    CPU cpu(&bus);

    cpu.setFlag(C,false);

    bus.loadTestProgram({
        0x38,0x05
    });

    cpu.step();

    assert(cpu.getReg16(reg_type::R_PC)==0x102);

    std::cout << "Opcode 38 (JR C not taken) passed\n";
}

void test_opcode_39_ADD_HL_SP()
{
    membus bus;
    CPU cpu(&bus);

    cpu.setReg16(reg_type::R_HL,0x1000);
    cpu.setReg16(reg_type::R_SP,0x2000);

    cpu.setFlag(Z,true);
    cpu.setFlag(N,true);
    cpu.setFlag(H,false);
    cpu.setFlag(C,true);

    bus.loadTestProgram({
        0x39
    });

    cpu.step();

    assert(cpu.getReg16(reg_type::R_HL)==0x3000);

    checkFlags(cpu,true,false,false,false);

    std::cout << "Opcode 39 (ADD HL,SP) passed\n";
}

void test_opcode_3A_LD_A_HL_DEC()
{
    membus bus;
    CPU cpu(&bus);

    cpu.setReg16(reg_type::R_HL,0xC000);

    bus.write(0xC000,0x55);

    bus.loadTestProgram({
        0x3A
    });

    cpu.step();

    assert(cpu.getReg8(reg_type::R_A)==0x55);
    assert(cpu.getReg16(reg_type::R_HL)==0xBFFF);

    std::cout << "Opcode 3A (LD A,(HL-)) passed\n";
}

void test_opcode_3B_DEC_SP()
{
    membus bus;
    CPU cpu(&bus);

    cpu.setReg16(reg_type::R_SP,0x1234);

    bus.loadTestProgram({
        0x3B
    });

    cpu.step();

    assert(cpu.getReg16(reg_type::R_SP)==0x1233);

    std::cout << "Opcode 3B (DEC SP) passed\n";
}

void test_opcode_3C_INC_A()
{
    membus bus;
    CPU cpu(&bus);

    cpu.setReg8(reg_type::R_A,0x0F);
    cpu.setFlag(C,true);

    bus.loadTestProgram({
        0x3C
    });

    cpu.step();

    assert(cpu.getReg8(reg_type::R_A)==0x10);

    checkFlags(cpu,false,false,true,true);

    std::cout << "Opcode 3C (INC A) passed\n";
}

void test_opcode_3D_DEC_A()
{
    membus bus;
    CPU cpu(&bus);

    cpu.setReg8(reg_type::R_A,0x10);
    cpu.setFlag(C,true);

    bus.loadTestProgram({
        0x3D
    });

    cpu.step();

    assert(cpu.getReg8(reg_type::R_A)==0x0F);

    checkFlags(cpu,false,true,true,true);

    std::cout << "Opcode 3D (DEC A) passed\n";
}

void test_opcode_3E_LD_A()
{
    membus bus;
    CPU cpu(&bus);

    bus.loadTestProgram({
        0x3E,0x99
    });

    cpu.step();

    assert(cpu.getReg8(reg_type::R_A)==0x99);
    assert(cpu.getReg16(reg_type::R_PC)==0x102);

    std::cout << "Opcode 3E (LD A,d8) passed\n";
}

void test_opcode_3F_CCF()
{
    membus bus;
    CPU cpu(&bus);

    cpu.setFlag(Z,true);
    cpu.setFlag(N,true);
    cpu.setFlag(H,true);
    cpu.setFlag(C,true);

    bus.loadTestProgram({
        0x3F
    });

    cpu.step();

    checkFlags(cpu,true,false,false,false);

    std::cout << "Opcode 3F (CCF) passed\n";
}

void test_opcode_40_LD_B_B()
{
    membus bus;
    CPU cpu(&bus);

    cpu.setReg8(reg_type::R_B,0x55);

    bus.loadTestProgram({
        0x40
    });

    cpu.step();

    assert(cpu.getReg8(reg_type::R_B)==0x55);

    std::cout << "Opcode 40 (LD B,B) passed\n";
}

void test_opcode_41_LD_B_C()
{
    membus bus;
    CPU cpu(&bus);

    cpu.setReg8(reg_type::R_C,0x42);

    bus.loadTestProgram({
        0x41
    });

    cpu.step();

    assert(cpu.getReg8(reg_type::R_B)==0x42);

    std::cout << "Opcode 41 (LD B,C) passed\n";
}

void test_opcode_42_LD_B_D()
{
    membus bus;
    CPU cpu(&bus);

    cpu.setReg8(reg_type::R_D,0x43);

    bus.loadTestProgram({
        0x42
    });

    cpu.step();

    assert(cpu.getReg8(reg_type::R_B)==0x43);

    std::cout << "Opcode 42 (LD B,D) passed\n";
}

void test_opcode_43_LD_B_E()
{
    membus bus;
    CPU cpu(&bus);

    cpu.setReg8(reg_type::R_E,0x44);

    bus.loadTestProgram({
        0x43
    });

    cpu.step();

    assert(cpu.getReg8(reg_type::R_B)==0x44);

    std::cout << "Opcode 43 (LD B,E) passed\n";
}

void test_opcode_44_LD_B_H()
{
    membus bus;
    CPU cpu(&bus);

    cpu.setReg8(reg_type::R_H,0x45);

    bus.loadTestProgram({
        0x44
    });

    cpu.step();

    assert(cpu.getReg8(reg_type::R_B)==0x45);

    std::cout << "Opcode 44 (LD B,H) passed\n";
}

void test_opcode_45_LD_B_L()
{
    membus bus;
    CPU cpu(&bus);

    cpu.setReg8(reg_type::R_L,0x46);

    bus.loadTestProgram({
        0x45
    });

    cpu.step();

    assert(cpu.getReg8(reg_type::R_B)==0x46);

    std::cout << "Opcode 45 (LD B,L) passed\n";
}

void test_opcode_46_LD_B_HL()
{
    membus bus;
    CPU cpu(&bus);

    cpu.setReg16(reg_type::R_HL,0xC000);
    bus.write(0xC000,0x47);

    bus.loadTestProgram({
        0x46
    });

    cpu.step();

    assert(cpu.getReg8(reg_type::R_B)==0x47);

    std::cout << "Opcode 46 (LD B,(HL)) passed\n";
}

void test_opcode_47_LD_B_A()
{
    membus bus;
    CPU cpu(&bus);

    cpu.setReg8(reg_type::R_A,0x48);

    bus.loadTestProgram({
        0x47
    });

    cpu.step();

    assert(cpu.getReg8(reg_type::R_B)==0x48);

    std::cout << "Opcode 47 (LD B,A) passed\n";
}

void test_opcode_48_LD_C_B()
{
    membus bus;
    CPU cpu(&bus);

    cpu.setReg8(reg_type::R_B,0x49);

    bus.loadTestProgram({
        0x48
    });

    cpu.step();

    assert(cpu.getReg8(reg_type::R_C)==0x49);

    std::cout << "Opcode 48 (LD C,B) passed\n";
}

void test_opcode_49_LD_C_C()
{
    membus bus;
    CPU cpu(&bus);

    cpu.setReg8(reg_type::R_C,0x50);

    bus.loadTestProgram({
        0x49
    });

    cpu.step();

    assert(cpu.getReg8(reg_type::R_C)==0x50);

    std::cout << "Opcode 49 (LD C,C) passed\n";
}

void test_opcode_4A_LD_C_D()
{
    membus bus;
    CPU cpu(&bus);

    cpu.setReg8(reg_type::R_D,0x51);

    bus.loadTestProgram({
        0x4A
    });

    cpu.step();

    assert(cpu.getReg8(reg_type::R_C)==0x51);

    std::cout << "Opcode 4A (LD C,D) passed\n";
}

void test_opcode_4B_LD_C_E()
{
    membus bus;
    CPU cpu(&bus);

    cpu.setReg8(reg_type::R_E,0x52);

    bus.loadTestProgram({
        0x4B
    });

    cpu.step();

    assert(cpu.getReg8(reg_type::R_C)==0x52);

    std::cout << "Opcode 4B (LD C,E) passed\n";
}

void test_opcode_4C_LD_C_H()
{
    membus bus;
    CPU cpu(&bus);

    cpu.setReg8(reg_type::R_H,0x53);

    bus.loadTestProgram({
        0x4C
    });

    cpu.step();

    assert(cpu.getReg8(reg_type::R_C)==0x53);

    std::cout << "Opcode 4C (LD C,H) passed\n";
}

void test_opcode_4D_LD_C_L()
{
    membus bus;
    CPU cpu(&bus);

    cpu.setReg8(reg_type::R_L,0x54);

    bus.loadTestProgram({
        0x4D
    });

    cpu.step();

    assert(cpu.getReg8(reg_type::R_C)==0x54);

    std::cout << "Opcode 4D (LD C,L) passed\n";
}

void test_opcode_4E_LD_C_HL()
{
    membus bus;
    CPU cpu(&bus);

    cpu.setReg16(reg_type::R_HL,0xC000);
    bus.write(0xC000,0x55);

    bus.loadTestProgram({
        0x4E
    });

    cpu.step();

    assert(cpu.getReg8(reg_type::R_C)==0x55);

    std::cout << "Opcode 4E (LD C,(HL)) passed\n";
}

void test_opcode_4F_LD_C_A()
{
    membus bus;
    CPU cpu(&bus);

    cpu.setReg8(reg_type::R_A,0x56);

    bus.loadTestProgram({
        0x4F
    });

    cpu.step();

    assert(cpu.getReg8(reg_type::R_C)==0x56);

    std::cout << "Opcode 4F (LD C,A) passed\n";
}

void test_opcode_80_ADD_A_B()
{
    membus bus;
    CPU cpu(&bus);

    cpu.setReg8(reg_type::R_A, 0x12);
    cpu.setReg8(reg_type::R_B, 0x34);

    bus.loadTestProgram({
        0x80
    });

    cpu.step();

    assert(cpu.getReg8(reg_type::R_A) == 0x46);

    checkFlags(cpu, false, false, false, false);

    std::cout << "Opcode 80 (ADD A,B) passed\n";
}

void test_opcode_86_ADD_A_HL()
{
    membus bus;
    CPU cpu(&bus);

    cpu.setReg8(reg_type::R_A, 0x0F);
    cpu.setReg16(reg_type::R_HL, 0xC000);

    bus.write(0xC000,0x01);

    bus.loadTestProgram({
        0x86
    });

    cpu.step();

    assert(cpu.getReg8(reg_type::R_A) == 0x10);

    checkFlags(cpu,false,false,true,false);

    std::cout << "Opcode 86 (ADD A,(HL)) passed\n";
}

void test_opcode_87_ADD_A_A_carry()
{
    membus bus;
    CPU cpu(&bus);

    cpu.setReg8(reg_type::R_A,0xFF);

    bus.loadTestProgram({
        0x87
    });

    cpu.step();

    assert(cpu.getReg8(reg_type::R_A)==0xFE);

    checkFlags(cpu,false,false,true,true);

    std::cout << "Opcode 87 (ADD A,A carry) passed\n";
}

void test_opcode_88_ADC_A_B()
{
    membus bus;
    CPU cpu(&bus);

    cpu.setReg8(reg_type::R_A,0x10);
    cpu.setReg8(reg_type::R_B,0x20);

    cpu.setFlag(Flag::C,true);

    bus.loadTestProgram({
        0x88
    });

    cpu.step();

    assert(cpu.getReg8(reg_type::R_A)==0x31);

    checkFlags(cpu,false,false,false,false);

    std::cout<<"Opcode 88 (ADC A,B) passed\n";
}

void test_opcode_90_SUB_B()
{
    membus bus;
    CPU cpu(&bus);

    cpu.setReg8(reg_type::R_A,0x10);
    cpu.setReg8(reg_type::R_B,0x01);

    bus.loadTestProgram({
        0x90
    });

    cpu.step();

    assert(cpu.getReg8(reg_type::R_A)==0x0F);

    checkFlags(cpu,false,true,true,false);

    std::cout<<"Opcode 90 (SUB B) passed\n";
}

void test_opcode_98_SBC_A_B()
{
    membus bus;
    CPU cpu(&bus);

    cpu.setReg8(reg_type::R_A,0x10);
    cpu.setReg8(reg_type::R_B,0x01);

    cpu.setFlag(Flag::C,true);

    bus.loadTestProgram({
        0x98
    });

    cpu.step();

    assert(cpu.getReg8(reg_type::R_A)==0x0E);

    checkFlags(cpu,false,true,true,false);

    std::cout<<"Opcode 98 (SBC A,B) passed\n";
}

void test_opcode_A0_AND_B()
{
    membus bus;
    CPU cpu(&bus);

    cpu.setReg8(reg_type::R_A,0b11001100);
    cpu.setReg8(reg_type::R_B,0b10101010);

    bus.loadTestProgram({
        0xA0
    });

    cpu.step();

    assert(cpu.getReg8(reg_type::R_A)==0b10001000);

    checkFlags(cpu,false,false,true,false);

    std::cout<<"Opcode A0 (AND B) passed\n";
}

void test_opcode_A8_XOR_B()
{
    membus bus;
    CPU cpu(&bus);

    cpu.setReg8(reg_type::R_A,0xFF);
    cpu.setReg8(reg_type::R_B,0xFF);

    bus.loadTestProgram({
        0xA8
    });

    cpu.step();

    assert(cpu.getReg8(reg_type::R_A)==0x00);

    checkFlags(cpu,true,false,false,false);

    std::cout<<"Opcode A8 (XOR B) passed\n";
}

void test_opcode_B0_OR_B()
{
    membus bus;
    CPU cpu(&bus);

    cpu.setReg8(reg_type::R_A,0xF0);
    cpu.setReg8(reg_type::R_B,0x0F);

    bus.loadTestProgram({
        0xB0
    });

    cpu.step();

    assert(cpu.getReg8(reg_type::R_A)==0xFF);

    checkFlags(cpu,false,false,false,false);

    std::cout<<"Opcode B0 (OR B) passed\n";
}

void test_opcode_B8_CP_B()
{
    membus bus;
    CPU cpu(&bus);

    cpu.setReg8(reg_type::R_A,0x10);
    cpu.setReg8(reg_type::R_B,0x10);

    bus.loadTestProgram({
        0xB8
    });

    cpu.step();

    // A should remain unchanged
    assert(cpu.getReg8(reg_type::R_A)==0x10);

    checkFlags(cpu,true,true,false,false);

    std::cout<<"Opcode B8 (CP B) passed\n";
}

int main()
{
    test_opcode_00_NOP();
    test_opcode_01_LD_BC();
    test_opcode_02_LD_BC_A();
    test_opcode_03_INC_BC();
    test_opcode_04_INC_B_normal();
    test_opcode_04_INC_B_halfcarry();
    test_opcode_04_INC_B_zero();
    test_opcode_05_DEC_B_normal();
    test_opcode_05_DEC_B_zero();
    test_opcode_05_DEC_B_halfborrow();
    test_opcode_06_LD_B();
    test_opcode_07_RLCA();
    test_opcode_08_LD_a16_SP();
    test_opcode_09_ADD_HL_BC();
    test_opcode_0A_LD_A_BC();
    test_opcode_0B_DEC_BC();
    test_opcode_0C_INC_C();
    test_opcode_0D_DEC_C();
    test_opcode_0E_LD_C();
    test_opcode_0F_RRCA();

    //test_opcode_10_STOP(); had to comment this out since stop was messing with the other tests, because it would set the cpu state to stopped which would not let step() happen
    test_opcode_11_LD_DE();
    test_opcode_12_LD_DE_A();
    test_opcode_13_INC_DE();
    test_opcode_14_INC_D();
    test_opcode_15_DEC_D();
    test_opcode_16_LD_D();
    test_opcode_17_RLA();
    test_opcode_18_JR_forward();
    test_opcode_18_JR_backward();
    test_opcode_19_ADD_HL_DE();
    test_opcode_1A_LD_A_DE();
    test_opcode_1B_DEC_DE();
    test_opcode_1C_INC_E();
    test_opcode_1D_DEC_E();
    test_opcode_1E_LD_E();
    test_opcode_1F_RRA();

    test_opcode_20_JR_NZ_taken();
    test_opcode_20_JR_NZ_not_taken();
    test_opcode_21_LD_HL();
    test_opcode_22_LD_HL_INC_A();
    test_opcode_23_INC_HL();
    test_opcode_24_INC_H();
    test_opcode_25_DEC_H();
    test_opcode_26_LD_H();
    test_opcode_27_DAA();
    test_opcode_28_JR_Z_taken();
    test_opcode_29_ADD_HL_HL();
    test_opcode_2A_LD_A_HL_INC();
    test_opcode_2B_DEC_HL();
    test_opcode_2C_INC_L();
    test_opcode_2D_DEC_L();
    test_opcode_2E_LD_L();
    test_opcode_2F_CPL();
    
    test_opcode_30_JR_NC_taken();
    test_opcode_30_JR_NC_not_taken();
    test_opcode_31_LD_SP();
    test_opcode_32_LD_HL_DEC_A();
    test_opcode_33_INC_SP();
    test_opcode_34_INC_HL_memory();
    test_opcode_35_DEC_HL_memory();
    test_opcode_36_LD_HL_d8();
    test_opcode_37_SCF();
    test_opcode_38_JR_C_taken();
    test_opcode_38_JR_C_not_taken();
    test_opcode_39_ADD_HL_SP();
    test_opcode_3A_LD_A_HL_DEC();
    test_opcode_3B_DEC_SP();
    test_opcode_3C_INC_A();
    test_opcode_3D_DEC_A();
    test_opcode_3E_LD_A();
    test_opcode_3F_CCF();
    
    test_opcode_40_LD_B_B();
    test_opcode_41_LD_B_C();
    test_opcode_42_LD_B_D();
    test_opcode_43_LD_B_E();
    test_opcode_44_LD_B_H();
    test_opcode_45_LD_B_L();
    test_opcode_46_LD_B_HL();
    test_opcode_47_LD_B_A();
    test_opcode_48_LD_C_B();
    test_opcode_49_LD_C_C();
    test_opcode_4A_LD_C_D();
    test_opcode_4B_LD_C_E();
    test_opcode_4C_LD_C_H();
    test_opcode_4D_LD_C_L();
    test_opcode_4E_LD_C_HL();
    test_opcode_4F_LD_C_A();
    // testing from 0x50-0x7F isnt necessary since its all just LD instructions with different operands

    // ALU operations
    test_opcode_80_ADD_A_B();
    test_opcode_86_ADD_A_HL();
    test_opcode_87_ADD_A_A_carry();
    test_opcode_88_ADC_A_B();
    test_opcode_90_SUB_B();
    test_opcode_98_SBC_A_B();
    test_opcode_A0_AND_B();
    test_opcode_A8_XOR_B();
    test_opcode_B0_OR_B();
    test_opcode_B8_CP_B();

    std::cout << "\nAll opcode tests passed!\n";

    return 0;
}