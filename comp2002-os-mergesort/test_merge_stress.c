#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "mergesort.h"

// Global variables
int cutoff;
int *A;
int *B;

int is_sorted(int *arr, int size) {
    for (int i = 0; i < size - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            return 0;
        }
    }
    return 1;
}

void stress_test(int size, int cutoff_level, int seed) {
    printf("\nStress Test: size=%d, cutoff=%d, seed=%d\n", size, cutoff_level, seed);
    
    A = (int *)malloc(size * sizeof(int));
    B = (int *)malloc(size * sizeof(int));
    
    if (A == NULL || B == NULL) {
        printf("✗ Memory allocation failed!\n");
        return;
    }
    
    srand(seed);
    for (int i = 0; i < size; i++) {
        A[i] = rand();
    }
    
    cutoff = cutoff_level;
    
    clock_t start = clock();
    struct argument *arg = buildArgs(0, size - 1, 0);
    parallel_mergesort(arg);
    clock_t end = clock();
    
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    
    if (is_sorted(A, size)) {
        printf("✓ PASSED - Time: %.4f seconds\n", time_spent);
    } else {
        printf("✗ FAILED - Array not properly sorted\n");
    }
    
    free(A);
    free(B);
}

void compare_serial_vs_parallel(int size, int seed) {
    printf("\n=== Comparing Serial vs Parallel (size=%d) ===\n", size);
    
    // Generate test array
    srand(seed);
    int *original = (int *)malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        original[i] = rand();
    }
    
    // Test serial (cutoff 0)
    A = (int *)malloc(size * sizeof(int));
    B = (int *)malloc(size * sizeof(int));
    memcpy(A, original, size * sizeof(int));
    
    cutoff = 0;
    clock_t start = clock();
    struct argument *arg = buildArgs(0, size - 1, 0);
    parallel_mergesort(arg);
    clock_t end = clock();
    double serial_time = (double)(end - start) / CLOCKS_PER_SEC;
    
    int serial_correct = is_sorted(A, size);
    printf("Serial (cutoff=0): %.4f seconds - %s\n", 
           serial_time, serial_correct ? "✓" : "✗");
    
    free(A);
    free(B);
    
    // Test parallel cutoff levels
    int cutoff_levels[] = {1, 2, 3, 4, 5};
    for (int i = 0; i < 5; i++) {
        A = (int *)malloc(size * sizeof(int));
        B = (int *)malloc(size * sizeof(int));
        memcpy(A, original, size * sizeof(int));
        
        cutoff = cutoff_levels[i];
        start = clock();
        arg = buildArgs(0, size - 1, 0);
        parallel_mergesort(arg);
        end = clock();
        double parallel_time = (double)(end - start) / CLOCKS_PER_SEC;
        
        int parallel_correct = is_sorted(A, size);
        double speedup = serial_time / parallel_time;
        
        printf("Parallel (cutoff=%d): %.4f seconds - %s - Speedup: %.2fx\n",
               cutoff_levels[i], parallel_time, 
               parallel_correct ? "✓" : "✗", speedup);
        
        free(A);
        free(B);
    }
    
    free(original);
}

void endurance_test(int num_iterations) {
    printf("\n=== Endurance Test (%d iterations) ===\n", num_iterations);
    
    int passed = 0;
    int failed = 0;
    
    for (int i = 0; i < num_iterations; i++) {
        int size = 1000 + (rand() % 9000); // Random size 1000-10000
        int cutoff_level = rand() % 4; // Random cutoff 0-3
        int seed = rand();
        
        A = (int *)malloc(size * sizeof(int));
        B = (int *)malloc(size * sizeof(int));
        
        srand(seed);
        for (int j = 0; j < size; j++) {
            A[j] = rand() % 100000;
        }
        
        cutoff = cutoff_level;
        struct argument *arg = buildArgs(0, size - 1, 0);
        parallel_mergesort(arg);
        
        if (is_sorted(A, size)) {
            passed++;
        } else {
            failed++;
            printf("Iteration %d FAILED: size=%d, cutoff=%d, seed=%d\n", 
                   i+1, size, cutoff_level, seed);
        }
        
        free(A);
        free(B);
        
        if ((i + 1) % 10 == 0) {
            printf("Progress: %d/%d tests completed\n", i + 1, num_iterations);
        }
    }
    
    printf("\nResults: %d passed, %d failed (%.1f%% success rate)\n", 
           passed, failed, (100.0 * passed) / (passed + failed));
}

int main() {
    printf("=== STRESS TESTS FOR PARALLEL MERGE SORT ===\n");
    
    // Test 1: Large arrays with different cutoff levels
    stress_test(10000, 0, 1234);
    stress_test(10000, 2, 1234);
    stress_test(10000, 4, 1234);
    
    stress_test(50000, 0, 5678);
    stress_test(50000, 3, 5678);
    
    stress_test(100000, 0, 9999);
    stress_test(100000, 4, 9999);
    
    // Test 2: Performance comparison
    compare_serial_vs_parallel(50000, 1234);
    
    // Test 3: Endurance test
    srand(time(NULL));
    endurance_test(50);
    
    printf("\n=== ALL STRESS TESTS COMPLETED ===\n");
    
    return 0;
}