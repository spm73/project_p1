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
    int score;
} TTamagotchi;

TTamagotchi Tamagotchi(const char name[NAME]);

void get_name(char name[]);

void load_sprites(char sprites[N_SPRITES][SPRITE_WIDHT][SPRITE_LENGTH]);

void clean_sprites(char sprites[N_SPRITES][SPRITE_WIDHT][SPRITE_LENGTH]);

void print_sprite(const char sprite[SPRITE_WIDHT][SPRITE_LENGTH]);

void blink(const char sprites[N_SPRITES][SPRITE_WIDHT][SPRITE_LENGTH]);

void die(const TTamagotchi* tmgtchi, const char dead_sprite[SPRITE_WIDHT][SPRITE_LENGTH]);

void main_loop(TTamagotchi* tmgtchi, const char sprites[N_SPRITES][SPRITE_WIDHT][SPRITE_LENGTH], WINDOW* win);

void print_instructions();

TTamagotchi init_game(char sprites[N_SPRITES][SPRITE_WIDHT][SPRITE_LENGTH]);

int eat(const char sprites[N_SPRITES][SPRITE_WIDHT][SPRITE_LENGTH], int hunger, WINDOW* win);

void hunger_update(int* hunger, const char tmgcthi_name[NAME], const char sprites[N_SPRITES][SPRITE_WIDHT][SPRITE_LENGTH]);

void tiredness_update(int* tiredness, bool* ill);

void hygiene_update(int* hygiene, bool* ill);

void illness_lvl_update(TTamagotchi* tmgtchi, WINDOW* win, const char sprites[N_SPRITES][SPRITE_WIDHT][SPRITE_LENGTH]);

void take_medicaments(bool* drink_potion, bool* smoke_weed, const char sprites[N_SPRITES][SPRITE_WIDHT][SPRITE_LENGTH], WINDOW* win);

void bath(int* hygiene, const char sprites[N_SPRITES][SPRITE_WIDHT][SPRITE_LENGTH]);

void tmgchti_sleep(int* tiredness, const char sprites[N_SPRITES][SPRITE_WIDHT][SPRITE_LENGTH]);

int update_score(int score);

void update_stats(TTamagotchi* tmgtchi, const char sprites[N_SPRITES][SPRITE_WIDHT][SPRITE_LENGTH], WINDOW* win);