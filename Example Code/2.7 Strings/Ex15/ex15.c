#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char pat[] = "world";
    char str[] = "Hello world I am a student.";
    char *t = strstr(str, pat);

    if(t) {
        printf("The string returned by strstr is '%s'\n", t);
    }
    else {
        printf("The pattern was not found with strstr.\n");
    }
}