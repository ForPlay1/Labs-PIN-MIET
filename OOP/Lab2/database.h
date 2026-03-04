#pragma once
#include <iostream>
#include <fstream>

class item {
    char* name;
    double price;
    int quant;

public:
    int init(char* name, int len, double price, int quant);
    int init();
    void show();
    bool isName(char* name);
    bool showName(char* name);
    char* getName();
    double getPrice();
    double* getPricePtr();
    bool isCostMore(double cost);
    bool showCostMore(double cost);
    int* getQuantPtr();
};

class storage {
    item* database;
    int current_count;
    int n;
public:
    static const char* filename;
    storage(int n);
    void searchName();
    int write_to_file();
    void add();
    void show();
    void searchCost();
    int readfile();
    ~storage();
    void show_total();
};

bool checkInt(char* buffer);
bool checkDouble(char* buffer);
int readNumber(const char* filename);
int enterNumber();
void database();