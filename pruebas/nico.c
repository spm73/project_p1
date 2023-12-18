#include<stdio.h>
#include<unistd.h>
#include "sergio.c"
/*todo esta metido con modulos, estos son solo los contadores de hambre, sueño, hygiene y nivel de lele pancha*/
void hunger_update();
void tiredness_update();
void hygiene_update();
void illness_lvl_update();
bool eat();
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
    
    if (eat()){
        hunger = hunger - 30;
        while(hunger < 0){hunger = 0;}
        *h = hunger;
        //estos mensajes apareceran si cuando le has dado de comer el hambre sigue siendo mayor a 50 de e mensaje de nuevo
        if((hunger > 50)&&(hunger <=75)){
            printf("I'm hungry :(");}
        if else(hunger > 75){
            printf("I'm starving");}
    }
    else{
        hunger++;
        //cada 2 segundos bajará el hambre
        sleep(2);
        //y devuelve el valor por un puntero al main
        *h = hunger;
        if((hunger > 50)&&(hunger <=75)){
            printf("I'm hungry :(");}
        if else(hunger > 75){
            printf("I'm starving");}
        if else(hygiene > 100){
            //modulo de la muerte de doraemon:(
            die();}
    }
}

//la diferencia de este modulo con el primero es que si llega al limiite de sueño no morira y que dormir supone el reabastecimiento completo de el sueño
void tierdness_update(int* t, bool* ill){
    int tierdness = *t;

    if (has_sleep()){
        tiredness = 0;
        *t = tierdness;
    }
    
    else{
        tiredness++;
        sleep(1);
        t* = tiredness;
        if((tierdness > 50)&&(tierdness <=75)){
            printf("I'm tierd :(");}
        if else(tierdness > 75){
            printf("I'm so tierd");}
        if else(tierdness > 100){
            printf("heil hitler");
            *ill = true;}
    }
}    


//la higiene es igual al cansancio
void hygiene_update(int* g, bool* ill){
    int hygiene = *g;


    if (bath()){
        hygiene = 0;
        *g = hygiene;
    }
    else{
        tiredness++;
        sleep(2);
        *g = hygiene;
        if((hygiene > 50)&&(hygiene <= 75)){
            printf("I should have a shower");}
        if else((hygiene > 75)&&(hygiene <= 100)){
            printf("I need a shower");}
        if else(hygiene == 100){
            printf("oni chan");
            *ill = true;}
    }
}
//esta es la funcion más especial porque depende de un modulo, ya que solo se activar el contador cuando este enfermo
void illness_lvl_update(int* l, bool* ill, int* score){
    int illness_lvl = *l;
    char chose = 0;
    bool smoke_weed = false;
    bool drink_potion = false;
    if(ill == true){
        do{
        printf("do you want a medicament(y|n)\n");
        scanf("%c", &chose)
        }
        while((chose != 'y')||(chose != 'n'));
        if(chose == 'y'){
            take_medicament(&smoke_weed, &drink_potion);
            if (smoke_weed == true){
                illness_lvl = 0;
                *l = illness_lvl;
                *score = *score - 200;
                }
            else if (drink_potion == true){
                illness_lvl = illness_lvl - 30;
                *score = *score - 500;
                    while(hunger < 0){hunger = 0;}
                *l = illness_lvl;
                if ((illness_lvl > 50)&&(illness_lvl <=75)){
                    printf("I'm hungry :(");}
                if else(illness_lvl > 75){
                    printf("I'm starving");}   
            }
            if(illness_lvl == 0){*ill = false;}
        }
    }    
    else{
        illness_level++;
        sleep(1);
        *l = illness_lvl;
        if((illness_lvl > 50)&&(illness_lvl <=75)){
            printf("I'm feeling bad");}
        if else((illness_lvl > 75)&&(illness_lvl <= 100)){
            printf("I'm going to vomit");}
        if else(illness_lvl > 100){
            die();}
    }
}

void take_medicaments(bool* drink_potion, bool* drink_potion, const char sprites[N_SPRITES][SPRITE_WIDHT][SPRITE_LENGTH]){
    int chose_med = 0;
    printf("which medicament do you want?\n")
    printf("1.potion (health+30)| 200 score\n");
    printf("2.secret way(health max)| 500 score\n");
    printf("other number to exit\n");
    scanf("%d", &chose_med);
    if(chose_med == 1){
        *drink_potion == true;
        print_sprite(sprites[7]);
    }
    else if(chose_med == 2){
        *smoke_weed == true;
        print_sprite(sprites[8]);
    }

}

void bath(const char sprites[N_SPRITES][SPRITE_WIDHT][SPRITE_LENGTH]){
    print_sprite(sprites[6]);
}

void has_sleep (const char sprites[N_SPRITES][SPRITE_WIDHT][SPRITE_LENGTH]){
    print_sprite(sprites[0]);
}