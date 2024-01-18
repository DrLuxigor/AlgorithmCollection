#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <limits.h>

/**
 * \brief sorts an array of positive integers from smallest to largest.
 * Negative values will at the end of the array, also from smallest to largest
 * Result: 10.000.000 numbers from 0 to 32767: 1.259 seconds
 * \param length length of the array
 * \param array array to be sorted
 */
void radixSortBinary(const unsigned int length, int* array) {
    printf("Sorting %d numbers!\n", length);
    const clock_t startTime = clock();
    if (length < 2)
        return;

    int max = array[0];
    for (int i = 0; i < length; i++) {
        if (array[i] > max)
            max = array[i];
    }

    int msbPos = 0;
    while (max >> msbPos != 0) {
        msbPos++;
    }

    //One could assume that the there is roughly an equal amount of numbers in each bucket every time
    //Allocating half the size of the array for each bucket + margin and reallocations if neccessarry
    //would safe a lot of space
    int* zeroBucket = malloc(sizeof(int) * length);
    int* onesBucket = malloc(sizeof(int) * length);
    for (int bitPos = 0; bitPos < msbPos; bitPos++) {
        int zeroCount = 0;
        int onesCount = 0;
        for (int n = 0; n < length; n++) {
            if ((array[n] >> bitPos & 0x1) == 0) {
                zeroBucket[zeroCount] = array[n];
                zeroCount++;
            }
            else {
                onesBucket[onesCount] = array[n];
                onesCount++;
            }
        }
        for (int i = 0; i < zeroCount; i++) {
            array[i] = zeroBucket[i];
        }
        for (int i = zeroCount; i < length; i++) {
            array[i] = onesBucket[i - zeroCount];
        }
    }
    free(zeroBucket);
    free(onesBucket);
    const clock_t endTime = clock();
    const double s = (double)(endTime - startTime) / CLOCKS_PER_SEC;
    printf("Radix Sorted %d elements in %fs\n", length, s);
}


void merge(int* array, const unsigned int leftStart, const unsigned int leftEnd, const unsigned int rightStart, const unsigned int rightEnd) {
    const unsigned int mergeSize = rightEnd - leftStart;
    int* mergedArray = calloc(mergeSize, sizeof(int));
    unsigned int i = leftStart;
    unsigned int j = rightStart;
    int pos = 0;
    while (i < leftEnd && j < rightEnd) {
        if (array[i] <= array[j]) {
            mergedArray[pos] = array[i];
            pos++;
            i++;
        }
        else {
            mergedArray[pos] = array[j];
            pos++;
            j++;
        }
    }
    if (i < leftEnd) {
        for (int remaining = i; remaining < leftEnd; ++remaining) {
            mergedArray[pos] = array[remaining];
            pos++;
        }
    }
    else if (j < rightEnd) {
        for (int remaining = j; remaining < rightEnd; ++remaining) {
            mergedArray[pos] = array[remaining];
            pos++;
        }
    }
    memcpy(&array[leftStart], mergedArray, mergeSize * sizeof(int));
    free(mergedArray);
}

/**
 * \brief Time O(n log n)
 * additional space O(n) unfortunately no in place implementation possible
 * Result: 10.000.000 elements in 1.98 seconds
 * \param array
 * \param startIndex
 * \param endIndex
 */
void mergeSort(int* array, const unsigned int startIndex, const unsigned int endIndex) {
    if (endIndex - startIndex <= 1)
        return;
    const unsigned int index = (int)((endIndex - startIndex) / 2);
    mergeSort(array, startIndex, startIndex + index);
    mergeSort(array, startIndex + index, endIndex);
    merge(array, startIndex, startIndex + index, startIndex + index, endIndex);
}

void mergeSortWrapper(unsigned int len, int* array) {
    const clock_t startTime = clock();
    mergeSort(array, 0, len);
    const clock_t endTime = clock();
    const double s = (double)(endTime - startTime) / CLOCKS_PER_SEC;
    printf("Merge Sorted %d elements in %fs\n", len, s);
}

/**
 * \brief sorts an array of integers 0 through k - 1 from smallest to largest.
 * Result: 1.000.000.000 elements: 3.96 seconds (30x radix sort performance)
 * Time O(n + k)
 * Additional Space O(k)
 * for large arrays even a full 32bit would be neglegable since it would
 * only result in a runtime of ~5n if there are say 1 billion elements
 * \param length length of array
 * \param array array to be sorted
 * \param k range of possibile numbers
 */
void countingSort(const unsigned int length, int* array, const unsigned int k) {
    const clock_t startTime = clock();
    int* counters = malloc(sizeof(int) * k);
    memset(counters, 0, sizeof(int) * k);
    for (int i = 0; i < length; ++i) {
        counters[array[i]] += 1;
    }
    int pos = 0;
    for (int i = 0; i < k; ++i) {
        for (int j = 0; j < counters[i]; ++j) {
            array[pos] = i;
            pos++;
        }
    }
    free(counters);
    const clock_t endTime = clock();
    const double s = (double)(endTime - startTime) / CLOCKS_PER_SEC;
    printf("Counting Sorted %d elements with %d discrete values in %fs\n", length, k, s);
}


void printArray(const unsigned int length, const int* array) {
    for (int i = 0; i < length; ++i) {
        printf("%d ", array[i]);
        if ((i + 1) % 20 == 0)
            printf("\n");
    }
}

int main() {
    srand(time(NULL));
    const unsigned int len = 10000000;
    int* arr = malloc(sizeof(int) * len);
    for (int i = 0; i < len; ++i) {
        arr[i] = rand();
    }
    //radixSortBinary(len, arr);
    //countingSort(len, arr, RAND_MAX + 1);
    mergeSortWrapper(len, arr);
    //printArray(len, arr)
    free(arr);
    return 0;
}
