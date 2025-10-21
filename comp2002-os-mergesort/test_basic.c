#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mergesort.h"

// Function to check if array is sorted
int is_sorted(int *arr, int size) {
    for (int i = 0; i < size - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            return 0;
        }
    }
    return 1;
}

// Function to print array (for small arrays)
void print_array(int *arr, int size) {
    printf("[");
    for (int i = 0; i < size; i++) {
        printf("%d", arr[i]);
        if (i < size - 1) printf(", ");
    }
    printf("]\n");
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: %s <input size> <cutoff level> <seed>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);
    cutoff = atoi(argv[2]);
    int seed = atoi(argv[3]);

    // Allocate arrays
    A = (int *)malloc(n * sizeof(int));
    B = (int *)malloc(n * sizeof(int));

    if (A == NULL || B == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    // Initialize random seed
    srand(seed);

    // Generate random array
    for (int i = 0; i < n; i++) {
        A[i] = rand() % 10000;
    }

    printf("Testing with %d elements, cutoff level %d, seed %d\n", n, cutoff, seed);
    
    // Print array if small enough
    if (n <= 20) {
        printf("Before sorting: ");
        print_array(A, n);
    }

    // Start timing
    clock_t start = clock();

    // Sort using serial merge sort
    struct argument *arg = buildArgs(0, n - 1, 0);
    parallel_mergesort(arg);

    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;

    // Print array if small enough
    if (n <= 20) {
        printf("After sorting:  ");
        print_array(A, n);
    }

    // Verify sorting
    if (is_sorted(A, n)) {
        printf("✓ Sorting PASSED!\n");
        printf("Time taken: %.4f seconds\n", time_spent);
    } else {
        printf("✗ Sorting FAILED!\n");
        if (n <= 100) {
            printf("Array is not properly sorted.\n");
        }
    }

    // Clean up
    free(A);
    free(B);

    return 0;
}