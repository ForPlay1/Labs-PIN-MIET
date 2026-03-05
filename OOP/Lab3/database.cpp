#include "database.h"

using namespace std;

const char* storage::filename = "data.bin";

void date::show() {
    cout << day << "." << month << "." << year;
}

date::date() {
    this->day = 1;
    this->month = 1;
    this->year = 2000;
}

date::date(int day, int month, int year) {
    this->day = day;
    this->month = month;
    this->year = year;
}

int* date::getDayPtr() {
    return &this->day;
}

int* date::getMonthPtr() {
    return &this->month;
}

int* date::getYearPtr() {
    return &this->year;
}

date* item::getDeliveryDatePtr() {
    return &this->delivery_date;
}

ostream& operator<<(ostream& os, const item& item) {
    return os << item.name << "  " << item.price << "  " << item.quant << " " << item.delivery_date.day << "." << item.delivery_date.month << "." << item.delivery_date.year;
}

int item::init(char* name, int len, double price, int quant, int day, int month, int year) {
    this->name = new char[len + 1];
    strcpy_s(this->name, len + 1, name);
    this->price = price;
    this->quant = quant;
    this->delivery_date = date(day, month, year);
    return 1;
}

int item::init() {
    char buf_name[80];
    cout << "Enter name: ";
    cin >> buf_name;

    this->name = new char[strlen(buf_name) + 1];
    strcpy_s(this->name, strlen(buf_name) + 1, buf_name);

    char buf_price[80];
    cout << "Enter price(number with float point): ";
    cin >> buf_price;
    if (!checkDouble(buf_price)) {
        this->price = 10.0;
    }
    else {
        this->price = strtod(buf_price, NULL);
    }

    char buff_quant[80];
    cout << "Enter quantity(positive integer): ";
    cin >> buff_quant;
    if (!checkInt(buff_quant)) {
        cout << "Not a positive integer.\n";
        this->quant = 1;
    }
    else {
        this->quant = atoi(buff_quant);
    }
    char buf_day[80];
    cout << "Enter day of delivery: ";
    cin >> buf_day;
    if (!checkInt(buf_day) || atoi(buf_day) < 1 || atoi(buf_day) > 31) {
        cout << "Not a valid day.\n";
        this->delivery_date = date();
        return 1;
    }
    int day = atoi(buf_day);
    char buf_month[80];
    cout << "Enter number of month of delivery(1-12): ";
    cin >> buf_month;
    if (!checkInt(buf_month) || atoi(buf_month) < 1 || atoi(buf_month) > 12) {
        cout << "Not a valid month.\n";
        this->delivery_date = date();
        return 1;
    }
    int month = atoi(buf_month);
    char buf_year[80];
    cout << "Enter year of delivery: ";
    cin >> buf_year;
    if (!checkInt(buf_year)) {
        cout << "Not a valid year.\n";
        this->delivery_date = date();
        return 1;
    }
    int year = atoi(buf_year);
    this->delivery_date = date(day, month, year);
    return 1;
}

bool item::operator>(const date& otherDate) { 
    return this->delivery_date.year > otherDate.year ||
        (this->delivery_date.year == otherDate.year && this->delivery_date.month > otherDate.month) ||
        (this->delivery_date.year == otherDate.year && this->delivery_date.month == otherDate.month && this->delivery_date.day > otherDate.day);
 }

bool item::isName(char* name) {
    return strcmp(this->name, name) == 0;
}

bool item::showName(char* name) {
    if (isName(name)) {
        cout << *this << endl;
        return true;
    }
    return false;
}

char* item::getName() {
    return name;
}

double item::getPrice() {
    return price;
}

double* item::getPricePtr() {
    return &price;
}

bool item::isCostMore(double cost) {
    return price > cost;
}

bool item::showCostMore(double cost) {
    if (isCostMore(cost)) {
        cout << *this << endl;
        return true;
    }
    return false;
}

int* item::getQuantPtr() {
    return &this->quant;
}

storage::storage(int n) {
    this->database = new item[n];
    this->current_count = 0;
    this->n = n;
}

void storage::searchName() {
    char buf_name[80];
    cout << "Enter name to search: ";
    cin >> buf_name;
    for (int i = 0; i < current_count; i++) {
        if (this->database[i].showName(buf_name)) {
            return;
        }
    }
    cout << "Not found any item with name " << buf_name << ".\n";
}
    
int storage::write_to_file() {
    ofstream outFile(storage::filename, ios::binary);
    if (!outFile) {
        return 1;
    }
    outFile.write(reinterpret_cast<char*>(&current_count), sizeof(current_count));
    for (int i = 0; i < current_count; i++) {
        int len = strlen(this->database[i].getName());
        outFile.write(this->database[i].getName(), sizeof(char)*(len + 1));
        outFile.write(reinterpret_cast<char*>(this->database[i].getPricePtr()), sizeof(double));
        outFile.write(reinterpret_cast<char*>(this->database[i].getQuantPtr()), sizeof(int));
        outFile.write(reinterpret_cast<char*>(this->database[i].getDeliveryDatePtr()->getDayPtr()), sizeof(int));
        outFile.write(reinterpret_cast<char*>(this->database[i].getDeliveryDatePtr()->getMonthPtr()), sizeof(int));
        outFile.write(reinterpret_cast<char*>(this->database[i].getDeliveryDatePtr()->getYearPtr()), sizeof(int));
    }
    outFile.close();
    return 0;
}

void storage::add() {
    if (this->current_count < this->n) {
        this->current_count += this->database[current_count].init();
    }
    else {
        cout << "No available space in database." << endl;
    }
}

void storage::show() {
    for (int i = 0; i < current_count; i++) {
        cout << this->database[i] << endl;
    }
}

void storage::searchCost() {
    char buf_cost[80];
    cout << "Enter cost to search: ";
    cin >> buf_cost;
    if (!checkDouble(buf_cost)) {
        cout << "Not a valid number.\n";
        return;
    }
    double cost = strtod(buf_cost, NULL);
    bool isFound = false;
    for (int i = 0; i < current_count; i++) {
        if (this->database[i].showCostMore(cost)) {
            isFound = true;
        }
    }
    if (!isFound) {
        cout << "Not found any item with cost more than " << buf_cost << ".\n";
    }
}

int storage::readfile() {
    ifstream inFile(storage::filename, ios::binary);
    if (!inFile) {
        return 1;
    }
    int amount;
    inFile.read(reinterpret_cast<char*>(&amount), sizeof(amount));
    if (inFile.eof()){
        inFile.close();
        return 2;
    }
    for (int i = 0; i < amount; i++) {
        char* buff = new char[80];
        int len = 0;
        do {
            inFile.read(&(buff[len]), sizeof(char));
            len++;
        } while (buff[len - 1] != '\0');
        char* name = new char[len];
        strcpy_s(name, len, buff);
        double price;
        inFile.read(reinterpret_cast<char*>(&price), sizeof(double));
        int quant;
        inFile.read(reinterpret_cast<char*>(&quant), sizeof(int));
        int day;
        inFile.read(reinterpret_cast<char*>(&day), sizeof(int));
        int month;
        inFile.read(reinterpret_cast<char*>(&month), sizeof(int));
        int year;
        inFile.read(reinterpret_cast<char*>(&year), sizeof(int));
        this->current_count += this->database[i].init(name, len, price, quant, day, month, year);
    }
    inFile.close();
    return 0;
}

void storage::show_total() {
    cout << "Total amount of items: " << this->current_count << endl;
}

void storage::compare() {
    this->show();
    cout << "Enter, which item to compare(index, starts with 0): ";
    char buf_index[80];
    cin >> buf_index;
    if (!checkInt(buf_index)) {
        cout << "Incorrect number format.\n";
        return;
    }
    int index = atoi(buf_index);
    if (index < 0 || index >= current_count) {
        cout << "Incorrect index.\n";
        return;
    }
    item item_to_compare = this->database[index];
    cout << "Enter year to compare: ";
    char buf_year[80];
    cin >> buf_year;
    if (!checkInt(buf_year)) {
        cout << "Incorrect number format.\n";
        return;
    }
    int year = atoi(buf_year);
    cout << "Enter month to compare: ";
    char buf_month[80];
    cin >> buf_month;
    if (!checkInt(buf_month) || atoi(buf_month) < 1 || atoi(buf_month) > 12) {
        cout << "Incorrect number format.\n";
        return;
    }
    int month = atoi(buf_month);
    cout << "Enter day to compare: ";
    char buf_day[80];
    cin >> buf_day;
    if (!checkInt(buf_day) || atoi(buf_day) < 1 || atoi(buf_day) > 31) {
        cout << "Incorrect number format.\n";
        return;
    }
    int day = atoi(buf_day);
    date date_to_compare = date(day, month, year);
    if (item_to_compare > date_to_compare) {
        cout << "Item " << item_to_compare.getName() << " has later delivery date than " << day << "." << month << "." << year << endl;
    }
    else {
        cout << "Item " << item_to_compare.getName() << " has earlier delivery date than " << day << "." << month << "." << year << endl;
    }
}

storage::~storage() {
    delete[] database;
}

storage* warehouse;

void database() {
    int n = 0;
    n = enterNumber(storage::filename);
    warehouse = new storage(n);
    int read = (*warehouse).readfile();
    switch (read) {
    case 1: {
        cout << "There is no such file" << endl;
        break;
    }
    case 2: {
        cout << "Empty file" << endl;
        break;
    }
    case 0: {
        cout << "All correct" << endl;
        break;
    }
    }
    system("pause");
    int choose;
    char buffer[80];
    do {
        system("cls");
        choose = 1;
        cout << "Choose(1 - add new item, 2 - show all items, 3 - total amount of items, 4 - find item by name, 5 - find items with cost more than input, 6 - compare item to date): ";
        cin >> buffer;
        if (!checkInt(buffer)) {
            printf("Not a number!\n");
            continue;
        };
        choose = atoi(buffer);
        switch (choose)
        {
        case 1: {
            (*warehouse).add();
            break;
        }
        case 2: {
            (*warehouse).show();
            break;
        }
        case 3: {
            (*warehouse).show_total();
            break;
        }
        case 4: {
            (*warehouse).searchName();
            break;
        }
        case 5: {
            (*warehouse).searchCost();
            break;
        }
        
        case 6: {
            (*warehouse).compare();
            break;
        }
    }
        system("pause");
    } while (choose > 0 && choose < 7);

    int write = (*warehouse).write_to_file();
    switch (read) {
    case 1: {
        cout << "Error openning file to write, created new" << endl;
        break;
    }
    case 0: {
        cout << "All corect" << endl;
        break;
    }
    }
    delete warehouse;
}
