# Corewar

## Introduction

Corewar is a competitive programming project written in C that simulates a virtual battle between multiple programs, known as champions, written in a custom assembly language. These champions compete for control of a shared memory space in a simulated arena, attempting to outlast or eliminate their opponents by executing strategic instructions.

## Documentation

For more information about our **corewar** code, visit our [documentation page]( https://doussangsebastien.github.io/Corewar/).

## Features

### Flags

| Flag    | Parameter | Description                                                                 | Example Usage                     |
|---------|-----------|-----------------------------------------------------------------------------|-----------------------------------|
| `-n`    | `<id>`    | **Assign custom champion ID**<br>- Must be unique positive integer<br>- Applies to next champion file | `./corewar -n 42 player.cor`      |
| `-a`    | `<addr>`  | **Set champion load address**<br>- Address range: 0 to `MEM_SIZE`-1<br>- Auto-wraps using modulo | `./corewar -a 2048 player.cor`    |
| `-dump` | `<cycle>` | **Dump memory state**<br>- Prints hex arena at specified cycle<br>- Exits after dump | `./corewar -dump 1000 player.cor` |

## Usage Notes:
1. **Order Sensitive**: Flags apply to the immediately following champion file
   ```bash
   ./corewar -n 1 -a 0 p1.cor -n 2 p2.cor

### Champions

In the `tests` directory, you’ll find an `asm` binary that can be used to compile a `champion.s` file into a `champion.cor` binary.

If you're looking for ready-to-use champions, you can find example `.cor` files in both the `tests` and `tests/champions` directories.

## Getting Started

### Prerequisites

- Linux or UNIX system
- `make`, `gcc` and optionally `ncurses` installed

### Installation

1. **Clone the repository**:
   ```bash
   git clone https://github.com/EpitechPGEPromo2029/B-CPE-200-BDX-2-1-corewar-alexis.roufast-chalada.git Corewar
   cd Corewar
   ```

2. **Compile the program**:
   for a basic game:
   ```bash
   make
   ```
   For the graphical interface (bonus):
   ```bash
   make bonus
   ```

3. **Run tests** (optional):
   ```bash
   make coverage
   ```

4. **Run a battle**:
   ```bash
   ./corewar champion1.cor champion2.cor [...]
   ```
