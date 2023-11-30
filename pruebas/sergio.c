//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

#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>

#define NAME 20
#define SPRITE_LENGTH 91
#define SPRITE_WIDHT 45

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

void get_sprite(char sprite[][],int index, FILE* sprite_file) {
    for (int i = 0; i < SPRITE_WIDHT; i++) {
        fscanf(sprite_file, "%[^\n]s", sprite[index][i]);
    }
}

void upload_sprites(char sprites[][][]) {
    FILE *sprties_file = fopen("./sprites.txt", "r");

}

int main() {
    char name[NAME];
    get_name(name);
    
    TTamagotchi tmgcthi = Tamagotchi(name);
    
}