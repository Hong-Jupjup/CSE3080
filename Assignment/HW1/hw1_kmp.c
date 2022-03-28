#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING 10000000
#define MAX_PATTERN 3000

char str[MAX_STRING];
char pat[MAX_PATTERN];
int failure[MAX_PATTERN];
int match_pos[MAX_STRING] = {0, }; // the position where the pattern matches.

void kmp();
void fail();

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

	/* get pattern from the file pattern.txt */
	fp_pat = fopen("pattern.txt", "r");
	if(fp_pat == NULL) { // if the file pattern.txt does not exist, print the error message and quit the program.
		printf("The pattern file does not exist.\n");
		return 0;	
	}
	fgets(pat, MAX_PATTERN, fp_pat);
	pat[strlen(pat)-1] = '\0'; // remove the newline letter

	/* execute of pattern matching using the fail and kmp algorithm */
	fail();
	kmp();

	fclose(fp_str);
	fclose(fp_pat);
}

void kmp()
{
	int i=0, j=0;
	int n = 0; // the number of matching patterns
	int lens = strlen(str);
	int lenp = strlen(pat);

	while(i < lens) {
		if(str[i] == pat[j]) {
			i++;
			j++;
		}
		else if(j == 0) {
			i++;
		}
		else {
			j = failure[j-1] + 1;
		}
		if(j == lenp) {
			match_pos[n++] = i-lenp;
			j = failure[j-1] + 1; // re-initialize j in order to rewind the while-loop.
		}
	}

	/* print the results into the file result_kmp.txt */
	FILE *fp = fopen("result_kmp.txt", "w");
	fprintf(fp, "%d\n", n);
	for(i=0; i<n; i++) {
		fprintf(fp, "%d ", match_pos[i]);
	}
	fclose(fp);
}

void fail()
{
	int i, j, lenp = strlen(pat);

	failure[0] = -1;
	for(j=1; j < lenp; j++) {
		i = failure[j-1];
		while((pat[j] != pat[i+1]) && (i >= 0)) {
			i = failure[i];
		}
		if(pat[j] == pat[i+1]) {
			failure[j] = i+1;
		}
		else {
			failure[j] = -1;
		}
	}
}
