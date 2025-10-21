#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mergesort.h"

int is_sorted(int *arr, int size) {
    for (int i = 0; i < size - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            return 0;
        }
    }
    return 1;
}

void print_array(int *arr, int size) {
    printf("[");
    for (int i = 0; i < size; i++) {
        printf("%d", arr[i]);
        if (i < size - 1) printf(", ");
    }
    printf("]\n");
}

void run_test(const char *test_name, int *input, int size, int cutoff_level) {
    printf("\n--- %s ---\n", test_name);
    
    // Allocate arrays
    A = (int *)malloc(size * sizeof(int));
    B = (int *)malloc(size * sizeof(int));
    
    // Copy input to A
    memcpy(A, input, size * sizeof(int));
    
    printf("Before: ");
    print_array(A, size);
    
    cutoff = cutoff_level;
    struct argument *arg = buildArgs(0, size - 1, 0);
    parallel_mergesort(arg);
    
    printf("After:  ");
    print_array(A, size);
    
    if (is_sorted(A, size)) {
        printf("✓ PASSED\n");
    } else {
        printf("✗ FAILED\n");
    }
    
    free(A);
    free(B);
}

int main() {
    printf("=== BOUNDARY CONDITION TESTS ===\n");
    
    // Test 1: Single element
    int test1[] = {42};
    run_test("Single Element", test1, 1, 0);
    
    // Test 2: Two elements (unsorted)
    int test2[] = {5, 3};
    run_test("Two Elements (Unsorted)", test2, 2, 0);
    
    // Test 3: Two elements (sorted)
    int test3[] = {3, 5};
    run_test("Two Elements (Sorted)", test3, 2, 0);
    
    // Test 4: Already sorted array
    int test4[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    run_test("Already Sorted", test4, 10, 0);
    
    // Test 5: Reverse sorted array
    int test5[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    run_test("Reverse Sorted", test5, 10, 0);
    
    // Test 6: All same elements
    int test6[] = {5, 5, 5, 5, 5, 5, 5, 5};
    run_test("All Same Elements", test6, 8, 0);
    
    // Test 7: Array with duplicates
    int test7[] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3};
    run_test("Array with Duplicates", test7, 10, 0);
    
    // Test 8: Array with negative numbers
    int test8[] = {-5, 3, -1, 7, -9, 2, -3, 8};
    run_test("Negative Numbers", test8, 8, 0);
    
    // Test 9: Small array with parallel (cutoff 1)
    int test9[] = {9, 3, 7, 1, 5, 2, 8, 4, 6};
    run_test("Small Array (Parallel cutoff=1)", test9, 9, 1);
    
    // Test 10: Small array with parallel (cutoff 2)
    int test10[] = {16, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15};
    run_test("16 Elements (Parallel cutoff=2)", test10, 16, 2);
    
    printf("\n=== ALL BOUNDARY TESTS COMPLETED ===\n");
    
    return 0;
}