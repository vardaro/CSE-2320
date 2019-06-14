// ANTHONY VARDARO 1001522383 6/14/2019

#include <stdio.h>
#include "hw02-lib.h"

const int ARRAY_SIZE = 100;
const int ARRAY_LOWER_BOUND = 1;
const int ARRAY_UPPER_BOUND = 2000;

struct Unit {
    int n;
    int comparisons;
    int * arr;
};

/**
 * Sorts an array via insertion sort
 * @param arr array to sort
 * @param n length of array
 */
void sort(struct Unit* u) {
    int i, key, j;

    for (i = 1; i < u->n; i++) {
        key = u->arr[i];
        j = i - 1;

        while (j >= 0 && u->arr[j] > key) {
            u->comparisons++; // this is how we count number times the line above execs
            u->arr[j+1] = u->arr[j];
            j = j-1;
        }

        u->comparisons++; // the condition failed, but still executed, we need to count it

        u->arr[j+1] = key;
    }
}
void printArray(int * arr, int n) {
    int i;
    for (i = 0; i < n; i++) {
        if (i < n-1) {
            printf("%4d, ", arr[i]);
        } else {
            printf("%4d", arr[i]);
        }
    }
}

/**
 * fn = (n^2 + 3n - 4) / 4
 * @param n number of elements in array
 * @return fn at n
 */
double getPredictedAvg(int n) {
    double numerator = (n*n) + (n*3) - 4;
    return numerator / 4;
}

/**
 * compute average comparisons given array of units
 * @param u array of units
 * @param n sizeof(array)
 * @return double average of u.comparisons
 */
double getRealAvg(struct Unit u[], int n) {
    int i;
    int sum = 0;
    for (i = 0; i < n; i++ ) {
        sum += u[i].comparisons;
    }

    return sum / n;
}

int main() {

    // Generate 5 test cases
    struct Unit testCases[5];

    int i;
    int * cur;
    for (i = 0; i < 5; i++) {
        cur = randArray(ARRAY_SIZE, ARRAY_LOWER_BOUND, ARRAY_UPPER_BOUND, i+1);
        testCases[i].arr = cur;
        testCases[i].comparisons = 0;
        testCases[i].n = ARRAY_SIZE;

        // Print their unsorted state, sort the array,
        // then print the comparison number after
        printArray(testCases[i].arr, 5);
        sort(&testCases[i]);
        printf("    comparisons = %d\n", testCases[i].comparisons);
    }

    // compute averages
    printf("\navg number of experiments = %.1f\n", getRealAvg(testCases, 5));
    printf("        predicted average = %.1f\n", getPredictedAvg(100));


    return 0;
}