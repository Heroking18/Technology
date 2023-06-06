#include <stdio.h>
#include <time.h>
/* 2nd part of Assignment 1 SD */
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

int get_difference_between_min_and_max_sum_of_k_elems(int array[], int K, int N)
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

	int min_sum = 0;
	int max_sum = 0;

	//  for loop takes the first and last K elements and sums it to variable min_sum/max_sum.
	for (int i = 0; i < K; i++)
	{
		min_sum += array[i];
		max_sum += array[((N - 1) - i)];
	}

	return max_sum - min_sum; // returns the difference between variable min_sum/max_sum.
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
	scanf("%d", &K); // INPUT size of the min/max

	int outcome = 0;

	outcome = get_difference_between_min_and_max_sum_of_k_elems(array, K, N);

	/* implement here your code e.g. like this
	 * outcome = get_difference_between_min_and_max_sum_of_k_elems( choose your own arguments );
	 */

	/* this is the (performance) test code, please don't touch it */

	t = clock() - t;
	time_taken = ((double)t) / CLOCKS_PER_SEC;
	printf("difference between minimum and maximum sum of K elements is %d\n", outcome);
#ifdef TEST_TIME
	printf("time needed was %f seconds\n", time_taken);
#endif
	return 0;
}
