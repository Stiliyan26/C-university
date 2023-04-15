#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define LEN 31
#define CH_LEN 8

typedef struct 
{
    char name[LEN];
    char chip[CH_LEN];
    float price;
} Pet;

Pet inputPet()
{
    FILE* fp = fopen("C:/BPE/lab/animalText.txt", "a");

    Pet pet;

    printf("Enter name: ");
    fgets(pet.name, sizeof(pet.name), stdin);
    fflush(stdin);
    pet.name[strlen(pet.name) - 1] = '\0';

    printf("Enter chip: ");
    fgets(pet.chip, sizeof(pet.chip), stdin);
    fflush(stdin);

    printf("Enter price: ");
    scanf("%f", &pet.price);
    fflush(stdin);

    if (fp == NULL)
    {
        perror("Error occured");
        exit(2);
    }

    fprintf(fp, "%s,%.2f\n", pet.name, pet.price);
    fclose(fp);

    return pet;
}

void printPetByPrice(Pet pets[], unsigned len, float price)
{
    bool isFound = false;
    for (int i = 0; i < len; i++)
    {
        if (pets[i].price == price)
        {
            isFound = true;
            printf("%s - %s", pets[i].name, pets[i].chip);
        }
    }

    if (!isFound)
    {
        puts("No such data...");
    }
}

void printPets(float price)
{
    FILE* fp;
    unsigned len;
    Pet pet;
    bool isFirst;

}

void main()
{
    const unsigned SIZE = 2;

    Pet pets[SIZE];
    for (int i = 0; i < SIZE; i++)
    {
        pets[i] = inputPet();
    }

    printPetByPrice(pets, SIZE, 22.22);
    writeToBin(pets, SIZE);

    printPets(25);
}

void writeToBin(Pet pets[], unsigned len)
{
    FILE *fp = fopen("C:/BPE/lab/animalBin.bin", "wb");
    unsigned size;

    if (fp == NULL)
    {
        perror("Write error: ");
        exit(3);
    }

    for (int i = 0; i < len; i++)
    {
        size = strlen(pets[i].name);
        fwrite(&size, sizeof(unsigned), 1, fp);
        fwrite(pets[i].name, sizeof(char), size, fp);
        fwrite(pets[i].chip, sizeof(char), CH_LEN - 1, fp);
        fwrite(&pets[i].price, sizeof(float), 1, fp);
    }

    fclose(fp);
}