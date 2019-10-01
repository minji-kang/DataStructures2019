#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)
#define MAX 1000
int failure[MAX];

void fail(char*);
int pmatch(char*, char*);
int main()
{
	FILE *fp;
	char string[MAX];
	char pat[MAX];
	int result;

	fp = fopen("kmp.txt", "r");
	
	if (fp == NULL) {
		fprintf(stderr, "file open error\n");
		system("pause");
		exit(1);
	}

	fgets(string, MAX, fp);
	fgets(pat, MAX, fp);

	fail(pat);
	result = pmatch(string, pat);
	printf("%d\n", result);

	system("pause");
	return 0;
}

void fail(char *pat)
{
	int i, n = strlen(pat);
	failure[0] = -1;
	for (int j = 1; j < n; j++) {
		i = failure[j - 1];
		while ((pat[j] != pat[i + 1]) && i >= 0) i = failure[i];
		if (pat[j] == pat[i + 1]) failure[j] = i + 1;
		else failure[j] = -1;
	}
}

int pmatch(char *string, char *pat)
{
	int i = 0, j = 0;
	int lens = strlen(string);
	int lenp = strlen(pat);
	while (i < lens && j < lenp) {
		if (string[i] == pat[j]) {
			i++;
			j++;
		}
		else if (j == 0) i++;
		else j = failure[j - 1] + 1;
	}
	return ((j == lenp) ? (i - lenp) : -1);
}
