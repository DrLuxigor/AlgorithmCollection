import time
import random


def radix_sort_binary(array):
    """
    Radix sort algorithm for integers
    Result: 10.000.000 numbers from 0 to 32767: 27 seconds
    :param array: array to sort
    :return: ordered array
    """
    start = time.time()
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
    end = time.time()
    print(f'Elapsed time: {end - start}s')
    return array


length = 10000000
arr = [random.randint(0, 32767) for _ in range(length)]
sorted_arr = radix_sort_binary(arr)
