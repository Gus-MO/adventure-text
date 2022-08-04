#include "../Screen.h"

int main() {
    int rows, columns;
    initialize_window();
    printw("Hello World!!\n");

    get_terminal_size(columns, rows);

    for (int i = 0; i < 5; i++) {
        printw("Your text: %s\n", read_user_input().c_str());
    }

    getch();
    close_window();
}
