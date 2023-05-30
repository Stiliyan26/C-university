#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define LEN 56
#define ID_LEN 7

typedef struct {
    char fullName[LEN];
    char id[ID_LEN];
    float price;
    int code; 
} Member;

Member* InputMember(Member* members, int size);

float AveragePrice(Member* members, int size);

void WriteInBinFile(Member* members, int size);

void ReadBinFile(char id[]);

void main()
{
    int size = 0;
    Member* members = (Member*)malloc(size * sizeof(Member));

    int count;
    printf("Member count: ");
    scanf("%d", &count);
    fflush(stdin);

    for (int i = 0; i < count; i++)
    {
        //First exercise
        members = InputMember(members, size);
        size++;
    }

    //second exercise
    float averagePrice = AveragePrice(members, size);
    printf("Avg price is: %.2f\n", averagePrice);

    //Not mandatory for exercise three
    WriteInBinFile(members, size);
    //third exercise
    ReadBinFile("2");
}

//Third exercise
void ReadBinFile(char id[])
{
    Member member;
    FILE* fp;
    fp = fopen("C:/BPE/lab/members.bin", "rb");

    if (fp == NULL)
    {
        perror("Error reading bin!");
        exit(3);
    }

    bool isFound = false;

    while (true)
    {
        int len;

        if (fread(&len, sizeof(int), 1, fp) != 1)
        {
            if (!feof(fp))
            {
                fclose(fp);
                perror("Error reading file!");
                exit(4);
            }

            else 
            {
                break;
            }
        }

        if (fread(member.fullName, sizeof(char), LEN - 1, fp) != LEN - 1)
        {
            perror("Error reading name!");
            exit(5);
        }

        if (fread(member.id, sizeof(char), ID_LEN - 1, fp) !=  ID_LEN - 1)
        {
            perror("Error reading id!");
            exit(6);
        }

        if (fread(&member.price, sizeof(float), 1, fp) != 1)
        {
            perror("Error reading price!");
            exit(7);
        }

        if (fread(&member.code, sizeof(int), 1, fp) != 1)
        {
            perror("Error reading code!");
            exit(8);
        }

        if (strcmp(member.id, id) == 0)
        {
            isFound = true;
            break;
        }
    }
    
    fclose(fp);

    if (isFound)
    {
        printf("Bin Names: %s\n", member.fullName);
        printf("Bin ID: %s\n", member.id);
        printf("Bin M_Price: %.2f\n", member.price);
        printf("Bin Locker: %d\n", member.code);
    }
    else 
    {
        printf("No such data!");
    }
}

//Not mandatory for third exericse 
void WriteInBinFile(Member* members, int size)
{
    FILE* fp = fopen("C:/BPE/lab/members.bin", "wb");

    if (fp == NULL)
    {
        perror("Error opening bin!");
        exit(2);
    }

    for (int i = 0; i < size; i++)
    {
        Member member = members[i];
        int len = strlen(member.fullName);

        fwrite(&len, sizeof(int), 1, fp);
        fwrite(member.fullName, sizeof(char), LEN - 1, fp);
        fwrite(member.id, sizeof(char), ID_LEN - 1, fp);
        fwrite(&member.price, sizeof(float), 1, fp);
        fwrite(&member.code, sizeof(int), 1, fp);
    }
    
    fclose(fp);
}

//Second exercise
float AveragePrice(Member* members, int size)
{
    float averagePrice = 0;
    float totalPrice = 0;

    for (int i = 0; i < size; i++)
    {
        totalPrice += members[i].price;
    }
    
    averagePrice = totalPrice / size;

    for (int i = 0; i < size; i++)
    {
        if (averagePrice > members[i].price)
        {
            printf("%s - %s - %.2f\n", members[i].fullName, members[i].id, members[i].price);
        }
    }
    
    return averagePrice;
}

//First exercise
Member* InputMember(Member* members, int size)
{
    int newSize = size + 1;
    Member* newArray = (Member*)realloc(members, newSize * sizeof(Member));

    FILE* fp = fopen("C:/BPE/lab/membersText.txt", "a");

    if (fp == NULL)
    {
        perror("Open txt error!");
        exit(1);
    }

    Member member;

    printf("Name: ");
    fgets(member.fullName, LEN, stdin);
    member.fullName[strlen(member.fullName) - 1] = '\0';

    printf("Id: ");
    fgets(member.id, ID_LEN, stdin);
    member.id[strlen(member.id) - 1] = '\0';

    printf("Price: ");
    scanf("%f", &member.price);
    fflush(stdin);

    printf("Code: ");
    scanf("%d", &member.code);
    fflush(stdin);

    newArray[size] = member;

    int len = strlen(member.fullName);

    fprintf(fp, "%d;%s;%s;%.2f;%d\n", len, member.fullName, member.id, member.price, member.code);

    fclose(fp);
    return newArray;
}
