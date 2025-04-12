#ifndef SAVE_LOAD_H
#define SAVE_LOAD_H

#include <vector>

void SaveGame(const std::vector<std::vector<int>>& board, int Size, int score);
bool LoadGame(std::vector<std::vector<int>>& board, int& Size, int& score);

#endif