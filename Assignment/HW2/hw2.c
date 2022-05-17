#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_ELEMENTS 1000000
#define HEAP_FULL(n) (n == MAX_ELEMENTS - 1)
#define HEAP_EMPTY(n) (!n)

typedef struct {
	int key;
} element;

element max_heap[MAX_ELEMENTS];
element min_heap[MAX_ELEMENTS];
int max_n = 0;
int min_n = 0;

void insert_max_heap(element, int*);
element delete_max_heap(element heap[], int*);
void print_max_heap(element heap[], int n, FILE *fp);
void insert_min_heap(element, int*);
element delete_min_heap(element heap[], int*);
void print_min_heap(element heap[], int n, FILE *fp);


int main(int argc, char *argv[])
{
	clock_t start, end;
	
	start = clock();

	/* Error message when argc is not 2 */
	if(argc != 2) {
		fprintf(stderr, "usage: ./hw2 input_filename\n");
		exit(0);
	}

	element item;
	FILE *fp1 = fopen(argv[1], "r");
	FILE *fp2 = fopen("hw2_result.txt", "w");

	/* Error message when the file does not exist */
	if(fp1 == NULL) {
		fprintf(stderr, "The input file does not exist.\n");
		exit(0);
	}

	while(1) {
		element item;
		char command[10]; /* INSERT or ASCEND or DESCEND */
		int insert_num; /* When the command is INSERT */
		element heap_copy[MAX_ELEMENTS];
		int n_copy;

		/* Read the command */
		if(fscanf(fp1, "%s", command) == EOF)
			break;
		
		/* Command INSERT */
		if(!strcmp(command, "INSERT")) {
			fscanf(fp1, "%d", &insert_num);
			item.key = insert_num;
			insert_max_heap(item, &max_n);
			insert_min_heap(item, &min_n);
		}

		/* Command ASCEND */
		else if(!strcmp(command, "ASCEND")) {
			for(int i=1; i <= min_n; i++) {
				heap_copy[i] = min_heap[i];
			}
			n_copy = min_n;
			print_min_heap(heap_copy, n_copy, fp2);
		}

		/* Command DESCEND */
		else if(!strcmp(command, "DESCEND")) {
			for(int i=1; i <= max_n; i++) {
				heap_copy[i] = max_heap[i];
			}
			n_copy = max_n;
			print_max_heap(heap_copy, n_copy, fp2);
		}
	}

	fclose(fp1);
	fclose(fp2);

	end = clock();
	printf("output written to hw2_result.txt.\n");
	printf("running time: %lf seconds\n", ((double)(end - start) / CLOCKS_PER_SEC));
}

void insert_max_heap(element item, int *n)
{
	/* Insert item into a max heap of current size *n */
	int i;
	if(HEAP_FULL(*n)) {
		fprintf(stderr, "The heap is full.\n");
		exit(1);
	}

	i = ++(*n);
	while((i != 1) && (item.key > max_heap[i/2].key)) {
		max_heap[i] = max_heap[i/2];
		i /= 2;
	}
	max_heap[i] = item;
}

element delete_max_heap(element heap[], int *n)
{
	/* Delete element with the highest key from the heap */
	int parent, child;
	element item, temp;

	if(HEAP_EMPTY(*n)) {
		fprintf(stderr, "The heap is empty.\n");
		exit(1);
	}

	/* Save value of the element with the largest key */
	item = heap[1];

	/* Use the last element in the heap to adjust heap */
	temp = heap[(*n)--];
	parent = 1;
	child = 2;

	while(child <= *n) {
		/* Find the larger child of the current parent */
		if((child < *n) && (heap[child].key < heap[child+1].key))
			child++;
		if(temp.key >= heap[child].key)
			break;

		/* Move to the next lower level */
		heap[parent] = heap[child];
		parent = child;
		child *= 2;
	}
	heap[parent] = temp;
	return item;
}

void insert_min_heap(element item, int *n)
{
	/* Insert item into a min heap of current size *n */
	int i;
	if(HEAP_FULL(*n)) {
		fprintf(stderr, "The heap is full.\n");
		exit(1);
	}

	i = ++(*n);
	while((i != 1) && (item.key < min_heap[i/2].key)) {
		min_heap[i] = min_heap[i/2];
		i /= 2;
	}
	min_heap[i] = item;
}

element delete_min_heap(element heap[], int *n)
{
	/* Delete element with the highest key from the heap */
	int parent, child;
	element item, temp;

	if(HEAP_EMPTY(*n)) {
		fprintf(stderr, "The heap is empty.\n");
		exit(1);
	}

	/* Save value of the element with the largest key */
	item = heap[1];

	/* Use the last element in the heap to adjust heap */
	temp = heap[(*n)--];
	parent = 1;
	child = 2;

	while(child <= *n) {
		/* Find the larger child of the current parent */
		if((child < *n) && (heap[child].key > heap[child+1].key))
			child++;
		if(temp.key <= heap[child].key)
			break;

		/* Move to the next lower level */
		heap[parent] = heap[child];
		parent = child;
		child *= 2;
	}
	heap[parent] = temp;
	return item;
}

void print_max_heap(element heap[], int n, FILE *fp)
{
	element item;

	while(n) {
		item = delete_max_heap(heap, &n);
		fprintf(fp, "%d ", item.key);
	}
	fprintf(fp, "\n");
}

void print_min_heap(element heap[], int n, FILE *fp)
{
	element item;

	while(n) {
		item = delete_min_heap(heap, &n);
		fprintf(fp, "%d ", item.key);
	}
	fprintf(fp, "\n");
}
