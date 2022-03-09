#include <stdio.h>
#include <stdlib.h>

#define MAX 101

int sum(int*, int);

int main()
{
    int i;
    int input[MAX];
    int answer;

    for(i=0; i<MAX; i++)
    {
        input[i] = i;
    }

    printf("value of input: %p\n", input);
    printf("address of input[0]: %p\n", &input[0]);
    printf("address of input[1]: %p\n", &input[1]);
    printf("address of input[3]: %p\n", &input[3]);

    printf("value of the item in address input: %d\n", *input);
    printf("value of the item in adedress input[1]: %d\n", *(input+1));
    printf("value of input+1: %p\n", input+1);

    answer = sum(input, MAX);
    printf("sum of the list: %d\n", answer);
}

int sum(int *list, int n)
{
    int i, tmpsum = 0;

    for(i=0; i<n; i++)
    {
        tmpsum += list[i];
    }

    printf("address of the list: %p\n", list);

    return tmpsum;
}