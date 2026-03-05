#pragma once
#include <iostream>
#include <cstring>
#include <fstream>
#include "functools.h"

class item;

class date {
    int day;
    int month;
    int year;
    public:
    date(int day, int month, int year);
    date();
    void show();
    int* getDayPtr();
    int* getMonthPtr();
    int* getYearPtr();
    friend class item;
    friend std::ostream& operator<<(std::ostream& os, const item& item);
};

class item {
    char* name;
    double price;
    int quant;
    date delivery_date;

public:
    int init(char* name, int len, double price, int quant, int day, int month, int year);
    int init();
    bool isName(char* name);
    bool showName(char* name);
    char* getName();
    double getPrice();
    double* getPricePtr();
    bool isCostMore(double cost);
    bool showCostMore(double cost);
    int* getQuantPtr();
    date* getDeliveryDatePtr();
    bool operator>(const date& otherDate);
    friend std::ostream& operator<<(std::ostream& os, const item& item);
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
    void compare();
    void show_total();
};

void database();