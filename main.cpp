#include <iostream>
#include <iomanip>
#include <unistd.h>
#include "save_load.h"
#include "game_menu.h"
using namespace std;

// Initialise score variable
int score = 0;

// Initialise game status variable
bool game_over = false;
bool game_victory = false;

// Initialise quit variable
bool quit = false;

// Difficulty variable
string difficulty;

// Variable (N x N) grid
int Size = 4;
vector<vector<int>> grid = vector<vector<int>>(Size, vector<int>(Size, 0));

// Checks if Merge is possible through comparing numbers
bool CanMerge(int a, int b) {
    return a == b && a != 0;
}

// In the following, Movement functions: MoveLeft / MoveRight / MoveUp / MoveDown are defined
// Each function works in a 3 step work flow
// Step 1: the 4 Rows(Left/Right) or 4 Columns(Up/Down) are compacted with no Merge (e.g. [0 2 2 4] -> [2 2 4 0])
// Step 2: adjacent tiles are Merged (e.g. [2 2 4 0] -> [4 0 4 0])
// Step 3: Using the same code in First Step, the Rows/Columns are compacted again (e.g. [4 0 4 0] -> [4 4 0 0])
// Further comments are provided for MoveLeft(), the 3 other functions work in the SAME logic

void MoveLeft() {
  // looping through all rows
    for (int i = 0; i < Size; i++) {
      // Step 1 for row i: Compact tiles
      // Slide tiles left multiple times (Repeat "sliding by one grid" Size-2 times to ensure compact)
        for (int s = 0; s < Size-1; s++) {
          // Slide tiles left by one grid
            for (int j = 0; j < Size-1; j++) {
                if (grid[i][j] == 0) {
                  // if tile on left is 0, replace tile on left by the number of current tile
                    grid[i][j] = grid[i][j+1];
                  // current tile is set to 0
                    grid[i][j+1] = 0;
                }
            }
        }

        // Step 2 for Row i: Merge adjacent tiles
        for (int j = 0; j < Size-1; j++) {
            if (CanMerge(grid[i][j], grid[i][j+1])) {
              // Mutiply Merge tile value by 2 and set the tile value on the right to 0
                grid[i][j] *= 2;
                score += grid[i][j];
                grid[i][j+1] = 0;
            }
        }

        // Step 1 again (same code): Re-slide after merging
        for (int s = 0; s < Size-1; s++) {
            for (int j = 0; j < Size-1; j++) {
                if (grid[i][j] == 0) {
                    grid[i][j] = grid[i][j+1];
                    grid[i][j+1] = 0;
                }
            }
        }
    }
}

void MoveRight() {
    for (int i = 0; i < Size; i++) {
        for (int s = 0; s < Size-1; s++) {
            for (int j = Size-1; j > 0; j--) {
                if (grid[i][j] == 0) {
                    grid[i][j] = grid[i][j-1];
                    grid[i][j-1] = 0;
                }
            }
        }

        for (int j = Size-1; j > 0; j--) {
            if (CanMerge(grid[i][j], grid[i][j-1])) {
                grid[i][j] *= 2;
                score += grid[i][j];
                grid[i][j-1] = 0;
            }
        }

        for (int s = 0; s < Size-1; s++) {
            for (int j = Size-1; j > 0; j--) {
                if (grid[i][j] == 0) {
                    grid[i][j] = grid[i][j-1];
                    grid[i][j-1] = 0;
                }
            }
        }
    }
}

void MoveUp() {
    for (int j = 0; j < Size; j++) {
        for (int s = 0; s < Size-1; s++) {
            for (int i = 0; i < Size-1; i++) {
                if (grid[i][j] == 0) {
                    grid[i][j] = grid[i+1][j];
                    grid[i+1][j] = 0;
                }
            }
        }

        for (int i = 0; i < Size-1; i++) {
            if (CanMerge(grid[i][j], grid[i+1][j])) {
                grid[i][j] *= 2;
                score += grid[i][j];
                grid[i+1][j] = 0;
            }
        }

        for (int s = 0; s < Size-1; s++) {
            for (int i = 0; i < Size-1; i++) {
                if (grid[i][j] == 0) {
                    grid[i][j] = grid[i+1][j];
                    grid[i+1][j] = 0;
                }
            }
        }
    }
}

void MoveDown() {
    for (int j = 0; j < Size; j++) {
        for (int s = 0; s < Size-1; s++) {
            for (int i = Size-1; i > 0; i--) {
                if (grid[i][j] == 0) {
                    grid[i][j] = grid[i-1][j];
                    grid[i-1][j] = 0;
                }
            }
        }

        for (int i = Size-1; i > 0; i--) {
            if (CanMerge(grid[i][j], grid[i-1][j])) {
                grid[i][j] *= 2;
                score += grid[i][j];
                grid[i-1][j] = 0;
            }
        }

        for (int s = 0; s < Size-1; s++) {
            for (int i = Size-1; i > 0; i--) {
                if (grid[i][j] == 0) {
                    grid[i][j] = grid[i-1][j];
                    grid[i-1][j] = 0;
                }
            }
        }
    }
}

bool nearbysamevalue(const vector<vector<int>> & grid, int x, int y) {
    int boxvalue = grid[x][y];
    if (x > 0 && grid[x-1][y] == boxvalue)
        return true;
    if (x < Size-1 && grid[x+1][y] == boxvalue)
        return true;
    if (y > 0 && grid[x][y-1] == boxvalue)
        return true;
    if (y < Size-1 && grid[x][y+1] == boxvalue)
        return true;
    return false;
}

bool allnotempty(const vector<vector<int>>& grid) {
    for (int i = 0; i < Size; i++){
       for (int j = 0; j < Size; j++){
           if (grid[i][j] == 0){
               return false;
                   }
       }
    }
    return true;
}

void addrandom() {
    vector<pair<int, int>> emptyblock;
    for (int i = 0; i < Size; i++){
       for (int j = 0; j < Size; j++){
          if (grid[i][j] == 0) {
             emptyblock.push_back({i,j});
          }
       }
    }
    srand(time(0));
    int randomplace = rand() % emptyblock.size();
    auto [row, col] = emptyblock[randomplace];
    int randomnum = (rand() % 2 == 0)? 2 : 4;
    grid[row][col] = randomnum;
    if (allnotempty(grid)){
        bool canmove = false;
        for (int i = 0; i < Size; i++){
            for (int j = 0; j < Size; j++){
               if (nearbysamevalue(grid, i, j)){
                   canmove = true;
                   break;
               }
            }
        if (canmove){
            break;
        }
        }
        if (!canmove){
            game_over = true;
            return;
       }
    }         
}

void initializeGrid() {
    grid = vector<vector<int>>(Size, vector<int>(Size, 0));
    addrandom();
    addrandom();
}

void printBoard() {
    system("clear");
    cout << "Score: " << score << "\n\n";
    
    // Print top border
    cout << "  +";
    for (int j = 0; j < Size; j++) {
        cout << "-----+";
    }
    cout << "\n";
    
    // Print each row with grid lines
    for (int i = 0; i < Size; i++) {
        cout << "  |";
        for (int j = 0; j < Size; j++) {
            if (grid[i][j] == 0) {
                cout << "     |"; // Empty tile
            } else {
                cout << setw(5) << grid[i][j] << "|";
            }
        }
        cout << "\n";
        
        // Print horizontal line between rows (except after last row)
        if (i < Size - 1) {
            cout << "  +";
            for (int j = 0; j < Size; j++) {
                cout << "-----+";
            }
            cout << "\n";
        }
    }
    
    // Print bottom border
    cout << "  +";
    for (int j = 0; j < Size; j++) {
        cout << "-----+";
    }
    cout << "\n\n";
    
    cout << "Use WASD to move, Esc for menu\n";

}

void difficultyMenu() {
    vector<string> difficultyMenuOptions = {"Normal", "Hard", "Ex Hard"}; // Difficulty Menu
    int difficultyChoice = showGenericMenu("DIFFICULTY", difficultyMenuOptions, score);
    if (difficultyChoice == 0) { // Normal
        difficulty = "Normal";
        Size = 4;
    } else if (difficultyChoice == 1) { // Hard
        difficulty = "Hard";
        Size = 8;
    } else if (difficultyChoice == 2) { // Ex Hard
        difficulty = "Ex Hard";
        Size = 12;
    }
    initializeGrid();
    printBoard();
}

void mainMenu() {
    vector<string> mainMenuOptions = {"New Game", "Load", "Quit"}; // Main Menu
    int mainChoice = showGenericMenu("MAIN MENU", mainMenuOptions, score);
    if (mainChoice == 0) { // New Game
        score = 0;
        game_over = false;
        game_victory = false;
        difficultyMenu();
    } else if (mainChoice == 1) { // Load
        loadGame(grid, Size, score);
        printBoard();
    } else if (mainChoice == 2) { // Quit
        game_over = true;
        quit = true;
    }
}

void escMenu() {
    vector<string> inGameMenuOptions = {"Continue", "Load", "Save", "Quit"};
    int choice = showGenericMenu("MENU", inGameMenuOptions, score);
    
    if (choice == 0) { // Continue
        printBoard();
    } else if (choice == 1) { // Load
        loadGame(grid, Size, score);
        printBoard();
    } else if (choice == 2) { // Save
        saveGame(grid, Size, score);
        printBoard();
    } else if (choice == 3) { // Quit
        game_over = true;
    }

}

void gameOver() {
    vector<string> gameOverOptions = {"Back to Main Menu"}; // Game Over Menu
    int endChoice = showGenericMenu("Game Over! Final Score: " + to_string(score), gameOverOptions, score);
    if (endChoice == 0) { // Back to Main Menu
        game_over = false;
    }
}

void victory() {
    std::vector<std::string> victoryOptions = {"Continue", "Back to Main Menu"}; // Victory Menu
    int victoryChoice = showGenericMenu("Victory! Final Score: " + std::to_string(score), victoryOptions, score);
    game_victory = true;
    if (victoryChoice == 0) { // Continue
        printBoard();
    } else if (victoryChoice == 1) { // Back to Main Menu
        game_over = true;
    }
}
bool game_over(const vector<vector<int>> & grid){
    int i, j;
    for(i = 0; i < 4; ++i){
        for(j = 0; j < 4; ++j){
            if(grid[i][j] == 0){
                return false;
            }
            else if(i < 3 && CanMerge(grid[i][j],grid[i+1][j]){
                return false;
            }
            else if(j < 3 && CanMerge(grid[i][j],grid[i][j+1]){
                return false;
            }
        }
    }
    return true;
}
int main() {
    setNonBlockingInput();
    mainMenu();
    
    while (game_over == false) {
        if (kbhit()) {
            char ch;
            cin >> ch;

            // Save the current state of the grid to compare later
            vector<vector<int>> previous_grid = grid;

            if (ch == 'w') {
                MoveUp();
                 // Check if the grid has changed; if not, continue
                if (grid == previous_grid) {
                    continue;
                }
                addrandom();
                printBoard();
            } else if (ch == 's') {
                MoveDown();
                // Check if the grid has changed; if not, continue
                if (grid == previous_grid) {
                    continue;
                }
                addrandom();
                printBoard();
            } else if (ch == 'a') {
                MoveLeft();
                // Check if the grid has changed; if not, continue
                if (grid == previous_grid) {
                    continue;
                }
                addrandom();
                printBoard();
            } else if (ch == 'd') {
                MoveRight();
                // Check if the grid has changed; if not, continue
                if (grid == previous_grid) {
                    continue;
                }
                addrandom();
                printBoard();
            } else if (ch == 27) { // Escape key
                escMenu();
            }
            if (game_victory == false) {
                for (int i = 0; i < Size; i++){
                    for (int j = 0; j < Size; j++){
                       if (grid[i][j] == 2048) {
                          game_victory = true;
                          victory();
                       }
                    }
                }
            }
            game_over = game_over(grid)
            if (game_over == true) {
                break;
            }
            
        }
        usleep(100000);
    }

    game_victory = false;
    game_over = false;

    if (quit == true) {
        restoreInput();
        return 0;
    } else {
        gameOver();
        main();
    };
    return 0;
}