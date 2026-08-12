#include "Joypad.h"

Joypad::Joypad(membus *bus) : bus(bus){
    select_bits = 0x30;
    action_state = 0x0F;
    direction_state = 0x0F;

    /*
    0x30 → neither group selected
    0x0F → all buttons released
    Released = 1
    Pressed = 0
    */
}


uint8_t Joypad::read(){
    uint8_t result = 0xFF;
    
    // bit 5 low = game wants action buttons
    if (!(select_bits & 0x20)) {
        result &= (action_state | 0xF0);    // lower nibble = button states
    }

    // bit 4 low = game wants direction buttons  
    if (!(select_bits & 0x10)) {
        result &= (direction_state | 0xF0);
    }

    // preserve the select bits in result
    result = (result & 0x0F) | (select_bits & 0x30) | 0xC0;

    return result;
}

void Joypad::write(uint8_t value){
    select_bits = value & 0x30;
}

void Joypad::buttonPress(uint8_t button){
    if (button <= BTN_DOWN) { // direction 
        direction_state &= ~(1 << button);
    } else { // action
        action_state &= ~(1 << (button - 4));
    }

    requestInterrupt();
}

void Joypad::buttonRelease(uint8_t button){
    if (button <= BTN_DOWN) { // direction 
        direction_state |= (1 << button);
    } else { // action
        action_state |= (1 << (button - 4));
    }

}

void Joypad::requestInterrupt(){
    uint8_t interrupt_flags = bus->read(0xFF0F);
    interrupt_flags |= 0x10; // joypad interrupt is in bit 4, turn it on
    bus->write(0xFF0F, interrupt_flags);
}


