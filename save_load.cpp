#include <fstream>
#include <string>
#include "save_load.h"

using namespace std;

// @param board: The game board，which is a pointer to a dynamic array of pointers
// @param Size: The size of the board (N x N)
// @param score: The current score
// @param streak: The current streak of merges
// @param difficulty: The current difficulty level
// @return None
// This function saves the current game state to a file named "save.txt"
void SaveGame(int** & board, int Size, int score, int streak, string difficulty) {
    string filename = "save.txt";
    ofstream file(filename);
    if (!file.is_open()) return;
    file << score << "\n";
    file << Size << "\n";
    file << streak << "\n";
    file << difficulty << "\n";
    for (int i = 0; i < Size; i++) {
        for (int j = 0; j < Size; j++) {
            file << board[i][j] << " ";
        }
        file << "\n";
    }
    file.close();
}

// @param board: The game board，which is a pointer to a dynamic array of pointers
// @param Size: The size of the board (N x N)
// @param streak: The current streak of merges
// @param difficulty: The current difficulty level
// @param score: The current score
// @return true if the game state was loaded successfully, false otherwise
// This function loads the game state from a file named "save.txt"
bool LoadGame(int** & board, int& Size, int& score, int& streak, string& difficulty) {
    string filename = "save.txt";
    ifstream file(filename);
    if (!file.is_open()) return false;

    // Release the memory of old dynamic borad if the borad is not empty
    if (board != nullptr) {
        for (int i = 0; i < Size; ++i) {
            delete[] board[i];
            board[i] = nullptr;
        }
        delete[] board;
        board = nullptr;
    }
    
    file >> score;
    file >> Size;
    file >> streak;
    file >> difficulty;

    // Recreate a dynamic borad with saved data
    board = new int* [Size];
    for (int i = 0; i < Size; ++i) {
        board[i] = new int[Size];
    }
    for (int i = 0; i < Size; i++) {
        for (int j = 0; j < Size; j++) {
            file >> board[i][j];
        }
    }
    file.close();
    return true;
}
