#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Object {
    int index;
    char name[100];
    float area; 
    float power;
    float price;
} object;

typedef struct dayObject {
    int index;
    float energyNeeded;
    float totalPower;
    float spPower;
    float ggPower;
    float wnPower;
    float spEff;
    float ggEff;
    float wnEff;
} dayObject;

void showSolarPanel(object *sp, int index) {
    printf("\n---------------------------------\n");
    printf(" \n Solar panel #%d\n", index + 1);
    printf("%s\n", sp[index].name);
    printf("Area: %.2f\n", sp[index].area);
    printf("Power Generated: %.2f\n", sp[index].power);
    printf("Price: %.2f\n", sp[index].price);
    printf("\n---------------------------------\n");
}

void showGeothermalGenerator(object *gg, int index) {
    printf("\n---------------------------------\n");
    printf(" \n Geothermal Generator #%d\n", index + 1);
    printf("%s\n", gg[index].name);
    printf("Area: %.2f\n", gg[index].area);
    printf("Power Generated: %.2f\n", gg[index].power);
    printf("Price: %.2f\n", gg[index].price);
    printf("\n---------------------------------\n");
}

void showWindTurbine(object *wt, int index){
    printf("\n---------------------------------\n");
    printf(" \n Wind turbine #%d\n", index + 1);
    printf("%s\n",  wt[index].name);
    printf("Area: %.2f\n", wt[index].area);
    printf("Power Generated: %.2f\n", wt[index].power);
    printf("Price: %.2f\n", wt[index].price);
    printf("\n---------------------------------\n");
}

void addObj(object *obj, int index, char name[100], float area, float power, float price) {
    obj[index].index = index;
    strcpy(obj[index].name, name);
    obj[index].area = area;
    obj[index].power = power;
    obj[index].price = price;
}


void removeObj(object *obj, int index, int *sum) {
    if (index-1 == *sum) {
        (*sum)--;
    } else {
        for(int i = index; i < *sum; i++) {
            obj[i] = obj[i+1];
        }
        (*sum)--;
    }
}

void showDay(dayObject *day, int index) {
    printf("\n Day %d: \n", index + 1);
    printf(" Energy needed                   : %.2f kwd\n", day[index].energyNeeded);
    printf(" Energy from solar panels        : %.2f kwd\n", day[index].spPower);
    printf(" Energy from Geothermal turbines : %.2f kwd\n", day[index].ggPower);
    printf(" Energy from wind turbines       : %.2f kwd\n", day[index].wnPower);
    printf(" Total energy fulfilled          : %.2f kwd\n", day[index].totalPower);
    printf("-----------------------------------------------------------------\n");
}