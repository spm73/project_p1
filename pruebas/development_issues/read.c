#include <stdio.h>

int main() {
    char arr[4][4];

    FILE *text;

    if (text = fopen("text.txt", "r")) {
        for (int i = 0; i < 4; i++) {
            fscanf(text, "%[^\n]s", arr[i]);
            // printf("%s\n", arr[i]);
            // fgets(arr[i], 5, text);
            fseek(text, 1, SEEK_CUR);
        }
        fclose(text);
    }
    for (int j = 0; j < 4; j++) {
        // printf("%s\n", arr[j]);
        for (int k = 0; k < 4; k++) {
            printf("%c", arr[j][k]);
        }
        printf("\n");
    }
}