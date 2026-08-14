#include "membus.h"
#include "../cartridge/Cartridge.h"
#include "../timer/timer.h"
#include "../input/Joypad.h"

membus::membus() : cartridge(std::make_unique<Cartridge>()){}

void membus::loadCartridge(const std::string& path){
    cartridge->load(path);
    uint8_t type = cartridge->getCartridgeType();
    if(type == 0x01 || type == 0x02 || type == 0x03){
        /*
        $01	MBC1
        $02	MBC1+RAM
        $03	MBC1+RAM+BATTERY
        */
        cartridge = std::make_unique<MBC1>();
        cartridge->load(path);
    }
    else if(type == 0x05 || type == 0x06){
        /*
        $05	MBC2
        $06	MBC2+BATTERY
        */
        //cartridge = std::make_unique<MBC2>();
        //cartridge->load(path);
        
    }
    else if(type == 0x0F || type == 0x10 || type == 0x11 || type == 0x12 || type == 0x13){
        /*
        $0F	MBC3+TIMER+BATTERY
        $10	MBC3+TIMER+RAM+BATTERY 12
        $11	MBC3
        $12	MBC3+RAM 12
        $13	MBC3+RAM+BATTERY 
        */
        //cartridge = std::make_unique<MBC3>();
        //cartridge->load(path);
    }
    /*
    read the file
    peek at byte 0x147
    if type is 0x01/0x02/0x03: cartridge = make_unique<MBC1>()
    else if type is MBC3: cartridge = make_unique<MBC3>()
    else: cartridge = make_unique<Cartridge>()
    cartridge->load(path)
    */
}   

void membus::setTimer(timer *t){
    timr = t;
}

void membus::setJoypad(Joypad *j){
    pad = j;
}

uint8_t membus::read(uint16_t addr){
    /*
     if addr is 0x0000–0x7FFF, delegate to cartridge.read(addr). Otherwise fall through to flat memory array for RAM regions.
    */
    uint8_t value;

    //if (addr == 0xFF44) return 0x90;
    
    if(testMode){
        return memory[addr];
    }

    if(addr <= 0x7FFF || (addr >= 0xA000 && addr <= 0xBFFF)){
        value = cartridge->read(addr);
    } 
    else {
        value = memory[addr];
    }
    if(addr == 0xFF00){ return pad->read(); }
    if(addr == 0xFF04){ return timr->getDiv(); }
    if(addr == 0xFF05){ return timr->getTima(); }
    if(addr == 0xFF06){ return timr->getTma(); }
    if(addr == 0xFF07){ return timr->getTac(); }
    //printf("READ %04X -> %02X\n", addr, value);

    return value;

}
void membus::write(uint16_t addr, uint8_t value){
    // if(addr == 0xFF01 || addr == 0xFF02){
    //     std::cout << "SERIAL WRITE addr: 0x"
    //               << std::hex << addr
    //               << " value: 0x"
    //               << (int)value
    //               << std::endl;
    // }

    if(addr <= 0x7FFF){
        cartridge->writeRegister(addr, value);
        return; // don't write to flat memory array
    }
    if(addr >= 0xA000 && addr <= 0xBFFF){
        cartridge->writeRegister(addr, value);
        return;
    }
    
    memory[addr] = value;

    if(addr == 0xFF00) pad->write(value);
    if(addr == 0xFF02 && (value & 0x80)){
        std::cout << static_cast<char>(memory[0xFF01]) << std::flush;
    }
    if(addr == 0xFF04){ timr->setDiv(0); return; }  // writing DIV always resets to 0
    if(addr == 0xFF05){ timr->setTima(value); return; }
    if(addr == 0xFF06){ timr->setTma(value); return; }
    if(addr == 0xFF07){ timr->setTac(value); return; }
    //if (addr == 0xFF40) printf("LCDC write: %02X\n", value);
    if(addr == 0xFF46){
        uint16_t source = static_cast<uint16_t>(value) << 8;
        for(int i = 0; i <= 0x9F; i++){
            memory[0xFE00 + i] = read(static_cast<uint16_t>(source + i));
        }
        return;
    }
}

// Use this to write and test each opcode to test things as instructions are implemented
void membus::loadTestProgram(const std::vector<uint8_t>& program){
    testMode = true;
    std::copy(program.begin(), program.end(), &memory[0x100]);
}
