#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define LEN 31
#define EXP_LEN 11

typedef struct {
    char name[LEN];
    int ID;
    char expiryDate[EXP_LEN];
    float price;
} Product;

Product InputProduct();

Product* ReturnArrWithAbovePrice(Product* products, unsigned count, float price);

void ReadBinWriteTxtAndPrint();

void main()
{
    unsigned count;
    printf("Enter count of products: ");
    scanf("%d", &count);
    fflush(stdin);

    Product* products = (Product*)malloc(count * sizeof(Product));
    //Exrcise 1
    for (unsigned i = 0; i < count; i++)
    {
        Product product = InputProduct();
        products[i] = product;
    }

    //Exercise 2
    Product* resultArr = ReturnArrWithAbovePrice(products, count, 24.2);

    //Exercise 3
    ReadBinWriteTxtAndPrint();
}

//Exercise 3
void ReadBinWriteTxtAndPrint()
{
    FILE* fpBin;
    FILE* fpTxt;

    fpBin = fopen("C:/BPE/lab/in.bin", "rb");
    fpTxt = fopen("C:/BPE/lab/out.txt", "a");

    if (fpBin == NULL)
    {
        perror("Bin reader err!");
        exit(6);
    }

    if (fpTxt == NULL)
    {
        perror("Txt write err!");
        exit(6);
    }

    while (true)
    {
        Product product;

        if (fread(product.name, sizeof(char), LEN - 1, fpBin) != LEN - 1)
        {
            if (!feof(fpBin))
            {
                perror("Reading from bin error");
                exit(10);
                fclose(fpBin);
            }
            else 
            {
                break;
            }
        }

        if (fread(&product.ID, sizeof(int), 1, fpBin) != 1)
        {
            perror("Reading ID error!");
            exit(8);
        }

        if (fread(product.expiryDate, sizeof(char), EXP_LEN - 1, fpBin) != EXP_LEN - 1)
        {
            perror("Reading expiry date error!");
            exit(9);
        }

        if (fread(&product.price, sizeof(float), 1, fpBin) != 1)
        {
            perror("Reading price error!");
            exit(9);
        }

        fprintf(fpTxt, "%s\n", product.name);
        fprintf(fpTxt, "%d\n", product.ID);
        fprintf(fpTxt, "%s\n", product.expiryDate);
        fprintf(fpTxt, "%.2f\n", product.price);

        printf("Binary Item:\n");
        printf("  Name: %s\n", product.name);
        printf("  ID: %d\n", product.ID);
        printf("  Expire Date: %s\n", product.expiryDate);
        printf("  Price: %.2f\n", product.price);

        printf("Text Item:\n");
        printf("  Name: %s\n", product.name);
        printf("  ID: %d\n", product.ID);
        printf("  Expire Date: %s\n", product.expiryDate);
        printf("  Price: %.2f\n", product.price);

        printf("----------------------\n");
    }

    fclose(fpBin);
    fclose(fpTxt);
}

//Exercise 2
Product* ReturnArrWithAbovePrice(Product* products, unsigned count, float price)
{
    Product* newArr = (Product*)malloc(count * sizeof(Product));

    unsigned counter = 0;

    for (unsigned i = 0; i < count; i++)
    {
        if (products[i].price > price)
        {
            newArr[counter] = products[i];
            counter++;
        }
    }
    
    return newArr;
}

//Exercise 1
Product InputProduct()
{
    FILE* fp = fopen("C:/BPE/lab/in.bin", "ab");

    if (fp == NULL)
    {
        perror("Write bin error!");
        exit(1);
    }

    Product product;

    printf("Name: ");
    fgets(product.name, LEN, stdin);
    product.name[strlen(product.name) - 1] = '\0';

    printf("ID: ");
    scanf("%d", &product.ID);
    fflush(stdin);

    printf("Enter expiry date: ");
    fgets(product.expiryDate, EXP_LEN, stdin);
    product.expiryDate[strlen(product.expiryDate) - 1] = '\0';

    printf("Enter price: ");
    scanf("%f", &product.price);
    fflush(stdin);

    if (fwrite(product.name, sizeof(char), LEN - 1, fp) != LEN - 1)
    {
        perror("Write name bin err!");
        exit(2);
    }

    if (fwrite(&product.ID, sizeof(int), 1, fp) != 1)
    {
        perror("Write ID bin err!");
        exit(3);
    }

    if (fwrite(product.expiryDate, sizeof(char), EXP_LEN - 1, fp) != EXP_LEN - 1)
    {
        perror("Write expirity date err!");
        exit(4);
    }

    if (fwrite(&product.price, sizeof(float), 1, fp) != 1)
    {
        perror("Write price err!");
        exit(5);
    }

    fclose(fp);

    return product;
}