#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING 10000000
#define MAX_PATTERN 3000

char str[MAX_STRING];
char pat[MAX_PATTERN];
int match_pos[MAX_STRING] = {0, }; // the position where the pattern matches.

void naive();

int main()
{
	FILE *fp_str, *fp_pat;

	/* get string from the file string.txt */
	fp_str = fopen("string.txt", "r");
	if(fp_str == NULL) { // if the file string.txt does not exist, print the error message and quit the program.
		printf("The string file does not exist.\n");
		return 0;
	}
	fgets(str, MAX_STRING, fp_str);
	str[strlen(str)-1] = '\0'; // remove the newline letter
	
	/* get pattern from the file patter.txt */
	fp_pat = fopen("pattern.txt", "r");
	if(fp_pat == NULL) { // if the file pattern.txt does not exist, print the error message and quit the program.
		printf("The pattern file does not exist.\n");
		return 0;
	}
	fgets(pat, MAX_PATTERN, fp_pat);
	pat[strlen(pat)-1] = '\0'; // remove the newline letter

	/* execute of pattern matching using the naive algorithm */
	naive();

	fclose(fp_str);
	fclose(fp_pat);
}

void naive()
{
	int i, j, start = 0;
	int n = 0;	// the number of matching patterns
	int lasts = strlen(str) - 1;
	int lastp = strlen(pat) - 1;
	int endmatch = lastp;
	
	for(i=0; endmatch <= lasts; endmatch++, start++) {
		if(str[endmatch] == pat[lastp]) {
			for(j=0, i=start; j < lastp && str[i] == pat[j]; i++, j++) {
				;
			}
		}

		if(j == lastp) {
			match_pos[n++] = start;
		}
		j = 0; // initialize j to zero in order to rewind the for-loop.
	}

	/* print the results into the file result_naive.txt */
	FILE *fp = fopen("result_naive.txt", "w");
	fprintf(fp, "%d\n", n);
	for(i=0; i<n; i++) {
		fprintf(fp, "%d ", match_pos[i]);
	}
	fclose(fp);
}
