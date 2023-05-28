#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define NAME_LEN 31
#define CHIP_LEN 8

typedef struct 
{
    char name[NAME_LEN];
    char chip[CHIP_LEN];
    float price;
} Pet;

Pet CreatePets();

void WritePetTxt(Pet petToBeWritten);

void PrintPatientByPrice(Pet* pets, unsigned size, float searchedPrice);

void WriteToBinFile(Pet* pets, unsigned size);

void ReadAndPrintFromBinFile(float price);

void main()
{
    unsigned numberOfPatients;
    printf("Enter number of patients: ");
    scanf("%u", &numberOfPatients); 
    getchar();

    Pet* pets = (Pet*)malloc(numberOfPatients * sizeof(Pet)); 

    //int* numbers = (int*)calloc(numberOfPatients, sizeof(int));

    for (unsigned i = 0; i < numberOfPatients; i++)
    {
        Pet newPet = CreatePets();
        WritePetTxt(newPet);
        pets[i] = newPet;
    }

    PrintPatientByPrice(pets, numberOfPatients, 20.2);
    WriteToBinFile(pets, numberOfPatients);
    ReadAndPrintFromBinFile(20.3);
}

void ReadAndPrintFromBinFile(float price)
{
    FILE *fp;
    unsigned len;
    Pet pet;
    bool isFirst = true;

    if ((fp = fopen("C:/BPE/lab/pet2.bin", "rb")) == NULL)
    {
        perror("Open bin error!");
        exit(3);
    }

    while (true)
    {
        if (fread(&len, sizeof(unsigned), 1, fp) != 1)
        {
            if (!feof(fp))
            {
                perror("Reading from bin error");
                exit(4);
                fclose(fp);
            }
            else 
            {
                break;
            }
        }

        if (fread(&pet.name, sizeof(char), len, fp) != len)
        {
            perror("Reading from bin error");
            fclose(fp);
            exit(5);
        }
        pet.name[len] = '\0';


        if (fread(&pet.chip, sizeof(char), CHIP_LEN - 1, fp) != CHIP_LEN - 1)
        {
            perror("Reading from bin error");
            fclose(fp);
            exit(6);
        }

        pet.chip[CHIP_LEN - 1] = '\0';

        if (fread(&pet.price, sizeof(float), 1, fp) != 1)
        {
            perror("Reading from bin error");
            fclose(fp);
            exit(7);
        }

        if (pet.price >= price)
        {
            if (isFirst)
            {
                isFirst = false;
            }
            else
            {
                puts("---------");
            }

            printf("Bin Owner Name: %s\n", pet.name);
            printf("Bin Chip: %s\n", pet.chip);
            printf("Bin Price: %.2f\n", pet.price);
        }
    }

    fclose(fp);
}

void WriteToBinFile(Pet* pets, unsigned numberOfPatients)
{
    FILE* fp;
    fp = fopen("C:/BPE/lab/pet2.bin", "wb");

    unsigned size, sizeOfChip;

    if (fp == NULL)
    {
        perror("Write error\n");
        exit(2);
    }

    for (unsigned i = 0; i < numberOfPatients; i++)
    {
        size = strlen(pets[i].name);
        fwrite(&size, sizeof(unsigned), 1, fp);
        fwrite(pets[i].name, sizeof(char), size, fp);
        fwrite(pets[i].chip, sizeof(char), CHIP_LEN - 1, fp);
        fwrite(&pets[i].price, sizeof(float), 1, fp);
    }    
    fclose(fp);
}

void PrintPatientByPrice(Pet* pets, unsigned size, float searchedPrice)
{
    bool isFound = false;

    for (unsigned i = 0; i < size; i++)
    {
        Pet pet = pets[i];

        if (pet.price == searchedPrice)
        {
            isFound = true;
            printf("%s - %s", pet.name, pet.chip);
            break;
        }
    }

    if (!isFound)
    {
        printf("No such data...\n");
    }
    
}

void WritePetTxt(Pet petToBeWritten)
{
    FILE* fp;
    fp = fopen("C:/BPE/lab/pet2.txt", "a");

    if (fp == NULL)
    {
        perror("File could not be open.\n");
        exit(1);
    }

    fprintf(fp, "%s, %.2f\n", petToBeWritten.name, petToBeWritten.price);
    fclose(fp);
}

Pet CreatePets()
{
    Pet pet;

    printf("Enter pet name: ");
    fgets(pet.name, NAME_LEN, stdin);
    pet.name[strlen(pet.name) - 1] = '\0';

    printf("Enter chip: ");
    fgets(pet.chip, CHIP_LEN, stdin);
    pet.chip[strlen(pet.chip) - 1] = '\0';

    printf("Enter price: ");
    scanf("%f", &pet.price);
    fflush(stdin);

    return pet;
}