#include <iostream>
#include <vector>
#include <string>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

using std::string, std::vector, std::cin, std::cout;
struct termios orig_term;

bool kbhit() {
    char ch;
    int n = read(STDIN_FILENO, &ch, 1);
    if (n > 0) {
        ungetc(ch, stdin);
        return true;
    }
    return false;
}

void restoreInput() {
    tcsetattr(STDIN_FILENO, TCSANOW, &orig_term);
    int flags = fcntl(STDIN_FILENO, F_GETFL);
    fcntl(STDIN_FILENO, F_SETFL, flags & ~O_NONBLOCK);
}

void setNonBlockingInput() {
    struct termios ttystate;
    tcgetattr(STDIN_FILENO, &orig_term);
    tcgetattr(STDIN_FILENO, &ttystate);
    ttystate.c_lflag &= ~(ICANON | ECHO);
    ttystate.c_cc[VMIN] = 0;
    ttystate.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSANOW, &ttystate);
    fcntl(STDIN_FILENO, F_SETFL, fcntl(STDIN_FILENO, F_GETFL) | O_NONBLOCK);
}


void printGenericMenu(const string& title, const vector<string>& options, int selected, int score) {
    system("clear");
    cout << "Score: " << score << "\n\n";
    cout << "===== " << title << " =====\n";
    for (int i = 0; i < options.size(); i++) {
        cout << (selected == i ? "> " : "  ") << options[i] << "\n";
    }
    cout << "\nUse W/S to navigate, E to select\n";
}

int showGenericMenu(const string& title, const vector<string>& options, int score) {
    int selected = 0;
    printGenericMenu(title, options, selected, score);
    
    while (true) {
        if (kbhit()) {
            char ch;
            cin >> ch;
            if (ch == 'w') {
                selected = (selected - 1 + options.size()) % options.size();
                printGenericMenu(title, options, selected, score);
            } else if (ch == 's') {
                selected = (selected + 1) % options.size();
                printGenericMenu(title, options, selected, score);
            } else if (ch == 'e') {
                return selected;
            }
        }
        usleep(100000);
    }
}

