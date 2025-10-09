/**
 * This file implements parallel mergesort.
 */
 
#include <stdio.h>
#include <string.h> /* for memcpy */
#include <stdlib.h> /* for malloc */
#include "mergesort.h"

/* this function will be called by mergesort() and also by parallel_mergesort(). */
void merge(int leftstart, int leftend, int rightstart, int rightend){
    int leftSize = leftend - leftstart + 1;
    int rightSize = rightend - rightstart + 1;
    int totalSize = leftSize + rightSize;
    
    // Copy both subarrays to temporary array B
    memcpy(B + leftstart, A + leftstart, totalSize * sizeof(int));
    
    int left = leftstart;      // index for left subarray in B
    int right = rightstart;     // index for right subarray in B
    int current = leftstart;    // index for merged array in A
    
    // Merge the two subarrays back into A
    while (left <= leftend && right <= rightend) {
        if (B[left] <= B[right]) {
            A[current] = B[left];
            left++;
        } else {
            A[current] = B[right];
            right++;
        }
        current++;
    }
    
    // Copy remaining elements from left subarray, if any
    while (left <= leftend) {
        A[current] = B[left];
        left++;
        current++;
    }
    
    // Copy remaining elements from right subarray, if any
    while (right <= rightend) {
        A[current] = B[right];
        right++;
        current++;
    }
}

/* this function will be called by parallel_mergesort() as its base case. */
void my_mergesort(int left, int right){
}

/* this function will be called by the testing program. */
void * parallel_mergesort(void *arg){
		return NULL;
}

/* we build the argument for the parallel_mergesort function. */
struct argument * buildArgs(int left, int right, int level){
		return NULL;
}

