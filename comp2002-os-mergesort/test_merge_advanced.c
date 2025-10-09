#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mergesort.h"

/* Test arrays - need to be global as required by mergesort.h */
int *A;
int *B;
int cutoff = 0; /* Not used in this test but required by header */

void test_arbitrary_positions() {
    printf("\n=== Testing merge with arbitrary array positions ===\n");
    
    /* Create a larger array where we'll merge subarrays in the middle */
    int size = 10;
    A = (int*)malloc(size * sizeof(int));
    B = (int*)malloc(size * sizeof(int));
    
    /* Initialize array: [0, 1, 3, 5, 2, 4, 6, 7, 8, 9] */
    /*                    unused  left   right  unused  */
    /*                   [0,1]   [2,4]  [5,7]   [8,9]   */
    int data[] = {0, 1, 1, 3, 5, 2, 4, 6, 7, 8};
    memcpy(A, data, size * sizeof(int));
    
    printf("Original array: ");
    int i;
    for (i = 0; i < size; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");
    
    printf("Merging A[2-4] with A[5-7]\n");
    printf("Left subarray A[2-4]: ");
    for (i = 2; i <= 4; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");
    
    printf("Right subarray A[5-7]: ");
    for (i = 5; i <= 7; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");
    
    /* Merge subarrays at positions [2-4] and [5-7] */
    merge(2, 4, 5, 7);
    
    printf("After merge: ");
    for (i = 0; i < size; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");
    
    /* Check that positions 2-7 are sorted */
    printf("Merged section A[2-7]: ");
    for (i = 2; i <= 7; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");
    
    /* Verify it's sorted */
    int sorted = 1;
    for (i = 2; i < 7; i++) {
        if (A[i] > A[i+1]) {
            sorted = 0;
            break;
        }
    }
    
    printf("Merged section is sorted: %s\n", sorted ? "YES" : "NO");
    printf("Expected merged section: 1 2 3 4 5 6\n");
    
    free(A);
    free(B);
}

void test_edge_cases() {
    printf("\n=== Testing edge cases ===\n");
    
    /* Test case: Adjacent single elements */
    printf("\nTest: Adjacent single elements\n");
    A = (int*)malloc(2 * sizeof(int));
    B = (int*)malloc(2 * sizeof(int));
    
    A[0] = 5;
    A[1] = 3;
    
    printf("Before: A[0]=%d, A[1]=%d\n", A[0], A[1]);
    merge(0, 0, 1, 1);  /* merge A[0] with A[1] */
    printf("After:  A[0]=%d, A[1]=%d\n", A[0], A[1]);
    printf("Result: %s\n", (A[0] == 3 && A[1] == 5) ? "PASS" : "FAIL");
    
    free(A);
    free(B);
    
    /* Test case: Same values */
    printf("\nTest: Arrays with identical values\n");
    A = (int*)malloc(4 * sizeof(int));
    B = (int*)malloc(4 * sizeof(int));
    
    A[0] = 5; A[1] = 5;  /* left subarray */
    A[2] = 5; A[3] = 5;  /* right subarray */
    
    printf("Before: ");
    int i;
    for (i = 0; i < 4; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");
    
    merge(0, 1, 2, 3);
    
    printf("After:  ");
    for (i = 0; i < 4; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");
    
    int all_five = 1;
    for (i = 0; i < 4; i++) {
        if (A[i] != 5) {
            all_five = 0;
            break;
        }
    }
    printf("Result: %s\n", all_five ? "PASS" : "FAIL");
    
    free(A);
    free(B);
}

int main() {
    printf("Advanced testing of merge function...\n");
    
    test_arbitrary_positions();
    test_edge_cases();
    
    printf("\nAll advanced tests completed!\n");
    return 0;
}