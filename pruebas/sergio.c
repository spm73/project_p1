#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>

#define NAME 20
#define SPRITE_LENGTH 91
#define SPRITE_WIDHT 43 
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

void get_sprite(char sprite[SPRITE_WIDHT][SPRITE_LENGTH], FILE* sprite_file) {
    
    /*
    Module for getting a sprite
    The sprites are in the file sprites.txt (2nd argument)
    The first argument is a bidimensional array that store a sprite
    This procedure reads from the sprite file a single sprite.
    */

    for (int i = 0; i < SPRITE_WIDHT; i++) {
        fscanf(sprite_file, "%[^\n]s", sprite[i]); // another [] implies adding by chars
        // when calls fscanf the pointer moves to the last char of a line, so to move to a new line 
        // just move the pointer 1 position to the right
        fseek(sprite_file, 1, SEEK_CUR);
    }
    // rewind(sprite_file);
}

void load_sprites(char sprites[N_SPRITES][SPRITE_WIDHT][SPRITE_LENGTH]) {

    /*
    Module for charging all the sprites
    Needs of a 3 dimensional array to store them (an array for all the sprites, an array of strings (sprite) and an array of chars)
    */

    FILE *sprites_file;
    if (sprites_file = fopen("./sprites.txt", "r")) { // if fopen returns NULL, does not execute the code.
        int sprites_loaded = 0;
        char is_n;
        while (sprites_loaded < N_SPRITES) {
            is_n = getc(sprites_file);
            if (is_n != 'n') {
                fseek(sprites_file, -1, SEEK_CUR);
                sprites_loaded++;
                for (int i = 0; i < SPRITE_WIDHT; i++) {
                    fscanf(sprites_file, "%[^\n]s", sprites[sprites_loaded][i]); // another [] implies adding by chars
                    // when calls fscanf the pointer moves to the last char of a line, so to move to a new line 
                    // just move the pointer 1 position to the right
                    fseek(sprites_file, 1, SEEK_CUR);
                }
            }
        }
        fclose(sprites_file);
    }
}

int main() {
    // char name[NAME];
    // get_name(name);
    
    char sprites[N_SPRITES][SPRITE_WIDHT][SPRITE_LENGTH];
    load_sprites(sprites);
    // TTamagotchi tmgcthi = Tamagotchi(name);
    for (int i = 0; i < N_SPRITES; i++) {
        for(int j = 0; j < SPRITE_WIDHT; j++) {
            printf("%s\n", sprites[i][j]);
        }
    }
}