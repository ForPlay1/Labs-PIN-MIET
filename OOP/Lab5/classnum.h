#include <iostream>

template <class num>
class array {
    int n;
    num* Bp;
    num* Tp;
public:
    array(int size);
    ~array();
    void show();
    num* negative();
};

void test2();