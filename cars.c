#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define LEN 36
#define REG_LEN 9

typedef struct {
    char name[LEN];
    char reg_number[REG_LEN];
    float price;
    int priority;
} Car;

Car* InputCar(Car* cars, int size);

float AveragePrice(Car* cars, int count);

void WriteBin(Car* cars, int count);

void ReadBin(char reg_num[]);

void main()
{
    int size = 0;
    Car* cars = (Car*)malloc(size * sizeof(Car));

    int count;
    printf("Enter count: ");
    scanf("%d", &count);
    fflush(stdin);

    for (int i = 0; i < count; i++)
    {
        //First exercise
        cars = InputCar(cars, i);
    }

    //Second exercise
    float avgPrice = AveragePrice(cars, count);
    printf("Average Price: %.2f\n", avgPrice);

    //Not mandatory for the exam
    WriteBin(cars, count);

    //Third exercise
    ReadBin("AB");
}

//Third exercise
void ReadBin(char reg_num[])
{
    FILE* fp;
    fp = fopen("C:/BPE/lab/auto.bin", "rb");

    if (fp == NULL)
    {
        fclose(fp);
        perror("Error reading bin!");
        exit(3);
    }

    Car car;
    bool isFound = false;
    int len;

    while (true)
    {
        if (fread(&len, sizeof(int), 1, fp) != 1)
        {
            if (!feof(fp))
            {
                perror("Error reading file!");
                exit(4);
            }
            else
            {
                break;
            }
        }

        if (fread(car.name, sizeof(char), LEN - 1, fp) != LEN - 1)
        {
            perror("Reading name error!");
            exit(5);
        }

        if (fread(car.reg_number, sizeof(char), REG_LEN - 1, fp) != REG_LEN - 1)
        {
            perror("Reading number error!");
            exit(6);
        }

        if (fread(&car.price, sizeof(float), 1, fp) != 1)
        {
            perror("Reading price error!");
            exit(7);
        }

        if (fread(&car.priority, sizeof(int), 1, fp) != 1)
        {
            perror("Reading priority error!");
            exit(8);
        }

        if (strcmp(car.reg_number, reg_num) == 0)
        {
            isFound = true;
            break;
        }
    }

    fclose(fp);
    
    if (isFound)
    {
        printf("Bin Name: %s\n", car.name);
        printf("Bin L_Plate: %s\n", car.reg_number);
        printf("Bin Price: %.2f\n", car.price);
        printf("Bin Priority: %d\n", car.priority);

    }

    else 
    {
        printf("No such data...");
    }
}


//Not mandatory for the exam
void WriteBin(Car* cars, int count)
{
    FILE* fp;

    fp = fopen("C:/BPE/lab/auto.bin", "wb");

    if (fp == NULL)
    {
        perror("Error opening bin!");
        exit(2);
    }

    for (int i = 0; i < count; i++)
    {
        int len = strlen(cars[i].name);
        fwrite(&len, sizeof(int), 1, fp);
        fwrite(cars[i].name, sizeof(char), LEN - 1, fp);
        fwrite(cars[i].reg_number, sizeof(char), REG_LEN - 1, fp);
        fwrite(&cars[i].price, sizeof(float), 1, fp);
        fwrite(&cars[i].priority, sizeof(int), 1, fp);
    }

    fclose(fp);
}

//Second exercise
float AveragePrice(Car* cars, int count)
{
    float avgPrice = 0;
    float totalPrice = 0;

    for (int i = 0; i < count; i++)
    {
        totalPrice += cars[i].price;
    }

    avgPrice = totalPrice / count;

    for (int i = 0; i < count; i++)
    {
        if (cars[i].price > avgPrice)
        {
            printf("%s - %.2f\n", cars[i].reg_number, cars[i].price);
        }
    }

    return avgPrice;
}

//First exercise
Car* InputCar(Car* cars, int size)
{
    int newSize = size + 1;
    Car* newArray = (Car*)realloc(cars, newSize * sizeof(Car));

    FILE* fp = fopen("C:/BPE/lab/autoText.txt", "a");

    if (fp == NULL)
    {
        perror("Error opening txt file!");
        exit(1);
    }

    Car newCar;

    printf("Name: ");
    fgets(newCar.name, LEN, stdin);
    newCar.name[strlen(newCar.name) - 1] = '\0';

    printf("Registration number: ");
    fgets(newCar.reg_number, REG_LEN, stdin);
    newCar.reg_number[strlen(newCar.reg_number) - 1] = '\0';
    
    printf("Price: ");
    scanf("%f", &newCar.price);
    fflush(stdin);

    printf("Priority: ");
    scanf("%d", &newCar.priority);
    fflush(stdin);

    newArray[size] = newCar;

    int len = strlen(newCar.name);

    fprintf(fp, "%d;%s;%s;%.2f;%d\n", len, newCar.name, newCar.reg_number, newCar.price, newCar.priority);

    fclose(fp);

    return newArray;
}
