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

typedef struct waterTurbine {
    char name[100];
    float flowRate;
    float power;
    float price;
} WaterTurbine;

void showSP(SolarPanel *sp, int index) {
    printf("Solar panel #%d\n", index + 1);
    printf("%s\n", sp[index].name);
    printf("Length: %.2f\n", sp[index].length);
    printf("Width: %.2f\n", sp[index].width);
    printf("Area: %.2f\n", sp[index].area);
    printf("Power Generated: %.2f\n", sp[index].power);
    printf("Price: %.2f\n", sp[index].price);
}

void showWT(WaterTurbine *wt, int index) {
    printf("Water turbine #%d\n", index + 1);
    printf("%s\n", wt[index].name);
    printf("Flow Rate: %.2f\n", wt[index].flowRate);
    printf("Power Generated: %.2f\n", wt[index].power);
    printf("Price: %.2f\n", wt[index].price);
}

void addSP(SolarPanel *sp, char name[100], float length, float width, float power, float price) {
    strcpy(sp->name, name);
    sp->length = length;
    sp->width = width;
    sp->power = power;
    sp->price = price;
    sp->area = length * width;
}

void addWT(WaterTurbine *wt, char name[100], float flowRate, float power, float price) {
    strcpy(wt->name, name);
    wt->flowRate = flowRate;
    wt->power = power;
    wt->price = price;
}

int main() {
    int one = 1;
    float area; //Luas daerah yang bisa dipakai
    float needs; //Energi yang dibutuhkan berupa KWh
    SolarPanel *sp = calloc(1, sizeof(SolarPanel));
    WaterTurbine *wt = calloc(1, sizeof(WaterTurbine));
    int spCounter = 0;
    int wtCounter = 0;
    int input = 0;
    char name[100];
    float length;
    float width;
    float power; //Kilowatt
    float price;
    float flowRate;

    scanf("%f", &area);
    while (one == 1) {
        printf("Energy Needed: %f\n", needs);
        printf("Usable Area: %f\n", area);
        if (spCounter > 0) {
            printf("Solar Panels:\n");
            for (int i = 0; i < spCounter; i++) {
                showSP(sp, i);
            }
        }
        if (wtCounter > 0) {
            printf("Water Turbines:\n");
            for (int i = 0; i < wtCounter; i++) {
                showWT(wt, i);
            }
        }
        scanf("%d", &input);
        switch (input) {
            case 1: {
                scanf("%99[^\n]", name);
                scanf("%f", &length);
                scanf("%f", &width);
                scanf("%f", &power);
                scanf("%f", &price);
                addSP(sp, name, length, width, power, price);
                spCounter++;
            } break;
            case 2: {
                scanf("%99[^\n]", name);
                scanf("%f", &flowRate);
                scanf("%f", &power);
                scanf("%f", &price);
                addWT(wt, name, flowRate, power, price);
                wtCounter++;
            } break;

            default:
                break;
        }
    }
    free(sp);
    free(wt);
    return 0;
}
