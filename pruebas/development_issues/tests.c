#include <stdio.h>
#include <time.h>
#include <curses.h>
#include <unistd.h>

int main() {
    WINDOW* win = initscr();
    keypad(win, true);
    nodelay(win, true);
    int user_input;
    // do {
    //     flushinp(); 
    //     printw("enter char");
    //     refresh();
    //     sleep(1);
    //     user_input = wgetch(win);
    //     if (user_input != ERR)
    //         printw("%d", user_input);
    //     refresh();
    //     sleep(1);
    //     erase();
    // } while (user_input != 'e');
    nodelay(win, false);
    user_input = wgetch(win);
    nodelay(win, true);
    printw("%d", user_input);
}