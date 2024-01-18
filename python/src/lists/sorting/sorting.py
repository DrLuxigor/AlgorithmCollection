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
    print(f'Radix Sort, Elapsed time: {end - start}s')
    return array


def bubble_sort(array):
    """
    O(n^2) time complexity
    O(1) additional space complexity
    :param array: array to be sorted
    :return: array in order
    """
    start = time.time()
    swapped = True
    while swapped:
        swapped = False
        for i in range(1, len(array)):
            if array[i] < array[i - 1]:
                swapped = True
                temp = array[i - 1]
                array[i - 1] = array[i]
                array[i] = temp
    end = time.time()
    print(f'Bubble Sort, Elapsed time: {end - start}s')
    return array


def selection_sort(array):
    """
    Time complexity O(n^2)
    Additional space complexity O(1)
    :param array:
    :return:
    """
    start = time.time()
    for i in range(len(array)):
        min_index = i
        for j in range(i, len(array)):
            if array[j] < array[min_index]:
                min_index = j
        temp = array[i]
        array[i] = array[min_index]
        array[min_index] = temp
    end = time.time()
    print(f'Selection Sort, Elapsed time: {end - start}s')
    return array


def insertion_sort(array):
    """
    Time complexity O(n^2)
    Additional space complexity O(1)
    :param array:
    :return:
    """
    start = time.time()
    for i in range(1, len(array)):
        key = array[i]
        j = i - 1
        while j >= 0 and key < array[j]:
            array[j + 1] = array[j]
            j = j - 1
        array[j + 1] = key
    end = time.time()
    print(f'Insertion Sort, Elapsed time: {end - start}s')
    return array


def merge_sort(array):
    """
    Time complexity O(n log n)
    Additional space complexity O(n)
    :param array:
    :return:
    """
    if len(array) <= 1:
        return array
    split_index = int(len(array) / 2)
    left = merge_sort(array[0:split_index])
    right = merge_sort(array[split_index:])
    return merge(left, right)


def merge(left, right):
    merged = []
    i, j = 0, 0
    while i < len(left) and j < len(right):
        if left[i] <= right[j]:
            merged.append(left[i])
            i += 1
        else:
            merged.append(right[j])
            j += 1
    merged += left[i:]
    merged += right[j:]
    return merged


def counting_sort(array, k):
    """
    ^_^_^_^_^_^
    | crown  | Winner, 100 Million numbers 0 through 32767 in 10 seconds in PYTHON!
    ----------
    Time complexity O(n + k) where k is the number of discrete options in array
    additional space complexity O(k) if original array is "freed" before result is generated from counts
    alternatively write on array in place while looping through counters
    Use a map for unpredictable but range limited sets? sort keys, add values, would work with objects as well
    :param array:
    :param k:
    :return:
    """
    start = time.time()
    counter = [0] * k
    for i in range(len(array)):
        counter[array[i]] += 1

    result = []
    for i in range(k):
        result += [i] * counter[i]
    end = time.time()
    print(f'Counting Sort, Elapsed time: {end - start}s')
    return result


if '__main__' == __name__:
    length = 100000000
    arr = [random.randint(0, 32767) for _ in range(length)]
    #sorted_arr = radix_sort_binary(arr.copy())
    #sorted_arr = bubble_sort(arr.copy())
    #sorted_arr = selection_sort(arr.copy())
    #sorted_arr = insertion_sort(arr.copy())
    #start = time.time()
    #sorted_arr = merge_sort(arr.copy())
    #end = time.time()
    #print(f'Merge Sort, Elapsed time: {end - start}s')
    sorted_arr = counting_sort(arr.copy(), 32768)
