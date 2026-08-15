#include "timer.h"

timer::timer(membus* bus) : bus(bus){
    div_counter = 0;
    timer_counter = 0;
    div_cycles = 0;
    tima_cycles = 0;
}

uint16_t timer::getTimaRate(){
    switch(tac & 0x03){ // isolate bottom 2 bits
        case 0: return 1024; //  clock select: 00   increment every 256 machine cycles (x4 to get clock cycles)
        case 1: return 16;   //  clock select: 01  increment every 4 machine cycles (x4 to get clock cycles)
        case 2: return 64;   //  clock select: 10  increment every 16 machine cycles (x4 to get clock cycles)
        case 3: return 256;  //  clock select: 11  increment every 64 machine cycles (x4 to get clock cycles)
    }
    return 1024; 
}

void timer::step(uint8_t cycles){
    // DIV always increments
    div_cycles += cycles;
    while(div_cycles >= 256){
        div_cycles -= 256;
        div++;
    }

    // TIMA only increments if timer is enabled (TAC bit 2)
    if(!(tac & 0x04)) return;

    tima_cycles += cycles;
    uint16_t rate = getTimaRate();
    
    while(tima_cycles >= rate){
        tima_cycles -= rate;
        tima++;
        
        if(tima == 0){
            // overflow — reload from TMA and request interrupt
            tima = tma;
            uint8_t IF = bus->read(0xFF0F);
            bus->write(0xFF0F, IF | 0x04);  // bit 2 = timer interrupt
        }
    }
}

void timer::setDiv(uint8_t value){
    div = value;
}
void timer::setTima(uint8_t value){
    tima = value;
}

void timer::setTma(uint8_t value){
    tma = value;
}

void timer::setTac(uint8_t value){
    tac = value;
}

uint8_t timer::getDiv(){
    return div;
}

uint8_t timer::getTima(){
    return tima;
}

uint8_t timer::getTma(){
    return tma;
}

uint8_t timer::getTac(){
    return tac;
}

