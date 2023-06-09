#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define LEN 51
#define D_LEN 11

typedef struct {
    char name[LEN];
    char date[D_LEN];
    int lectures;
    float price;
} Course;

void WriteInBin();

void DecreasePriceByIndex(Course* courses, int n, int index);

int CoursesInRange(Course* courses, int n, float min, float max);

Course* RemoveCourseByNameAndDate(Course* courses, int n, char name[], char date[]);

void main ()
{
    //First exercise!
    FILE* fp = fopen("C:/GitHub/C-university/courses.bin", "rb");

    if (fp == NULL)
    {
        perror("Error reading bin!");
        exit(1);
    }

    int n;

    if (fread(&n, sizeof(int), 1, fp) != 1)
    {
        perror("Error reading n!");
        exit(1);
    }

    Course* courses = (Course*)malloc(n * sizeof(Course));

    for (int i = 0; i < n; i++)
    {
        if (fread(&courses[i], sizeof(Course), 1, fp) != 1)
        {
            perror("Error reading course!");
            exit(1);
        }
    }
    
    fclose(fp);

    //Second exercise!
    DecreasePriceByIndex(courses, n, 1);
    //Third exercise!
    int count = CoursesInRange(courses, n, 200, 300);
    //Fourth exercise!
    courses = RemoveCourseByNameAndDate(courses, n, "Angular", "20.12.2023");
}

//Second exercise!
void DecreasePriceByIndex(Course* courses, int n, int index)
{
    //Checks if the index is not in the range of the given courses!
    if (index < 0 || n <= index)
    {
        perror("Index out of range!");
        exit(1);
    }

   //Price decreases with 10%!
    courses[index].price *= 0.9; 
    printf("%.2fлв. - %s - %s\n", courses[index].price, courses[index].name, courses[index].date);
}

//Third exercise!
int CoursesInRange(Course* courses, int n, float minPrice, float maxPrice)
{
    FILE* fp = fopen("C:/GitHub/C-university/offer.txt", "wt");

    int count = 0;

    if (fp == NULL)
    {
        perror("Error opening bin!");
        exit(1);
    }

    int nameLen;
    int dateLen;

    for (int i = 0; i < n; i++)
    {
        if (minPrice < courses[i].price && courses[i].price < maxPrice)
        {
            nameLen = strlen(courses[i].name);
            dateLen = strlen(courses[i].date);

            //We check if the written name + the new line are the exprected length that is written!
            //You can replace (!= nameLen + 1) with (< 1)
            if (fprintf(fp, "%s\n", courses[i].name) != nameLen + 1)
            {
                perror("Error writing name!");
                exit(1);
            }

            if (fprintf(fp, "%s\n", courses[i].date) != dateLen + 1)
            {
                perror("Error writing date!");
                exit(1);
            }

            if (fprintf(fp, "%d лекции\n", courses[i].lectures) < 1)
            {
                perror("Error writing lectures!");
                exit(1);
            }
            
            if (fprintf(fp, "%.2f лв.\n\n", courses[i].price) < 1)
            {
                perror("Error writing price!");
                exit(1);
            }

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

//Fourth exericse!
Course* RemoveCourseByNameAndDate(Course* courses, int n, char name[], char date[])
{
    Course* newArr = (Course*)malloc(n * sizeof(Course));
    int counter = 0;

    for (int i = 0; i < n; i++)
    {
        if (strcmp(courses[i].name, name) == 0 && strcmp(courses[i].date, date) == 0)
        {
            int newSize = n - 1;
            newArr = (Course*)realloc(newArr, newSize * sizeof(Course));

            if (newArr == NULL)
            {
                return courses;
            }

            continue;
        }

        newArr[counter] = courses[i];
        counter++;
    }

    free(courses);

    // for (int i = 0; i < n - 1; i++)
    // {
    //     printf("%s\n", newArr[i].name);
    //     printf("%s\n", newArr[i].date);
    //     printf("%d\n", newArr[i].lectures);
    //     printf("%.2f\n", newArr[i].price);
    // }
    return newArr; 
}

//Not mandatory for the exam!!!!
void WriteInBin()
{
    FILE* fp = fopen("C:/GitHub/C-university/courses.bin", "wb");
    
    if (fp == NULL)
    {
        perror("Error opening bin!");
        exit(1);
    }

    int n;

    printf("Enter number of courses: ");
    scanf("%d", &n);
    fflush(stdin);

    Course* courses = (Course*)malloc(n * sizeof(Course));

    fwrite(&n, sizeof(int), 1, fp);

    for (int i = 0; i < n; i++)
    {
        printf("Name: ");
        fgets(courses[i].name, LEN, stdin);
        fflush(stdin);
        courses[i].name[strlen(courses[i].name) - 1] = '\0';

        printf("Date: ");
        fgets(courses[i].date, D_LEN, stdin);
        fflush(stdin);

        printf("Lectures: ");
        scanf("%d", &courses[i].lectures);
        fflush(stdin);

        printf("Price: ");
        scanf("%f", &courses[i].price);
        fflush(stdin);

        if (fwrite(&courses[i], sizeof(Course), 1, fp) != 1)
        {
            perror("Error writing in file!");
            exit(1);
        }
    }
    
    fclose(fp);
}