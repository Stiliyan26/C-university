#include <stdio.h>
#include <string.h>

#define PRODUCT_LEN 20
#define ADDRESS_LEN 30

typedef struct 
{
    char productName[PRODUCT_LEN];
    float productPrice;
    int uniqueProductNumber;
} Product;

typedef struct 
{
    char address[ADDRESS_LEN];
    int numberOfProduct;
} Order;

Product* removeProduct(Product* products, int size, int index);

void main()
{
    char option[50];
    printf("Choose option: Product/Order: ");
    scanf("%s", option);

    Product* products;
    int index = 0;
    int sizeArr = 0;

    while (strcmp(option, "END") != 0)
    {
        if (strcmp(option, "Product") == 0)
        {
            Product currentStudent;

            printf("Enter product name: ");
            scanf("%s", currentStudent.productName);

            printf("Enter price: ");
            scanf("%f", &currentStudent.productPrice);

            printf("Enter product number: ");
            scanf("%d", &currentStudent.uniqueProductNumber);

            products[index] = currentStudent;
            index++;
            sizeArr++;
        }

        else if (strcmp(option, "Order") == 0)
        {
            Order currentOrder;

            printf("Enter address: ");
            scanf("%s", currentOrder.address);

            printf("Enter product number: ");
            scanf("%d", &currentOrder.numberOfProduct);

            int size = sizeArr;
            
            for (int i = 0; i < size; i++)
            {
                if (products[i].uniqueProductNumber == currentOrder.numberOfProduct)
                {
                    Product product = products[i];
                    products = removeProduct(products, size, i);
                    printf("Client %s ordered %s\n", currentOrder.address , product.productName);

                    sizeArr--;
                }
            }
        }   

        printf("Choose option: Product/Order: ");
        scanf("%s", option);
    }

    printf("------------\n");

    for (int i = 0; i < sizeArr; i++)
    {
        printf("Name: %s\n", products[i].productName);
        printf("Price: %.2f\n", products[i].productPrice);
        printf("Product number: %d\n", products[i].uniqueProductNumber);
    }
}

  Product* removeProduct(Product* products, int size, int index)
    {
        Product* newPorducts = (Product*)malloc(size * sizeof(Product));

        for (int i = 0; i < size; i++)
        {
            if (i < index)
            {
                newPorducts[i] = products[i];
            }

            else if (i > index)
            {
                newPorducts[i - 1] = products[i];
            }
        }

        return newPorducts;
    }