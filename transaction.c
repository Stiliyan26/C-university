#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define T_LEN 7
#define D_LEN 11
#define LEN 31

typedef struct {
    char type[T_LEN];
    char date[D_LEN];
    char name[LEN];
    float price;
} Transaction;

void WriteBin();

void PrintBiggestTransaction(Transaction* transactions, int n);

Transaction* ChangeTransactionByIndex(Transaction* transactions, int n, int index);

void WriteInTxt(Transaction* transactions, int n, char date[]);

void main()
{
    //WriteBin();

    //First exercise!
    FILE* fp = fopen("C:/GitHub/C-university/statements.bin", "rb");

    if (fp == NULL)
    {
        perror("Error opening bin!");
        exit(1);
    }

    int n;

    if (fread(&n, sizeof(int), 1, fp) != 1)
    {
        perror("Error readin n!");
        exit(1);
    }

    Transaction* transactions = (Transaction*)malloc(n * sizeof(Transaction));

    for (int i = 0; i < n; i++)
    {
        if (fread(&transactions[i], sizeof(Transaction), 1, fp) != 1)
        {
            perror("Error reading transaction!");
            exit(1);
        }
        // printf("%s\n", transactions[i].type);
        // printf("%s\n", transactions[i].date);
        // printf("%s\n", transactions[i].name);
        // printf("%.2f\n", transactions[i].price);
    }
    
    fclose(fp);

    //Second exercise!
    PrintBiggestTransaction(transactions, n);
    //Third exercise!
    transactions = ChangeTransactionByIndex(transactions, n, 1);
    //Fourth exerice!
    WriteInTxt(transactions, n, "12.03.2024");
}

//Second exercise!
void PrintBiggestTransaction(Transaction* transactions, int n)
{
    int biggestTransactionValue = 0;
    Transaction biggestTransaction;
    bool hasTransaction = false;

    for (int i = 0; i < n; i++)
    {
        if (biggestTransactionValue < transactions[i].price)
        {
            biggestTransactionValue = transactions[i].price;
            biggestTransaction = transactions[i];
            hasTransaction = true;
        }
    }
    
    //we check if there is a transaction! 
    if (hasTransaction)
    {
        printf("%s\n", biggestTransaction.type);
        printf("%s\n", biggestTransaction.date);
        printf("%s\n", biggestTransaction.name);
        printf("%.2f лв.\n", biggestTransaction.price);
    }
}

//Third exercise!
Transaction* ChangeTransactionByIndex(Transaction* transactions, int n, int index)
{
    if (index < 0 || n <= index)
    {
        return NULL;
    }

    Transaction updatedTransaction;
    //Checks if the type is equal to the given type in our case ("razhod"). 
    //If it's equal updatedTransaction.type is set to "prihod" if it's not it is set to "razhod"
    strcmp(transactions[index].type, "razhod") == 0
        ? strcpy(updatedTransaction.type, "prihod")
        : strcpy(updatedTransaction.type, "razhod");

    strcmp(transactions[index].name, "nareditel") == 0
        ? strcpy(updatedTransaction.name, "poluchatel")
        : strcpy(updatedTransaction.name, "nareditel");

    strcpy(updatedTransaction.date, transactions[index].date);

    updatedTransaction.price = transactions[index].price;

    //Set on this position the new updated transaction
    transactions[index] = updatedTransaction;

    // printf("%s\n", transactions[index].type);
    // printf("%s\n", transactions[index].date);
    // printf("%s\n", transactions[index].name);
    // printf("%.2f\n", transactions[index].price);
    return transactions;
}

//Fourth exercise!
void WriteInTxt(Transaction* transactions, int n, char date[])
{
    FILE* fp = fopen("C:/GitHub/C-university/balance.txt", "wt");

    if (fp == NULL)
    {
        perror("Error opening txt!");
        exit(1);
    }

    int typeLen;
    int dateLen;
    int nameLen;

    for (int i = 0; i < n; i++)
    {
        if (strcmp(transactions[i].date, date) == 0)
        {
            typeLen = strlen(transactions[i].type);
            dateLen = strlen(transactions[i].date);
            nameLen = strlen(transactions[i].name);

            //Checks if the written length is equal to the length of the type plus the new line /n
            if (fprintf(fp, "%s\n", transactions[i].type) < typeLen + 1)
            {
                perror("Error writing type!");
                exit(1);
            }

            if (fprintf(fp, "%s\n", transactions[i].date) < dateLen + 1)
            {
                perror("Error writing date!");
                exit(1);
            }

            if (fprintf(fp, "%s\n", transactions[i].name) < nameLen + 1)
            {
                perror("Error writing name!");
                exit(1);
            }

            if (fprintf(fp, "%.2f\n\n", transactions[i].price) < 1)
            {
                perror("Error writing price!");
                exit(1);
            }
        }
    }

    fclose(fp);
}

//Not mandatory for the exam!!!! Tova ne e po uslovie!!!!
void WriteBin()
{
    FILE* fp = fopen("C:/GitHub/C-university/statements.bin", "wb");
    
    if (fp == NULL)
    {
        perror("Error opening bin!");
        exit(1);
    }

    int n;

    printf("Enter number of transactions: ");
    scanf("%d", &n);
    fflush(stdin);

    Transaction* transactions = (Transaction*)malloc(n * sizeof(Transaction));

    fwrite(&n, sizeof(int), 1, fp);

    for (int i = 0; i < n; i++)
    {
        printf("Type: ");
        fgets(transactions[i].type, T_LEN, stdin);
        fflush(stdin);

        printf("Date: ");
        fgets(transactions[i].date, D_LEN, stdin);
        fflush(stdin);

        printf("Name: ");
        fgets(transactions[i].name, LEN, stdin);
        transactions[i].name[strlen(transactions[i].name) - 1] = '\0';
        fflush(stdin);

        printf("Price: ");
        scanf("%f", &transactions[i].price);
        fflush(stdin);

        if (fwrite(&transactions[i], sizeof(Transaction), 1, fp) != 1)
        {
            perror("Error writing in file!");
            exit(1);
        }
    }
    
    fclose(fp);
}