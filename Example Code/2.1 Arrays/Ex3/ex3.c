#include <stdio.h>
#include <stdlib.h>

void print1(int*, int);

int main()
{
    int one[] = {0, 1, 2, 3, 4};
    print1(one, 5);
}

void print1(int *ptr, int rows)
{
    /* print out an one-dimensional array using a pointer */
    int i;
    printf("Address        Contents\n");
    for(i=0; i<rows; i++) {
        printf("%8p%5d\n", ptr+i, *(ptr+i));
        // printf("%8p%5d\n", &ptr[i], ptr[i]);
    }
    printf("\n");
}