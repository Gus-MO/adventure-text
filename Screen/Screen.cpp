#include "Screen.hpp"

void get_terminal_size(int& width, int& height) {
    getmaxyx(stdscr,height,width);		// ncurses
}

void initialize_window() {
    int columns;
    int rows;

    get_terminal_size(columns, rows);

    initscr();				// From ncurses
    keypad(stdscr, TRUE);
    scrollok(stdscr, TRUE);
    idlok(stdscr, TRUE);

    mvaddch(rows-1, 0, '\n');		// ncurses, 0 column
}

void close_window() {
    endwin();
}

std::string read_user_input() {
    int columns;
    int rows;

    get_terminal_size(columns, rows);

    char userIn[STR_LIMIT];
    std::string userOut;

    printw(PROMPT);
    mvgetnstr(rows-1, 2, userIn, STR_LIMIT);
    userOut = static_cast<std::string>(userIn);

    return userOut;
}
