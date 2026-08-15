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
        virtual void load(const std::string& path);
        virtual uint8_t read(uint16_t addr);
        virtual void writeRegister(uint16_t addr, uint8_t value);
        virtual void save();
        uint8_t getCartridgeType();
    protected: // moved these to protected for the MBC subclasses
        std::vector<uint8_t> rom_data;
        uint8_t cartridge_type;
        std::string rom_path;
        std::string sav_path;

    private:
        void parseHeader();
        uint8_t current_rom_bank = 1;
        
};  
