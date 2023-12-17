#include<stdio.h>
#include<unistd.h>
#include "sergio.c"
#include <curses.h>
/*todo esta metido con modulos, estos son solo los contadores de hambre, sueño, hygiene y nivel de lele pancha*/
void hunger_update();
void tierdness_update();
void hygiene_update();
void illness_lvl_update();
bool eat();
// bool die(); no hace falta que lo hagas que ya la he hecho yo
bool psico();
bool otaku();

// en el main tan solo se ejecutan los modulos, piensa que esto es provisional y debe ir anidado a otras funciones
int main(){
    int hunger;
    int tierdness;
    int hygiene;
    int illness_lvl;

    hunger_update(&hunger);
    tierdness_update(&tierdness);
    hygiene_update(&hygiene);
    illness_level_update(&illness_lvl);


}
//cada modulo cuenta con un puntero que es el valor que pasa como actualización
void hunger_update(int* h){
    int hunger = *h;
    
    if (has_eat()){
        hunger = hunger - 30; // hunger -= 30
        while(hunger < 0){hunger = 0;}
        *h = hunger;
        // el switch solo sirve para valores constantes, es decir, que no puedes hacer comparaciones en los casos porque no devuelven siempre el mismo valor.
        // osea que toca hacerlo con if y else if y else, te dejo un ejemplo.
        // switch(hunger){
        //     //estos mensajes apareceran si cuando le has dado de comer el hambre sigue siendo mayor a 50 de e mensaje de nuevo
        //     case(hunger =< 50):
        //         break;
        //     case((hunger > 50)&&(hunger <=75)):
        //         printf("I'm hungry :(");
        //         break;
        //     case(hunger > 75):
        //         printf("I'm starving");
        //         break;
        // }
        if (hunger > 50 && hunger <= 75) {
            printw("I'm hungry :("); // para printear con ncurses se usa esta función, que funciona igual que printf
        } else if (hunger > 75) {
            printw("I'm starving");
        } 
        refresh(); // para actualizar la pantalla de ncurses
    }
    else{
        //esto es un bucle que siempre esta activo donde se cuenta el nivel de hambre
        for (hunger; hunger >= 100; hunger++){ // para que sea más facil de leer, usa un while
            // además, ten en cuenta que la idea es que haya un bucle principal donde se llamen a funciones para actualizar los valores
            // osea que las puedes hacer para que no use punteros (si quieres claro)
            //cada 2 segundos bajará el hambre
            sleep(2);
            //y devuelve el valor por un puntero al main
            *h = hunger;
            switch(hunger){
                case(hunger =< 50):
                    break;
                case((hunger > 50)&&(hunger <=75)):
                    printf("I'm hungry :(");
                    break;
                case(hunger > 75):
                    printf("I'm starving");
                    break;
                case(hygiene > 100): // aquí pone hygiene y es una función de comer
                    //modulo de la muerte de doraemon:(
                    die();
                    break;
            }
        }
    }
}
//la diferencia de este modulo con el primero es que si llega al limiite de sueño no morira y que dormir supone el reabastecimiento completo de el sueño
void tierdness_update(int* t){
    int tierdness = *t;

    if (has_sleep()){
        tierdness = 0;
        *t = tierdness;
        }
    
    else{
        for (tierdness; tierdness >= 100; tierdness++){
            sleep(1);
            t* = tierdness; // t* no existe en C, *t para deferenciar el valor
            switch(tierdness){
                case(tierdness =< 50):
                    break;
                case((tierdness > 50)&&(tierdness <=75)):
                    printf("I'm tired :(");
                    break;
                case(tierdness > 75):
                    printf("I'm so tired");
                    break;
                case(tierdness > 100):
                    printf("heil hitler");
                    psico();
                    break;
            }
        }    
    }
}
//la higiene es igual al cansancio
void hygiene_update(int* g){
    int hygiene = *g;

    if (has_bath()){
        hygiene = 0;
        *g = hygiene;
        }
    else{
        for (hygiene; hygiene >= 100; hygiene++){
            sleep(2);
            *g = hygiene;
            switch(hygiene){
                case(hygiene =< 50):
                    break;
                case((hygiene > 50)&&(hygiene <= 75)):
                    printf("I should have a shower");
                    break;
                case((hygiene > 75)&&(hygiene <= 100)):
                    printf("I need a shower");
                    break;
                case(hygiene > 100):
                        printf("oni chan");
                        otaku();
                        break;
            }
        }
    }
}
//esta es la funcion más especial porque depende de un modulo, ya que solo se activar el contador cuando este enfermo
void illness_lvl_update(int *l){
    int illness_lvl = *l;
    if(ill()){
        if (smoke_weed()){
            illness_lvl = 0;
            *l = illness_lvl;
        }
        else if (take_medicaments()){
            illness_lvl = illness_lvl - 30;
                while(hunger < 0){hunger = 0;}
            *l = illness_lvl;
            switch(illness_lvl){
                //estos mensajes apareceran si cuando le has dado el medicamento y la salud sigue siendo mayor a 50 de e mensaje de nuevo
                case(illness_lvl =< 50):
                    break;
                case((illness_lvl > 50)&&(illness_lvl <=75)):
                    printf("I'm hungry :(");
                    break;
                case(illness_lvl > 75):
                    printf("I'm starving");
                    break;
            }
        }    
        else{
            for (illness_lvl;  >= 100; illness_lvl++){
                sleep(1);
                *l = illness_lvl;
                switch(illness_lvl){
                    case(illness_lvl =< 50):
                    break;
                    case((illness_lvl > 50)&&(illness_lvl <=75)):
                        printf("I'm feeling bad");
                        break;
                    case((illness_lvl > 75)&&(illness_lvl <= 100)):
                        printf("I'm going to vomit");
                        break;
                    case(illness_lvl > 100):
                        die();
                        break;
                }
            }

        }
    }
}

bool eat(){
    char touch = 0;
    print_sprite(4); // debes pasarle una array bidimensional de carácteres (sprite), no un número.
    printf("press e to eat\n"); // con ncurses debes usar printw("string que quiereas") y luego usar refresh()
    scanf("%c\n", &touch);
    if((touch != 'e')||(sleep(10))){ // sleep(10) siempre devuelve verdadero
        clean_sprites(); // esta función limpia todos los sprites, osea, que de aquí en adelante no habrá sprites. Además recibe como parámetro el array de sprites.
        // creo que tu lo interpretas como una función para borrar el sprite que esta en pantalla. Para eso, usando ncurses es usando la función erase()
        printf("you fail\n");
        }
    else{
        print_sprite(5);
        return(touch == 'e');
        clean_sprite();
    }
}

