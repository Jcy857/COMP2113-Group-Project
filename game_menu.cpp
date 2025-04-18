#include <iostream>
#include <vector>
#include <string>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

using namespace std;
struct termios orig_term;

extern int** grid;
extern int Size;

// @param None
// @return true if a key has been pressed, false otherwise
// This function uses non-blocking I/O to check for key presses without waiting for input
bool kbhit() {
    char ch;
    int n = read(STDIN_FILENO, &ch, 1);
    if (n > 0) {
        ungetc(ch, stdin);
        return true;
    }
    return false;
}

// @param None
// @return None
// This function restores the terminal settings to their original state and releases the dynamic memory of the grid
void RestoreInput() {
    tcsetattr(STDIN_FILENO, TCSANOW, &orig_term);
    int flags = fcntl(STDIN_FILENO, F_GETFL);
    fcntl(STDIN_FILENO, F_SETFL, flags & ~O_NONBLOCK);
    // Release the memory of the old dynamic board if the board is not empty
    if (grid != nullptr) {
        for (int i = 0; i < Size; ++i) {
            delete[] grid[i];
            grid[i] = nullptr;
        }
        delete[] grid;
        grid = nullptr;
    }
}

// @param None
// @return None
// This function sets the terminal to non-blocking input mode
void SetNonBlockingInput() {
    struct termios ttystate;
    tcgetattr(STDIN_FILENO, &orig_term);
    tcgetattr(STDIN_FILENO, &ttystate);
    ttystate.c_lflag &= ~(ICANON | ECHO);
    ttystate.c_cc[VMIN] = 0;
    ttystate.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSANOW, &ttystate);
    fcntl(STDIN_FILENO, F_SETFL, fcntl(STDIN_FILENO, F_GETFL) | O_NONBLOCK);
}

// @param title: The title of the menu
// @param options: A vector of strings representing the menu options
// @param selected: The index of the currently selected option
// @param score: The current score to display
// @param error_msg: An optional error message to display
// @return None
// This function prints a generic menu with the title, options, selected option, and score
void PrintGenericMenu(const string& title, const vector<string>& options, int selected, int score, string error_msg) {
    system("clear");
    cout << "Score: " << score << "\n\n";
    cout << "===== " << title << " =====\n";
    for (int i = 0; i < options.size(); i++) {
        cout << (selected == i ? "> " : "  ") << options[i] << "\n";
    }
    cout << "\nUse W/S to navigate, E to select\n";
    if (!error_msg.empty()) {
        cout << "====================================\n";
        cout << error_msg << "\n";
    }
}

// @param title: The title of the menu
// @param options: A vector of strings representing the menu options
// @param score: The current score to display
// @param error_msg: An optional error message to display
// @return The index of the selected option
// This function shows a generic menu and returns the index of the selected option
int ShowGenericMenu(const string& title, const vector<string>& options, int score, string error_msg) {
    int selected = 0;
    PrintGenericMenu(title, options, selected, score, error_msg);
    
    while (true) {
        if (kbhit()) {
            char ch;
            cin >> ch;
            if (ch == 'w') {
                selected = (selected - 1 + options.size()) % options.size();
                PrintGenericMenu(title, options, selected, score, error_msg);
            } else if (ch == 's') {
                selected = (selected + 1) % options.size();
                PrintGenericMenu(title, options, selected, score, error_msg);
            } else if (ch == 'e') {
                return selected;
            }
        }
        usleep(100000);
    }
}

