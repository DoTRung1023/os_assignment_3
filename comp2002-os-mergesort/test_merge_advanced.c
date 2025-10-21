#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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

void test_different_cutoffs(int size, int seed) {
    printf("\n=== Testing Different Cutoff Levels (size=%d, seed=%d) ===\n", size, seed);
    
    srand(seed);
    
    // Generate test array once
    int *original = (int *)malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        original[i] = rand() % 10000;
    }
    
    // Test cutoff levels 0 through 5
    for (int level = 0; level <= 5; level++) {
        A = (int *)malloc(size * sizeof(int));
        B = (int *)malloc(size * sizeof(int));
        
        // Copy original array
        memcpy(A, original, size * sizeof(int));
        
        cutoff = level;
        
        clock_t start = clock();
        struct argument *arg = buildArgs(0, size - 1, 0);
        parallel_mergesort(arg);
        clock_t end = clock();
        
        double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
        
        if (is_sorted(A, size)) {
            printf("Cutoff %d: ✓ PASSED (%.4f seconds)\n", level, time_spent);
        } else {
            printf("Cutoff %d: ✗ FAILED\n", level);
        }
        
        free(A);
        free(B);
    }
    
    free(original);
}

void test_multiple_seeds(int size, int cutoff_level) {
    printf("\n=== Testing Multiple Seeds (size=%d, cutoff=%d) ===\n", size, cutoff_level);
    
    int seeds[] = {1234, 5678, 9999, 42, 12345};
    int num_seeds = 5;
    
    for (int i = 0; i < num_seeds; i++) {
        srand(seeds[i]);
        
        A = (int *)malloc(size * sizeof(int));
        B = (int *)malloc(size * sizeof(int));
        
        for (int j = 0; j < size; j++) {
            A[j] = rand() % 10000;
        }
        
        cutoff = cutoff_level;
        struct argument *arg = buildArgs(0, size - 1, 0);
        parallel_mergesort(arg);
        
        if (is_sorted(A, size)) {
            printf("Seed %d: ✓ PASSED\n", seeds[i]);
        } else {
            printf("Seed %d: ✗ FAILED\n", seeds[i]);
        }
        
        free(A);
        free(B);
    }
}

void test_special_patterns(int size) {
    printf("\n=== Testing Special Patterns (size=%d) ===\n", size);
    
    // Test 1: Ascending order
    printf("Pattern: Ascending... ");
    A = (int *)malloc(size * sizeof(int));
    B = (int *)malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) A[i] = i;
    
    cutoff = 2;
    struct argument *arg = buildArgs(0, size - 1, 0);
    parallel_mergesort(arg);
    printf("%s\n", is_sorted(A, size) ? "✓ PASSED" : "✗ FAILED");
    free(A);
    free(B);
    
    // Test 2: Descending order
    printf("Pattern: Descending... ");
    A = (int *)malloc(size * sizeof(int));
    B = (int *)malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) A[i] = size - i;
    
    arg = buildArgs(0, size - 1, 0);
    parallel_mergesort(arg);
    printf("%s\n", is_sorted(A, size) ? "✓ PASSED" : "✗ FAILED");
    free(A);
    free(B);
    
    // Test 3: Alternating high-low
    printf("Pattern: Alternating... ");
    A = (int *)malloc(size * sizeof(int));
    B = (int *)malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) A[i] = (i % 2 == 0) ? i : size - i;
    
    arg = buildArgs(0, size - 1, 0);
    parallel_mergesort(arg);
    printf("%s\n", is_sorted(A, size) ? "✓ PASSED" : "✗ FAILED");
    free(A);
    free(B);
    
    // Test 4: All same values
    printf("Pattern: All Same... ");
    A = (int *)malloc(size * sizeof(int));
    B = (int *)malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) A[i] = 42;
    
    arg = buildArgs(0, size - 1, 0);
    parallel_mergesort(arg);
    printf("%s\n", is_sorted(A, size) ? "✓ PASSED" : "✗ FAILED");
    free(A);
    free(B);
}

int main() {
    printf("=== ADVANCED MERGE SORT TESTS ===\n");
    
    // Test 1: Different cutoff levels
    test_different_cutoffs(1000, 1234);
    
    // Test 2: Multiple random seeds
    test_multiple_seeds(5000, 2);
    
    // Test 3: Special patterns
    test_special_patterns(1000);
    
    printf("\n=== ALL ADVANCED TESTS COMPLETED ===\n");
    
    return 0;
}