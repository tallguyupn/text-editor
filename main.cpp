#include <iostream>
#include <fstream>
#include <string>
#include <ncurses.h>

void input(std::string &text);

int main() {
    std::string FileName;
    std::string text;

    initscr();
    cbreak();
    keypad(stdscr, TRUE);
    curs_set(0);

    printw("Text editor\nPress 'E' or '1' to enter input mode\n");
    refresh();

    int command = getch();  // No need for a pointer

    if (command == 'E' || command == '1') {  // Use character literals
        input(text);
        refresh();
    }

    endwin();  // Restore terminal settings before printing to console
    std::cout << "hello world" << std::endl;
    return 0;
}

void input(std::string &text) {
    clear();  // Clear screen instead of calling initscr() again
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    curs_set(1);

    printw("Type something. Press ESC to exit.\n");
    refresh();

    int ch;
    while ((ch = getch()) != 27) {  // Loop until ESC key (27) is pressed
        if (ch == '\n') {  // Handle new lines
            text += '\n';
            printw("\n");
        } else if (ch == KEY_BACKSPACE || ch == 127) {  // Handle backspace
            if (!text.empty()) {
                text.pop_back();
                int y, x;
                getyx(stdscr, y, x);
                move(y, x - 1);
                delch();
            }
        } else {
            text += ch;
            printw("%c", ch);
        }
        refresh();
    }

    clear();  // Clear screen before returning
    printw("Exited input mode.\n");
    refresh();
}