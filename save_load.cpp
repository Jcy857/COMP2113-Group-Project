#include <fstream>
#include <string>
#include "save_load.h"

using namespace std;

// @param board: The game board
// @param Size: The size of the board (N x N)
// @param score: The current score
// @return None
// This function saves the current game state to a file named "save.txt"
void SaveGame(const vector<vector<int>>& board, int Size, int score) {
    string filename = "save.txt";
    ofstream file(filename);
    if (!file.is_open()) return;
    file << score << "\n";
    file << Size << "\n";
    for (int i = 0; i < Size; i++) {
        for (int j = 0; j < Size; j++) {
            file << board[i][j] << " ";
        }
        file << "\n";
    }
    file.close();
}

// @param board: The game board
// @param Size: The size of the board (N x N)
// @param score: The current score
// @return true if the game state was loaded successfully, false otherwise
// This function loads the game state from a file named "save.txt"
bool LoadGame(vector<vector<int>>& board, int& Size, int& score) {
    string filename = "save.txt";
    ifstream file(filename);
    if (!file.is_open()) return false;
    file >> score;
    file >> Size;
    board.resize(Size, vector<int>(Size, 0));
    for (int i = 0; i < Size; i++) {
        for (int j = 0; j < Size; j++) {
            file >> board[i][j];
        }
    }
    file.close();
    return true;
}
