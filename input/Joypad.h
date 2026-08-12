#include "../bus/membus.h"

class Joypad{
    public:
        Joypad(membus* bus);
        uint8_t read(); // membus::read(0xFF00) calls this
        void write(uint8_t value); // membus::write(0xFF00, value) calls this
        void buttonPress(uint8_t button);
        void buttonRelease(uint8_t button);

        static constexpr uint8_t BTN_RIGHT  = 0;
        static constexpr uint8_t BTN_LEFT   = 1;
        static constexpr uint8_t BTN_UP     = 2;
        static constexpr uint8_t BTN_DOWN   = 3;
        static constexpr uint8_t BTN_A      = 4;
        static constexpr uint8_t BTN_B      = 5;
        static constexpr uint8_t BTN_SELECT = 6;
        static constexpr uint8_t BTN_START  = 7;


    private:
        membus* bus;
        uint8_t select_bits;    // bits 4-5 written by game (which group to read)
        uint8_t action_state;   // bits 0-3, 0=pressed for A/B/Select/Start
        uint8_t direction_state;// bits 0-3, 0=pressed for Right/Left/Up/Down

        void requestInterrupt();
};