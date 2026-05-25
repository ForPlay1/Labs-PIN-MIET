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
};

class item {
    char* name;
    double price;
    int quant;

public:
    item();
    int init();
    bool isName(char* name);
    bool showName(char* name);
    char* getName();
    virtual int getType();
    double getPrice();
    double* getPricePtr();
    bool isCostMore(double cost);
    virtual bool showCostMore(double cost);
    int* getQuantPtr();
    void setName(char* name);
    void setPrice(double price);
    void setQuant(int quant);
};

class food : public item {
    date delivery_date;
    
    public:
    food();
    int init(char* name, int len, double price, int quant, int day, int month, int year);
    int init();
    int getType() override;
    bool showCostMore(double cost) override;
    date* getDeliveryDatePtr();
    bool operator>(const date& otherDate);
    friend std::ostream& operator<<(std::ostream& os, food& item);
};

class toy: public item {
    int age_limit;
    public:
    int init(char* name, int len, double price, int quant, int age_limit);
    int init();
    int getType() override;
    bool showCostMore(double cost) override;
    int getAgeLimit();
    int* getAgeLimitPtr();
    friend std::ostream& operator<<(std::ostream& os, toy& item);
};

class item12: public food, public toy{};

class storage {
    item** database;
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