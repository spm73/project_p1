#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <curses.h>

#define NAME 20
#define SPRITE_LENGTH 91 // length of a line in the sprites file
#define SPRITE_WIDHT 45 // max number of lines a sprite can have
#define N_SPRITES 9 // number of sprites
#define NORMAL_TICK 750000 // use for change sprites and so on
#define LONG_TICK 2000000

/*todo esta metido con modulos, estos son solo los contadores de hambre, sueño, hygiene y nivel de lele pancha*/
void hunger_update(int*);
void tiredness_update(int*, bool*);
void hygiene_update(int*, bool*);
void illness_lvl_update(int*, bool*, int*, WINDOW*, const char sprites[N_SPRITES][SPRITE_WIDHT][SPRITE_LENGTH]);
void has_sleep(int*, const char sprites[N_SPRITES][SPRITE_WIDHT][SPRITE_LENGTH]);
void bath(int*, const char sprites[N_SPRITES][SPRITE_WIDHT][SPRITE_LENGTH]);
void take_medicaments(bool*, bool*, const char sprites[N_SPRITES][SPRITE_WIDHT][SPRITE_LENGTH], WINDOW*);
void die(const TTamagotchi* tmgtchi, const char dead_sprite[SPRITE_WIDHT][SPRITE_LENGTH]);
// en el main tan solo se ejecutan los modulos, piensa que esto es provisional y debe ir anidado a otras funciones
int main(){
    // int hunger;
    // int tireddness;
    // int hygiene;
    // int illness_lvl;

    // hunger_update(&hunger);
    // tiredness_update(&tiredness);
    // hygiene_update(&hygiene);
    // illness_level_update(&illness_lvl, &ill, &score);


}
//cada modulo cuenta con un puntero que es el valor que pasa como actualización
void hunger_update(int* hunger){
    // int hunger = *h;
    // hunger++;
    // *h = hunger;
    (*hunger)++;
    if (*hunger == 100)
        die();
}

//la diferencia de este modulo con el primero es que si llega al limiite de sueño no morira y que dormir supone el reabastecimiento completo de el sueño
void tiredness_update(int* tiredness, bool* ill){
    (*tiredness)++;
    if(*tiredness == 100){
        printw("I'm starting to feel strange");
        refresh();
        *ill = true;
    }
}    


//la higiene es igual al cansancio
void hygiene_update(int* hygiene, bool* ill){
    (*hygiene)++;
    if (*hygiene == 100){
        printw("I'm starting to feel strange");
        refresh();
        *ill = true;
    }
}

//esta es la funcion más especial porque depende de un modulo, ya que solo se activar el contador cuando este enfermo
void illness_lvl_update(int* illness_lvl, bool* ill, int* score, WINDOW* win, const char sprites[N_SPRITES][SPRITE_WIDHT][SPRITE_LENGTH]){
    int choose;
    bool smoke_weed = false;
    bool drink_potion = false;
    clock_t begin_count = clock();
    clock_t end_count;
    double time_passed;
    if(*ill == true){
        do{
            printw("do you want a medicament(y|n)\n");
            refresh();
            choose = wgetch(win);
            switch(choose) {
                case 'y':
                    take_medicament(&smoke_weed, &drink_potion, sprites, win);
                    if (smoke_weed == true) {
                        *illness_lvl = 0;
                        *score = *score - 500;
                    }
                    else if(drink_potion == true) {
                        *illness_lvl -= 30;
                        *score = *score - 200;
                        while(*illness_lvl < 0)
                            *illness_lvl = 0;
                    }
                    else{
                        *illness_lvl += 5;
                        if(*illness_lvl == 100)
                            die();
                    }
                    break;
                case 'n':
                    *illness_lvl += 5;
                    if(*illness_lvl == 100)
                        die();
                    break;
                default:
                    *illness_lvl += 5;
                    if(*illness_lvl == 100) 
                        die();
                    break;
            }
            end_count = clock();
            time_passed = (end_count - begin_count) / CLOCKS_PER_SEC;

            if(*illness_lvl == 0)
                *ill = false;
        }while(((choose != 'y')&&(choose != 'n'))&& time_passed < 2);
    }    
}


void take_medicaments(bool* drink_potion, bool* smoke_weed, const char sprites[N_SPRITES][SPRITE_WIDHT][SPRITE_LENGTH], WINDOW* win){
    int chose_med;
    int potion_sprite = 7;
    int smoke_sprite = 8;
    clock_t begin_count = clock();
    clock_t end_count;
    double time_passed;
    bool pressed = false;
    printw("which medicament do you want?\n");
    printw("1.potion (health+30)| 200 score\n");
    printw("2.secret way(health max)| 500 score\n");
    printw("other number to exit\n");
    refresh();
    chose_med = wgetch(win);
    do{
        switch(chose_med){
            case 1:
                *drink_potion = true;
                print_sprite(sprites[potion_sprite]);
                usleep(LONG_TICK);
                pressed = true;
                break;
            case 2:
                *smoke_weed = true;
                print_sprite(sprites[smoke_sprite]);
                usleep(LONG_TICK);
                break;
                pressed = true;
            default:
                pressed = false;
                break;
        }
    end_count = clock();
    time_passed = (end_count - begin_count) / CLOCKS_PER_SEC; // update time spent
    }while(time_passed < 2 && !pressed);
}

void bath(int* hygiene, const char sprites[N_SPRITES][SPRITE_WIDHT][SPRITE_LENGTH]){
    *hygiene = 0;
    int bath_sprite = 6;
    print_sprite(sprites[bath_sprite]);
    usleep(LONG_TICK);
}

void has_sleep (int* tiredness, const char sprites[N_SPRITES][SPRITE_WIDHT][SPRITE_LENGTH]){
    *tiredness = 0;
    int sleep_sprite = 0;
    print_sprite(sprites[sleep_sprite]);
    usleep(LONG_TICK);
}

void die(const char tmgtchi_name[NAME], const char dead_sprite[SPRITE_WIDHT][SPRITE_LENGTH]) {
    
    /*
    Void to execute if the tamagotchi dies.
    */

    erase(); // clears screen
    print_sprite(dead_sprite); // prints gravestone
    printw("%s has died of ligma\n", tmgtchi_name); // followed by the name of the tamagotchi
    refresh();
    usleep(LONG_TICK);
    endwin();
    exit(0);
}