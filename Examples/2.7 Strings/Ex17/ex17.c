#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STIRNG_SIZE 100
#define MAX_PATTERN_SIZE 100

int pmatch(char*, char*);
void fail(char*);

int failure[MAX_PATTERN_SIZE];
char string[MAX_STIRNG_SIZE];
char pattern[MAX_PATTERN_SIZE];

int main()
{
    int rv, i;

    strcpy(string, "ababcabcabababdabaabaabacabaababaaabaabaacaaba");
    strcpy(pattern, "abaababaaaba");
    
    fail(pattern);

    for(i=0; i<strlen(pattern); i++) {
        printf("%d ", failure[i]);
    }
    printf("\n");

    rv = pmatch(string, pattern);
    printf("rv: %d\n", rv);
}

int pmatch(char *string, char *pattern)
{
    int i=0, j=0;
    int lens = strlen(string);
    int lenp = strlen(pattern);

    while(i<lens && j<lenp) {
        if(string[i] == pattern[j]) {
            i++; j++;
        }
        else if(j==0) {
            i++;
        }
        else {
            j = failure[j-1] + 1;
        }
    }
    return ((j == lenp) ? (i-lenp) : -1);
}

void fail(char *pattern)
{
    int i, j, lenp = strlen(pattern);
    
    failure[0] = -1;
    for(j=1; j<lenp; j++) {
        i = failure[j-1];
        while((pattern[j] != pattern[i+1]) && (i >= 0)) {
            i = failure[i];
        }
        if(pattern[j] == pattern[i+1]) {
            failure[j] = i + 1;
        }
        else {
            failure[j] = -1;
        }
    }
}