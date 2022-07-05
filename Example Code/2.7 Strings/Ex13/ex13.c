/* It's an error code. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char s[] = "dog";
    char t[] = "house";
    char u[] = "rainbow";

    printf("%p: %s\n", s, s);
    printf("%p: %s\n", t, t);
    printf("%p: %s\n\n", u, u);
    strcat(s, u);
    printf("%s\n", s);
    printf("%s\n", t);
    printf("%s\n", u);
}