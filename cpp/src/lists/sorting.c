#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
    const double ms = (double)(endTime - startTime) / CLOCKS_PER_SEC;
    printf("Elapsed Time: %fs\n", ms);
}


int main() {
    srand(time(NULL));
    const unsigned int len = 10000000;
    int* arr = malloc(sizeof(int) * len);
    for (int i = 0; i < len; ++i) {
        arr[i] = rand();
    }
    radixSortBinary(len, arr);
    free(arr);
    return 0;
}
