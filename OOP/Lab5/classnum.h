#pragma once
#include <iostream>
#include <ctime>

bool checkDouble(char* buffer);
bool checkInt(char* buffer);

template <class num>
class array {
    int n;
    int* Bp;
    int* Tp;
public:
    array(int size);
    ~array();
    void show();
    num* negative();
    void set_random();
    void write();
};

void test2();