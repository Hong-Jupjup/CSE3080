#include <stdio.h>
#include <stdlib.h>

#define MAX_TERMS 100
#define COMPARE(x, y) (x < y ? -1 : (x > y ? 1 : 0))

typedef struct {
    int coef;
    int expon;
} polynomial;

// Shared memory for storing polynomials.
polynomial terms[MAX_TERMS];
int avail = 0;

void p_add(int, int, int, int, int*, int*);
void p_print(int, int);
void attach(int, int);

int main()
{
    // starta and finisha define polynomial a
    int starta, finisha;
    int startb, finishb;
    int startc, finishc;

    // Define polynomial a(2x^1000 + 1)
    starta = avail;
    terms[avail].expon = 1000;  terms[avail].coef = 2;
    avail++;
    terms[avail].expon = 0;     terms[avail].coef = 1;
    finisha = avail;
    avail++;
    
    // Define polynomial b(x^4 + 10x^3 + 3x^2 + 1)
    startb = avail;
    terms[avail].expon = 4; terms[avail].coef = 1;
    avail++;
    terms[avail].expon = 3; terms[avail].coef = 10;
    avail++;
    terms[avail].expon = 2; terms[avail].coef = 3;
    avail++;
    terms[avail].expon = 0; terms[avail].coef = 1;
    finishb = avail;
    avail++;

    p_add(starta, finisha, startb, finishb, &startc, &finishc);

    p_print(starta, finisha);
    p_print(startb, finishb);
    p_print(startc, finishc);
}

void p_add(int starta, int finisha, int startb, int finishb, int *startc, int *finishc)
{
    float coefficient;
    *startc = avail;

    while(starta <= finisha && startb <= finishb) {
        switch(COMPARE(terms[starta].expon, terms[startb].expon)) {
            case -1:
                attach(terms[startb].coef, terms[startb].expon);
                startb++;
                break;

            case 0:
                coefficient = terms[starta].coef + terms[startb].coef;
                if(coefficient != 0) {
                    attach(coefficient, terms[starta].expon);
                }
                starta++;
                startb++;
                break;

            case 1:
                attach(terms[starta].coef, terms[starta].expon);
                starta++;
                break;
        }
    }

    // Add in remaining terms of A(X)
    for(; starta <= finisha; starta++) {
        attach(terms[starta].coef, terms[starta].expon);
    }
    for(; startb <= finishb; startb++) {
        attach(terms[startb].coef, terms[startb].expon);
    }
    *finishc = avail - 1;
}

void attach(int coefficient, int exponent)
{
    // Add a new term to the polynomial
    if(avail >= MAX_TERMS) {
        fprintf(stderr, "TOO MANY TERMS IN THE POLYNOMIAL");
        exit(1);
    }
    terms[avail].coef = coefficient;
    terms[avail].expon = exponent;
    avail++;
}

void p_print(int starta, int finisha)
{
    // No exception handling.
    int i;

    for(i=starta; i<=finisha; i++) {
        if(i == starta) {
            printf("%dx^%d", terms[i].coef, terms[i].expon);
        }
        else {
            printf(" + %dx^%d", terms[i].coef, terms[i].expon);
        }
    }
    printf("\n");
}