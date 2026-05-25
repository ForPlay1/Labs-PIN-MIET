#pragma once
#include <iostream>
#include <cstring>

class fio {
    char* name;
    char* surname;
public:
    fio(const char* name, const char* surname);
    ~fio();
    friend std::ostream& operator<<(std::ostream & out, const fio& fio);
    fio();
    fio(const fio& other);
    char* getName() const;
    char* getSurname() const;
    void setName(const char* name);
    void setSurname(const char* surname);
};

class student {
    fio man;
    int zk;
    int grup;
public:
    student();
    void init();
    friend std::ostream & operator<<(std::ostream & out, const student & student);
    friend std::istream& operator>>(std::istream& in, student& student);
    bool operator==(const fio& fio);
    friend student* search(student* students, int count, int grup);
    int getGroup() const;
};

student* search(student* students, int count, int grup);
std::ostream& operator<<(std::ostream& out, const student& student);
std::istream& operator>>(std::istream& in, student& student);
void database();