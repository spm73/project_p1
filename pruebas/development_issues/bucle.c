#include <curses.h>
#include <stdlib.h>
#include <unistd.h>

void main() {
    WINDOW* win = initscr();
    keypad(win, true);
    nodelay(win, true);
    int a = 0;
    for (;;) {
        int pressed = wgetch(win);
        if (pressed == KEY_LEFT) { 
            a++;
            putp("HelloP");
        }
        erase();
        mvaddstr(a,0,"Hello");
        usleep(100000);
    }
    endwin();
}