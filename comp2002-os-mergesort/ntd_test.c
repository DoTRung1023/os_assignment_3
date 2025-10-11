#include <stdio.h>
#include <stdlib.h>
#include "mergesort.h"

/* Provide globals expected by mergesort.c */
int cutoff = 0;
int *A;
int *B;

int main(void){
    int n = 11; /* test odd length */
    A = malloc(sizeof(int) * n);
    B = malloc(sizeof(int) * n);
    if(!A || !B){
        perror("malloc");
        return 1;
    }

    /* fill A with a reversed sequence to exercise sorting */
    for(int i=0;i<n;i++) A[i] = n - i;

    printf("Before:\n");
    for(int i=0;i<n;i++) printf("%d ", A[i]);
    printf("\n");

    my_mergesort(0, n-1);

    printf("After:\n");
    for(int i=0;i<n;i++) printf("%d ", A[i]);
    printf("\n");

    /* verify sorted */
    for(int i=0;i<n-1;i++){
        if(A[i] > A[i+1]){
            printf("Sort failed at index %d: %d > %d\n", i, A[i], A[i+1]);
            free(A); free(B);
            return 1;
        }
    }

    printf("Sort succeeded\n");
    free(A); free(B);
    return 0;
}
