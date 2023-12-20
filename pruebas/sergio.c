#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <curses.h>
#include <time.h>

#define NAME 20
#define SPRITE_LENGTH 91
#define SPRITE_WIDHT 45
#define N_SPRITES 9

typedef struct {

    /*
    Type for Tamagotchi, we called it TTamagotchi as we later have defined a constructor function
    A Tamagotchi has a name (string) and some stats which increase or decrease as time goes by. 
    To make the game funier, some stats increase or decrease with a minigame.
        hunger: measures the hunger of the Tamagotchi. It increases as time passes. 
                If passes certain value, you have to feed it. To feed it, user has to play a minigame in which user
                has to make a dish.
        tiredness: measures how tired is the Tamagotchi. It increases as tiem passes.
                If passes certain value, you have to send the Tamagotchi to sleep. To decrease it, you have to stay 
                some time with the Tamagotchi sleeping.
        hygene: measures how clean is the Tamagotchi. Initially, the Tamagotchi is clean and with time it gets dirty.
                If it gets very dirty, you have to clean it by playing a minigame.
        go_to_bathroom: if the Tamagotchi has to make its necessities, it turns into true.
        ill: if the Tamagotchi is ill, then it turns into true.
        illness_lvl: if the Tamagotchi is ill, then this stat measures how ill it is. This stat does not increase
                if ill is false. To decrease it, user has to play a minigame to make the medicine.
        alive: by default, the Tamagotchi is alive. However, if user does not feed him or does not treat him when it is ill,
                the Tamagotchi can eventually die.
    */

    char name[NAME];
    int hunger;
    int tiredness;
    int hygene;
    bool go_to_bathroom;
    bool ill;
    int illness_lvl;
    bool alive;
} TTamagotchi;

TTamagotchi Tamagotchi(const char name[NAME]) {
   
    /*
    Constructor for a TTamagotchi.
    Creates a TTamagotchi with its name and sets default values. 
    */

    TTamagotchi tmgtchi;
    strcpy(tmgtchi.name, name);
    tmgtchi.hunger = 0;
    tmgtchi.tiredness = 0;
    tmgtchi.hygene = 100;
    tmgtchi.go_to_bathroom = false;
    tmgtchi.ill = false;
    tmgtchi.illness_lvl = 0;
    tmgtchi.alive = true;

    return tmgtchi;
}

void get_name(char name[]) {
    // Function to get the name of the Tamagotchi from the user
    // First function to be called
    printf("Introduce the name of your Tamagotchi: ");
    scanf("%[^\n]s", name);
}

void load_sprites(char sprites[N_SPRITES][SPRITE_WIDHT][SPRITE_LENGTH]) {

    /*
    Module for charging all the sprites
    Needs of a 3 dimensional array to store them (an array for all the sprites, an array of strings (sprite) and an array of chars)
    In sprites file, 'n' is used for separating sprites
    */

    FILE *sprites_file;
    int loaded_sprites = 0;
    int sprite_lines = 0;
    char next_char;

    if (sprites_file = fopen("./sprites.txt", "r")) { // if does not open, the code does not execute.
        fseek(sprites_file, 1, SEEK_CUR);
        do {
            next_char = getc(sprites_file);
            if (next_char == 'n') {
                // 'n' is found, store sprite in next position.
                loaded_sprites++;
                sprite_lines = 0;
            } else {
                // get the lines of the sprite
                fscanf(sprites_file, "%[^\n]s", sprites[loaded_sprites][sprite_lines]);
                sprite_lines++;
                fseek(sprites_file, 1, SEEK_CUR);
            }
        } while (next_char != EOF);
        fclose(sprites_file); // close only if it has been opened
    }

    // for (int k = 0; k < N_SPRITES; k++) {
    //     for (int i = 0; i < SPRITE_WIDHT; i++) {
    //         for (int j = 0; j < SPRITE_LENGTH; j++) {
    //             printf("%c", sprites[k][i][j]);
    //         }
    //         printf("\n");
    //         // printf("%s\n", sprites[0][i]); // wtf?
    //     }
    // }
}

void clean_sprites(char sprites[N_SPRITES][SPRITE_WIDHT][SPRITE_LENGTH]) {

    /*
    Procedure that makes all the values of the array of sprites be a blank space
    */
   
    for (int i = 0; i < N_SPRITES; i++) 
        for (int j = 0; j < SPRITE_WIDHT; j++) 
            for (int k = 0; k < SPRITE_LENGTH; k++)
                sprites[i][j][k] = ' ';
}

void print_sprite(const char sprite[SPRITE_WIDHT][SPRITE_LENGTH]) {

    /*
    Procedure to print a single sprite
    */

    erase(); // clears the terminal so that a new sprite could be displayed
    // print display
    for (int i = 0; i < SPRITE_WIDHT; i++) {
        for (int j = 0; j < SPRITE_LENGTH; j++)
            printw("%c", sprite[i][j]);
        printw("\n");
    }
    refresh();
}

void blink(const char sprites[N_SPRITES][SPRITE_WIDHT][SPRITE_LENGTH], const char message[NAME]) {
    
    /*
    Procedure to draw the blinks of the tamagotchi.
    Also, prints an info message of the state of the tamagotchi. 
    */
    
    // Declare and assign the value for the blink
    const int TIME = 750000;
    for (int i = 0; i < 2; i++) {
        print_sprite(sprites[i % 2 + 1]);
        printw("%s", message);
        refresh();
        usleep(TIME);
        // sleep(time);
    }
}

void die(const char tmgtchi_name[NAME], const char dead_sprite[SPRITE_WIDHT][SPRITE_LENGTH]) {
    
    /*
    Void to execute if the tamagotchi dies.
    */

    const int TIME = 2000000;
    // system("clear");
    erase(); // clears screen
    print_sprite(dead_sprite); // prints gravestone
    printw("%s has died of ligma\n", tmgtchi_name); // followed by the name of the tamagotchi
    refresh();
    usleep(TIME);
}

int eat(const char sprites[N_SPRITES][SPRITE_WIDHT][SPRITE_LENGTH], int hunger, WINDOW* win) {

    /*
    Function that makes the animations for eating and updates the stats
    First, we print the dorayaki and wait until the user gives the order to eat
    If the user gives the order, then we change the sprite and we set the return value to 0,
        whichi means that the tamagothci is no longer hungry
    However, if the user does not give the order, the value stays the same and the sprite does not change 
    */

    int dorayaki_sprite = 3; // index of the full dorayaki sprite
    int user_input;
    bool pressed = false;
    // now we set the variables to measure time
    clock_t begin_count = clock();
    clock_t end_count;
    double time_passed;
    do {
        print_sprite(sprites[dorayaki_sprite]); // print the full dorayaki sprite
        user_input = wgetch(win); // get user input
        switch (user_input) {
            case 'e':
                hunger = 0; // as the tamagotchi has been fed, then it is no longer hungry
                pressed = true;
                dorayaki_sprite = 4; // change index of sprite
                print_sprite(sprites[dorayaki_sprite]);
                usleep(2000000);
                break;
            default:
                pressed = false;
                break;
        }
        end_count = clock();
        time_passed = (end_count - begin_count) / CLOCKS_PER_SEC; // update time spent
    } while (time_passed < 2 && !pressed);

    return hunger;
}

void main_loop(TTamagotchi* tmgtchi, const char sprites[N_SPRITES][SPRITE_WIDHT][SPRITE_LENGTH], WINDOW* win) {
    
    int user_input;
    char message[NAME] = ""; // must be initialized to an empty string as the message could contain weird characters generated randomly 

    while ((*tmgtchi).alive) {
        blink(sprites, message);
        // user_input = ERR;
        (*tmgtchi).hunger += 10;
        if ((*tmgtchi).hunger >= 70) {
            strcpy(message, "I'm hungry\n");
            // scanf("%c", &user_input);
            user_input = wgetch(win);
            switch (user_input) {
                case 'e':
                    flushinp();
                    (*tmgtchi).hunger = eat(sprites, (*tmgtchi).hunger, win);
                    if ((*tmgtchi).hunger == 0)
                        strcpy(message, "");
                default:
                    if ((*tmgtchi).hunger >= 100) 
                        (*tmgtchi).alive = false;
                    break;
            }
        } else if ((*tmgtchi).tiredness >= 70) {
            printf("I'm tired!\n");
        } else if ((*tmgtchi).hygene <= 30) {
            printf("Can I have a bath?\n");
        } else if ((*tmgtchi).go_to_bathroom) {
            printf("I need to go to the bathroom\n");
        } else if ((*tmgtchi).ill) {
            printf("Mr Stark, I don't feel so good\n");
        }
        flushinp();
    }
    die((*tmgtchi).name, sprites[5]);
}

void create_screen(WINDOW* win) {
    
    /*
    Procedure to create a window to display the tamagotchi
    error
    */

    win = initscr(); // initialize window
    keypad(win, true); // unables to enter special keys from keyword such as the arrows
    nodelay(win, true); // unables continue process even though user does not enter a value
}

TTamagotchi init_game(char sprites[N_SPRITES][SPRITE_WIDHT][SPRITE_LENGTH]) {
    
    /*
    Function to initialize the game, in other words, sets up all things for
    the correct functioning.
    Must be called before initializing a window with ncurses.
    */

    char name[NAME];
    get_name(name);
    clean_sprites(sprites);
    load_sprites(sprites);
    TTamagotchi tmgcthi = Tamagotchi(name);
    return tmgcthi;
}

int main() {
    char sprites[N_SPRITES][SPRITE_WIDHT][SPRITE_LENGTH];
    
    TTamagotchi tmgcthi = init_game(sprites);

    WINDOW* win = initscr();
    keypad(win, true);
    nodelay(win, true);
    // create_screen(win);
    main_loop(&tmgcthi, sprites, win);
    endwin();
    system("clear");
}