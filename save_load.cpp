#include <fstream>
#include <string>
#include "save_load.h"

using namespace std;

void saveGame(const vector<vector<int>>& board, int Size, int score) {
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

bool loadGame(vector<vector<int>>& board, int& Size, int& score) {
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
