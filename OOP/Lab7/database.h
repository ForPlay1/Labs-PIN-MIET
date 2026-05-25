#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <clocale>
#include <algorithm>

class Fio {
    void copyStr(char*& dest, const char* src);

public:
    char* lastName;
    char* firstName;

    Fio();
    Fio(const char* ln, const char* fn);
    Fio(const Fio& other);
    Fio& operator=(const Fio& other);
    ~Fio();
    void update(const char* ln, const char* fn);
};

class Student {
    Fio man;
    int zk;   
    int grup; 

public:
    Student();
    Student(const char* ln, const char* fn, int z, int g);
    int getGroup() const;
    friend std::ostream& operator<<(std::ostream& out, const Student& s);
    friend std::istream& operator>>(std::istream& in, Student& s);
    bool operator==(const Fio& f)const;
    void saveToFile(std::ofstream& out)const;
    bool loadFromFile(std::ifstream& in);
};

void printHeader();
void printFooter() ;
void database();