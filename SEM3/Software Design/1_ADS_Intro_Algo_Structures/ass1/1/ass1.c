#include <stdio.h>
#include <time.h>
#include <stdlib.h>
/* 1st part of Assignment 1 SD */
int temp = 0;
int counter;
int a = 0;

// Function to swap elements
void swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

int FindDup(int array[], int K, int N)
{
	// Sorting the array from small big numbers.
	int i, j, min_element;
	for (i = 0; i < N - 1; i++)
	{
		min_element = i;
		for (j = i + 1; j < N; j++)
			if (array[j] < array[min_element])
				min_element = j;
		swap(&array[min_element], &array[i]);
	}

	// Find minimum number of K occurences
	for (int i = 0; i < N; i++)
	{
		counter = 0;
		for (int j = 0; j < N; j++)
		{
			if (array[i] == array[j]) // checks if array element is equal
			{
				counter++;
			}
		}
		if (counter == K)
		{
			return a = array[i];
		}
	}
	return 0;
}

int main()
{
	/* this is code to measure the time of your algorithm, please don't touch it */

	clock_t t;
	double time_taken;

	t = clock();

	/* read here the stdin to get the values of N, a1...an and K
	 * and store them
	 *
	 * for this you can use scanf e.g. like this:
	 *
	 * int n;
	 * scanf("%d", &n);
	 */

	// Variables

	int N = 0;
	scanf("%d", &N); // INPUT array size

	int array[N];
	for (int i = 0; i < N; i++)
	{
		scanf("%d", array + i); // INPUT element values
	}

	int K = 0;
	scanf("%d", &K); // INPUT number of repeated times

	int outcome = 0;

	outcome = FindDup(array, K, N);

	/* implement her your code e.g. like this
	 * outcome = get_minimum_number_with_k_occurences( choose your own arguments );
	 */

	/* this is the (performance) test code, please don't touch it */

	t = clock() - t;
	time_taken = ((double)t) / CLOCKS_PER_SEC;
	printf("minimum number of K occurences is %d\n", outcome);
#ifdef TEST_TIME
	printf("time needed was %f seconds\n", time_taken);
#endif
	return 0;
}
