#include <cstdint>
#include "../bus/membus.h"

class timer{
    
    public:
        timer(membus* bus);
        void step(uint8_t cycles);
        // getters and setters for all timer registers
        void setDiv(uint8_t value);
        void setTima(uint8_t value);
        void setTma(uint8_t value);
        void setTac(uint8_t value);
        uint8_t getDiv();
        uint8_t getTima();
        uint8_t getTma();
        uint8_t getTac();
    private:
        membus* bus;
        uint8_t div;    // divider register (0xFF04)
        uint8_t tima;   // timer counter (0xFF05)
        uint8_t tma;    // timer modulo (0xFF06)
        uint8_t tac;    // timer control (0xFF07)

        uint16_t div_counter;
        uint16_t timer_counter;
        uint16_t div_cycles;   // accumulator for DIV (counts to 256)
        uint16_t tima_cycles;  // accumulator for TIMA
        uint16_t getTimaRate(); // returns cycles per TIMA tick based on TAC
};  