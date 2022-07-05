#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 10000
#define INF 99999999
#define TRUE 1
#define FALSE 0

int numVertices;
int numEdges;
int cost[MAX_VERTICES][MAX_VERTICES];

int v;
int distance[MAX_VERTICES];

void createGraph();
void createGraph2();
void bellmanFord();

int main()
{
    int i, j;

    createGraph();

    for(i=0; i<numVertices; i++) {
        distance[i] = INF;
    }

    v = 0;
    bellmanFord();

    for(i=0; i<numVertices; i++) {
        if(distance[i] != INF) {
            printf("SRC: %d, DST: %d, LENGTH: %3d\n", v, i, distance[i]);
        }
        else {
            printf("SRC: %d, DST: %d, LENGTH: ---\n", v, i);
        }
    }
}

void createGraph() {
    int i, j;
    numVertices = 5;
    numEdges = 9;
    
    // cost adjacency matrix
    for(i=0; i<numVertices; i++) {
        for(j=0; j<numVertices; j++) {
            cost[i][j] = INF;
        }
    }

    cost[0][1] = 4;
    cost[0][3] = 2;
    cost[1][2] = 2;
    cost[1][3] = 3;
    cost[1][4] = 3;
    cost[3][1] = 1;
    cost[3][2] = 4;
    cost[3][4] = 5;
    cost[4][2] = -5;
}

void createGraph2() {
    int i, j;
    numVertices = 4;
    numEdges = 4;
    
    // cost adjacency matrix
    for(i=0; i<numVertices; i++) {
        for(j=0; j<numVertices; j++) {
            cost[i][j] = INF;
        }
    }

    cost[0][1] = 3;
    cost[0][3] = 5;
    cost[2][1] = -6;
    cost[3][2] = 2;
}

void bellmanFord()
{
    int i, j, k;
    for(i=0; i<numVertices; i++) {
        distance[i] = cost[v][i];
    }
    distance[v] = 0;
    for(k=2; k<numVertices; k++) {
        for(i=0; i<numVertices; i++) {
            for(j=0; j<numVertices; j++) {
                if(cost[i][j] == INF) continue;;
                //relaxation
                if(distance[j] > distance[i] + cost[i][j])
                    distance[j] = distance[i] + cost[i][j];
            }
        }
    }
}