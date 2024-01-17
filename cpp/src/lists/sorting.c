#include <stdio.h>
#include <stdlib.h>

int main() {
    return 0;
}

void radixSortBinary(int length, int* array) {
    if(length < 2)
        return array;

    int max = array[0];
    for(int i = 0; i < length; i++) {
        if(array[i] > max)
            max = array[i];
    }

    int msbPos = 0;
    while (max >> i != 0) {
        msbPos++;
    }

    int* zeroBucket = malloc(sizeof(int) * length);
    int* onesBucket = malloc(sizeof(int) * length);
    for(int bitPos = 0; bitPos < msbPos; bitPos++) {
        int zeroCount = 0;
        int onesCount = 0;
        for(int n = 0; n < length; n++){
            if(array[n] >> bitPos & 1 == 0) {
                zeroBucket[zeroCount] = array[n];
                zeroCount++;
            } else {
                onesBucket[onesCount] = array[n];
                onesCount++;
            }
        }
        for(int i = 0; i < zeroCount; i++) {
            array[i] = zeroBucket[i];
        }
        for(int i = zeroCount; i < length; i++) {
            array[i] = onesBucket[i - zeroCount];
        }
    }
    free(zeroBucket);
    free(onesBucket);
}