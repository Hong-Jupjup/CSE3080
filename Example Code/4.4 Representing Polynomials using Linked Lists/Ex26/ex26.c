#include <stdio.h>
#include <stdlib.h>

#define COMPARE(x, y) (x < y ? -1: (x > y ? 1 : 0))
#define IS_FULL(x) !x

struct poly_node {
  float coef;
  int expon;
  struct poly_node *link;
};
typedef struct poly_node* poly_pointer;
poly_pointer a, b, d;

poly_pointer padd(poly_pointer, poly_pointer);
void attach(float, int, poly_pointer*);
void print_polynomial(poly_pointer);
void erase(poly_pointer*);
void eerase(poly_pointer);

int main() {

  /* create two polynomials a and b */
  poly_pointer a, a_rear, b, b_rear, d;
  a = (poly_pointer)malloc(sizeof(struct poly_node));
  a->coef = 3;
  a->expon = 14;
  a_rear = a;
  attach(2, 8, &a_rear);
  attach(1, 0, &a_rear);

  b = (poly_pointer)malloc(sizeof(struct poly_node));
  b->coef = 8;
  b->expon = 14;
  b_rear = b;
  attach(-3, 10, &b_rear);
  attach(10, 6, &b_rear);

  print_polynomial(a);
  print_polynomial(b);
  d = padd(a, b);
  print_polynomial(d);

  erase(&a);
}

void print_polynomial(poly_pointer a) {

  poly_pointer tmp = a;
  if(tmp) {
    printf("%.1fx^%d", tmp->coef, tmp->expon);
    tmp = tmp->link;
  }
  while(tmp) {
    if(tmp->coef >= 0.0) printf("+%.1fx^%d", tmp->coef, tmp->expon);
    else printf("%.1fx^%d", tmp->coef, tmp->expon);
    tmp = tmp->link;
  }
  printf("\n");
}

poly_pointer padd(poly_pointer a, poly_pointer b) {

  /* return a polynomial which is the sum of a and b */
  poly_pointer front, rear, tmp;
  float sum;
  rear = (poly_pointer)malloc(sizeof(struct poly_node));
  if(IS_FULL(rear)) {
    fprintf(stderr, "The memory is full\n");
    exit(1);
  }
  front = rear;

  while(a && b) {
    switch(COMPARE(a->expon, b->expon)) {
      case -1:    /* a->expon < b->expon */
        attach(b->coef, b->expon, &rear);
        b = b->link;
        break;
      case 0:     /* a->expon = b->expon */
        sum = a->coef + b->coef;
        if(sum) attach(sum, a->expon, &rear);
        a = a->link;
        b = b->link;
        break;
      case 1:     /* a->expon > b->expon */
        attach(a->coef, a->expon, &rear);
        a = a->link;
    }
  }

  /* copy rest of list a then list b */
  for( ; a; a = a->link) attach(a->coef, a->expon, &rear);
  for( ; b; b = b->link) attach(b->coef, b->expon, &rear);
  rear->link = NULL;

  /* delete extra initial node */
  tmp = front;
  front = front->link;
  free(tmp);
  return front;
}

void attach(float coefficient, int exponent, poly_pointer *ptr) {
 
  /* Create a new node and attach it to the node pointed to by ptr.
     ptr is updated to point to this new node. */

  poly_pointer tmp;
  tmp = (poly_pointer)malloc(sizeof(struct poly_node));
  if(IS_FULL(tmp)) {
    fprintf(stderr, "The memory is full\n");
    exit(1);
  }
  tmp->coef = coefficient;
  tmp->expon = exponent;
  (*ptr)->link = tmp;
  *ptr = tmp;
}

void erase(poly_pointer *ptr) {
  /* erase the pointer pointed by ptr */
  poly_pointer tmp;
  while(*ptr) {
    tmp = *ptr;
    *ptr = (*ptr)->link;
    free(tmp);
  }
}


void eerase(poly_pointer ptr) {
  poly_pointer tmp;
  while(ptr) {
    tmp = ptr;
    ptr = ptr->link;
    free(tmp);
  }
}