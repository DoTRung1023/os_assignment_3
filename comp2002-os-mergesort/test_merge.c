#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mergesort.h"

// Global variables
int cutoff;
int *A;
int *B;

void print_array(int *arr, int start, int end, const char* name) {
    printf("%s[%d-%d]: ", name, start, end);
    for (int i = start; i <= end; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void test_merge_case(const char* test_name, int* left_data, int left_size, 
                     int* right_data, int right_size, int* expected) {
    printf("\n=== Testing %s ===\n", test_name);
    
    int total_size = left_size + right_size;
    
    /* Allocate the global arrays A and B */
    A = (int*)malloc(total_size * sizeof(int));
    B = (int*)malloc(total_size * sizeof(int));
    
    /* Copy test data into A (left subarray then right subarray) */
    memcpy(A, left_data, left_size * sizeof(int));
    memcpy(A + left_size, right_data, right_size * sizeof(int));
    
    printf("Before merge:\n");
    print_array(A, 0, left_size - 1, "Left ");
    print_array(A, left_size, total_size - 1, "Right");
    
    /* Call merge function */
    merge(0, left_size - 1, left_size, total_size - 1);
    
    printf("After merge:\n");
    print_array(A, 0, total_size - 1, "Result");
    print_array(expected, 0, total_size - 1, "Expected");
    
    /* Check if result matches expected */
    int success = 1;
    for (int i = 0; i < total_size; i++) {
        if (A[i] != expected[i]) {
            success = 0;
            break;
        }
    }
    
    printf("Result: %s\n", success ? "PASS" : "FAIL");
    
    free(A);
    free(B);
}

int main() {
    /* Set the global cutoff value (not used in this test but required) */
    cutoff = 0;
    
    printf("Testing merge function...\n");
    
    /* Test Case 1: Basic merge of two sorted arrays */
    int left1[] = {1, 3, 5};
    int right1[] = {2, 4, 6};
    int expected1[] = {1, 2, 3, 4, 5, 6};
    test_merge_case("Basic merge", left1, 3, right1, 3, expected1);
    
    /* Test Case 2: Left array all smaller */
    int left2[] = {1, 2, 3};
    int right2[] = {7, 8, 9};
    int expected2[] = {1, 2, 3, 7, 8, 9};
    test_merge_case("Left all smaller", left2, 3, right2, 3, expected2);
    
    /* Test Case 3: Right array all smaller */
    int left3[] = {7, 8, 9};
    int right3[] = {1, 2, 3};
    int expected3[] = {1, 2, 3, 7, 8, 9};
    test_merge_case("Right all smaller", left3, 3, right3, 3, expected3);
    
    /* Test Case 4: Arrays with duplicates */
    int left4[] = {1, 3, 5, 5};
    int right4[] = {2, 3, 4};
    int expected4[] = {1, 2, 3, 3, 4, 5, 5};
    test_merge_case("With duplicates", left4, 4, right4, 3, expected4);
    
    /* Test Case 5: Single element arrays */
    int left5[] = {5};
    int right5[] = {3};
    int expected5[] = {3, 5};
    test_merge_case("Single elements", left5, 1, right5, 1, expected5);
    
    /* Test Case 6: Different sizes */
    int left6[] = {1, 4, 7, 10};
    int right6[] = {2, 3};
    int expected6[] = {1, 2, 3, 4, 7, 10};
    test_merge_case("Different sizes", left6, 4, right6, 2, expected6);
    
    printf("\nAll tests completed!\n");
    return 0;
}