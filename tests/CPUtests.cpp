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

    std::cout << "\nAll opcode tests passed!\n";

    return 0;
}