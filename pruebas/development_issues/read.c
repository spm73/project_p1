#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#define SPRITE_LENGTH 91
#define SPRITE_WIDHT 45
#define N_SPRITES 9
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

    system("clear"); // needed. If not, a part of the last sprite appears on the top.
    // erase(); // clears the terminal so that a new sprite could be displayed
    // print display
    for (int i = 0; i < SPRITE_WIDHT; i++) {
        for (int j = 0; j < SPRITE_LENGTH; j++)
            printf("%c", sprite[i][j]);
        printf("\n");
    }
}
int main() {
    // char arr[4][4];

    // FILE *text;

    // if (text = fopen("text.txt", "r")) {
    //     for (int i = 0; i < 4; i++) {
    //         fscanf(text, "%[^\n]s", arr[i]);
    //         // printf("%s\n", arr[i]);
    //         // fgets(arr[i], 5, text);
    //         fseek(text, 1, SEEK_CUR);
    //     }
    //     fclose(text);
    // }
    // for (int j = 0; j < 4; j++) {
    //     // printf("%s\n", arr[j]);
    //     for (int k = 0; k < 4; k++) {
    //         printf("%c", arr[j][k]);
    //     }
    //     printf("\n");
    // }
    char arr[N_SPRITES][SPRITE_WIDHT][SPRITE_LENGTH];
    clean_sprites(arr);
    load_sprites(arr);
    for (int i = 0; i < N_SPRITES; i++) {
        print_sprite(arr[i]);
        sleep(2);
    }
}