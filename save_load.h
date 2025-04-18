#ifndef SAVE_LOAD_H
#define SAVE_LOAD_H

#include <vector>

void SaveGame(int** & board, int Size, int score, int streak, std::string difficulty);
bool LoadGame(int** & board, int& Size, int& score, int& streak, std::string& difficulty);

#endif
