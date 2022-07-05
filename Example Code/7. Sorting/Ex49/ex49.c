#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_NUMBERS 100
#define MAX_VALUE 100

int buffer[MAX_NUMBERS];

void init_list(int*, int);
void print_list(int*, int);
void merge(int*, int, int, int);
void merge_sort(int*, int, int);

int main()
{
    int i;
    int list[MAX_NUMBERS];

    srand(time(NULL));

    init_list(list, 10);
    print_list(list, 10);
    merge_sort(list, 0, 9);
    print_list(list, 10);
}

void init_list(int *list, int n)
{
    int i;
    for(i=0; i<n; i++) {
        list[i] = rand() % MAX_VALUE + 1;
    }
}

void print_list(int *list, int n)
{
    int i;
    for(i=0; i<n; i++) {
        printf("%3d ", list[i]);
    }
    printf("\n");
}

void merge(int *list, int left, int middle, int right)
{
    int i, i_left, i_right;

    for(i=0; i<(right-left+1); i++) {
        buffer[left+i] = list[left+i];
    }

    i_left = left;
    i_right = middle + 1;
    i = left;

    while((i_left <= middle) && (i_right <= right)) {
        if(buffer[i_left] < buffer[i_right]) {
            list[i++] = buffer[i_left++];
        }
        else {
            list[i++] = buffer[i_right++];
        }
    }

    while(i_left <= middle) {
        list[i++] = buffer[i_left++];
    }

    while(i_right <= middle) {
        list[i++] = buffer[i_right++];
    }
}

void merge_sort(int *list, int left, int right)
{
    int middle;
    if(left < right) {
        middle = (left + right) / 2;
        merge_sort(list, left, middle);
        merge_sort(list, middle+1, right);

        merge(list, left, middle, right);
    }
}