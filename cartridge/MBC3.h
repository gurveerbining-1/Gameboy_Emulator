#include "Cartridge.h"

class MBC3 : public Cartridge{
    public:
        MBC3();
        uint8_t read(uint16_t addr);
        void writeRegister(uint16_t addr, uint8_t value);
        void save();
        void load(const std::string& path);

    private:
        uint8_t rtc_seconds;            //
        uint8_t rtc_minutes;            //
        uint8_t rtc_hours;              //
        uint8_t rtc_dl;                 // Lower 8 bits of Day Counter
        uint8_t rtc_dh;                 // Upper 1 bit of Day Counter, Carry Bit, Halt Flag. Bit 0: Most significant bit (Bit 8) of Day Counter Bit 6: Halt (0=Active, 1=Stop Timer) Bit 7: Day Counter Carry Bit (1=Counter Overflow)
        uint8_t ram_and_timer_enable;   //
        uint8_t ram_rtc_select;
        uint8_t rom_bank_number;        //
        uint8_t ram_bank_number;        //
        uint8_t latch_clock_data;       //
        std::vector<uint8_t> ram_data;  // vector for external RAM (up to 32KB, 4 banks of 8KB)
};