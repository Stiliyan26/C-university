#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define ID_LEN 3
#define LEN 21

typedef struct {
    char id[ID_LEN];
    char name[LEN];
    int weight;
    float price
} IceCream;

float TotalPrice(IceCream* creams, int n, char letter);

int WriteInTxt(IceCream* creams, int n, float price, int weight);

void WriteInBin(IceCream* creams, int n);

void ReadBin(char id[]);

void main()
{
    int n;
    printf("Enter n: ");
    scanf("%d", &n);
    fflush(stdin);

    while (true)
    {
        if (5 < n && n < 15)
        {
            return n;
        }

        printf("n not in range!");
        printf("Enter n: ");
        scanf("%d", &n);
        fflush(stdin);
    }

    IceCream* creams = (IceCream*)malloc(n * sizeof(IceCream));

    if (creams == NULL)
    {
        perror("Memory allocation failed!");
        exit(1);
    }

    for (int i = 0; i < n; i++)
    {
        IceCream cream;

        printf("Id: ");
        fgets(cream.id, ID_LEN, stdin);
        fflush(stdin);

        printf("Name: ");
        fgets(cream.name, LEN, stdin);
        fflush(stdin);
        cream.name[strlen(cream.name) - 1] = '\0';

        printf("Weight: ");
        scanf("%d", &cream.weight);
        fflush(stdin);

        printf("Price: ");
        scanf("%f", &cream.price);
        fflush(stdin);

        creams[i] = cream;
    }
    
    float totalPrice = TotalPrice(creams, n, 'K');
    printf("Total price: %.2f\n", totalPrice);

    int count = WriteInTxt(creams, n, 20, 5);
    printf("Count: %d\n", count);

    WriteInBin(creams, n);
    ReadBin("A1");
}

// fourth
void ReadBin(char id[])
{
    FILE* fp = fopen("C:/BPE/lab/icecream.bin", "rb");

    if (fp == NULL)
    {
        perror("Error opening bin!");
        exit(1);
    }

    bool isFound = false; 
    IceCream cream;
    int len;

    while (true)
    {
        if (fread(cream.id, sizeof(char), ID_LEN - 1 , fp) != ID_LEN - 1)
        {
            if (!feof(fp))
            {
                fclose(fp);
                perror("Error reading from bin file!");
                exit(1);
            }
             
            else 
            {
                break;
            }
        }

        if (fread(&len, sizeof(int), 1, fp) != 1)
        {
            perror("Error reading len!");
            exit(1);
        }

        if (fread(cream.name, sizeof(char), len, fp) != len)
        {
            perror("Error reading name!");
            exit(1);
        }

        cream.name[len] = '\0';

        if (fread(&cream.weight, sizeof(int), 1, fp) != 1)
        {
            perror("Error reading weight!");
            exit(1);
        }

        if (fread(&cream.price, sizeof(float), 1, fp) != 1)
        {
            perror("Error reading price!");
            exit(1);
        }

        if (strcmp(cream.id, id) == 0) 
        {
            isFound = true;
            break;
        }
    }

    if (isFound)
    {
        printf("=================\n");
        printf("IceCream - %s\n", cream.name);
        printf("Price - %.2f\n", cream.price);
        printf("=================\n");
    }

    else
    {
        printf("No such data...");
    }

    fclose(fp);
}

void WriteInBin(IceCream* creams, int n)
{
    FILE* fp = fopen("C:/BPE/lab/icecream.bin", "wb");

    if (fp == NULL)
    {
        perror("Error opening bin file!");
        exit(1);
    }

    int len;

    for (int i = 0; i < n; i++)
    {
        IceCream cream = creams[i];
        len = strlen(creams[i].name);
        fwrite(creams[i].id, sizeof(char), ID_LEN - 1, fp);
        fwrite(&len, sizeof(int), 1, fp);
        fwrite(creams[i].name, sizeof(char), len, fp);
        fwrite(&creams[i].weight, sizeof(int), 1, fp);
        fwrite(&creams[i].price, sizeof(float), 1, fp);
    }
    
    fclose(fp);
}

//third
int WriteInTxt(IceCream* creams, int n, float price, int weight)
{
    FILE* fp = fopen("C:/BPE/lab/info.txt", "a");

    if (fp == NULL)
    {
        perror("Error opening file!");
        exit(1);
    }

    int counter = 0;

    for (int i = 0; i < n; i++)
    {
        if (creams[i].price < price && creams[i].weight > weight)
        {
            fprintf(fp, "%s;%s;%d;%.2fleva\n", creams[i].id, creams[i].name, creams[i].weight, creams[i].price);
            counter++;
        }
    }

    if (counter == 0)
    {
        return 0;
    }

    return counter;    
}

//second 
float TotalPrice(IceCream* creams, int n, char letter)
{
    float totalPrice = 0;
    int counter = 0;

    for (int i = 0; i < n; i++)
    {
        if (creams[i].name[0] == letter)
        {
            totalPrice += creams[i].price * creams[i].weight;
            counter++;
        }
    }

    if (counter == 0)
    {
        return 0;
    }
    
    return totalPrice;
}

