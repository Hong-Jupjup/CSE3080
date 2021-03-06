#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i, n, m, *data;
    
    printf("How many integers do you want to generate? ");
    scanf("%d", &n);
    
    data = malloc(n * sizeof(int));

    for(i=0; i<n; i++) {
        data[i] = rand();
    }

    printf("How many integers do you want to generate additionally? ");
    scanf("%d", &m);

    data = realloc(data, (n+m) * sizeof(int));
    
    for(i; i<n+m; i++) {
        data[i] = rand();
    }

    for(i=0; i<n+m; i++) {
        printf("%3d: %8d\n", i+1, data[i]);
    }

    free(data);
}