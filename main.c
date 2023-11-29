#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct solarPanel {
    char name[100];
    float length;
    float width;
    float power;
    float price;
} SolarPanel;

int main () {
    int one = 1;
    float area; //Luas daerah yang bisa dipakai
    float needs; //Energi yang dibutuhkan berupa KWh
    SolarPanel* sp = calloc(1, sizeof(SolarPanel));
    int spCounter;
    int input = 0;

    scanf("%f", &area);
    while (one == 1) {
        printf("Energy Needed: %f", needs);
        printf("Usable Area: %f",area);
        if (spCounter > 0) {
            printf("Solar Panels:\n");
            for (int i = 0; i < spCounter; i++) {
                printf("%s", &(sp.name));
            }
        }
    }
    free(sp);
    return 0;
}
