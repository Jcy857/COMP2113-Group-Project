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

// @param None
// @return None
// This function moves the tiles to the left and merges them if possible
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

// @param None
// @return None
// This function moves the tiles to the right and merges them if possible
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

// @param None
// @return None
// This function moves the tiles up and merges them if possible
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

// @param None
// @return None
// This function moves the tiles down and merges them if possible
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

// @param grid: The game grid
// @param x: The row index of the tile
// @param y: The column index of the tile
// @return true if there is a tile with the same value in the adjacent cells, false otherwise
// This function checks if there is a tile with the same value in the adjacent cells
bool NearBySameValue(const vector<vector<int>> & grid, int x, int y) {
    int boxvalue = grid[x][y];
    if (x > 0 && grid[x-1][y] == boxvalue)
        // check if left box is same
        return true;
    if (x < Size-1 && grid[x+1][y] == boxvalue)
        // check if right box is same
        return true;
    if (y > 0 && grid[x][y-1] == boxvalue)
        // check if upper box is same
        return true;
    if (y < Size-1 && grid[x][y+1] == boxvalue)
        // check if lower box is same
        return true;
    return false;
}

// @param grid: The game grid
// @return true if all cells in the grid are not empty, false otherwise
// This function checks if all cells in the grid are not empty
bool AllNotEmpty(const vector<vector<int>>& grid) {
    for (int i = 0; i < Size; i++){
       for (int j = 0; j < Size; j++){
           if (grid[i][j] == 0){
               return false;
                   }
       }
    }
    return true;
}

// @param None
// @return None
// This function adds a random number (2 or 4) to an empty cell in the grid
void AddRandom() {
    vector<pair<int, int>> emptyblock;
    // make a list of empty block
    for (int i = 0; i < Size; i++){
       for (int j = 0; j < Size; j++){
          if (grid[i][j] == 0) {
             emptyblock.push_back({i,j});
              // finding empty block and put in list
          }
       }
    }
    srand(time(0));
    // create different random seed
    int randomplace = rand() % emptyblock.size();
    // provide a random block in the list of empty block
    auto& temp = emptyblock[randomplace];
    int row = temp.first;
    int col = temp.second;
    int randomnum = (rand() % 2 == 0)? 2 : 4;
    // create a random number
    grid[row][col] = randomnum;
    // put the random number in the block
    if (allnotempty(grid)){
        // check if gameover when full
        bool canmove = false;
        for (int i = 0; i < Size; i++){
            for (int j = 0; j < Size; j++){
               if (NearBySameValue(grid, i, j)){
                   canmove = true;
                   // player can still move and merge, the game continue
                   break;
               }
            }
        if (canmove){
            break;
        }
        }
        if (!canmove){
            game_over = true;
            // really no move, game over
            return;
       }
    }         
}

// @param None
// @return None
// This function initialise the grid with two random numbers and set the score to 0
void InitializeGrid() {
    grid = vector<vector<int>>(Size, vector<int>(Size, 0));
    AddRandom();
    AddRandom();
}

// @param None
// @return None
// This function prints the current state of the grid and the score
void PrintBoard() {
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

// @param None
// @return None
// This function displays the difficulty menu and sets the game difficulty
void DifficultyMenu() {
    vector<string> DifficultyMenuOptions = {"Easy", "Normal", "Hard"}; // Difficulty Menu
    int difficultyChoice = ShowGenericMenu("DIFFICULTY", DifficultyMenuOptions, score);
    if (difficultyChoice == 0) { // Easy
        difficulty = "Easy";
        Size = 8;
    } else if (difficultyChoice == 1) { // Normal
        difficulty = "Normal";
        Size = 6;
    } else if (difficultyChoice == 2) { // Hard
        difficulty = "Hard";
        Size = 4;
    }
    InitializeGrid();
    PrintBoard();
}

// @param None
// @return None
// This function displays the main menu and handles user input for starting a new game, loading a game, or quitting
void MainMenu() {
    vector<string> MainMenuOptions = {"New Game", "Load", "Quit"}; // Main Menu
    int mainChoice = ShowGenericMenu("MAIN MENU", MainMenuOptions, score);
    if (mainChoice == 0) { // New Game
        score = 0;
        game_over = false;
        game_victory = false;
        DifficultyMenu();
    } else if (mainChoice == 1) { // Load
        LoadGame(grid, Size, score);
        PrintBoard();
    } else if (mainChoice == 2) { // Quit
        game_over = true;
        quit = true;
    }
}

// @param None
// @return None
// This function displays the in-game menu and handles user input for continuing, loading, saving, or quitting
void EscMenu() {
    vector<string> inGameMenuOptions = {"Continue", "Load", "Save", "Main Menu"};
    int choice = ShowGenericMenu("MENU", inGameMenuOptions, score);
    
    if (choice == 0) { // Continue
        PrintBoard();
    } else if (choice == 1) { // Load
        LoadGame(grid, Size, score);
        PrintBoard();
    } else if (choice == 2) { // Save
        SaveGame(grid, Size, score);
        PrintBoard();
    } else if (choice == 3) { // Main Menu
        game_over = true;
    }
}

// @param None
// @return None
// This function displays the game over menu and handles user input for continuing or quitting
void GameOverMenu() {
    vector<string> gameOverOptions = {"Back to Main Menu"}; // Game Over Menu
    int endChoice = ShowGenericMenu("Game Over! Final Score: " + to_string(score), gameOverOptions, score);
    if (endChoice == 0) { // Back to Main Menu
        game_over = false;
    }
}

// @param None
// @return None
// This function displays the victory menu and handles user input for continuing or going back to the main menu
void VictoryMenu() {
    std::vector<std::string> victoryOptions = {"Continue", "Back to Main Menu"}; // Victory Menu
    int victoryChoice = ShowGenericMenu("Victory! Final Score: " + std::to_string(score), victoryOptions, score);
    game_victory = true;
    if (victoryChoice == 0) { // Continue
        PrintBoard();
    } else if (victoryChoice == 1) { // Back to Main Menu
        game_over = true;
    }
}

/*
bool game_over(const vector<vector<int>> & grid){
    int i, j;
    for(i = 0; i < 4; ++i){
        for(j = 0; j < 4; ++j){
            if(grid[i][j] == 0){
                return false;
            } else if(i < 3 && CanMerge(grid[i][j],grid[i+1][j])) {
                return false;
            } else if(j < 3 && CanMerge(grid[i][j],grid[i][j+1])) {
                return false;
            }
        }
    }
    return true;
}
*/

int main() {
    SetNonBlockingInput();
    MainMenu();
    
    while (game_over == false) {
        if (kbhit()) {
            // Read user input
            char ch;
            cin >> ch;

            // Save the current state of the grid to compare later
            vector<vector<int>> previous_grid = grid;

            if (ch == 'w') { // Move up with w
                MoveUp();
            } else if (ch == 's') { // Move down with s
                MoveDown();
            } else if (ch == 'a') { // Move left with a
                MoveLeft();
            } else if (ch == 'd') { // Move right with d
                MoveRight();                
            } else if (ch == 27) { // Escape key = 27
                EscMenu();
            }

            // Check if the grid has changed; if not, continue. To prevent continue spawning blocks even if there is no movement
            if (grid == previous_grid) {
                continue;
            } else {
                AddRandom();
                PrintBoard();
            }
            
            // Check Victory condition
            if (game_victory == false) {
                for (int i = 0; i < Size; i++){
                    for (int j = 0; j < Size; j++){
                       if (grid[i][j] == 2048) {
                          game_victory = true;
                          VictoryMenu();
                       }
                    }
                }
            }

            //game_over = game_over(grid)
            if (game_over == true) {
                break;
            }
            
        }
        usleep(100000);
    }

    game_victory = false;
    game_over = false;

    // Check if the game is over and display the game over menu
    if (quit == true) {
        RestoreInput();
        return 0;
    } else {
        GameOverMenu();
        RestoreInput();
        main();
    };
    RestoreInput();
    return 0;
}