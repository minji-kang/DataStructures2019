#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#pragma warning(disable:4996)

int main()
{
	int size, i = 0;
	FILE *fp, *result;
	clock_t start;
	int t, j;
	double duration;
	int *inputData;

	result = fopen("result.txt", "w");
	fp = fopen("input_ver1.txt", "r");

	fscanf(fp, "%d", &size);

	inputData = malloc(sizeof(int)*size);

	while (i < size) {
		fscanf(fp, "%d", inputData + i);
		i++;
	}

	start = clock();

	for (i = 1; i < size; i++)
	{
		t = inputData[i];
		for (j = i - 1; j >= 0 && t < inputData[j]; j--)
		{
			inputData[j + 1] = inputData[j];
		}
		inputData[j + 1] = t;
	}

	duration = ((double)(clock() - start)) / CLOCKS_PER_SEC;
	printf("Elapsed time (sec): %f sec\n", duration);

	for (i = 0; i < size; i++) {
		fprintf(result, "%d\n", inputData[i]);
	}

	free(inputData);
	system("pause");
	return 0;
}