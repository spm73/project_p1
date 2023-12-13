#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

#define NAME 20
#define SPRITE_LENGTH 91
#define SPRITE_WIDHT 45
#define N_SPRITES 3

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

TTamagotchi Tamagotchi(char name[NAME]) {
   
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
};

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

    system("clear"); // clears the terminal so that a new sprite could be displayed
    // print display
    for (int i = 0; i < SPRITE_WIDHT; i++) {
        for (int j = 0; j < SPRITE_LENGTH; j++)
            printf("%c", sprite[i][j]);
        printf("\n");
    }
}

void blink(const char sprites[N_SPRITES][SPRITE_WIDHT][SPRITE_LENGTH]) {
    
    /*
    Procedure to draw the blinks of the tamagotchi.
    */
    
    // Declare and assign the value for the blink
    const float TIME = 1;
    for (int i = 0; i < 2; i++) {
        sleep(TIME);
        print_sprite(sprites[i % 2 + 1]);
        // sleep(time);
    }

}

void main_loop(TTamagotchi* tmgtchi, const char sprites[N_SPRITES][SPRITE_WIDHT][SPRITE_LENGTH]) {
    const float TIME = 1;
    
    char user_input;

    while ((*tmgtchi).alive) {
        blink(sprites);
        if ((*tmgtchi).hunger >= 70) {
            printf("I'm hungry!\n");
            scanf("%c", &user_input);
            if ((*tmgtchi).hunger >= 100) { 
                (*tmgtchi).alive = false;
                system("clear");
                printf("%s has died of ligma\n", (*tmgtchi).name);
            }
            switch (user_input) {
                case 'c':
                    (*tmgtchi).hunger = 0;
                default:
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
        (*tmgtchi).hunger += 10;
    }
}

int main() {
    char name[NAME];
    get_name(name);
    
    char sprites[N_SPRITES][SPRITE_WIDHT][SPRITE_LENGTH];
    clean_sprites(sprites);
    load_sprites(sprites);
    TTamagotchi tmgcthi = Tamagotchi(name);
    main_loop(&tmgcthi, sprites);
}