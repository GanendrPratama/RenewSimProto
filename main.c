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

int main() {
    //The states of the simulator program
    int activeState = 1;
    int menuState = 0; // menu
    int simState = 0; // simulator
    int editState = 0; //edit state

    float usableArea; // Initial usable area
    float totalArea = 0; // Total area covered by added components
    float needPower; //Power needed per hour in kilowatt per hour
    float totalPower= 0; //Power generated by the generators
    float money;

    //The generators that are available in this program
    object *sp = calloc(100, sizeof(object));
    object *gg = calloc(100, sizeof(object));
    object *wn = calloc(100, sizeof(object));

    int spCounter = 0;
    int ggCounter = 0;
    int wnCounter = 0;

    float spPower = 0;
    float ggPower = 0;
    float wnPower = 0;
    totalPower = spPower + ggPower + wnPower;

    float spEff = 1.0;
    float ggEff = 1.0;
    float wnEff = 1.0;

    //variables to temporarily store fields to be inserted
    int input = 0;
    int index = 0;
    char name[100];
    float area;
    float power; // Kilowatt per hour
    float price; // in dollars

    int totalDay = 0;
    dayObject *simDay = calloc(1, sizeof(dayObject));

    menuState = 1;
    printf("Enter the initial usable area in km squared: ");
    scanf("%f", &usableArea);
    printf("Enter the needed power in kwh: ");
    scanf("%f", &needPower);
    printf("Enter the initial money you have in dollars: ");
    scanf("%f", &money);

    while (activeState == 1) {
        while (menuState == 1) {
            input = 0;
            printf("Usable Area: %.2f\n", usableArea-totalArea);
            printf("Needed Power: %.2f\n", needPower-totalPower);
            printf("Money left: %.2f\n", money);
            if (usableArea == 0) {
            printf("You have no more area to build!\n");
            }
            if (money == 0) {
            printf("You have no more money to spend!\n");
            }
            if (needPower <= totalPower) {
            printf("You have fullfilled the energy needed!\n");
            }
            if (spCounter > 0) {
                printf("Solar Panels:\n");
                for (int i = 0; i < spCounter; i++) {
                    showSolarPanel(sp, i);
            }
        }
            if (ggCounter > 0) {
                printf("Geothermal Turbines:\n");
                for (int i = 0; i < ggCounter; i++) {
                    showGeothermalGenerator(gg, i);
            }
        }
            if (wnCounter > 0) {
                printf("Wind Turbines:\n");
                for (int i = 0; i < wnCounter; i++) {
                    showWindTurbine(wn, i);
            }
        }

            printf("===============================\n" 
		   "|                             |\n" 
		   "|          BUILD MENU         |\n" 
		   "|                             |\n" 
		   "===============================\n");
            printf("|1. Add Solar Panel           |\n");
            printf("|2. Add Geothermal Turbine    |\n");
            printf("|3. Add Wind Turbine          |\n");
            printf("|4. Remove Solar Panel        |\n");
            printf("|5. Remove Geothermal Turbine |\n");
            printf("|6. Remove Wind Turbine       |\n");
            printf("|7. Show the current data     |\n");
            printf("|9. Exit Simulation           |\n");
            printf("|0. Done Input                |\n");
            printf("===============================\n"); 
            printf("Enter your choice:");


            scanf("%d", &input);
        
            switch (input) {
                case 1: {
                    if (usableArea == 0 || money == 0) {
                        printf("You cannot build more generators!\n");
                        break;
                    } else {
                        printf("\n Enter details for Solar Panel:\n");
                        printf("Name: ");
                        scanf(" %[^\n]", name);
                        printf("Area (in Kilometer squared): ");
                        scanf("%f", &area);
                        printf("Power (in Kilowatt): ");
                        scanf("%f", &power);
                        printf("Price: ");
                        scanf("%f", &price);

                        if (usableArea - area <= 0) {
                            printf("You have no more area to build!\n");
                            break;
                        } else if (money - price <= 0) {
                            printf("You cannot afford this generator!\n");
                            break;
                        } else {
                            addObj(sp, spCounter, name, area, power, price);
                            spPower += power;
                            needPower -= power;  
                            usableArea -= area;
                            money -= price;
                            spCounter++;
                        }
                    } break;
                } break;
                case 2: {
                    if (usableArea == 0 || money == 0) {
                        printf("You cannot build more generators!\n");
                        break;
                    } else {
                        printf("\n Enter details for Geothermal Turbine:\n");
                        printf("Name: ");
                        scanf(" %[^\n]", name);
                        printf("Area (in Kilometer squared): ");
                        scanf("%f", &area);
                        printf("Power (in Kilowatt): ");
                        scanf("%f", &power);
                        printf("Price: ");
                        scanf("%f", &price);

                        if (usableArea - area <= 0) {
                            printf("You have no more area to build!\n");
                            break;
                        } else if (money - price <= 0) {
                            printf("You cannot afford this generator!\n");
                            break;
                        } else {
                            addObj(gg, ggCounter, name, area, power, price);
                            ggPower += power;
                            totalArea += area;
                            money -= price;
                            ggCounter++;
                        }
                    } break;
                } break;
                case 3: {
                    if (usableArea == 0 || money == 0) {
                        printf("You cannot build more generators!\n");
                        break;
                    } else {
                        printf("\n Enter details for Wind Turbine:\n");
                        printf("Name: ");
                        scanf(" %[^\n]", name);
                        printf("Area (in Kilometer squared): ");
                        scanf("%f", &area);
                        printf("Power (in Kilowatt): ");
                        scanf("%f", &power);
                        printf("Price: ");
                        scanf("%f", &price);

                        if (usableArea - area <= 0) {
                            printf("You have no more area to build!\n");
                            break;
                        } else if (money - price <= 0) {
                            printf("You cannot afford this generator!\n");
                            break;
                        } else {
                            addObj(wn, wnCounter, name, area, power, price);
                            wnPower += power;  
                            totalArea += area;
                            money -= price;
                            wnCounter++;
                        }
                    } break;
                } break;
                case 4: {
                    if (spCounter <= 0) {
                        printf("You have no solar panels. \n");
                        break;
                    } else {
                        for (int i = 0; i < spCounter; i++) {
                            showSolarPanel(sp,i);
                    }
                        printf("Type the index of the solar panel to be removed: \n");
                        printf("Please enter any minus integer to cancel deleting \n");
                        scanf("%d", &input);
                        if (input < 0) {
                            printf("Cancelling operation. \n");
                            break;
                        } else if (input-1 >= spCounter) {
                            printf("Index not found. \n");
                        } else {
                            spPower += sp[input-1].power;
                            totalArea -= sp[input-1].area;
                            totalPower -= sp[input-1].power;
                            money += sp[input-1].price;
                            removeObj(sp, input-1, &spCounter);
                        }
                    }
                } break;

                case 5: {
                    if (ggCounter <= 0) {
                        printf("You have no Geothermal turbine. \n");
                        break;
                    } else {
                        for (int i = 0; i < ggCounter; i++) {
                            showGeothermalGenerator(gg,i);
                        }
                        printf("Type the index of the Geothermal turbines to be removed: \n");
                        printf("Please enter any minus integer to cancel deleting \n");
                        scanf("%d", &input);
                        if (input < 0) {
                            printf("Cancelling operation. \n");
                            break;
                        } else if (input-1 >= ggCounter) {
                            printf("Index not found. \n");
                        } else {
                            ggPower += gg[input-1].power;
                            totalArea -= gg[input-1].area;
                            totalPower -= gg[input-1].power;
                            money += gg[input-1].price;
                            removeObj(gg, input-1, &ggCounter);
                        }
                    }
                } break;

                case 6: {
                    if (wnCounter <= 0) {
                        printf("You have no wind turbine. \n");
                        break;
                    } else {
                        for (int i = 0; i < wnCounter; i++) {
                            showWindTurbine(wn,i);
                        }
                        printf("Type the index of the solar panel to be removed: \n");
                        printf("Please enter any minus integer to cancel deleting \n");
                        scanf("%d", &input);
                        if (input < 0) {
                            printf("Cancelling operation. \n");
                            break;
                        } else if (input > wnCounter) {
                            printf("Index not found. \n");
                        } else {
                            wnPower += wn[input-1].power;
                            totalArea -= wn[input-1].area;
                            totalPower -= wn[input-1].power;
                            money += wn[input-1].price;
                            removeObj(wn, input-1, &wnCounter);
                        }
                    }
                } break;

                case 7:{
                    printf("-------------------");

                    printf("\nCurrent Data:\n");
                    printf("Energy Needed: %.2f KWh\n", needPower);
                    printf("Usable Area: %.2f\n", usableArea);

                    printf("------------------- \n \n");
                    break;
                }
                case 9: {
                    activeState++;
                    editState = 0;
                } break;
                case 0:{
                    menuState = 0;
                    simState = 1;
                    editState = 0;
                } break;
                
                default:{
                    printf("Please check your input again. \n");
                } break;
            }
        }
        //simulator menu activated
        while (simState == 1) {
            if (totalDay == 0) {
                printf("Please enter how many days to be simulated: ");
                scanf("%d", &totalDay);
                simDay = realloc(simDay, totalDay * sizeof(dayObject));
            } else {
                for (int i = 0; i < totalDay; i++) {
                    simDay[i].spEff = spEff;
                    simDay[i].ggEff = ggEff;
                    simDay[i].wnEff = wnEff; 

                    // Reset the energyNeeded for each day
                    simDay[i].energyNeeded = needPower;

                    // Calculate the power generated by each generator
                    simDay[i].spPower = simDay[i].spEff * 4.0 * spPower + 0.5 * simDay[i].spEff * 8.0 * spPower;
                    simDay[i].ggPower = simDay[i].ggEff * 24.0 * ggPower;
                    simDay[i].wnPower = simDay[i].wnEff * 24.0 * wnPower;

                    // Subtract the generated power from energyNeeded
                    simDay[i].energyNeeded -= simDay[i].spPower + simDay[i].ggPower + simDay[i].wnPower;

                    // Update the totalPower for the day
                    simDay[i].totalPower = simDay[i].spPower + simDay[i].ggPower + simDay[i].wnPower;
                }

                for (int i = 0; i < totalDay; i++) {
                    showDay(simDay,i);
                }
                printf("\n SIMULATOR MENU \n");
                printf(" 1. Edit the simulation of a day. \n");
                printf(" 2. Check the simulation of a day. \n");
                printf(" 3. Return to Build Menu. \n");
                printf(" 4. Exit the simulation. \n");
                scanf("%d", &input);
                switch (input) {
                    case 1: {
                        editState = 1;
                        while (editState == 1) {
                            printf("Please select the day to edit: ");
                            scanf("%d", &index + 1);
                            printf("Please select which component to edit: \n");
                            printf(" 1. Daylight intensity. \n");
                            printf(" 2. Geothermal power level. \n");
                            printf(" 3. Windflow strength. \n");
                            printf(" 4. Return to simulation. \n");
                            scanf("%d", &input);
                            switch (input) {
                                case 1: {
                                    printf("Please select the status of the component \n");
                                    printf(" 1. Really Strong (100%% effectiveness) \n");
                                    printf(" 2. Strong (75%% effectiveness) \n");
                                    printf(" 3. Medium (50%% effectiveness) \n");
                                    printf(" 4. Weak (25%% effectiveness) \n");
                                    printf(" 5. No Sunlight (100%% effectiveness) \n");
                                    printf(" 6. Custom Sunlight effectiveness \n");
                                    scanf("%d", &input); 
                                    switch (input) {
                                        case 1: {
                                            simDay[index + 1].spEff = 1;
                                        } break;
                                        case 2: {
                                            simDay[index + 1].spEff = 0.75;
                                        } break;
                                        case 3: {
                                            simDay[index + 1].spEff = 0.5;
                                        }
                                        case 4: {
                                            simDay[index + 1].spEff = 0.25;
                                        } break;
                                        case 5: {
                                            simDay[index + 1].spEff = 0;
                                        } break;
                                        case 6: {
                                            printf("Please enter the custom effectiveness percentage for Daylight intensity (0-100): ");
                                            scanf("%f", &input);
                                            simDay[index + 1].spEff = input / 100.0;
                                        }break;
                                    }
                                } break;
                                case 2: {
                                    printf("Please select the status of the component \n");
                                    printf(" 1. Really Strong (100%% effectiveness) \n");
                                    printf(" 2. Strong (75%% effectiveness) \n");
                                    printf(" 3. Medium (50%% effectiveness) \n");
                                    printf(" 4. Weak (25%% effectiveness) \n");
                                    printf(" 5. No Waterflow (100%% effectiveness) \n");
                                    printf(" 6. Custom power level effectiveness \n");
                                    scanf("%d", &input);
                                    switch (input) {
                                        case 1: {
                                            simDay[index + 1].ggEff = 1;
                                        } break;
                                        case 2: {
                                            simDay[index + 1].ggEff = 0.75;
                                        } break;
                                        case 3: {
                                            simDay[index + 1].ggEff = 0.5;
                                        }
                                        case 4: {
                                            simDay[index + 1].ggEff = 0.25;
                                        } break;
                                        case 5: {
                                            simDay[index + 1].ggEff = 0;
                                        } break;
                                        case 6: {
                                           printf("Please enter the custom effectiveness percentage for Waterflow velocity (0-100): ");
                                           scanf("%f", &input);
                                           simDay[index + 1].ggEff = input / 100.0;
                                        }break;
                                    }
                                } break;
                                case 3: {
                                    printf("Please select the status of the component \n");
                                    printf(" 1. Really Strong (100%% effectiveness) \n");
                                    printf(" 2. Strong (75%% effectiveness) \n");
                                    printf(" 3. Medium (50%% effectiveness) \n");
                                    printf(" 4. Weak (25%% effectiveness) \n");
                                    printf(" 5. No Windflow (100%% effectiveness) \n");
                                    printf(" 6. Custom Windflow effectiveness \n");
                                    scanf("%d", &input);
                                    switch (input) {
                                        case 1: {
                                            simDay[index + 1].wnEff = 1;
                                        } break;
                                        case 2: {
                                            simDay[index + 1].wnEff = 0.75;
                                        } break;
                                        case 3: {
                                            simDay[index + 1].wnEff = 0.5;
                                        }
                                        case 4: {
                                            simDay[index + 1].wnEff = 0.25;
                                        } break;
                                        case 5: {
                                            simDay[index + 1].wnEff = 0;
                                        } break;
                                        case 6: {
                                            printf("Please enter the custom effectiveness percentage for Windflow strength (0-100): ");
                                            scanf("%f", &input);
                                            simDay[index + 1].wnEff = input / 100.0;
                                        }break;
                                    }
                                } break;
                                case 4: {
                                    editState = 0;
                                } break;
                            }
                        }

                    } break;
                    case 2 : {
                        printf("Please enter the day to check \n");
                        scanf("%d", &index+1);
                        showDay(simDay, index);
                    } break;
                    case 3 : {
                        simState = 0;
                        menuState = 1;
                    } break;
                    case 4 : {
                        activeState++;
                    } break;
                    default : {
                        printf("Please check your input again. \n");
                    } break;
                }
            }
        }
    }
    free(sp);
    free(gg);
    free(wn);
    free(simDay);
    return 0;
}
