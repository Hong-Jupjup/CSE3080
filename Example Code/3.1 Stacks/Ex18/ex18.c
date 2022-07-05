#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 100
#define INVALID_KEY -1

typedef struct {
    int key;
} element;
element stack[MAX_STACK_SIZE];
int top = -1;

void push(element);
element pop();
void stackFull();
element stackEmpty();
void printStack();

int main()
{
    int i;
    element e;

    for(i=0; i<15; i++) {
        e.key = i;
        push(e);
        printf("key %d inserted into the stack.\n", e.key);
    }

    for(i=0; i<5; i++) {
        e = pop();
        printf("key %d deleted from the stack.\n", e.key);
    }

    printStack();
}

void push(element item)
{
    if(top >= MAX_STACK_SIZE - 1) {
        stackFull();
    }
    stack[++top] = item;
}

element pop() {
    if(top == -1){
        return stackEmpty();
    }
    return stack[top--];
}

void stackFull()
{
    fprintf(stderr, "Stack is full, cannot add element.\n");
    exit(EXIT_FAILURE);
}

element stackEmpty()
{
    element e;
    e.key = INVALID_KEY;
    return e;
}

void printStack()
{
    for(int i=0; i<=top; i++) {
        printf("%d ", stack[i].key);
    }
}