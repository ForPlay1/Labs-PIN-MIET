#include "classnum.h"

template <class num>
array<num>::array(int size) {
    n = size;
    Bp = new num[n];
    Tp = Bp;
    for (int i = 0; i < n; i++) {
        *Tp = rand() % 100 - 50;
        Tp++;
    }
    Tp = Bp;
}

template <class num>
array<num>::~array() {
    delete[] Bp;
}

template <class num>
void array<num>::show() {
    for (int i = 0; i < n; i++) {
        std::cout << *Tp << " ";
        Tp++;
    }
    std::cout << std::endl;
    Tp = Bp;
}

template <class num>
num* array<num>::negative() {
    num* negArr = new num[n];
    for (int i = 0; i < n; i++) {
        if (*Tp < 0) {
            negArr[i] = *Tp;
        } else {
            negArr[i] = 0;
        }
        Tp++;
    }
    Tp = Bp;
    return negArr;
}

void test2() {
    array<int> arr(10);
    array<double> arrD(10);
    std::cout << "Array elements: ";
    arr.show();
    std::cout << "Array elements (double): ";
    arrD.show();
    int* negArr = arr.negative();
    double* negArrD = arrD.negative();
    std::cout << "Negative elements: ";
    for (int i = 0; i < 10; i++) {
        if (negArr[i] != 0) {
            std::cout << negArr[i] << " ";
        }
    }
    std::cout << std::endl;
    std::cout << "Negative elements (double): ";
    for (int i = 0; i < 10; i++) {
        if (negArrD[i] != 0) {
            std::cout << negArrD[i] << " ";
        }
    }
    std::cout << std::endl;
    delete[] negArr;
    delete[] negArrD;
}