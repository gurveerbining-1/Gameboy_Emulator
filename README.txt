sources:
https://gbdev.io/pandocs/
https://www.youtube.com/watch?v=SCHlyX2sFN8
https://gekkio.fi/files/gb-docs/gbctr.pdf

Flow for GameBoy:
1. ROM Loader
2. Memory Bus
3. CPU
4. PPU (graphics/video)
5. APU (audio)
6. Input
7. Timers
8. Interrupt System
9. Main Emulation Loop

What to know about loading instructions:
    - copy data from one place (register, memory, immediate value) to another
    - memory address can use immediate values or register values as operands (including as memory addresses)
    - a register is a small bit of memory that is in a CPU and is only big enough for a single value
    - usually what happens in assembly is:
        - load some values from memory or immediate values into the register
        - perform some operations on that data
        - then store the result back to memory
    - There are 7 general purpose 8 bit registers used by the GameBoy:
        - A B C D E H L
        - registers can be combined into 16 bit registers:
            - AF BC DE HL
            - the lower 8 bits of the AF register are as follow:
            | Bit |	Name |	Explanation             |
            | 7	  |   z	 |  Zero flag               |
            | 6	  |   n	 |  Subtraction flag (BCD)  |
            | 5	  |   h	 |  Half Carry flag (BCD)   |
            | 4	  |   c	 |  Carry flag              |
    - A register and HL registers are special:
        - A is an accumulator (the accumulator is the primary register used by many arithmetic and logic instructions) 
        - looks like: A = A operation Thing
        - HL is primarily the register that can be used for addresses when accessing memory (only exceptions are simple load instruction)
    - There are also 3 special registers used by the GameBoy:
        - SP PC F
        - SP is the stack pointer and is the address of the top of the call stack (in RAM) (it is set to FFFE when the GameBoy starts up) when the stack grows SP gets smaller
        - PC is the program counter and is the address of the next instruction to be executed, every instruction changes PC either by incrementing it by the number of bytes used to encode the instruction or by setting it to a particular value
        - F is the flag register
    - GameBoy is little endian which means that the first byte of a 16 bit value is the least significant byte and the second byte is the most significant (this can be confusing since we tend to right byte data left to right and this is opposite)
        - Example (0x1234 in memory): 
            [address]     = 0x34
            [address + 1] = 0x12

Understanding the CPU instruction set:
The first byte of each instruction is typically called the “opcode” (for “operation code”). 
By noticing that some instructions perform identical operations but with different parameters, they can be grouped together; for example, 
inc bc, inc de, inc hl, and inc sp differ only in what 16-bit register they modify.
In each table, one line represents one such grouping. Since many groupings have some variation, 
the variation has to be encoded in the instruction; for example, the above four instructions will be collectively referred to as
inc r16. Here are the possible placeholders and their values:
	    0	1	2	3	4	5	6	    7
r8  	b	c	d	e	h	l	[hl]	a
r16	    bc	de	hl	sp	
r16stk	bc	de	hl	af	
r16mem	bc	de	hl+	hl-	
cond	nz	z	nc	c	
b3	        A 3-bit bit index
tgt3	    rst's target address, divided by 8
imm8	    The following byte
imm16	    The following two bytes, in little-endian order

r8          - 8 bit register
r16         - 16 bit register
r16stk      - A set of 16-bit register pairs that are allowed to be pushed/popped to RAM via the stack (by using the stack pointer)
r16mem      - A set of 16-bit register pairs that are used as memory addresses (behave like pointers into RAM)
cond        - condition code (2 bits inside the opcode) selects whether a conditional branch is taken, based on CPU flags, nz (not zero), z (zero), nc (no carry), c (carry) 
b3          - 3 bit index (number that can be stored from 0 to 7 AKA a number that can be stored in 3 bits) this is used for bit manipulation
tgt3	    - rst's (Restart Instruction which is basically a tiny, fixed-address function call built into the CPU) target address, divided by 8 (basically means the opcode just stores a 3 bit number and selects one of 8 fixed locations to jump to) where the actual address is computed as tgt3 × 8
imm8        - The following byte of the instruction
imm16       - The following two bytes of the instruction, in little-endian order

HOW TO READ OPCODE TABLE:
combine row + column (example: row 3x and column xE combine to opcode: 0x3E)
the two numbers under the instruction respectively are: the instruction length (in bytes) and number of machine cycles (1 machine cycle = 4 clock cycles, use clock cycles for the emulator)
the four dashes (- - - -) underneath the instruction length and number of machine cycles show which cpu flags are effected by the instruction

About Interrupts:
Interrupts are hardware signals that force the CPU to pause its current tasks, jump to a specific block of code to handle an event
(like a button press or screen update), and then resume what it was doing. There are 3 things that make interrupts work:
    1. Interrupt Request Flag (IF): Hardware sets a bit to flag which event happened
    2. Interrupt Enable Flags (EF): Software sets a bit to choose which events the system is currently allowed to deal with
    3. Interrupt Master Enable (IME): An on/off switch for all interrupts combined

THE 5 INTERRUPTS:
    VBlank (Vertical Blank): The most crucial interrupt. It triggers when the screen finishes drawing one frame and enters the blanking period. This is the only time the game can safely update graphics/VRAM without causing visual glitches.
    LCD STAT (LCD Status): Triggers based on specific states of the LCD screen (e.g., reaching a specific horizontal line), useful for advanced visual effects like raster bars or parallax scrolling.
    Timer: Triggers when the Game Boy's internal timer overflows, commonly used for tracking real-time events or timing game logic.
    Serial: Triggers when the Game Boy link cable finishes sending or receiving a byte of data.
    Joypad: Triggers when a button on the Game Boy is pressed, instantly waking the console from low-power states.

File architecture:
    src/
    │
    ├── cpu/
    │   ├── cpu.cpp
    │   ├── cpu.h
    │   ├── instructions.cpp
    │   ├── instructions.h
    │   └── registers.h
    │
    ├── bus/
    │   ├── bus.cpp
    │   └── bus.h
    │
    ├── memory/
    │   ├── ram.cpp
    │   ├── ram.h
    │   ├── vram.cpp
    │   └── vram.h
    │
    ├── cartridge/
    │   ├── cartridge.cpp
    │   ├── cartridge.h
    │   ├── mbc1.cpp
    │   └── mbc1.h
    │
    ├── ppu/
    │   ├── ppu.cpp
    │   └── ppu.h
    │
    ├── timer/
    │   ├── timer.cpp
    │   └── timer.h
    │
    ├── input/
    │   ├── joypad.cpp
    │   └── joypad.h
    │
    ├── apu/
    │   ├── apu.cpp
    │   ├── apu.h
    │   ├── channel1.cpp
    │   ├── channel2.cpp
    │   ├── channel3.cpp
    │   ├── channel4.cpp
    │
    ├── platform/
    │   ├── audio.cpp
    │   ├── audio.h
    │   ├── window.cpp
    │   └── input.cpp    
    |
    ├── gameboy/
    │   ├── gameboy.cpp
    │   └── gameboy.h
    │
    └── main.cpp


