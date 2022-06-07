#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_NUMBERS 100
#define MAX_VALUE 100

void init_list(int*, int);
void print_list(int*, int);
int partition(int*, int, int);
void quick_sort(int*, int, int);

int main()
{
    int i;
    int list[MAX_NUMBERS];

    srand(time(NULL));

    init_list(list, 10);
    print_list(list, 10);
    quick_sort(list, 0, 9);
    print_list(list, 10);
}

void init_list(int *list, int n) {
    int i;
    for(i=0; i<n; i++) {
        list[i] = rand() % MAX_VALUE + 1;
    }
}

void print_list(int *list, int n) {
    int i;
    for(i=0; i<n; i++) {
        printf("%3d ", list[i]);
    }
    printf("\n");
}

int partition(int *list, int left, int right)
{
    int i, pivot, tmp;

    pivot = left;
    for(i=left; i<right; i++) {
        if(list[i] < list[right]) {
            tmp = list[i];
            list[i] = list[pivot];
            list[pivot++] = tmp;
        }
    }

    tmp = list[right];
    list[right] = list[pivot];
    list[pivot] = tmp;
    return pivot;
}

void quick_sort(int *list, int left, int right)
{
    int pivot;

    if(right > left) {
        pivot = partition(list, left, right);

        quick_sort(list, left, pivot-1);
        quick_sort(list, pivot+1, right);
    }
}