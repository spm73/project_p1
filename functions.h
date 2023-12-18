#include <curses.h>

#define NAME 20 
#define SPRITE_LENGTH 91 
#define SPRITE_WIDHT 45 
#define N_SPRITES 9 
#define NORMAL_TICK 750000 
#define LONG_TICK 2000000 

typedef struct {
    char name[NAME];
    int hunger;
    int tiredness;
    int hygene;
    bool go_to_bathroom;
    bool ill;
    int illness_lvl;
    bool alive;
} TTamagotchi;

TTamagotchi Tamagotchi(const char name[NAME]);

void get_name(char name[]);

void load_sprites(char sprites[N_SPRITES][SPRITE_WIDHT][SPRITE_LENGTH]);

void clean_sprites(char sprites[N_SPRITES][SPRITE_WIDHT][SPRITE_LENGTH]);

void print_sprite(const char sprite[SPRITE_WIDHT][SPRITE_LENGTH]);

void blink(const char sprites[N_SPRITES][SPRITE_WIDHT][SPRITE_LENGTH], const char message[NAME]);

void die(const TTamagotchi* tmgtchi, const char dead_sprite[SPRITE_WIDHT][SPRITE_LENGTH]);

void main_loop(TTamagotchi* tmgtchi, const char sprites[N_SPRITES][SPRITE_WIDHT][SPRITE_LENGTH], WINDOW* win);

TTamagotchi init_game(char sprites[N_SPRITES][SPRITE_WIDHT][SPRITE_LENGTH]);