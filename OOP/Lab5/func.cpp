#include "func.h"

template <class num>
void swap(num& a, num& b) {
    num temp = a;
    a = b;
    b = temp;
}

template <class num>
void quickSort(num* arr, int size) {
    if (size <= 1) {
        return;
    }
    num pivot = arr[size - 1];
    int i = 0;
    for (int j = 0; j < size - 1; j++) {
        if (arr[j] < pivot) {
            swap(arr[i], arr[j]);
            i++;
        }
    }
    swap(arr[i], arr[size - 1]);
    quickSort(arr, i);
    quickSort(arr + i + 1, size - i - 1);
    return;
}

void quickSort(double* arr, int size) {
    if (size <= 1) {
        return;
    }
    double pivot = arr[size - 1];
    int i = 0;
    for (int j = 0; j < size - 1; j++) {
        if (arr[j] > pivot) {
            swap(arr[i], arr[j]);
            i++;
        }
    }
    swap(arr[i], arr[size - 1]);
    quickSort(arr, i);
    quickSort(arr + i + 1, size - i - 1);
    return;
}

template <class num>
void printArray(num* arr, int size) {
    for (int i = 0; i < size; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

void test() {
    int* arr = new int[5] {5, 4, 3, 2, 1};
    double* arr2 = new double[5] {5.5, 4.4, 3.3, 2.2, 1.1};
    char* arr3 = new char[5] {'e', 'd', 'c', 'b', 'a'};
    quickSort(arr, 5);
    quickSort(arr2, 5);
    quickSort(arr3, 5);
    printArray(arr, 5);
    printArray(arr2, 5);
    printArray(arr3, 5);
    delete[] arr;
    delete[] arr2;
    delete[] arr3;
}