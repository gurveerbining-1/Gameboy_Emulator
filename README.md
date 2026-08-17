# Game Boy Emulator

A Nintendo Game Boy (DMG) emulator written in C++, focused on hardware emulation, clean architecture, and testing against established Game Boy test ROMs.

---

## Screenshots

<img width="363" height="287" alt="image" src="https://github.com/user-attachments/assets/dd7e04a3-8846-4bb5-a6ff-f4945095d02e" />
<img width="363" height="284" alt="image" src="https://github.com/user-attachments/assets/20d639c0-cf0d-4474-a756-337fdd5c13ba" />
<img width="365" height="288" alt="image" src="https://github.com/user-attachments/assets/f6b6152e-8afc-40fe-8760-aecb534c0fe5" />


---

## Features

- **Full CPU** — All 500+ opcodes including the CB-prefix extended instruction set
- **Passes Blargg's CPU test ROMs** — `01-special`, `03` through `11` all pass
- **PPU** — Background, window, and sprite rendering with Game Boy priority rules
- **MBC Support** — MBC1 cartridge types (MBC3 support currently in development)
- **Battery saves** — SRAM persistence via `.sav` files
- **Timer** — DIV, TIMA, TMA, TAC registers with correct overflow and interrupt behavior
- **Interrupts** — VBlank, STAT, Timer, Serial, and Joypad with correct IME/EI delay behavior
- **Joypad** — Full 8-button input via keyboard

---

## Controls

| Game Boy | Keyboard |
|----------|----------|
| A | `Z` |
| B | `X` |
| Start | `C` |
| Select | `V` |
| D-Pad | Arrow keys |

---

## Building

### Prerequisites

- C++17 compiler (GCC or Clang)
- SDL2
- CMake 3.15+

### Linux / WSL

```bash
git clone https://github.com/gurveerbining-1/Gameboy_Emulator.git
cd Gameboy_Emulator

cmake -S . -B build
cmake --build build
```

## Compatibility

Games tested so far:

| Game | MBC | Status |
|------|-----|--------|
| Super Mario Land | MBC1 | ✅ Playable |
| Link's Awakening | MBC1 | ✅ Playable |
| Pokemon Red/Blue | MBC3 | ✅ Playable |

---

## Architecture

```
src/
├── CPU/          — Instruction decode/execute, registers, interrupt handling
├── PPU/          — Pixel processing, scanline rendering, OAM sprite scan
├── bus/          — Memory bus, address routing, DMA
├── cartridge/    — ROM loading, MBC1, MBC3 bank switching, battery saves
├── timer/        — DIV/TIMA/TMA/TAC registers
├── input/        — Joypad register emulation
└── platform/     — SDL2 window, renderer, and input event handling
```

### Design Decisions

**Dispatch table over switch statements** — The CPU uses two 256-entry function pointer tables (one for standard opcodes, one for CB-prefix) instead of a giant switch statement. Each opcode maps to a handler function that receives the CPU reference and an `Instruction` descriptor struct containing addressing mode, register operands, and cycle count. This makes adding or debugging individual instructions straightforward and keeps `execute_opcode` a two-line function.

**Data-driven instruction descriptors** — Each entry in the instruction table carries metadata (mnemonic, addressing mode, register fields, cycle count, condition code) separately from the handler function. This means conditional instructions like `JR NZ` and `JR Z` share one handler that reads the condition from the descriptor, rather than duplicating logic.

**Layered PPU rendering** — `renderScanline` computes background, window, and sprite layers into separate pixel buffers, then a compositor applies priority rules. This mirrors the hardware's conceptual design and makes each layer independently testable.

**Polymorphic cartridge MBC** — `Cartridge` is a base class with virtual `read`/`writeRegister`/`save`. `MBC1` and `MBC3` subclass it. `membus` holds a `unique_ptr<Cartridge>` and a factory in `loadCartridge` instantiates the correct type based on the header byte at `0x0147`.

**Dependency injection for circular dependencies** — Components that need each other (e.g. `membus` ↔ `timer`, `membus` ↔ `Joypad`) are constructed independently and wired together via setter methods, with forward declarations in headers to avoid circular includes.

---

## CPU

The Game Boy uses a Sharp LR35902 processor running at 4.194304 MHz.

### Registers

| Register | Size | Description |
|----------|------|-------------|
| A | 8-bit | Accumulator — primary register for arithmetic/logic |
| F | 8-bit | Flags (Z, N, H, C in bits 7-4) |
| B, C, D, E, H, L | 8-bit | General purpose; combinable as BC, DE, HL |
| SP | 16-bit | Stack pointer (initialized to `0xFFFE`) |
| PC | 16-bit | Program counter |

### Flag Register

| Bit | Flag | Set when |
|-----|------|----------|
| 7 | Z (Zero) | Result is zero |
| 6 | N (Subtract) | Last operation was a subtraction |
| 5 | H (Half Carry) | Carry from bit 3 to bit 4 |
| 4 | C (Carry) | Carry out of bit 7 / borrow |

### Interrupt Vectors

| Interrupt | Vector | IF Bit |
|-----------|--------|--------|
| VBlank | `0x0040` | 0 |
| LCD STAT | `0x0048` | 1 |
| Timer | `0x0050` | 2 |
| Serial | `0x0058` | 3 |
| Joypad | `0x0060` | 4 |

Interrupts are gated by the IME flag. `EI` enables interrupts with a one-instruction delay. `RETI` re-enables immediately. `DI` disables immediately.

---

## Memory Map

| Address Range | Hardware |
|---------------|----------|
| `0x0000–0x7FFF` | Cartridge ROM (banked via MBC) |
| `0x8000–0x9FFF` | VRAM |
| `0xA000–0xBFFF` | Cartridge RAM (banked, battery-backed) |
| `0xC000–0xDFFF` | Work RAM |
| `0xFE00–0xFE9F` | OAM (sprite attribute table) |
| `0xFF00–0xFF7F` | I/O registers |
| `0xFF80–0xFFFE` | High RAM (HRAM) |
| `0xFFFF` | Interrupt Enable register |

---

## PPU

The PPU renders 144 scanlines per frame at 60fps, cycling through four modes per line:

| Mode | Clock cycles | Description |
|------|--------|-------------|
| 2 — OAM Scan | 80 | Find sprites on current line (max 10) |
| 3 — Drawing | 172 | Render pixels for current line |
| 0 — HBlank | 204 | Rest period |
| 1 — VBlank | 4560 | 10 lines of rest after line 143 |

### Key Registers

| Register | Address | Description |
|----------|---------|-------------|
| LCDC | `0xFF40` | LCD control (enable, BG/sprite/window settings) |
| STAT | `0xFF41` | LCD status and interrupt enables |
| SCY/SCX | `0xFF42/43` | Background scroll |
| LY | `0xFF44` | Current scanline (read-only) |
| WY/WX | `0xFF4A/4B` | Window position |
| BGP | `0xFF47` | Background palette |
| OBP0/1 | `0xFF48/49` | Sprite palettes |

### Tile Addressing

LCDC bit 4 selects between two tile data addressing modes:

- **`$8000` method** (bit 4 = 1): unsigned index, tiles 0–255 start at `0x8000`
- **`$8800` method** (bit 4 = 0): signed index, tile 0 maps to `0x9000`

---

## MBC (Memory Bank Controllers)

The CPU can only address 32KB of cartridge space at once. MBC chips on the cartridge intercept writes to ROM space and use them as commands to swap which physical ROM bank appears in the `0x4000–0x7FFF` window.

### MBC1

Supports up to 2MB ROM and 32KB RAM. Has two modes controlled by a mode register:

- **Mode 0** (ROM banking): 5-bit ROM bank in lower window + 2 upper bits extend to 7-bit bank
- **Mode 1** (RAM banking): 2-bit value selects RAM bank instead

### MBC3

Supports up to 2MB ROM and 32KB RAM, plus a real-time clock (RTC). ROM bank is a direct 7-bit value with no mode bit. Stubbed RTC registers return 0.

### Battery Saves

Battery-backed cartridge RAM is persisted to `.sav` files and restored when the ROM is loaded.

---

## Testing

Unit tests for CPU opcodes are in `tests/CPUtests.cpp`. The project also validates against Blargg's Game Boy test ROMs and dmg-acid2 test for the PPU.


Results are printed via the Game Boy's serial port to stdout.

---

## References

- [Pan Docs](https://gbdev.io/pandocs/) — Primary Game Boy hardware reference
- [Gameboy Technical Reference](https://gekkio.fi/files/gb-docs/gbctr.pdf) — Detailed CPU timing documentation
- [System of Levers](https://www.youtube.com/watch?v=SCHlyX2sFN8) — High-level Game Boy hardware overview
- [Blargg's Test ROMs](https://github.com/retrio/gb-test-roms) — CPU correctness test suite
- [DMG-ACID2](https://github.com/mattcurrie/dmg-acid2) — PPU accuracy test ROM
