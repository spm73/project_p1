#include<stdio.h>
#include<unistd.h>
/*todo esta metido con modulos, estos son solo los contadores de hambre, sueño, hygiene y nivel de lele pancha*/
void hunger_update();
void tierdness_update();
void hygiene_update();
void illness_lvl_update();

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
        hunger = hunger - 30;
        *h = hunger;
        switch(hunger){
            //estos mensajes apareceran si cuando le has dado de comer el hambre sigue siendo mayor a 50 de e mensaje de nuevo
            case(hunger =< 50):
                break;
            case((hunger > 50)&&(hunger <=75)):
                printf("I'm hungry :(");
                break;
            case(hunger > 75):
                printf("I'm starving");
                break;
        }
    }
    else{
        //esto es un bucle que siempre esta activo donde se cuenta el nivel de hambre
        for (hunger; hunger >= 100; hunger++){
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
                case(hygiene > 100):
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
            t* = tierdness;
            switch(tierdness){
                case(tierdness =< 50):
                    break;
                case((tierdness > 50)&&(tierdness <=75)):
                    printf("I'm tierd :(");
                    break;
                case(tierdness > 75):
                    printf("I'm so tierd");
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