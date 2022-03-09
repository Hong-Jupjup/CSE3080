#include <stdio.h>
#include <stdlib.h>

#define MAX 1001

int main()
{
    int input;
    int unsorted[MAX], sorted[MAX];
    int index = 0;
    int i, j, tmp;

    while(1)
    {
        printf("Enter a number: ");
        scanf("%d", &input);
        unsorted[index] = input;
        sorted[index++] = input;

        for(i=0; i<index-1; i++)
        {
            for(j=0; j<index-1-i; j++)
            {
                if(sorted[j]>sorted[j+1])
                {
                    tmp = sorted[j];
                    sorted[j] = sorted[j+1];
                    sorted[j+1] = tmp;
                }
            }
        }

        printf("unsorted: ");
        for (i=0; i<index; i++)
        {
            printf("%d ", unsorted[i]);
        }
        printf("\nsorted: ");
        for(i=0; i<index; i++)
        {
            printf("%d ", sorted[i]);
        }
        printf("\n");
    }
}
