#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mergesort.h"

/* Test arrays - global as required */
int *A;
int *B;
int cutoff = 0;

void test_boundary_conditions() {
    printf("=== Testing Boundary Conditions ===\n");
    
    /* Test 1: Merge at the very beginning of array */
    printf("\nTest 1: Merge at array start\n");
    A = (int*)malloc(6 * sizeof(int));
    B = (int*)malloc(6 * sizeof(int));
    
    int data1[] = {3, 5, 7, 1, 2, 4};  /* [0-2] and [3-5] */
    memcpy(A, data1, 6 * sizeof(int));
    
    printf("Before: ");
    int i;
    for (i = 0; i < 6; i++) printf("%d ", A[i]);
    printf("\n");
    
    merge(0, 2, 3, 5);
    
    printf("After:  ");
    for (i = 0; i < 6; i++) printf("%d ", A[i]);
    printf("\n");
    
    /* Check if first 6 elements are sorted */
    int sorted = 1;
    for (i = 0; i < 5; i++) {
        if (A[i] > A[i+1]) {
            sorted = 0;
            break;
        }
    }
    printf("Result: %s\n", sorted ? "PASS" : "FAIL");
    
    free(A);
    free(B);
    
    /* Test 2: Single element subarrays */
    printf("\nTest 2: Two single-element arrays\n");
    A = (int*)malloc(2 * sizeof(int));
    B = (int*)malloc(2 * sizeof(int));
    
    A[0] = 10;
    A[1] = 5;
    
    printf("Before: A[0]=%d, A[1]=%d\n", A[0], A[1]);
    merge(0, 0, 1, 1);
    printf("After:  A[0]=%d, A[1]=%d\n", A[0], A[1]);
    printf("Result: %s\n", (A[0] == 5 && A[1] == 10) ? "PASS" : "FAIL");
    
    free(A);
    free(B);
    
    /* Test 3: Already perfectly sorted */
    printf("\nTest 3: Already sorted subarrays\n");
    A = (int*)malloc(6 * sizeof(int));
    B = (int*)malloc(6 * sizeof(int));
    
    int data3[] = {1, 3, 5, 2, 4, 6};
    memcpy(A, data3, 6 * sizeof(int));
    
    printf("Before: ");
    for (i = 0; i < 6; i++) printf("%d ", A[i]);
    printf("\n");
    
    merge(0, 2, 3, 5);
    
    printf("After:  ");
    for (i = 0; i < 6; i++) printf("%d ", A[i]);
    printf("\n");
    
    /* Expected: 1, 2, 3, 4, 5, 6 */
    int expected3[] = {1, 2, 3, 4, 5, 6};
    int match = 1;
    for (i = 0; i < 6; i++) {
        if (A[i] != expected3[i]) {
            match = 0;
            break;
        }
    }
    printf("Result: %s\n", match ? "PASS" : "FAIL");
    
    free(A);
    free(B);
}

void test_memory_correctness() {
    printf("\n=== Testing Memory Usage Correctness ===\n");
    
    printf("Test: Verify B array is used as temporary storage\n");
    
    A = (int*)malloc(4 * sizeof(int));
    B = (int*)malloc(4 * sizeof(int));
    
    /* Initialize B with recognizable values */
    int i;
    for (i = 0; i < 4; i++) {
        B[i] = 9999;
    }
    
    A[0] = 3; A[1] = 7;  /* left: [0,1] */
    A[2] = 1; A[3] = 5;  /* right: [2,3] */
    
    printf("A before: ");
    for (i = 0; i < 4; i++) printf("%d ", A[i]);
    printf("\n");
    
    printf("B before: ");
    for (i = 0; i < 4; i++) printf("%d ", B[i]);
    printf("\n");
    
    merge(0, 1, 2, 3);
    
    printf("A after:  ");
    for (i = 0; i < 4; i++) printf("%d ", A[i]);
    printf("\n");
    
    printf("B after:  ");
    for (i = 0; i < 4; i++) printf("%d ", B[i]);
    printf("\n");
    
    /* A should be sorted: 1, 3, 5, 7 */
    int expected[] = {1, 3, 5, 7};
    int correct = 1;
    for (i = 0; i < 4; i++) {
        if (A[i] != expected[i]) {
            correct = 0;
            break;
        }
    }
    
    printf("Final result correct: %s\n", correct ? "YES" : "NO");
    printf("B was used as temp storage: %s\n", 
           (B[0] != 9999 || B[1] != 9999) ? "YES" : "NO");
    
    free(A);
    free(B);
}

int main() {
    printf("Comprehensive boundary and correctness testing...\n");
    test_boundary_conditions();
    test_memory_correctness();
    printf("\nAll boundary tests completed!\n");
    return 0;
}