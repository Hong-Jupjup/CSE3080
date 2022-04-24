#include <stdio.h>
#include <string.h>

char aaa;
enum days {Mon, Tue, Wed, Thu};

char bbb[2][3] = {'a', '\0'};

union utag {
    char bb; float kk; char *c;
} haha;

struct aa {
    float j; char aaa; enum days bb; char bbb; union utag kk;
} lala, test[6][10];

int main()
{
    printf("%d\n", &(test[0][0]));
    printf("%d\n", &(test[4][11]));
    printf("%d\n", &(test[4][11]) + 1);
}