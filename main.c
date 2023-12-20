#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include "functions.h"

int main() {
    char sprites[N_SPRITES][SPRITE_WIDHT][SPRITE_LENGTH];

    TTamagotchi tmgchti = init_game(sprites);

    // Starting the terminal window and configure some values
    WINDOW* win = initscr();
    keypad(win, true);
    nodelay(win, true);
    
    // Game starts
    main_loop(&tmgchti, sprites, win);

    // When game ends, close the window
    endwin();
}