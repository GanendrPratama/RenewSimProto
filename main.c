#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct solarPanel {
    char name[100];
    float length;
    float width;
    float area;
    float power;
    float price;
} SolarPanel;

void showSP (SolarPanel* sp, int index) {
    printf("Solar panel #%d\n", index+1);
    printf("%s\n", sp[index].name);
    printf("Length: %.2f\n", sp[index].length);
    printf("Width: %.2f\n", sp[index].width);
    printf("Area: %.2f\n", sp[index].area);
    printf("Power Generated: %.2f\n", sp[index].power);
    printf("Price: %.2f\n", sp[index].price);
}

void addSP (SolarPanel* sp,char name[100], float length, float width, float power, float price) {
    strcpy(sp->name, name);
    sp->length = length;
    sp->width = width;
    sp->power = power;
    sp->price = price;
    sp->area = length*width;
}

int main () {
    int one = 1;
    float area; //Luas daerah yang bisa dipakai
    float needs; //Energi yang dibutuhkan berupa KWh
    SolarPanel* sp = calloc(1, sizeof(SolarPanel));
    int spCounter;
    int input = 0;
    char name[100];
    float length;
    float width;
    float power;
    float price;


    scanf("%f", &area);
    while (one == 1) {
        printf("Energy Needed: %f", needs);
        printf("Usable Area: %f",area);
        if (spCounter > 0) {
            printf("Solar Panels:\n");
            for (int i = 0; i < spCounter; i++) {
                showSP(sp, i);
            }
        }
        scanf("%d", input);
        switch (input)
        {
        case 1: {
            scanf("%99[^\n]", &name);
            scanf("%f", &length);
            scanf("%f", &width);
            scanf("%f", &power);
            scanf("%f", &price);
            addSP(sp, name, length, width, power, price);}
            break;
        
        default:
            break;
        }
    }
    free(sp);
    return 0;
}
