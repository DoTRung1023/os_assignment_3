#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "mergesort.h"

/* Test arrays - need to be global as required by mergesort.h */
int *A;
int *B;
int cutoff = 0;

int is_sorted(int *arr, int start, int end) {
    int i;
    for (i = start; i < end; i++) {
        if (arr[i] > arr[i+1]) {
            return 0;
        }
    }
    return 1;
}

void stress_test_merge() {
    printf("=== Stress Test: Large Arrays ===\n");
    
    int sizes[] = {100, 1000, 10000};
    int num_tests = sizeof(sizes) / sizeof(sizes[0]);
    int test;
    
    srand(time(NULL));
    
    for (test = 0; test < num_tests; test++) {
        int size = sizes[test];
        int left_size = size / 2;
        int right_size = size - left_size;
        
        printf("\nTesting with %d elements (%d left, %d right)...\n", 
               size, left_size, right_size);
        
        A = (int*)malloc(size * sizeof(int));
        B = (int*)malloc(size * sizeof(int));
        
        /* Generate sorted left subarray */
        int i;
        for (i = 0; i < left_size; i++) {
            A[i] = rand() % 1000;
        }
        
        /* Sort left subarray using simple bubble sort */
        int j;
        for (i = 0; i < left_size - 1; i++) {
            for (j = 0; j < left_size - 1 - i; j++) {
                if (A[j] > A[j+1]) {
                    int temp = A[j];
                    A[j] = A[j+1];
                    A[j+1] = temp;
                }
            }
        }
        
        /* Generate sorted right subarray */
        for (i = left_size; i < size; i++) {
            A[i] = rand() % 1000;
        }
        
        /* Sort right subarray */
        for (i = left_size; i < size - 1; i++) {
            for (j = left_size; j < size - 1 - (i - left_size); j++) {
                if (A[j] > A[j+1]) {
                    int temp = A[j];
                    A[j] = A[j+1];
                    A[j+1] = temp;
                }
            }
        }
        
        printf("Left subarray is sorted: %s\n", 
               is_sorted(A, 0, left_size - 1) ? "YES" : "NO");
        printf("Right subarray is sorted: %s\n", 
               is_sorted(A, left_size, size - 1) ? "YES" : "NO");
        
        /* Test merge function */
        clock_t start_time = clock();
        merge(0, left_size - 1, left_size, size - 1);
        clock_t end_time = clock();
        
        double cpu_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
        
        int result_sorted = is_sorted(A, 0, size - 1);
        printf("Merged array is sorted: %s\n", result_sorted ? "YES" : "NO");
        printf("Time taken: %.6f seconds\n", cpu_time);
        printf("Result: %s\n", result_sorted ? "PASS ✓" : "FAIL ✗");
        
        if (!result_sorted && size <= 20) {
            printf("Debug - Final array: ");
            for (i = 0; i < size; i++) {
                printf("%d ", A[i]);
            }
            printf("\n");
        }
        
        free(A);
        free(B);
    }
}

int main() {
    printf("Stress testing merge function...\n");
    stress_test_merge();
    printf("\nStress test completed!\n");
    return 0;
}