# COMP2113 Group Project: 2048 Game

## Group Members
- Cheng Kan Pang
- Lao Ka Hang
- Liu Skye
- Wu Yuzhou

## Application Description
The 2048 game is a single-player puzzle game played on a grid, typically 4x4, with customizable difficulty options of 8x8 and 12x12. The objective is to combine tiles with the same number by sliding them to create a tile with the value of 2048. Players use the WASD keys to move tiles left, right, up, or down to reorder or merge them. The game ends when the grid is full and no further moves are possible.

## Features
- Standard 4x4 grid with optional 8x8 and 12x12 grids for varying difficulty
- WASD controls for intuitive tile movement
- Tile merging mechanics to achieve the 2048 goal
- Game over condition when no moves are available

## Non-Standard Libraries
- `save_load.h`
- `game_menu.h`
- `<unistd.h>`
- `<fcntl.h>`
- `<termios.h>`

## Compilation and Execution Instructions
1. **Compile the program**:
   ```bash
   make main
   ```
2. **Run the program**:
   ```bash
   make run
   ```
3. **Clean up generated files**:
   ```bash
   make clean
   ```