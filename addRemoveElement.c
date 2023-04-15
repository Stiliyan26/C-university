#include <stdio.h>
#include <string.h>
#include <stdbool.h>

double* getArray(int);
void printArr(double*, int);
double* removeElement(double* grades, int size, int index);
double* addElement(double* grades, int size, int index);


void main()
{
    int size = 5;
    double* grades = getArray(size);

    bool stopCycleBool = false;
    char stopCycleString[50];
    char wantToAddOrRemove[50];

    int index;
    
    while (stopCycleBool == false)
    {
        if (stopCycleBool == true)
        {
            break;
        }

        printf("Read index: ");
        scanf("%d", &index);

        printf("Do you want to Add or Remove? ");
        scanf("%s", wantToAddOrRemove);

        if (strcmp(wantToAddOrRemove, "Add") == 0)
        {
            size++;
            printf("----Add-----\n");
            grades = addElement(grades, size, index);
        }

        else if (strcmp(wantToAddOrRemove, "Remove") == 0)
        {
            size--;
            printf("----Remove-----\n");
            grades = removeElement(grades, size, index);

            printArr(grades, size);
        }

        printf("Do you want to stop? ");
        scanf("%s", &stopCycleString);

        stopCycleBool = (strcmp(stopCycleString, "Yes") == 0) 
            ? true
            : false;
    }
}

double* removeElement(double* grades, int size, int index)
{
    double* newArray = (double*)malloc(size + 1 * sizeof(double));
    // double* newArray = (double*)malloc(size * sizeof(double));

    // for (int i = 0; i < size; i++)
    // {
    //     newArray[i] = grades[i];
    // }
    // free(grades);

    for (int i = 0; i < size + 1; i++)
    {
        if (i < index)
        {
            newArray[i] = grades[i];
        }

        else if (i > index)
        {
            newArray[i - 1] = grades[i];
        }
    }
    
    
    if (newArray != grades)
    {
        free(grades);
    }

    return newArray;
}

double* addElement(double* grades, int size, int index)
{
    // double* copyArrayBeforeTheIndex = (double*)realloc(grades, index * sizeof(double));
    
    double* newArray = (double*)malloc(size * sizeof(double));

    for (int i = 0; i < size; i++)
    {
        if (index == i)
        {
            printf("Add new number: ");
            scanf("%lf", &newArray[index]);
        }
        
        else if (i < index)
        {
            newArray[i] = grades[i];
        }

        else if (i > index)
        {
            newArray[i] = grades[i - 1];
        }
    }

    printArr(newArray, size);

    // for (int i = index + 1; i < size + 1; i++)
    // {
    //     newArray[i] = grades[i + 1];
    // }
    
    if (newArray != grades)
    {
        free(grades);
    }
    
    // double* newArray = (double*)realloc(grades, size * sizeof(double));
    
    // for (int i = 0; i < size; i++)
    // {
    //     if (i < size - 1)
    //     {
    //         newArray[i] = grades[i];
    //         continue;
    //     }

    //     printf("Add new number: ");
    //     scanf("%lf", &newArray[i]);
    // }

    // free(grades);
    
    

    return newArray;
}

void printArr(double* grades, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%.2lf grades\n", grades[i]);
    }
}

double* getArray(size)
{
    double* arr = (double*)malloc(size * sizeof(double));
    // double* arr = calloc(5, sizeof(double));
    
    for (int i = 0; i < size; i++)
    {
        printf("Enter value: ");
        scanf("%lf", &arr[i]);
    }

    return arr;
}

