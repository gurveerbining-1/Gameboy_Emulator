#include "MBC3.h"

MBC3::MBC3()
    : rtc_seconds(0),
      rtc_minutes(0),
      rtc_hours(0),
      rtc_dl(0),
      rtc_dh(0),
      ram_and_timer_enable(false),
      ram_rtc_select(0),
      rom_bank_number(1),
      ram_bank_number(0),
      latch_clock_data(0),
      ram_data(4 * 8192)
{
    // initialize ram_data, allocate 32KB space for now,
    // ram size is determined from the header at 0x0149
}

void MBC3::load(const std::string& path){
    Cartridge::load(path);  // call base first, populates rom_data, sets sav_path
    
    // NOW rom_data is populated, safe to read header
    uint8_t ram_size_code = rom_data[0x0149];
    size_t ram_size = 0;
    switch(ram_size_code){
        case 0x00: ram_size = 0;       break;
        case 0x01: ram_size = 2048;    break;
        case 0x02: ram_size = 8192;    break;
        case 0x03: ram_size = 32768;   break;
        case 0x04: ram_size = 131072;  break;
    }
    ram_data.resize(ram_size, 0xFF);
    
    // load save file if it exists
    std::ifstream sav(sav_path, std::ios::binary);
    if(sav && !ram_data.empty()){
        sav.read(reinterpret_cast<char*>(ram_data.data()), ram_data.size());
    }

}

void MBC3::save(){
    if(ram_data.empty()) return;
    std::ofstream sav(sav_path, std::ios::binary);
    sav.write(reinterpret_cast<char*>(ram_data.data()), ram_data.size());
}

uint8_t MBC3::read(uint16_t addr){
    if(addr <= 0x3FFF){
        return rom_data[addr]; 
    }
    else if(addr <= 0x7FFF){
        /*
        Same as for MBC1, except that accessing banks $20, $40, and $60 is supported now.
        */
        size_t index = rom_bank_number * 0x4000 + (addr - 0x4000);

        if(index >= rom_data.size())
            return 0xFF;

        return rom_data[index];
    }
    else if(addr >= 0xA000 && addr <= 0xBFFF){

        if(!ram_and_timer_enable)
            return 0xFF;

        if(ram_rtc_select <= 0x07){
            // RAM bank
            size_t index = ram_rtc_select * 0x2000
                         + (addr - 0xA000);

            if(index >= ram_data.size())
                return 0xFF;

            return ram_data[index];
        }
        else if(ram_rtc_select >= 0x08 &&
                ram_rtc_select <= 0x0C){
            // RTC register
            // handle this later
        }

        return 0xFF;
    }
    return 0xFF;
}

void MBC3::writeRegister(uint16_t addr, uint8_t value){
    if(addr <= 0x1FFF){
        if((value & 0x0F) == 0x0A){
            ram_and_timer_enable = true;
        }
        else{
            ram_and_timer_enable = false;
        }
    }
    else if(addr <= 0x3FFF){
        rom_bank_number = value & 0x7F;

        if(rom_bank_number == 0){
            rom_bank_number = 1;
        }

    }
    else if(addr <= 0x5FFF){
        ram_rtc_select = value & 0x0F;
    }
    else if(addr <= 0x7FFF){
    }
    else if(addr >= 0xA000 && addr <= 0xBFFF){
    }
}

