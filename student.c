#include <stdio.h>

typedef struct Student
{
    char name[30];
    double grade;
} Student;

void writeTextFile(Student [2], char []);

void main()
{
    Student students[2];
    char checker[50] = "Yes";
    char option[50];

    while(strcmp(checker, "No") != 0)
    {
        printf("Do you want to read or write: ");
        scanf("%s", option);

        if (strcmp(option, "Read") == 0)
        {
            // readTextFile(students, "C:/exam/students.txt");
            readBinFile(students, "C:/exam/students.bin");
        }
        else if (strcmp(option, "Write") == 0)
        {
            for (int i = 0; i < 2; i++)
            {
                Student currentStudent; 

                printf("Enter student info: ");
                scanf("%s %lf", currentStudent.name, &currentStudent.grade);

                students[i] = currentStudent;
            }

            // writeTextFile(students, "C:/exam/students.txt");
            writeBinFile(students, "C:/exam/students.bin");
        }

        printf("Do you want to countinue: ");
        scanf("%s", checker);
    }
}

void readBinFile(Student students[2], char file_name[])
{
    FILE* fp = fopen(file_name, "rb");
    int len;
    // fread(&len, sizeof(int), 1, fp);
    // printf("size: %d\n", len);
    // fread(students, len, 1, fp);
    fread(students, sizeof(Student), 2, fp);
    fclose(fp);
}

void writeBinFile(Student students[2], char file_name[])
{
    FILE* fp = fopen(file_name, "wb");

    if(fp == NULL)
    {
        printf("Error when writing to file!");
        exit(1);
    }

    fwrite(students, sizeof(Student), 2, fp);

    fclose(fp);
}

void readTextFile(Student students[5], char file_name[])
{
    FILE* fp = fopen(file_name, "rt");

    char name[30];
    double grade;

    for (int i = 0; i < 5; i++)
    {
        Student student;
        fscanf(fp, "%s %lf\n", student.name, &student.grade); 
        students[i] = student;
    }

    for (int i = 0; i < 5; i++)
    {
       printf("%s %.2lf\n", students[i].name, students[i].grade);
    }
    
    fclose(fp);
}

void writeTextFile(Student students[2], char file_name[])
{
    FILE* fp = fopen(file_name, "wt");

    if (fp == NULL)
    {
        perror("Error opening file.");
        exit(1);
    } 

    fprintf(fp, "%s %.2lf", students[0].name, students[0].grade);

    for (int i = 1; i < 2; i++)
    {
        fprintf(fp, "\n%s %.2lf", students[i].name, students[i].grade);
    }

    fclose(fp);
}