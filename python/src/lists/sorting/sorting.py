import numpy as np


def radix_sort_lsb(array):
    """
    Radix sort algorithm for integers
    Time: O(n)
    //n to find the maximum +
    //n * position of msb +
    //fraction of n to find first negative number
    //fraction of n to reverse the negative number list
    Additional Space: O(n)
    :param array: array to sort
    :return: ordered array
    """
    max_num = max(array)
    msb_pos = max_num.bit_length()

    for i in range(msb_pos):
        zero_bucket = []
        one_bucket = []
        for n in array:
            if n >> i & 0b1 == 0:
                zero_bucket.append(n)
            else:
                one_bucket.append(n)
        array = zero_bucket + one_bucket

    for i in range(len(array)):
        if array[i] < 0:
            positives = array[0:i]
            negatives = array[i:]
            array = negatives + positives
            break

    return array


arr = [170, 45, 75, 90, -3, 802, 24, 2, 66, -1, -2]
sorted_arr = radix_sort_lsb(arr)
print("Sorted array:", sorted_arr)
