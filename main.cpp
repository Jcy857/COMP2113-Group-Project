#include <iostream>
#include <iomanip>
#include <unistd.h>
#include "save_load.h"
#include "game_menu.h"
#include <vector>
#include <string>
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

// Declare the size of the grid
int Size = 4;

// Declare the grid variable globally, the grid variable is a pointer to a dynamic array of pointers.
int** grid = nullptr;

// Global Merge_this_step variable 
int Merge_this_step = 0;

// Declare the consecutive merge times variable
int consecutive_merge = 0;

// Declare the conditions of getting wildblock 
int wildblock_requirement = 4;

// @param a: The value of the first tile
// @param b: The value of the second tile
// @return true if the two tiles can be merged, false otherwise
// This function checks if two tiles can be merged
bool CanMerge(int a, int b) {
    if ((a == -1 && b != 0) || (b == -1 && a != 0)) {
        return true;
    // The wildblock is assigned value -1 (but displayed as w), and it can merge with any blocks
    }
    else{
        return (a == b && a != 0);
    }
}

//
// In the following, Movement functions: MoveLeft / MoveRight / MoveUp / MoveDown are defined
// Each function works in a 3-step workflow
// Step 1: the 4 Rows(Left/Right) or 4 Columns(Up/Down) are compacted with no Merge (e.g. [0 2 2 4] -> [2 2 4 0])
// Step 2: adjacent tiles are Merged (e.g. [2 2 4 0] -> [4 0 4 0])
// Step 3: Using the same code in the First Step, the Rows/Columns are compacted again (e.g. [4 0 4 0] -> [4 4 0 0])
// Further comments are provided for MoveLeft(), the 3 other functions work in the SAME logic

// @param None
// @return None
// This function moves the tiles to the left and merges them if possible
void MoveLeft() {
    //
    // record the merge times in this step
    Merge_this_step = 0;
  // looping through all rows
    for (int i = 0; i < Size; i++) {
      // Step 1 for row i: Compact tiles
      // Slide tiles left multiple times (Repeat "sliding by one grid" Size-2 times to ensure compact)
        for (int s = 0; s < Size-1; s++) {
          // Slide tiles left by one grid
            for (int j = 0; j < Size-1; j++) {
                if (grid[i][j] == 0) {
                  // if the tile on the left is 0, replace the tile on the left with the number of the current tile
                    grid[i][j] = grid[i][j+1];
                  // current tile is set to 0
                    grid[i][j+1] = 0;
                    // move left for the whole board
                }
            }
        }

        // Step 2 for Row i: Merge adjacent tiles
        for (int j = 0; j < Size-1; j++) {
            if (CanMerge(grid[i][j], grid[i][j+1])) {
                // finds out which block is going to merge, considering possible cases of wildblock
                int a = grid[i][j];
                int b = grid[i][j+1];
                int mergedValue;
                // multiply the Merge tile value by 2 
                if (a == -1) {
                    mergedValue = b * 2; 
                } else if (b == -1) {
                    mergedValue = a * 2; 
                } else {
                    mergedValue = a * 2;
                }
                // return the merged value
                grid[i][j] = mergedValue;
                // return the merged block to the grid
                score += mergedValue;
                // the user get the score of the merged value
                // the other tile is set to 0
                grid[i][j+1] = 0;
                if (Merge_this_step == 0) {
                    consecutive_merge = consecutive_merge + 1; // The merge time only count once for each steps
                    Merge_this_step = 1;
                }
            }
        }

        // Step 1 again (same code): Re-slide after merging
        for (int s = 0; s < Size-1; s++) {
            for (int j = 0; j < Size-1; j++) {
                if (grid[i][j] == 0) {
                    grid[i][j] = grid[i][j+1];
                    grid[i][j+1] = 0;
                    // exchange the value of two cells
                }
            }
        }
    }
}

//
// @param None
// @return None
// This function moves the tiles to the right and merges them if possible
void MoveRight() {
    Merge_this_step = 0;
    for (int i = 0; i < Size; i++) {
        for (int s = 0; s < Size-1; s++) {
            for (int j = Size-1; j > 0; j--) {
                if (grid[i][j] == 0) {
                    grid[i][j] = grid[i][j-1];
                    grid[i][j-1] = 0;
                    // move right for the whole board
                }
            }
        }

        for (int j = Size-1; j > 0; j--) {
            if (CanMerge(grid[i][j], grid[i][j-1])) {
                int a = grid[i][j];
                int b = grid[i][j-1];
                int mergedValue;
                if (a == -1) {
                    mergedValue = b * 2;
                } else if (b == -1) {
                    mergedValue = a * 2;
                } else {
                    mergedValue = a * 2;
                }
                grid[i][j] = mergedValue;
                score += mergedValue;
                grid[i][j-1] = 0;
                if (Merge_this_step == 0) {
                    consecutive_merge = consecutive_merge + 1;
                    Merge_this_step = 1;
                }
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
    Merge_this_step = 0;
    for (int j = 0; j < Size; j++) {
        for (int s = 0; s < Size-1; s++) {
            for (int i = 0; i < Size-1; i++) {
                if (grid[i][j] == 0) {
                    grid[i][j] = grid[i+1][j];
                    grid[i+1][j] = 0;
                    // move up for the whole board
                }
            }
        }

        for (int i = 0; i < Size-1; i++) {
            if (CanMerge(grid[i][j], grid[i+1][j])) {
                int a = grid[i][j];
                int b = grid[i+1][j];
                int mergedValue;
                if (a == -1) {
                    mergedValue = b * 2;
                } else if (b == -1) {
                    mergedValue = a * 2;
                } else {
                    mergedValue = a * 2;
                }
                grid[i][j] = mergedValue;
                score += mergedValue;
                grid[i+1][j] = 0;
                if (Merge_this_step == 0) {
                    consecutive_merge = consecutive_merge + 1;
                    Merge_this_step = 1;
                }
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
    Merge_this_step = 0;
    for (int j = 0; j < Size; j++) {
        for (int s = 0; s < Size-1; s++) {
            for (int i = Size-1; i > 0; i--) {
                if (grid[i][j] == 0) {
                    grid[i][j] = grid[i-1][j];
                    grid[i-1][j] = 0;
                    // move down for the whole board
                }
            }
        }

        for (int i = Size-1; i > 0; i--) {
            if (CanMerge(grid[i][j], grid[i-1][j])) {
                int a = grid[i][j];
                int b = grid[i-1][j];
                int mergedValue;
                if (a == -1) {
                    mergedValue = b * 2;
                } else if (b == -1) {
                    mergedValue = a * 2;
                } else {
                    mergedValue = a * 2;
                }
                grid[i][j] = mergedValue;
                score += mergedValue;
                grid[i-1][j] = 0;
                if (Merge_this_step == 0) {
                    consecutive_merge = consecutive_merge + 1;
                    Merge_this_step = 1;
                }
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

//
// @param grid: The game grid
// @param x: The row index of the tile
// @param y: The column index of the tile
// @return true if there is a tile with the same value in the adjacent cells, false otherwise
// This function checks if there is a tile with the same value in the adjacent cells
bool NearBySameValue(int ** & grid, int x, int y) {
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
    // there is no same blocks around the cell
}

//
// @param grid: The game grid
// @return true if all cells in the grid are not empty, false otherwise
// This function checks if all cells in the grid are not empty
bool AllNotEmpty(int ** & grid) {
    for (int i = 0; i < Size; i++){
       for (int j = 0; j < Size; j++){
           if (grid[i][j] == 0){
               // as there is a cell 0 in grid, it is not empty
               return false;
            }
        }
    }
    return true;
    // there is no 0 cell in grid, it is filled
}

//
// @param None
// @return None
// This function adds a random number (2 or 4) to an empty cell in the grid
void AddRandom() {
    struct Position {
    int row;
    int col;
    };
    // Define a new dynamic array to record the empty block in the grid
    Position* emptyblock = new Position[Size * Size];
    // Record the number of empty blocks
    int numberofemptyblocks = 0;
    // make a list of empty block
    for (int i = 0; i < Size; i++){
       for (int j = 0; j < Size; j++){
          if (grid[i][j] == 0) {
             // record the position and numbers of emptyblocks
             emptyblock[numberofemptyblocks].row = i;
             emptyblock[numberofemptyblocks].col = j;
             numberofemptyblocks++;
              // return the empty blocks to the list
          }
       }
    }
    srand(time(0));
    // create different random seed
    int randomplace = rand() % numberofemptyblocks;
    // provide a random block in the list of empty block
    // int* temp = emptyblock[randomplace];
    int row = emptyblock[randomplace].row;
    int col = emptyblock[randomplace].col;
    if (consecutive_merge % wildblock_requirement == 0 && consecutive_merge > 0) {
        grid[row][col] = -1;
    }
    // add a wildblcok in to a random block if the player has consecutively merged for the required times
    else{
        int randomnum = (rand() % 2 == 0)? 2 : 4;
        // create a random number when the merged time doesn't fulfill the requirement
        // create a 2/4 number
        grid[row][col] = randomnum;
        // put the random number in the block
    }
    if (AllNotEmpty(grid)){
        // check if gameover when full
        bool canmove = false;
        for (int i = 0; i < Size; i++){
            for (int j = 0; j < Size; j++){
               if (NearBySameValue(grid, i, j)){
                   // have similar blocks around for one of the cells
                   canmove = true;
                   // player can still move and merge
                   break;
                   // the game can continue
               }
            }
        if (canmove){
            break;
            // the game can continue
        }
        }
        if (!canmove){
            game_over = true;
            // really no move
            return;
            // game over
    }         
    delete[] emptyblock; // free the allocated memory
    }
}

//
// @param None
// @return None
// This function initialise the grid with two random numbers and set the score to 0, the grid is a dynamic array of dynamic arraise.
void InitializeGrid() {
    grid = new int* [Size];
    // make grid becomes a dynamic array with Size elements, and each elements is also a pointer.
    for (int i = 0; i < Size; ++i) {
        grid[i] = new int[Size];
        // each elements in grid becomes a pointer to a dynamic array with Size elements, and each elements are integers
        for (int j = 0; j < Size; ++j) {
            grid[i][j] = 0; 
            // Initialize all grid cells to 0  
        }
    }
    // initialise the grid and set all entrise to be zero
    AddRandom();
    AddRandom();
    // add two random numbers in random blocks
}

//
// @param None
// @return None
// This function prints the current state of the grid and the score
void PrintBoard() {
    system("clear");
    cout << "Score: " << score << "    Streak: " << consecutive_merge << "\n";
    cout << "Difficulty: " << difficulty << "\n";
    cout << "Wildblock Requirement: " << wildblock_requirement << "\n\n";

    // Print top border
    cout << "  +";
    for (int j = 0; j < Size; j++) {
        cout << "------+";
    }
    cout << "\n";
    
    // Print each row with grid lines
    for (int i = 0; i < Size; i++) {
        cout << "  |";
        for (int j = 0; j < Size; j++) {
            if (grid[i][j] == 0) {
                cout << "      |"; // Empty tile
            } else if (grid[i][j] == -1) {
                cout << "  w   |"; // Print w stands for wildblock
            } else {
                cout << setw(6) << grid[i][j] << "|";
            }
        }
        cout << "\n";
        
        // Print horizontal line between rows (except after last row)
        if (i < Size - 1) {
            cout << "  +";
            for (int j = 0; j < Size; j++) {
                cout << "------+";
            }
            cout << "\n";
        }
    }
    
    // Print bottom border
    cout << "  +";
    for (int j = 0; j < Size; j++) {
        cout << "------+";
    }
    cout << "\n\n";
    
    cout << "Use WASD to move, Esc for menu\n";
}

//
// @param None
// @return None
// This function displays the difficulty menu and sets the game difficulty
void DifficultyMenu() {
    vector<string> DifficultyMenuOptions = {"Easy", "Normal", "Hard"}; // Difficulty Menu
    int difficultyChoice = ShowGenericMenu("DIFFICULTY", DifficultyMenuOptions, score, "");
    if (difficultyChoice == 0) { // Easy
        difficulty = "Easy";
        Size = 8;
        wildblock_requirement = 4;
    } else if (difficultyChoice == 1) { // Normal
        difficulty = "Normal";
        Size = 4;
        wildblock_requirement = 4;
    } else if (difficultyChoice == 2) { // Hard
        difficulty = "Hard";
        Size = 4;
        wildblock_requirement = 1000;
    }
    InitializeGrid();
    PrintBoard();
}

//
// @param None
// @return None
// This function displays the main menu and handles user input for starting a new game, loading a game, or quitting
void MainMenu(string error_msg = "") {
    vector<string> MainMenuOptions = {"New Game", "Load", "Quit"}; // Main Menu
    int mainChoice = ShowGenericMenu("MAIN MENU", MainMenuOptions, score, error_msg);
    if (mainChoice == 0) { // New Game
        score = 0;
        consecutive_merge = 0;
        game_over = false;
        game_victory = false;
        DifficultyMenu();
    } else if (mainChoice == 1) { // Load
        if (LoadGame(grid, Size, score, consecutive_merge, difficulty)) {
            if (difficulty == "Easy") {
                wildblock_requirement = 4;
            } else if (difficulty == "Normal") {
                wildblock_requirement = 4;
            } else if (difficulty == "Hard") {
                wildblock_requirement = 1000;
            }
            // Load the game state from the file
            PrintBoard();
        } else {
            MainMenu("No saved game available to load.");
        }
    } else if (mainChoice == 2) { // Quit
        game_over = true;
        quit = true;
    }
}

//
// @param None
// @return None
// This function displays the in-game menu and handles user input for continuing, loading, saving, or quitting
void EscMenu(string error_msg = "") {
    vector<string> inGameMenuOptions = {"Continue", "Load", "Save", "Main Menu"};
    int choice = ShowGenericMenu("MENU", inGameMenuOptions, score, error_msg);
    if (choice == 0) { // Continue
        PrintBoard();
    } else if (choice == 1) { // Load
        if (LoadGame(grid, Size, score, consecutive_merge, difficulty)){
            if (difficulty == "Easy") {
                wildblock_requirement = 4;
            } else if (difficulty == "Normal") {
                wildblock_requirement = 4;
            } else if (difficulty == "Hard") {
                wildblock_requirement = 1000;
            }
            // Load the game state from the file
            PrintBoard();
        } else {
            EscMenu("No saved game available to load.");
        }
    } else if (choice == 2) { // Save
        SaveGame(grid, Size, score, consecutive_merge, difficulty);
        PrintBoard();
    } else if (choice == 3) { // Main Menu
        game_over = true;
    }
}

//
// @param None
// @return None
// This function displays the game over menu and handles user input for continuing or quitting
void GameOverMenu() {
    vector<string> gameOverOptions = {"Back to Main Menu"}; // Game Over Menu
    int endChoice = ShowGenericMenu("Game Over! Final Score: " + to_string(score), gameOverOptions, score, "");
    if (endChoice == 0) { // Back to Main Menu
        for (int i = 0; i < Size; ++i){
            delete[] grid[i];
            grid[i] = nullptr;
        }
        delete[] grid;
        grid = nullptr;
        // Release the dynamic memory after the game is over
        game_over = false;
    }
}

//
// @param None
// @return None
// This function displays the victory menu and handles user input for continuing or going back to the main menu
void VictoryMenu() {
    std::vector<std::string> victoryOptions = {"Continue", "Back to Main Menu"}; // Victory Menu
    int victoryChoice = ShowGenericMenu("Victory! Final Score: " + std::to_string(score), victoryOptions, score, "");
    game_victory = true;
    if (victoryChoice == 0) { // Continue
        PrintBoard();
    } else if (victoryChoice == 1) { // Back to Main Menu
            
        if (grid != nullptr) {
            for (int i = 0; i < Size; ++i) {
                delete[] grid[i];
                grid[i] = nullptr;
            }
            delete[] grid;
            grid = nullptr;
        }
        // release the dynamic memory after the victor achieved and player deceide to leave
        game_over = true;
    }
}

//
// @param grid: The game grid
// @param previous_grid: The saved game grid
// @param Size: The common size of the two game grids
// @return true if two grids are the same
// This is the function to compare two dynamic grids is same or not
bool compare_grid(int** grid, int** previous_grid, int Size) {
    for (int i = 0; i < Size; ++i) {
        for (int j = 0; j < Size; ++j) {
            if (grid[i][j] != previous_grid[i][j]) {
                return false;
                // one of the cell is different, the grid is different
            }
        }
    }
    return true;
    // all cell are same, the grid is same
}


//
// main function
int main() {
    SetNonBlockingInput();
    MainMenu();
    
    while (game_over == false) {
        if (kbhit()) {
            // Read user input
            char ch;
            cin >> ch;

            // Save the current state of the grid to compare later
            int** previous_grid = new int* [Size];
            for (int i = 0; i < Size; ++i) {
                previous_grid[i] = new int[Size];
            }
            for(int i = 0; i < Size; ++i) {
                for(int j = 0; j < Size; ++j) {
                     previous_grid[i][j] = grid[i][j];
                }
            }

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
            if (compare_grid(grid, previous_grid, Size)) {
                continue;
            } else {
                // reset streak if no merge occurs
                if (Merge_this_step == 0) {
                    consecutive_merge = 0;
                }
                AddRandom();
                // add a random block
                PrintBoard();
                // print out the board
            }
            
            // Check Victory condition
            if (game_victory == false) {
                for (int i = 0; i < Size; i++){
                    for (int j = 0; j < Size; j++){
                       if (grid[i][j] == 2048) {
                           // one of the cells contain a 2048 block
                          game_victory = true;
                           // the player wins as it obtains 2048
                          VictoryMenu();
                       }
                    }
                }
            }

            if (game_over == true) {
                break;
                // the player lose as grid is filled
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
