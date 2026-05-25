#include "main.h"
#include <cstring>

using namespace std;

// =========================================================================
// РЕАЛИЗАЦИЯ КЛАССА PRODUCT
// =========================================================================
product::product() {
    id = 0;
    name = nullptr;
    cost = 0.0f;
}

product::~product() {
    delete[] name; // Исправлено: delete[] для массивов char
}

void product::set_id(int id) { this->id = id; }
void product::set_cost(float cost) { this->cost = cost; }
float product::get_cost() { return cost; }
int product::get_id() { return id; }

void product::set_name(char* name) {
    delete[] this->name;
    if (name == nullptr) {
        this->name = nullptr;
        return;
    }
    this->name = new char[strlen(name) + 1];
    strcpy_s(this->name, strlen(name) + 1, name);
}

char* product::get_name() {
    if (!name) return nullptr;
    char* buff = new char[strlen(name) + 1];
    strcpy_s(buff, strlen(name) + 1, name);
    return buff;
}

// =========================================================================
// РЕАЛИЗАЦИЯ КЛАССА GROUPOFPRODUCTS
// =========================================================================
groupOfProducts::groupOfProducts() {
    id = 0;
    name = nullptr;
}

groupOfProducts::~groupOfProducts() {
    delete[] name; // Исправлено
}

void groupOfProducts::set_id(int id) { this->id = id; }
int groupOfProducts::get_id() { return id; }

void groupOfProducts::set_name(char* name) {
    delete[] this->name;
    if (name == nullptr) {
        this->name = nullptr;
        return;
    }
    this->name = new char[strlen(name) + 1];
    strcpy_s(this->name, strlen(name) + 1, name);
}

char* groupOfProducts::get_name() {
    if (!name) return nullptr;
    char* buff = new char[strlen(name) + 1];
    strcpy_s(buff, strlen(name) + 1, name);
    return buff;
}

// =========================================================================
// РЕАЛИЗАЦИЯ БАЗОВОГО КЛАССА USER
// =========================================================================
User::User() {
    name = nullptr;
    surname = nullptr;
    phone = nullptr;
    basePercent = 0.0f;
}

User::~User() {
    delete[] name;
    delete[] surname;
    delete[] phone;
}

void User::set_basePercent(float basePercent) { this->basePercent = basePercent; }
float User::get_basePercent() { return basePercent; }

void User::set_name(char* name) {
    delete[] this->name;
    if (name == nullptr) { this->name = nullptr; return; }
    this->name = new char[strlen(name) + 1];
    strcpy_s(this->name, strlen(name) + 1, name);
}

void User::set_surname(char* surname) {
    delete[] this->surname;
    if (surname == nullptr) { this->surname = nullptr; return; }
    this->surname = new char[strlen(surname) + 1];
    strcpy_s(this->surname, strlen(surname) + 1, surname);
}

void User::set_phone(char* phone) {
    delete[] this->phone;
    if (phone == nullptr) { this->phone = nullptr; return; }
    this->phone = new char[strlen(phone) + 1];
    strcpy_s(this->phone, strlen(phone) + 1, phone);
}

char* User::get_name() {
    if (!name) return nullptr;
    char* buff = new char[strlen(name) + 1];
    strcpy_s(buff, strlen(name) + 1, name);
    return buff;
}

char* User::get_surname() {
    if (!surname) return nullptr;
    char* buff = new char[strlen(surname) + 1];
    strcpy_s(buff, strlen(surname) + 1, surname);
    return buff;
}

char* User::get_phone() {
    if (!phone) return nullptr;
    char* buff = new char[strlen(phone) + 1];
    strcpy_s(buff, strlen(phone) + 1, phone);
    return buff;
}

// =========================================================================
// РЕАЛИЗАЦИЯ КЛАССА STANDARTUSER
// =========================================================================
standartUser::standartUser() : User() {}
standartUser::~standartUser() {}

float standartUser::calc_percent() { return get_basePercent(); }
int standartUser::calc_price(product& prod) {
    return (int)(prod.get_cost() * (1.0f - calc_percent()));
}

// =========================================================================
// РЕАЛИЗАЦИЯ КЛАССА PENSIONERUSER
// =========================================================================
pensionerUser::pensionerUser() : User() { extraPercent = 0.0f; }
pensionerUser::~pensionerUser() {}

void pensionerUser::set_extraPercent(float exPer) { extraPercent = exPer; }
float pensionerUser::get_extraPercent() { return extraPercent; }

float pensionerUser::calc_percent() { return get_extraPercent() * get_basePercent(); }
int pensionerUser::calc_price(product& prod) {
    return (int)(prod.get_cost() * (1.0f - calc_percent()));
}

// =========================================================================
// РЕАЛИЗАЦИЯ КЛАССА VIPUSER
// =========================================================================
VIPUser::VIPUser() : User() {
    countDates = 0;
    dates = nullptr;
    extraPercent = 0.0f;
}

VIPUser::~VIPUser() {
    if (dates) {
        for (int i = 0; i < countDates; i++) {
            delete dates[i];
        }
        delete[] dates;
    }
}

void VIPUser::set_extraPercent(float extraPercent) { this->extraPercent = extraPercent; }
float VIPUser::get_extraPercent() { return extraPercent; }
int VIPUser::get_countDates() { return countDates; }

void VIPUser::set_dates(tm** src_dates, int countDates) {
    if (this->dates) {
        for (int i = 0; i < this->countDates; i++) {
            delete this->dates[i];
        }
        delete[] this->dates;
    }

    this->countDates = countDates;
    if (countDates == 0 || src_dates == nullptr) {
        this->dates = nullptr;
        return;
    }

    this->dates = new tm * [countDates];
    for (int i = 0; i < countDates; i++) {
        this->dates[i] = new tm;
        this->dates[i]->tm_year = src_dates[i]->tm_year;
        this->dates[i]->tm_mon = src_dates[i]->tm_mon;
        this->dates[i]->tm_mday = src_dates[i]->tm_mday;
    }
}

tm** VIPUser::get_dates() {
    if (countDates == 0 || !dates) return nullptr;
    tm** buffer = new tm * [countDates];
    for (int i = 0; i < countDates; i++) {
        buffer[i] = new tm; // Исправлено выделение памяти
        buffer[i]->tm_year = this->dates[i]->tm_year;
        buffer[i]->tm_mon = this->dates[i]->tm_mon;
        buffer[i]->tm_mday = this->dates[i]->tm_mday;
    }
    return buffer;
}

float VIPUser::calc_percent() {
    if (countDates == 0 || dates == nullptr) return get_basePercent();

    time_t now = time(0);
    tm ltm;
    localtime_s(&ltm, &now);

    for (int i = 0; i < countDates; i++) {
        if (dates[i] &&
            ltm.tm_year == dates[i]->tm_year &&
            ltm.tm_mon == dates[i]->tm_mon &&
            ltm.tm_mday == dates[i]->tm_mday) {
            return get_basePercent() + get_extraPercent();
        }
    }
    return get_basePercent();
}

int VIPUser::calc_price(product& prod) {
    return (int)(prod.get_cost() * (1.0f - calc_percent()));
}

// =========================================================================
// ГЛАВНАЯ ФУНКЦИЯ ПРОГРАММЫ
// =========================================================================
int main() {
    standartUser* standUsers = new standartUser[3];
    pensionerUser* pensUsers = new pensionerUser[3];
    VIPUser* vipUsers = new VIPUser[3];

    for (int i = 0; i < 3; i++) {
        char name[80];
        char surname[80];
        char phone[80];
        float basePercent;
        float extraPercent;
        int countDates;

        cout << "\n--- Standart user " << i << " ---\n";
        cout << "Name: "; cin >> name;
        cout << "Surname: "; cin >> surname;
        cout << "Phone: "; cin >> phone;
        cout << "BasePercent (e.g. 0.1): "; cin >> basePercent;
        standUsers[i].set_name(name);
        standUsers[i].set_surname(surname);
        standUsers[i].set_phone(phone);
        standUsers[i].set_basePercent(basePercent);

        cout << "\n--- Pensioner user " << i << " ---\n";
        cout << "Name: "; cin >> name;
        cout << "Surname: "; cin >> surname;
        cout << "Phone: "; cin >> phone;
        cout << "BasePercent: "; cin >> basePercent;
        cout << "ExtraPercent: "; cin >> extraPercent;
        pensUsers[i].set_name(name);
        pensUsers[i].set_surname(surname);
        pensUsers[i].set_phone(phone);
        pensUsers[i].set_basePercent(basePercent);
        pensUsers[i].set_extraPercent(extraPercent);

        cout << "\n--- VIP user " << i << " ---\n";
        cout << "Name: "; cin >> name;
        cout << "Surname: "; cin >> surname;
        cout << "Phone: "; cin >> phone;
        cout << "BasePercent: "; cin >> basePercent;
        cout << "ExtraPercent: "; cin >> extraPercent;
        cout << "CountDates: "; cin >> countDates;

        tm** temp_dates = nullptr;
        if (countDates > 0) {
            temp_dates = new tm * [countDates];
            for (int j = 0; j < countDates; j++) {
                temp_dates[j] = new tm; // Исправлено: выделение памяти под каждый элемент
                cout << "Date " << j << " year: ";
                cin >> temp_dates[j]->tm_year;
                temp_dates[j]->tm_year -= 1900;
                cout << "Date " << j << " month (1-12): ";
                cin >> temp_dates[j]->tm_mon;
                temp_dates[j]->tm_mon -= 1;
                cout << "Date " << j << " day: ";
                cin >> temp_dates[j]->tm_mday;
            }
        }

        vipUsers[i].set_dates(temp_dates, countDates);
        vipUsers[i].set_name(name);
        vipUsers[i].set_surname(surname);
        vipUsers[i].set_phone(phone);
        vipUsers[i].set_basePercent(basePercent);
        vipUsers[i].set_extraPercent(extraPercent);

        if (temp_dates) {
            for (int j = 0; j < countDates; j++) {
                delete temp_dates[j];
            }
            delete[] temp_dates;
        }
    }

    int id;
    char prodName[80];
    float cost;
    cout << "\nWrite product's id: "; cin >> id;
    cout << "Write product's name: "; cin >> prodName;
    cout << "Write product's cost: "; cin >> cost;

    product pr;
    pr.set_cost(cost);
    pr.set_id(id);
    pr.set_name(prodName);

    cout << "\n--- Calculations ---" << endl;
    for (int i = 0; i < 3; i++) {
        cout << "Standart User " << i << " Price: " << standUsers[i].calc_price(pr) << endl;
        cout << "Pensioner User " << i << " Price: " << pensUsers[i].calc_price(pr) << endl;
        cout << "VIP User " << i << " Price: " << vipUsers[i].calc_price(pr) << endl;
    }

    delete[] standUsers;
    delete[] pensUsers;
    delete[] vipUsers;

    return 0;
}