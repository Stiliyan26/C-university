#include <stdio.h>

void main()
{
    // way1();
    way2();
}

void way1()
{
    double matrix[3][4] = 
    {
        { 1, 2, 3, 4 },
        { 5, 6, 7, 8 },
        { 9, 10, 11, 12 }
    };

    double *p2 = (double*)matrix;

    int counter = 0;
    for (int i = 0; i < 3; i++)
    {
        printf("%.0lf %.0lf %.0lf %.0lf \n",
         *(p2 + (i * 4) + counter),
         *(p2 + (i * 4) + counter + 1),
         *(p2 + (i * 4) + counter + 2),
         *(p2 + (i * 4) + counter + 3));
    }
}

void way2()
{
    double matrix[3][4] =  
    {
        { 1, 2, 3, 4 },
        { 5, 6, 7, 8 },
        { 9, 10, 11, 12 }
    };

    double *p2 = (double*)matrix;

    for (int i = 0; i < 12; i++)
    {
        if (i % 4 == 0 && i != 0)
        {
            printf("\n");
        }
        
        printf("%.0lf ", *(p2 + i));
    }
}