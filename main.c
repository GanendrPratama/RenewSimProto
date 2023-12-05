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
    float area; 
    float power;
    float price;
} WaterTurbine;

typedef struct windTurbine
{
    char name[100];
    float diameter;
    float height;
    float area;
    float power;
    float price;
} windTurbine;

void showSolarPanel(SolarPanel *sp, int index) {
    printf("\n---------------------------------\n");
    printf(" \n Solar panel #%d\n", index + 1);
    printf("%s\n", sp[index].name);
    printf("Length: %.2f\n", sp[index].length);
    printf("Width: %.2f\n", sp[index].width);
    printf("Area: %.2f\n", sp[index].area);
    printf("Power Generated: %.2f\n", sp[index].power);
    printf("Price: %.2f\n", sp[index].price);
    printf("\n---------------------------------\n");
}

void showWaterTurbine(WaterTurbine *wt, int index) {
    printf("\n---------------------------------\n");
    printf(" \n Water turbine #%d\n", index + 1);
    printf("%s\n", wt[index].name);
    printf("Flow Rate: %.2f\n", wt[index].flowRate);
    printf("Power Generated: %.2f\n", wt[index].power);
    printf("Price: %.2f\n", wt[index].price);
    printf("\n---------------------------------\n");
}

void showWindTurbine(windTurbine *wt, int index){
    printf("\n---------------------------------\n");
    printf(" \n Wind turbine #%d\n", index + 1);
    printf("%s\n",  wt[index].name);
    printf("Diameter: %.2f\n", wt[index].diameter);
    printf("Height: %.2f\n", wt[index].height);
    printf("Area: %.2f\n", wt[index].area);
    printf("Power Generated: %.2f\n", wt[index].power);
    printf("Price: %.2f\n", wt[index].price);
    printf("\n---------------------------------\n");
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
    wt->area = flowRate; // The formula for area might need to be updated based on your requirement
}

void addWindTurbine(windTurbine *wt, char name[100], float diameter, float height, float power, float price){
    strcpy(wt->name, name);
    wt->diameter = diameter;
    wt->height = height;
    wt->power = power;
    wt->price = price;
    wt->area = 3.14159 * (diameter / 2) * (diameter / 2); // Calculate the area of the circle
}

int main() {
    int one = 1;
    float usableArea; // Initial usable area
    double needs = 0; // Energy needed in KWh
    float totalArea = 0; // Total area covered by added components
    SolarPanel *sp = calloc(1, sizeof(SolarPanel));
    WaterTurbine *wt = calloc(1, sizeof(WaterTurbine));
    windTurbine *windTurbine = calloc(1, sizeof(windTurbine));
    int spCounter = 0;
    int wtCounter = 0;
    int windTurbineCounter = 0;
    int input = 0;
    char name[100];
    float length;
    float width;
    float power; // Kilowatt
    float price; // in dollars or indonesia?
    float flowRate;
    float diameter;
    float height;

    printf("Enter the initial usable area: ");
    scanf("%f", &usableArea);
    printf("Usable Area: %.2f\n", usableArea - totalArea);

    while (one == 1) {
        if (spCounter > 0) {
            printf("Solar Panels:\n");
            for (int i = 0; i < spCounter; i++) {
                showSolarPanel(sp, i);
            }
        }
        if (wtCounter > 0) {
            printf("Water Turbines:\n");
            for (int i = 0; i < wtCounter; i++) {
                showWaterTurbine(wt, i);
            }
        }
        if (windTurbineCounter > 0) {
            printf("Wind Turbines:\n");
            for (int i = 0; i < windTurbineCounter; i++) {
                showWindTurbine(windTurbine, i);
            }
        }

        printf("\n Menu Options \n");
        printf(" 1. Add Solar Panel \n");
        printf(" 2. Add Water Turbine \n");
        printf(" 3. Add Wind Turbine \n");
        printf(" 9. show the current data \n");
        printf(" 0. Done Input \n");
        printf(" Enter your choice: ");

        scanf("%d", &input);
        
        switch (input) {
            case 1: {
                printf("\n Enter details for Solar Panel:\n");
                printf("Name: ");
                scanf(" %[^\n]", name);
                printf("Length (in Meter): ");
                scanf("%f", &length);
                printf("Width (in Meter): ");
                scanf("%f", &width);
                printf("Power (in Kilowatt): ");
                scanf("%f", &power);
                printf("Price: ");
                scanf("%f", &price);

                addSP(sp, name, length, width, power, price);
                totalArea += sp[spCounter].area; ///total area akan dikurangi dengan usable area
                spCounter++;

                needs += power;  
                usableArea -= sp[spCounter - 1].area;
            } break;
            case 2: {
                printf(" \n Enter details for Water Turbine:\n");
                printf("Name: ");
                scanf(" %[^\n]", name);
                printf("Flow Rate: ");
                scanf("%f", &flowRate);
                printf("Power (in Kilowatt): ");
                scanf("%f", &power);
                printf("Price: ");
                scanf("%f", &price);

                addWT(wt, name, flowRate, power, price);
                totalArea += wt[wtCounter].area; //total area akan dikurangi dengan usable area
                wtCounter++;

                needs += power;  
                usableArea -= wt[wtCounter - 1].area;
            } break;
            case 3: {
                printf(" \n Enter details for Wind Turbine:\n");
                printf("Name: ");
                scanf(" %[^\n]", name);
                printf("Diameter: ");
                scanf("%f", &diameter);
                printf("Height: ");
                scanf("%f", &height);
                printf("Power (in Kilowatt): ");
                scanf("%f", &power);
                printf("Price: ");
                scanf("%f", &price);

                addWindTurbine(windTurbine, name, diameter, height, power, price);
                totalArea += windTurbine[windTurbineCounter].area; //total area akan dikurangi dengan usable area
                windTurbineCounter++;

                needs += power;  
                usableArea -= windTurbine[windTurbineCounter - 1].area;
            } break;
            case 9:{
                printf("-------------------");

                printf("\nCurrent Data:\n");
                printf("Energy Needed: %.2f KWh\n", needs);
                printf("Usable Area: %.2f\n", usableArea - totalArea);

                printf("------------------- \n \n");
                break;
            }
            case 0:
                one = 0;
                break;
        }
    }
    free(sp);
    free(wt);
    free(windTurbine);
    return 0;
}
