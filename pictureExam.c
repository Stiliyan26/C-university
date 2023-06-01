#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define N_LEN 31
#define T_LEN 31

typedef struct {
    int id;
    char name[N_LEN];
    char title[T_LEN];
    float price;
} Picture;

float AvgPrice(Picture* pics, int n, float price);

int WriteInTxt(Picture* pics, int n, char letter);

void WriteBin(Picture* pics, int n);

void ReadBin(char name[]);

void main()
{
    int n;
    printf("Enter n: ");
    scanf("%d", &n);
    getchar();

    // while (true)
    // {
    //     if (3 < n && n < 30)
    //     {
    //         break;
    //     }

    //     else 
    //     {
    //         printf("N is not in range!\n");
    //         printf("Enter n: ");
    //         scanf("%d", &n);
    //         getchar();
    //     }
    // }

    Picture* pictures = (Picture*)calloc(n, sizeof(Picture));

    if (pictures == NULL)
    {
        perror("Failed memory allocation!\n");
        exit(1);
    }

    for (int i = 0; i < n; i++)
    {
        printf("ID: ");
        scanf("%d", &pictures[i].id);
        getchar();

        printf("Name: ");
        fgets(pictures[i].name, N_LEN, stdin);
        pictures[i].name[strlen(pictures[i].name) - 1] = '\0';

        printf("Title: ");
        fgets(pictures[i].title, T_LEN, stdin);
        pictures[i].title[strlen(pictures[i].title) - 1] = '\0';

        printf("Price: ");
        scanf("%f", &pictures[i].price);
        getchar();
    }

    //2
    float avgPrice = AvgPrice(pictures, n, 20.2);
    printf("Avg price: %.2f\n", avgPrice);

    //3
    int count = WriteInTxt(pictures, n, 'K');
    printf("Count: %d\n", count);

    //ne e kum zadachata
    WriteBin(pictures, n);

    //4
    ReadBin("Pepi");
}

//Fourth exr
void ReadBin(char name[])
{
    FILE* fp;
    fp = fopen("C:/BPE/lab/picture.bin", "rb");
    int counter = 0;

    if (fp == NULL)
    {
        perror("Err reading bin!");
        exit(1);
    }

    Picture pic;
    bool isFound = false;
    int n_len, t_len;

    while (true)
    {
        if (fread(&pic.id, sizeof(int), 1, fp) != 1)
        {
            if (!feof(fp))
            {
                fclose(fp);
                perror("Error readng bin!");
                exit(1);
            }
            else
            {
                break;
            }
        }

        if (fread(&n_len, sizeof(int), 1, fp) != 1)
        {
            perror("Error reading name len!");
            exit(1);
        }

        if (fread(pic.name, sizeof(char), n_len, fp) != n_len)
        {
            perror("Error reading name!");
            exit(1);
        }

        pic.name[n_len]= '\0';

        if (fread(&t_len, sizeof(int), 1, fp) != 1)
        {
            perror("Error reading title len!");
            exit(1);
        }

        if (fread(pic.title, sizeof(char), t_len, fp) != t_len)
        {
            perror("Error reading title!");
            exit(1);
        }

        pic.title[t_len]= '\0';

        if (fread(&pic.price, sizeof(float), 1, fp) != 1)
        {
            perror("Error reading price!");
            exit(1);
        }

        if (strcmp(pic.name, name) == 0)
        {
            printf("Picture title: %s\n", pic.title);
            printf("Price: %.2f BGN\n", pic.price);
            counter++;
        }
    }

    if (counter == 0)
    {
        printf("No such data...");
    }

    fclose(fp);
}

//Ne e kum zadacahta
void WriteBin(Picture* pics, int n)
{
    FILE* fp = fopen("C:/BPE/lab/picture.bin", "wb");

    if (fp == NULL)
    {
        perror("Error opening bin!");
        exit(1);
    }

    for (int i = 0; i < n; i++)
    {
        int n_len = strlen(pics[i].name);
        int t_len = strlen(pics[i].title);
        
        fwrite(&pics[i].id, sizeof(int), 1, fp);
        fwrite(&n_len, sizeof(int), 1, fp);
        fwrite(pics[i].name, sizeof(char), n_len, fp);

        fwrite(&t_len, sizeof(int), 1, fp);
        fwrite(pics[i].title, sizeof(char), t_len, fp);
        fwrite(&pics[i].price, sizeof(float), 1, fp);
    }
    
    fclose(fp);
}


//third exercise
int WriteInTxt(Picture* pics, int n, char letter)
{
    FILE* fp;
    int count = 0;

    fp = fopen("C:/BPE/lab/info.txt", "a");

    if (fp == NULL)
    {
        perror("Error opeining file!");
    }

    for (int i = 0; i < n; i++)
    {
        if (pics[i].name[0] == letter)
        {
            fprintf(fp, "%d;%s;%.2fleva\n", pics[i].id, pics[i].name, pics[i].price);
            count++;
        }
    }

    fclose(fp);

    if (count == 0)
    {
        return 0;
    }

    return count;
}

//Second exercise!
float AvgPrice(Picture* pics, int n, float price)
{
    float totalPrice = 0;
    float avgPrice = 0;
    int counter = 0;

    for (int i = 0; i < n; i++)
    {
        if (pics[i].price > price)
        {
            totalPrice += pics[i].price;
            counter++;
        }
    }

    if (totalPrice == 0)
    {
        return 0;
    }
    
    avgPrice = totalPrice / counter;

    return avgPrice;
}
