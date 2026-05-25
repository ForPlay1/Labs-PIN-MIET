#pragma once
#include <iostream>
#include <ctime>

class product {
    int id;
    char* name;
    float cost;
public:
    product();
    ~product();
    void set_id(int id);
    void set_name(char* name);
    void set_cost(float cost);
    int get_id();
    char* get_name();
    float get_cost();
};

class groupOfProducts {
    int id;
    char* name;
public:
    groupOfProducts();
    ~groupOfProducts();
    int get_id();
    char* get_name();
    void set_id(int id);
    void set_name(char* name);
};

class User {
private:
    char* name;
    char* surname;
    char* phone;
    float basePercent;
public:
    User();
    virtual ~User(); // Виртуальный деструктор обязателен для полиморфизма
    virtual float calc_percent() = 0;
    virtual int calc_price(product& prod) = 0;
    void set_name(char* name);
    void set_surname(char* surname);
    void set_phone(char* phone);
    void set_basePercent(float basePercent);
    char* get_name();
    char* get_surname();
    char* get_phone();
    float get_basePercent();
};

class standartUser : public User {
public:
    standartUser();
    ~standartUser() override;
    float calc_percent() override;
    int calc_price(product& prod) override;
};

class pensionerUser : public User {
    float extraPercent;
public:
    pensionerUser();
    ~pensionerUser() override;
    float calc_percent() override;
    int calc_price(product& prod) override;
    void set_extraPercent(float exPer);
    float get_extraPercent();
};

class VIPUser : public User {
    tm** dates;
    int countDates;
    float extraPercent;
public:
    VIPUser();
    ~VIPUser() override;
    float calc_percent() override;
    int calc_price(product& prod) override;
    void set_dates(tm** dates, int countDates);
    tm** get_dates();
    int get_countDates();
    void set_extraPercent(float exPer);
    float get_extraPercent();
};