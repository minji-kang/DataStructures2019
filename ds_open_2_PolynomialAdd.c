#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)
#define COMPARE(x, y) x > y? 1: x == y? 0: -1

#define MAX_TERMS 100
typedef struct {
	float coef;
	int expon;
} polynomial;
polynomial terms[100];
int avail = 0;

void padd(int, int, int, int);
void attach(float, int);
void readPoly(FILE*);
void printPoly(int);
void insertionSort(int, int);

int main()
{
	FILE *fp;
	int startA, finishA, startB, finishB, i, j, t;
	polynomial temp;

	fp = fopen("A.txt", "r");
	startA = avail;
	readPoly(fp);
	finishA = avail - 1;
	fclose(fp);

	fp = fopen("B.txt", "r");
	startB = avail;
	readPoly(fp);
	finishB = avail - 1;
	fclose(fp);

	insertionSort(startA, finishA);
	insertionSort(startB, finishB);

	padd(startA, finishA, startB, finishB);

	printPoly(finishB + 1);

	system("pause");
	return 0;
}

void padd(int startA, int finishA, int startB, int finishB)
{
	int coefficient;
	while (startA <= finishA && startB <= finishB)
	{
		switch (COMPARE(terms[startA].expon, terms[startB].expon)) {
		case 1: attach(terms[startA].coef, terms[startA].expon);
			startA++;
			break;
		case 0: coefficient = terms[startA].coef + terms[startB].coef;
			if (coefficient) attach(coefficient, terms[startA].expon);
			startA++;
			startB++;
			break;
		case -1: attach(terms[startB].coef, terms[startB].expon);
			startB++;
		}
	}
	for (; startA <= finishA; startA++) attach(terms[startA].coef, terms[startA].expon);
	for (; startB <= finishB; startB++) attach(terms[startB].coef, terms[startB].expon);
}

void attach(float coefficient, int exponent)
{
	if (avail > 100) {
		fprintf(stderr, "Too many terms in the polynomial\n");
		exit(1);
	}
	terms[avail].coef = coefficient;
	terms[avail++].expon = exponent;
}

void readPoly(FILE *fp)
{
	while (!feof(fp))
	{
		fscanf(fp, "%f%d", &terms[avail].coef, &terms[avail].expon);
		avail++;
	}
}

void printPoly(int start)
{
	printf("(%.0f, %d)", terms[start].coef, terms[start].expon);
	for (int i = start + 1; i < avail; i++)
		printf(", (%.0f, %d)", terms[i].coef, terms[i].expon);
	printf("\n");
}

void insertionSort(int start, int finish)
{
	polynomial temp;
	int i, j, t;
	for (i = start + 1; i <= finish; i++)
	{
		temp = terms[i];
		t = terms[i].expon;
		for (j = i - 1; j >= 0 && t >= terms[j].expon; j--)
			terms[j + 1] = terms[j];
		terms[j + 1] = temp;
	}
}