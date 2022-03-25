#include <stdio.h>

#include <stdlib.h>
#include <string.h>

#define MAX_STRING 10000000
#define MAX_PATTERN 3000

char str[MAX_STRING];
char pat[MAX_PATTERN];
int match_pos[MAX_STRING]; // the position where the pattern matches.

void naive();

int main()
{
	FILE *fp;

	/* get string from string.txt */
	fp = fopen("string.txt", "r");
	fgets(str, MAX_STRING, fp);
	str[strlen(str)-1] = '\0';
	fclose(fp);
	
	/* get pattern from patter.txt */
	fp = fopen("pattern.txt", "r");
	fgets(pat, MAX_PATTERN, fp);
	pat[strlen(pat)-1] = '\0';
	fclose(fp);

	naive();
}

void naive()
{
	int i, j, start = -1, n = 0;
	int lasts = strlen(str) - 1;
	int lastp = strlen(pat) - 1;
	int endmatch;
	
	while(1) {
		start++;
		endmatch = start + lastp;
		j = 0;
		if(endmatch > lasts) {
			break;
		}
		for(; endmatch <= lasts; endmatch++, start++) {
			if(str[endmatch] == pat[lastp]) {
				for(i=start; j<lastp && str[i] == pat[j]; i++, j++) {
					;
				}
			}
			if(j == lastp) {
				match_pos[n++] = start;
				break;
			}
		}	
	}

	FILE *fp = fopen("result_naive.txt", "w");
	fprintf(fp, "%d\n", n);
	for(i=0; i<n; i++) {
		fprintf(fp, "%d ", match_pos[i]);
	}
	fclose(fp);
}
