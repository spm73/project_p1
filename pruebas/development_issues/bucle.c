#include <stdio.h>
#include <conio.h>

int main() {
    
    do {
        printf("To stop the loop press any key\n");
        getch();
    } while (!kbhit());
}