#include <stdio.h>
#include <stdlib.h>

#define MAX_STACKS 10
#define IS_FULL(x) !x
#define IS_EMPTY(x) !x

typedef struct {
    int key;
} element;

struct stack {
    element item;
    struct stack *link;
};

typedef struct stack* stack_pointer;
stack_pointer top[MAX_STACKS];

void add(stack_pointer*, element);
element delete(stack_pointer*);
void printStack(stack_pointer);

int main()
{
    int i;
    for(i=0; i<10; i++) {
        element e;
        e.key = i + 1;
        add(&top[0], e);
        printStack(top[0]);
    }
    
    for(i=0; i<10; i++) {
        element e;
        e = delete(&top[0]);
        printStack(top[0]);
    }
}

void add(stack_pointer *top, element item)
{
    stack_pointer tmp = (stack_pointer)malloc(sizeof(struct stack));
    if(IS_FULL(tmp)) {
        fprintf(stderr, "The memory is full\n");
        exit(1);
    }
    tmp->item = item;
    tmp->link = *top;
    *top = tmp;
}

element delete(stack_pointer *top)
{
    stack_pointer tmp = *top;
    element item;
    
    if(IS_EMPTY(tmp)) {
        fprintf(stderr, "The stack is empty\n");
        exit(1);
    }
    item = tmp->item;
    *top = tmp->link;
    free(tmp);
    return item;
}

void printStack(stack_pointer top)
{
    stack_pointer tmp = top;
    while(tmp != NULL) {
        printf("%2d ", tmp->item.key);
        tmp = tmp->link;
    }
    printf("\n");
}