#pragma once
#include <cstdint>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <memory>
#include "bootROM.h"

class Cartridge{
    public:
        void load(const std::string& path);
        virtual uint8_t read(uint16_t addr);
        virtual void writeRegister(uint16_t addr, uint8_t value);
        uint8_t getCartridgeType();
    protected: // moved these to protected for the MBC subclasses
        std::vector<uint8_t> rom_data;
        uint8_t cartridge_type;

    private:
        uint8_t entry[4]; // Most commercial games fill this 4-byte area with a nop instruction followed by a jp $0150
        static constexpr uint8_t logo[0x30] = {0xCE, 0xED, 0x66, 0x66, 0xCC, 0x0D, 0x00, 0x0B, 0x03, 0x73, 0x00, 0x83, 0x00, 0x0C, 0x00, 0x0D,
        0x00, 0x08, 0x11, 0x1F, 0x88, 0x89, 0x00, 0x0E, 0xDC, 0xCC, 0x6E, 0xE6, 0xDD, 0xDD, 0xD9, 0x99, 0xBB, 0xBB, 0x67, 0x63, 
        0x6E, 0x0E, 0xEC, 0xCC, 0xDD, 0xDC, 0x99, 0x9F, 0xBB, 0xB9, 0x33, 0x3E}; // 48 hex bytes
        void parseHeader();

        uint8_t current_rom_bank = 1;
        
};  
