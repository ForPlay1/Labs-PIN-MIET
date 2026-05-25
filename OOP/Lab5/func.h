#pragma once
#include <iostream>

template <class num>
void swap(num& a, num& b);

template <class num>
void quickSort(num* arr, int size);
void quickSort(double* arr, int size);

template <class num>
void printArray(num* arr, int size);

void test();