#include <stdio.h>
#include <stdlib.h>

int** make2dArray(int, int);

int main()
{
    int i, j;
    int **matrix;

    matrix = make2dArray(5, 5);

    for(i=0; i<5; i++)
    {
        for(j=0; j<5; j++)
        {
            matrix[i][j] = i*5 + j + 1;
            printf("%p: %2d| ", &matrix[i][j], matrix[i][j]);
        }
        printf("\n");
    }

    for(i=0; i<5; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
}

int** make2dArray(int rows, int cols)
{
    int **x, i;

    /* allocate memory for row pointers */
    x = malloc(rows * sizeof(*x));

    /* allocate memory for each row */
    for(i=0; i<rows; i++)
    {
        x[i] = malloc(cols * sizeof(**x));
    }

    return x;
}