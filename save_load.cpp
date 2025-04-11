#include <fstream>
#include <string>
#include "save_load.h"

using std::string, std::vector, std::ofstream, std::ifstream;

void saveGame(const vector<vector<int>>& board, int score) {
    string filename = "save.txt";
    ofstream file(filename);
    if (!file.is_open()) return;
    file << score << "\n";
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            file << board[i][j] << " ";
        }
        file << "\n";
    }
    file.close();
}

bool loadGame(vector<vector<int>>& board, int& score) {
    string filename = "save.txt";
    ifstream file(filename);
    if (!file.is_open()) return false;
    file >> score;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            file >> board[i][j];
        }
    }
    file.close();
    return true;
}
