#include <stdio.h>
#include <stdlib.h>

/**
 * \brief sorts an array of positive integers from smallest to largest.
 * Negative values will at the end of the array, also from smallest to largest
 * \param length length of the array
 * \param array array to be sorted
 */
void radixSortBinary(const int length, int* array) {
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
}


int main() {
    const int len = 11;
    int numbers[] = {170, 45, 75, 90, -3, 802, 24, 2, 66, -1, -2};

    radixSortBinary(len, numbers);
    for (int i = 0; i < len; ++i) {
        printf("%d ", numbers[i]);
    }
    return 0;
}
