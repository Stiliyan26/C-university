#include <stdio.h>
#include <string.h>
#include <math.h>

void main()
{
    int guests;
    float totalChairs = 0;
    float totalPeopleByTable= 0;
    float totalCups = 0;
    float totalDishesWithUtensils = 0;

    float totalPrice;

    char objects[50];

    printf("Enter guests: ");
    scanf("%d", &guests);

    printf("Enter an object: ");
    scanf("%s", &objects);

    while (strcmp(objects, "PARTY!") != 0)
    {
        if (strcmp(objects, "Chair") == 0)
        {
            totalPrice += 13.99;
            totalChairs += 1;
        }
        else if (strcmp(objects, "Table") == 0)
        {
            totalPrice += 42.00;
            totalPeopleByTable += 8;
        }
        else if (strcmp(objects, "Cups") == 0)
        {
            totalPrice += 5.98;
            totalCups += 6;
        }
        else if(strcmp(objects, "Dishes") == 0)
        {
            totalPrice += 21.02;
            totalDishesWithUtensils += 6;
        }

        printf("Enter an object: ");
        scanf("%s", &objects);
    }

    printf("Total price: %.2f\n", totalPrice);
    float neededChairs = guests - totalChairs;
    float neededPlacesOnTables = guests - totalPeopleByTable;
    float neededCups = guests - totalCups;
    float neededDishes = guests - totalDishesWithUtensils;

    if (neededChairs > 0)
    {
        printf("%d Chairs\n", neededChairs);
    }

    if (neededCups > 0)
    {
        float neededCupsComplekt = ceil(neededCups / 6);

        if (neededCupsComplekt == 0)
        {
            neededCupsComplekt = 1;
        }
        printf("%.0f Cups\n", neededCups);
    }

    if (neededPlacesOnTables > 0)
    {
        float neededTables = ceil(neededPlacesOnTables / 8);

        if (neededTables == 0)
        {
            neededTables = 1;
        }

        printf("%.0f Tables\n", neededTables);
    }

    if (neededDishes > 0)
    {
        float neededDishesComplekt = ceil(neededDishes / 6);

        if (neededDishesComplekt == 0)
        {
            neededDishesComplekt = 1;
        }

        printf("%.0f Dishes\n", neededDishesComplekt);
    }
}