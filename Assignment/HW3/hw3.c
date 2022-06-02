#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_VERTICES 10000
#define MAX_EDGES 50000000
#define HEAP_FULL(n) (n == MAX_EDGES - 1)
#define HEAP_EMPTY(n) (!n)
#define TRUE 1
#define FALSE 0

typedef struct {
	int u, v, w; // two vertices and weight
} element;


element min_heap[MAX_EDGES], spanning_tree[MAX_EDGES];
int Vertices, Edges; // Number of Vertices and Edges
int min_n = 0, tree_n = 0;

void insert_heap(element heap[], element, int*);
element delete_heap(element heap[], int*);
void print_min_heap(element heap[], int n, FILE *fp);

/* Union & Find fuction to determine that the spanning tree has a cycle. */
void initialize(int arr[]);
int getParent(int i, int arr[]);
int find(int arr[], int u, int v);
void f_union(int arr[], int u, int v);

int main(int argc, char *argv[])
{
	clock_t start, end;
	start = clock();

	/* Error message when argc is not 2 */
	if(argc != 2) {
		fprintf(stderr, "usage: /hw3 input_filename\n");
		exit(0);
	}

	FILE *fp1 = fopen(argv[1], "r");

	/* Error message when the file does not exist */
	if(fp1 == NULL) {
		fprintf(stderr, "The input file does not exist.\n");
		exit(0);
	}

	/* Read contents from the input file 
	   and put them into min_heap*/
	fscanf(fp1, "%d", &Vertices);
	fscanf(fp1, "%d", &Edges);

	int *arr = (int*)malloc(sizeof(int)*Vertices);
	initialize(arr);

	for(int i=0; i<Edges; i++) {
		element item;
		fscanf(fp1, "%d%d%d", &item.u, &item.v, &item.w);
		insert_heap(min_heap, item, &min_n);
	}
	fclose(fp1);

	/* Kruskal's Algorithm */
	while((tree_n <= Vertices-1) && (min_n > 0)) {
		element temp = delete_heap(min_heap, &min_n);
		if(find(arr, temp.u, temp.v) == 0) {
			insert_heap(spanning_tree, temp, &tree_n);
		}
		f_union(arr, temp.u, temp.v);
	}
	
	/* Print the spanning tree
	   and the weight 
	   and whether the spanning tree is connected or not*/
	int weight = 0;
	int status = 1;
	for(int i=1; i<=tree_n; i++) {
		weight += spanning_tree[i].w;
	}
	
	int *conn_arr = (int*)malloc(sizeof(int)*Vertices);
	for(int i=0; i<Vertices; i++) {
		conn_arr[i] = 0;
	}
	for(int i=0; i<Vertices; i++) {
		conn_arr[spanning_tree[i].u]++;
		conn_arr[spanning_tree[i].v]++;
	}
	for(int i=0; i<Vertices; i++) {
		if(conn_arr[i] == 0) {
			status = 0;
			break;
		}
	}

	FILE *fp2 = fopen("hw3_result.txt", "w");
	print_min_heap(spanning_tree, tree_n, fp2);
	fprintf(fp2, "%d\n", weight);
	if(status == 0)
		fprintf(fp2, "DISCONNECTED\n");
	else
		fprintf(fp2, "CONNECTED\n");
	fclose(fp2);

	end = clock();
	printf("output written to hw3_result.txt.\n");
	printf("running time: %lf seconds\n", ((double)(end - start) / CLOCKS_PER_SEC));
}

void insert_heap(element heap[], element item, int *n)
{
	int i;
	if(HEAP_FULL(*n)) {
		fprintf(stderr, "The heap is full.\n");
		exit(1);
	}

	i = ++(*n);
	while((i != 1) && (item.w < heap[i/2].w)) {
		heap[i] = heap[i/2];
		i /= 2;
	}
	heap[i] = item;
}

element delete_heap(element heap[], int *n)
{
	int parent, child;
	element item, temp;

	if(HEAP_EMPTY(*n)) {
		fprintf(stderr, "The heap is empty.\n");
		exit(1);
	}

	item = heap[1];

	temp = heap[(*n)--];
	parent = 1;
	child = 2;

	while(child <= *n) {
		if((child < *n) && (heap[child].w > heap[child+1].w))
			child++;
		if(temp.w <= heap[child].w)
			break;

		heap[parent] = heap[child];
		parent = child;
		child *= 2;
	}
	heap[parent] = temp;
	return item;
}

void print_min_heap(element heap[], int n, FILE *fp)
{
	element item;

	while(n) {
		item = delete_heap(heap, &n);
		fprintf(fp, "%d %d %d\n", item.u, item.v, item.w);
	}
}

void initialize(int arr[])
{
	for(int i=0; i<Vertices; i++)
		arr[i] = i;
}

int getParent(int i, int arr[])
{
	if(i == arr[i])
		return arr[i];
	else
		return arr[i] = getParent(arr[i], arr);
}

int find(int arr[], int u, int v)
{
	int i = getParent(u, arr);
	int j = getParent(v, arr);

	if(i == j)
		return TRUE;
	else
		return FALSE;
}

void f_union(int arr[], int u, int v)
{
	int i = getParent(u, arr);
	int j = getParent(v, arr);

	if(i < j)
		arr[j] = arr[i];
	else
		arr[i] = arr[j];
}
