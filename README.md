# COMP2113 Group Project: 2048 Game

## Group Members
- Cheng Kan Pang
- Lao Ka Hang
- Liu Skye
- Wu Yuzhou

## Application Description
2048 is a single-player puzzle game played on a grid (default 4x4) with customizable difficulty options (8x8 or appearance of wild block). Players combine tiles with identical numbers by sliding them using directional controls, aiming to create a 2048 tile. The game ends when the grid is full and no valid moves remain.

## Features
-WASD Controls: Intuitive keyboard inputs for tile movement (Left/A, Right/D, Up/W, Down/S).

-Tile Merging: Combine matching values to progress toward the 2048 goal.

-Game Over Detection: Ends when no moves or merges are possible.

-Wild Block Mechanic: Special "Wild Block" (W) tiles appear after achieving merge streaks.

## Requirements

-Generation of random events: Random tiles (2, 4, or W) spawn on empty grid spaces during gameplay.

-Data Structure Array: Arrays manage grid data and tile positions.

-Dynamic memory: Adjusts grid size (4x4, 8x8,) based on user-selected difficulty.

-File input and output: Save and load game states via file operations.

-Program codes in multiple files: Modular codebase organized into Makefile, game_menu, save_load, and main.

-Multiple difficulty level: Players choose grid size (4x4, 8x8) to adjust challenge intensity

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
