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
    /* base case: zero or one element */
    if (left >= right) {
        return;
    }

    /* find middle index; use left + (right-left)/2 to avoid overflow */
    int mid = left + (right - left) / 2;

    /* recursively sort left half and right half */
    my_mergesort(left, mid);
    my_mergesort(mid + 1, right);

    /* merge the two sorted halves back into A using the helper merge() */
    merge(left, mid, mid + 1, right);
}

/* this function will be called by the testing program. */
void * parallel_mergesort(void *arg){
	struct argument *args = (struct argument *) arg;
	int left = args->left;
	int right = args->right;
	int level = args->level;
	int mid;
	struct argument *leftArg = NULL;
	struct argument *rightArg = NULL;
	pthread_t tLeft, tRight;
	int rcLeft = 0;
	int rcRight = 0;
	int jr;

	/* base case 1: empty or single-element range is already sorted */
	if (left >= right) {
		return NULL;
	}

	/* base case 2: reached cutoff level, switch to serial mergesort */
	if (level >= cutoff) {
		my_mergesort(left, right);
		return NULL;
	}

	/* recursive case: split, sort halves in parallel, then merge */
	mid = left + (right - left) / 2;
	leftArg = buildArgs(left, mid, level + 1);
	rightArg = buildArgs(mid + 1, right, level + 1);

	rcLeft = pthread_create(&tLeft, NULL, parallel_mergesort, (void *) leftArg);
	rcRight = pthread_create(&tRight, NULL, parallel_mergesort, (void *) rightArg);

	/* If a thread fails to start, fall back to serial for that half. */
	if (rcLeft != 0) {
		fprintf(stderr, "pthread_create failed for left half: %d\n", rcLeft);
		my_mergesort(left, mid);
		/* since left thread did not start, we must free its arg here */
		free(leftArg);
		leftArg = NULL;
	}
	if (rcRight != 0) {
		fprintf(stderr, "pthread_create failed for right half: %d\n", rcRight);
		my_mergesort(mid + 1, right);
		/* since right thread did not start, we must free its arg here */
		free(rightArg);
		rightArg = NULL;
	}

	/* Wait for any successfully-started child threads. */
	if (rcLeft == 0) {
		jr = pthread_join(tLeft, NULL);
		if (jr != 0) {
			fprintf(stderr, "pthread_join failed for left half: %d\n", jr);
		}
		/* child finished, parent frees the child arg */
		free(leftArg);
		leftArg = NULL;
	}
	if (rcRight == 0) {
		jr = pthread_join(tRight, NULL);
		if (jr != 0) {
			fprintf(stderr, "pthread_join failed for right half: %d\n", jr);
		}
		/* child finished, parent frees the child arg */
		free(rightArg);
		rightArg = NULL;
	}

	/* Both halves are now sorted (via threads or serial fallback). Merge them. */
	merge(left, mid, mid + 1, right);

	return NULL;
}

/* we build the argument for the parallel_mergesort function. */
struct argument * buildArgs(int left, int right, int level){
	struct argument *args = (struct argument *) malloc(sizeof(struct argument));
	if (args == NULL) {
		fprintf(stderr, "malloc failed in buildArgs()\n");
		exit(EXIT_FAILURE);
	}
	args->left = left;
	args->right = right;
	args->level = level;
	return args;
}

