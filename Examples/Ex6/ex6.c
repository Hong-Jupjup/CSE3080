#include <stdio.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

typedef struct {
    char name[10];
    int age;
    float salary;
} humanBeing;

int human_equal(humanBeing, humanBeing);

int main()
{
    humanBeing p1, p2;

    strcpy(p1.name, "James");
    p1.age = 10;
    p1.salary = 35000;

    strcpy(p2.name, "James");
    p2.age = 10;
    p2.salary = 35000;

    if(human_equal(p1, p2))
        printf("The two human beings are the same.\n");
    else
        printf("The two human beings are NOT the same.\n");
}

int human_equal(humanBeing p1, humanBeing p2)
{
    if(strcmp(p1.name, p2.name) != 0)
        return FALSE;

    if(p1.age != p2.age)
        return FALSE;
    
    if(p1.salary != p2.salary)
        return FALSE;

    return TRUE;
}