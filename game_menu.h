#ifndef GAME_MENU_H
#define GAME_MENU_H

#include <vector>
#include <string>
using std::string, std::vector;

bool kbhit();
void restoreInput();
void setNonBlockingInput();
void printGenericMenu(const string& title, const vector<string>& options, int selected, int score);
int showGenericMenu(const string& title, const vector<string>& options, int score);
#endif