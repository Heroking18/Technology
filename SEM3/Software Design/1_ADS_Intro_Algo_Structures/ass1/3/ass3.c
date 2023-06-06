#include <stdio.h>
#include <time.h>
#include <string.h>
/* 3rd part of Assignment 1 SD */

/* Function to sort an array using insertion sort */
void insertion_sort(int *arr, int n)
{
	int i, key, j;
	for (i = 1; i < n; i++)
	{
		key = *(arr + i);
		j = i - 1;

		/* Move elements of arr[0..i-1], that are
		  greater than key, to one position ahead
		  of their current position */
		while (j >= 0 && *(arr + j) > key)
		{
			*(arr + j + 1) = *(arr + j);
			j = j - 1;
		}
		*(arr + j + 1) = key;
	}
}

//***********************Insertion Sort***********************//
static void alg1(int *arr, int n)
{
	/* Here comes your implemenation of the first sorting algorithm */
	insertion_sort(arr, n);
}

/* Function to sort an array using quick sort */
void quick_sort(int *arr, int first, int last)
{
	int i, j, pivot, temp;

	if (first < last)
	{
		pivot = first;
		i = first;
		j = last;

		while (i < j)
		{
			while (*(arr + i) <= *(arr + pivot) && i < last)
				i++;
			while (*(arr + j) > *(arr + pivot))
				j--;
			if (i < j)
			{
				temp = *(arr + i);
				*(arr + i) = *(arr + j);
				*(arr + j) = temp;
			}
		}

		temp = *(arr + pivot);
		*(arr + pivot) = *(arr + j);
		*(arr + j) = temp;
		quick_sort(arr, first, j - 1);
		quick_sort(arr, j + 1, last);
	}
}

//***********************Quick Sort***********************//
static void alg2(int *arr, int n)
{
	/* Here comes your implementation of the second sorting algorithm */
	quick_sort(arr, 0, n - 1);
}

// Function used in Heap Sort
void swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

// To heapify a subtree rooted with node i
// which is an index in arr[].
// n is size of heap
void heapify(int *arr, int N, int i)
{
	// Find largest among root, left child and right child

	// Initialize largest as root
	int largest = i;

	// left = 2*i + 1
	int left = 2 * i + 1;

	// right = 2*i + 2
	int right = 2 * i + 2;

	// If left child is larger than root
	if (left < N && (*(arr + left)) > (*(arr + largest)))

		largest = left;

	// If right child is larger than largest
	// so far
	if (right < N && (*(arr + right)) > (*(arr + largest)))

		largest = right;

	// Swap and continue heapifying if root is not largest
	// If largest is not root
	if (largest != i)
	{

		swap(&(*(arr + i)), &(*(arr + largest)));

		// Recursively heapify the affected
		// sub-tree
		heapify(arr, N, largest);
	}
}

/* Function to sort an array using heap sort */
void heap_sort(int *arr, int N)
{

	// Build max heap
	for (int i = N / 2 - 1; i >= 0; i--)

		heapify(arr, N, i);

	// Heap sort
	for (int i = N - 1; i >= 0; i--)
	{

		swap(&(*(arr + 0)), &(*(arr + i)));

		// Heapify root element to get highest element at
		// root again
		heapify(arr, i, 0);
	}
}

//***********************Heap Sort***********************//
static void alg3(int *arr, int n)
{
	/* Here comes your implemenation of the third sorting algorithm */
	heap_sort(arr, n);
}

static void read_in_arrays_to_sort(int *arr1, int *arr2, int *arr3, int n1, int n2, int n3)
{
	for (int i = 0; i < n1; i++)
	{
		scanf("%d", &arr1[i]);
	}
	for (int i = 0; i < n2; i++)
	{
		scanf("%d", &arr2[i]);
	}
	for (int i = 0; i < n3; i++)
	{
		scanf("%d", &arr3[i]);
	}
}

static void write_to_file(int *arr1, int *arr2, int *arr3, int n1, int n2, int n3, char *filename)
{
	FILE *f = fopen(filename, "w");
	if (f == NULL)
	{
		printf("Error in creating output file %s", filename);
		return;
	}
	for (int i = 0; i < n1; i++)
	{
		fprintf(f, "%d ", arr1[i]);
	};
	fprintf(f, "\n");
	for (int i = 0; i < n2; i++)
	{
		fprintf(f, "%d ", arr2[i]);
	}
	fprintf(f, "\n");
	for (int i = 0; i < n3; i++)
	{
		fprintf(f, "%d ", arr3[i]);
	}
	fclose(f);
}

static void execute_algorithm(int *arr, int n, void (*sort_alg)())
{
	clock_t t;
	double time_taken;
	t = clock();
	sort_alg(arr, n);
	t = clock() - t;
	time_taken = ((double)t) / CLOCKS_PER_SEC;
	printf("Time needed to sort %d elements was %f seconds\n", n, time_taken);
}

static void copy_input_arrays(int *arr1, int *arr2, int *arr3, int *sarr1, int *sarr2, int *sarr3, int n1, int n2, int n3)
{
	memcpy(arr1, sarr1, n1 * sizeof(int));
	memcpy(arr2, sarr2, n2 * sizeof(int));
	memcpy(arr3, sarr3, n3 * sizeof(int));
}

int main()
{
	/* Don't touch main */

	const int n1 = 10;
	const int n2 = 1000;
	const int n3 = 10000;
	int arr1[n1];
	int arr2[n2];
	int arr3[n3];
	int sarr1[n1];
	int sarr2[n2];
	int sarr3[n3];

	read_in_arrays_to_sort(sarr1, sarr2, sarr3, n1, n2, n3);
	copy_input_arrays(arr1, arr2, arr3, sarr1, sarr2, sarr3, n1, n2, n3);

	printf("Execution of the first alg1 algorithm\n");

	execute_algorithm(arr1, n1, alg1);
	execute_algorithm(arr2, n2, alg1);
	execute_algorithm(arr3, n3, alg1);
	write_to_file(arr1, arr2, arr3, n1, n2, n3, "out_alg1");

	copy_input_arrays(arr1, arr2, arr3, sarr1, sarr2, sarr3, n1, n2, n3);

	printf("Execution of the second alg2 algorithm\n");

	execute_algorithm(arr1, n1, alg2);
	execute_algorithm(arr2, n2, alg2);
	execute_algorithm(arr3, n3, alg2);
	write_to_file(arr1, arr2, arr3, n1, n2, n3, "out_alg2");

	copy_input_arrays(arr1, arr2, arr3, sarr1, sarr2, sarr3, n1, n2, n3);

	printf("Execution of the third alg3 algorithm\n");

	execute_algorithm(arr1, n1, alg3);
	execute_algorithm(arr2, n2, alg3);
	execute_algorithm(arr3, n3, alg3);
	write_to_file(arr1, arr2, arr3, n1, n2, n3, "out_alg3");
	return 0;
}
