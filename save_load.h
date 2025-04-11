#ifndef SAVE_LOAD_H
#define SAVE_LOAD_H

#include <vector>

void saveGame(const std::vector<std::vector<int>>& board, int Size, int score);
bool loadGame(std::vector<std::vector<int>>& board, int& Size, int& score);

#endif