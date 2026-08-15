#include "Cartridge.h"

class MBC1 : public Cartridge{
    public:
        MBC1();
        uint8_t read(uint16_t addr);
        void writeRegister(uint16_t addr, uint8_t value);
        void save();
        void load(const std::string& path);
    private:
        bool ram_enabled;               // bool, only allow RAM reads/writes when true
        uint8_t rom_bank;               // 5-bit value (bits 0-4), the lower ROM bank number
        uint8_t upper_bits;             // 2-bit value (bits 5-6 of ROM bank, OR RAM bank number)
        uint8_t banking_mode;           // 0 = ROM banking mode, 1 = RAM banking mode
        std::vector<uint8_t> ram_data;  // vector for external RAM (up to 32KB, 4 banks of 8KB)
        uint8_t current_ram_bank;       // which 8KB RAM bank is visible at 0xA000-0xBFFF
};