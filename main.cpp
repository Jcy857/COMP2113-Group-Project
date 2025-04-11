#include <iostream>
using namespace std;

// Initilise score variable
int Score = 0;

// Variable (N x N) grid
int Size = 4;
int grid[Size][Size] = {0};

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
            cout << "No moves, Game Over!!" << endl;
            return;
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
