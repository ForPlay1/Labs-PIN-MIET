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
    friend class food;
    friend std::ostream& operator<<(std::ostream& os, const item& item);
};

class item {
    char* name;
    double price;
    int quant;

public:
    bool isName(char* name);
    bool showName(char* name);
    char* getName();
    double getPrice();
    double* getPricePtr();
    bool isCostMore(double cost);
    bool showCostMore(double cost);
    int* getQuantPtr();
    void setName(char* name);
    void setPrice(double price);
    void setQuant(int quant);
};

class food : public item {
    date delivery_date;
    
    public:
    int init(char* name, int len, double price, int quant, int day, int month, int year);
    int init();
    date* getDeliveryDatePtr();
    bool operator>(const date& otherDate);
    friend std::ostream& operator<<(std::ostream& os, food& item);
};

class toy: public item {
    int age_limit;
    public:
    int init(char* name, int len, double price, int quant, int age_limit);
    int init();
    int getAgeLimit();
    int* getAgeLimitPtr();
    friend std::ostream& operator<<(std::ostream& os, toy& item);
};

class storage {
    food* food_database;
    toy* toy_database;
    int current_count_food;
    int current_count_toy;
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