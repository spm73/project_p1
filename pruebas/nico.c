#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
/*todo esta metido con modulos, estos son solo los contadores de hambre, sueño, hygiene y nivel de lele pancha*/
void hunger_update();
void tiredness_update();
void hygiene_update();
void illness_lvl_update();
bool die();
bool ill;
void has_sleep();
void bath();
void take_medicaments();
// en el main tan solo se ejecutan los modulos, piensa que esto es provisional y debe ir anidado a otras funciones
int main(){
    int hunger;
    int tireddness;
    int hygiene;
    int illness_lvl;

    hunger_update(&hunger);
    tiredness_update(&tiredness);
    hygiene_update(&hygiene);
    illness_level_update(&illness_lvl, &ill, &score);


}
//cada modulo cuenta con un puntero que es el valor que pasa como actualización
void hunger_update(int* h){
    int hunger = *h;
        hunger++;
        *h = hunger;
        if (hygiene == 100){
            die();}
    }

//la diferencia de este modulo con el primero es que si llega al limiite de sueño no morira y que dormir supone el reabastecimiento completo de el sueño
void tierdness_update(int* t, bool* ill){
    int tierdness = *t;
        tiredness++;
        t* = tiredness;
        if(tierdness == 100){
            printf("I'm starting to feel strange");
            *ill = true;}
}    


//la higiene es igual al cansancio
void hygiene_update(int* g, bool* ill){
    int hygiene = *g;
        tiredness++;
        *g = hygiene;
        if(hygiene == 100){
            printf("I'm starting to feel strange");
            *ill = true;}
    }

//esta es la funcion más especial porque depende de un modulo, ya que solo se activar el contador cuando este enfermo
void illness_lvl_update(int* l, bool* ill, int* score, WINDOW* win){
    int illness_lvl = *l;
    char chose = 0;
    bool smoke_weed = false;
    bool drink_potion = false;
    clock_t begin_count = clock();
    clock_t end_count;
    if(*ill == true){
        do{
        printf("do you want a medicament(y|n)\n");
        scanf("%c", &chose);
        switch(chose){
            case 'y':
                take_medicament(&smoke_weed, &drink_potion, sprites, win);
                if (smoke_weed == true){
                    illness_lvl = 0;
                    *l = illness_lvl;
                    *score = *score - 500;
                }
                else if(drink_potion == true){
                    illness_lvl = illness_lvl - 30;
                    *score = *score - 200;
                    while(illness_lvl < 0){illness_level = 0;}
                    *l = illness_lvl;
                }
                else{
                    illness_lvl = illness_level + 5;
                    *l = illness_level
                    if(illness_level == 100){die();}
                }
                break;
            case 'n':
                 illness_lvl = illness_lvl + 5;
                *l = illness_level;
                if(illness_level == 100){die();}
                break;
            default:
                illness_lvl = illness_lvl + 5;
                *l = illness_level;
                if(illness_level == 100){die();}
                break;
        }
        end_count = clock();
        time_passed = (end_count - begin_count) / CLOCKS_PER_SEC;
        if(illness_lvl == 0){*ill = false;}
        }while(((chose != 'y')&&(chose != 'n'))&& time_passed < 2);
    }    
}


void take_medicaments(bool* drink_potion, bool* smoke_weed, const char sprites[N_SPRITES][SPRITE_WIDHT][SPRITE_LENGTH], WINDOW* win){
    int chose_med = 0;
    int potion_sprite = 7;
    int smoke_sprite = 8;
    clock_t begin_count = clock();
    clock_t end_count;
    bool pressed = false;
    printf("which medicament do you want?\n")
    printf("1.potion (health+30)| 200 score\n");
    printf("2.secret way(health max)| 500 score\n");
    printf("other number to exit\n");
    scanf("%d", &chose_med);
    do{
        switch(chose_med){
            case 1:
                *drink_potion == true;
                print_sprite(sprites[potion_sprite]);
                usleep(2000000);
                pressed = true;
                break;
            case 2:
                *smoke_weed == true;
                print_sprite(sprites[smoke_sprite]);
                usleep(2000000);
                break;
                pressed = true
            default:
                pressed = false;
                break;
        }
    end_count = clock();
    time_passed = (end_count - begin_count) / CLOCKS_PER_SEC; // update time spent
    }while(time_passed < 2 && !pressed)
}

void bath(int* hygiene, const char sprites[N_SPRITES][SPRITE_WIDHT][SPRITE_LENGTH]){
    *hygiene = 0;
    int bath_sprite = 6;
    print_sprite(sprites[bath_sprite]);
    usleep(2000000);
}

void has_sleep (int* tiredness, const char sprites[N_SPRITES][SPRITE_WIDHT][SPRITE_LENGTH]){
    *tireddness = 0;
    int sleep_sprite = 0;
    print_sprite(sprites[sleep_sprite]);
    usleep(2000000);
}