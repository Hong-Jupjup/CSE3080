#include <stdio.h>
#include <stdlib.h>

#define IS_FULL(x) !x
#define IS_EMPTY(x) !x
#define MAX_QUEUES 10

typedef struct {
    int key;
} element;

struct queue {
    element item;
    struct queue *link;
};
typedef struct queue *queue_pointer;

queue_pointer front[MAX_QUEUES], rear[MAX_QUEUES];

void addq(queue_pointer *front, queue_pointer *rear, element item);
element deleteq(queue_pointer *front);
void printQueue(queue_pointer front);

int main()
{
    int i;

    for(i=0; i<10; i++) {
        element e;
        e.key = i+1;
        addq(&front[0], &rear[0], e);
        printQueue(front[0]);
    }

    for(i=0; i<10; i++) {
        element e;
        e = deleteq(&front[0]);
        printQueue(front[0]);
    }
}

void addq(queue_pointer *front, queue_pointer *rear, element item)
{
    queue_pointer tmp = (queue_pointer)malloc(sizeof(struct queue));
    if(IS_FULL(tmp)) {
        fprintf(stderr, "The memory is full\n");
        exit(1);
    }
    tmp->item = item;
    tmp->link = NULL;
    if(*front) {
        (*rear)->link = tmp;
    }
    else
        *front = tmp;
    *rear = tmp;
}

element deleteq(queue_pointer *front)
{
    queue_pointer tmp = *front;
    element item;

    if(IS_EMPTY(tmp)) {
        fprintf(stderr, "The memeory is empty\n");
        exit(1);
    }
    item = tmp->item;
    *front = tmp->link;
    free(tmp);
    return item;
}

void printQueue(queue_pointer front)
{
    queue_pointer tmp = front;
    while(tmp != NULL) {
        printf("%2d ", tmp->item.key);
        tmp = tmp->link;
    }
    printf("\n");
}