#include <stdio.h>
<<<<<<< HEAD
=======
#include <ncurses.h>
#include <unistd.h>

int main() {
    // initscr();
    char a;
    nodelay(stdscr, TRUE);
    // printf("To stop the loop press any key\n");
    for (int i = 0; i < 10; i++) {
        if ((a = getch()) == ERR) {
            printf("User has not pressed\n");
        } else {
            printf("User pressed %c\n", a);
        }
        sleep(1);
    }
}
>>>>>>> 06aa1a80e0a074946801f1cd921cfabf6b24c3ec
