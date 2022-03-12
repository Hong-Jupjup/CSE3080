#include <stdio.h>
#include <stdlib.h>

#define MAX_DEGREE 101

typedef struct {
    int degree;
    int coef[MAX_DEGREE];
} polynomial;

polynomial p_add(polynomial, polynomial);
void p_print(polynomial);

int main()
{
    int i;
    polynomial p1; // p1 = 3x^2 + 2x + 4
    polynomial p2; // p2 = x^4 + 10x^3 + 3x^2 + 1
    polynomial p3; // p3 = p1 + p2

    // Initialize all coefficients to zero.
    p1.degree = -1;
    p2.degree = -1;
    for(i=0; i<MAX_DEGREE; i++)
    {
        p1.coef[i] = 0;
        p2.coef[i] = 0;
    }

    // Assign coefficients of p1 and p2.
    p1.degree = 2; p1.coef[2] = 3; p1.coef[1] = 2; p1.coef[0] = 4;
    p2.degree = 4; p2.coef[4] = 1; p2.coef[3] = 10; p2.coef[2] = 3; p2.coef[0] = 1;

    p_print(p1);
    p_print(p2);

    p3 = p_add(p1, p2);
    p_print(p3);
}

polynomial p_add(polynomial p1, polynomial p2)
{
    polynomial p3;
    int i, degree;

    if(p1.degree > p2.degree)
        degree = p1.degree;
    else
        degree = p2.degree;

    p3.degree = degree;
    
    for(i=0; i<p3.degree; i++)
    {
        p3.coef[i] = p1.coef[i] + p2.coef[i];
    }

    return p3;
}

void p_print(polynomial p)
{
    int i;

    // 첫 항 처리.
    if(p.coef[p.degree] == 1)
    {
        printf("x^%d", p.degree);
    }
    else if(p.degree == 1)
    {
        printf("%dx", p.coef[p.degree]);
    }
    else if(p.degree == 0)
    {
        printf("%d", p.coef[p.degree]);
    }
    else
    {
        printf("%dx^%d", p.coef[p.degree], p.degree);
    }

    // 나머지 항 처리.
    for(i=p.degree-1; i>=0; i--)
    {
        if(p.coef[i] == 0)
        {
            continue;
        }
        else if(p.coef[i] == 1)
        {
            if(i == 0)
            {
                printf(" + 1");
            }
            else if(i == 1)
            {
                printf(" + x");
            }
            else
            {
                printf(" + x^%d", i);
            }
        }
        else if(i == 1)
        {
            printf(" + %dx", p.coef[i]);
        }
        else if(i == 0)
        {
            printf(" + %d", p.coef[i]);
        }
        else
        {
            printf(" + %dx^%d", p.coef[i], i);
        }
    }
    printf("\n");
}