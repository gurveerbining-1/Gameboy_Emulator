#include "../bus/membus.h"
#include <cstdint>

class Cartridge{
    public:

    private:
        uint8_t entry[4]; // Most commercial games fill this 4-byte area with a nop instruction followed by a jp $0150
        static constexpr uint8_t logo[0x30] = {0xCE, 0xED, 0x66, 0x66, 0xCC, 0x0D, 0x00, 0x0B, 0x03, 0x73, 0x00, 0x83, 0x00, 0x0C, 0x00, 0x0D,
        0x00, 0x08, 0x11, 0x1F, 0x88, 0x89, 0x00, 0x0E, 0xDC, 0xCC, 0x6E, 0xE6, 0xDD, 0xDD, 0xD9, 0x99, 0xBB, 0xBB, 0x67, 0x63, 
        0x6E, 0x0E, 0xEC, 0xCC, 0xDD, 0xDC, 0x99, 0x9F, 0xBB, 0xB9, 0x33, 0x3E}; // 48 hex bytes

        char title[16]; //16 character title, padded with 00s if less than 16
        uint8_t cgbflag;
        uint16_t new_license_code;
        uint8_t sgbflag;
        uint8_t cartridge_type;
        uint8_t ROM_size;
        uint8_t RAM_size;
        uint8_t dest_code; // either Japan (0x0) or overseas (0x1)
        uint8_t old_license_code; // 0x33 (or $33 as written in pandocs) indicates that the new license code must be used instead 
        uint8_t version; // mask rom version number
        uint8_t checksum; // bootrom verifies the checksum 
        uint8_t global_checksum;
};