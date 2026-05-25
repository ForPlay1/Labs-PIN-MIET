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

date* food::getDeliveryDatePtr() {
    return &this->delivery_date;
}

void item::setName(char* name) {
    this->name = new char[strlen(name) + 1];
    strcpy_s(this->name, strlen(name) + 1, name);
}

void item::setPrice(double price) {
    this->price = price;
}

void item::setQuant(int quant) {
    this->quant = quant;
}

ostream& operator<<(ostream& os, food& food_item) {
    return os << "Food: " << food_item.getName() << "  " << food_item.getPrice() << "  " << *(food_item.getQuantPtr()) << " " << *(food_item.getDeliveryDatePtr()->getDayPtr()) << "." << *(food_item.getDeliveryDatePtr()->getMonthPtr()) << "." << *(food_item.getDeliveryDatePtr()->getYearPtr());
}

int food::init(char* name, int len, double price, int quant, int day, int month, int year) {
    this->setName(name);
    this->setPrice(price);
    this->setQuant(quant);
    this->delivery_date = date(day, month, year);
    return 1;
}

int food::init() {
    char b;
    char buf_init[80];
    cout << "Enter name: ";
    cin.get(buf_init, 80);
    cin.clear();
    cin.get(b);
    while (b != '\n') {
        cin.get(b);
    }

    this->setName(buf_init);
    cout << "Enter price(number with float point): ";
    cin.get(buf_init, 80);
    cin.clear();
    cin.get(b);
    while (b != '\n') {
        cin.get(b);
    }
    if (!checkDouble(buf_init)) {
        this->setPrice(10.0);
    }
    else {
        this->setPrice(strtod(buf_init, NULL));
    }

    cout << "Enter quantity(positive integer): ";
    cin.get(buf_init, 80);
    cin.clear();
    cin.get(b);
    while (b != '\n') {
        cin.get(b);
    }
    if (!checkInt(buf_init)) {
        cout << "Not a positive integer.\n";
        this->setQuant(1);
    }
    else {
        this->setQuant(atoi(buf_init));
    }
    cout << "Enter day of delivery: ";
    cin.get(buf_init, 80);
    cin.clear();
    cin.get(b);
    while (b != '\n') {
        cin.get(b);
    }
    if (!checkInt(buf_init) || atoi(buf_init) < 1 || atoi(buf_init) > 31) {
        cout << "Not a valid day.\n";
        this->delivery_date = date();
        return 1;
    }
    int day = atoi(buf_init);
    cout << "Enter number of month of delivery(1-12): ";
    cin.get(buf_init, 80);
    cin.clear();
    cin.get(b);
    while (b != '\n') {
        cin.get(b);
    }
    if (!checkInt(buf_init) || atoi(buf_init) < 1 || atoi(buf_init) > 12) {
        cout << "Not a valid month.\n";
        this->delivery_date = date();
        return 1;
    }
    int month = atoi(buf_init);
    cout << "Enter year of delivery: ";
    cin.get(buf_init, 80);
    cin.clear();
    cin.get(b);
    while (b != '\n') {
        cin.get(b);
    }
    if (!checkInt(buf_init) || atoi(buf_init) < 1) {
        cout << "Not a valid year.\n";
        this->delivery_date = date();
        return 1;
    }
    int year = atoi(buf_init);
    this->delivery_date = date(day, month, year);
    return 1;
}

bool food::operator>(const date& otherDate) { 
    return this->delivery_date.year > otherDate.year ||
        (this->delivery_date.year == otherDate.year && this->delivery_date.month > otherDate.month) ||
        (this->delivery_date.year == otherDate.year && this->delivery_date.month == otherDate.month && this->delivery_date.day > otherDate.day);
 }

int toy::init(char* name, int len, double price, int quant, int age_limit) {
    this->setName(name);
    this->setPrice(price);
    this->setQuant(quant);
    this->age_limit = age_limit;
    return 1;
}

int item::getType() {
    return 0;
}

int food::getType() {
    return 1;
}

food::food() {
    cout << 2;
}

item::item() {
    cout << 1;
}

int toy::getType() {
    return 2;
}

int toy::init() {
    char b;
    char buf_init[80];
    cout << "Enter name: ";
    cin.get(buf_init, 80);
    cin.clear();
    cin.get(b);
    while (b != '\n') {
        cin.get(b);
    }

    this->setName(buf_init);
    cout << "Enter price(number with float point): ";
    cin.get(buf_init, 80);
    cin.clear();
    cin.get(b);
    while (b != '\n') {
        cin.get(b);
    }
    if (!checkDouble(buf_init)) {
        this->setPrice(10.0);
    }
    else {
        this->setPrice(strtod(buf_init, NULL));
    }

    cout << "Enter quantity(positive integer): ";
    cin.get(buf_init, 80);
    cin.clear();
    cin.get(b);
    while (b != '\n') {
        cin.get(b);
    }
    if (!checkInt(buf_init)) {
        cout << "Not a positive integer.\n";
        this->setQuant(1);
    }
    else {
        this->setQuant(atoi(buf_init));
    }
    cout << "Enter age limit: ";
    cin.get(buf_init, 80);
    cin.clear();
    cin.get(b);
    while (b != '\n') {
        cin.get(b);
    }
    if (!checkInt(buf_init) || atoi(buf_init) < 0) {
        cout << "Not a valid age limit.\n";
        this->age_limit = 0;
        return 1;
    }
    this->age_limit = atoi(buf_init);
    return 1;
}

int toy::getAgeLimit() {
    return this->age_limit;
}

std::ostream& operator<<(std::ostream& os, toy& item){
    return os << "Toy: " << item.getName() << "  " << item.getPrice() << "  " << *(item.getQuantPtr()) << " " << item.age_limit;
}

bool item::isName(char* name) {
    return strcmp(this->name, name) == 0;
}

bool item::showName(char* name) {
    if (isName(name)) {
        cout << this->getName() << "  " << this->getPrice() << "  " << *(this->getQuantPtr()) << endl;
        return true;
    }
    return false;
}

char* item::getName() {
    return name;
}

int* toy::getAgeLimitPtr(){
    return &this->age_limit;
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
        cout << this->getName() << "  " << this->getPrice() << "  " << *(this->getQuantPtr()) << endl;
        return true;
    }
    return false;
}

bool food::showCostMore(double cost) {
    if (isCostMore(cost)) {
        cout << "Food: " << this->getName() << "  " << this->getPrice() << "  " << *(this->getQuantPtr()) << endl;
        return true;
    }
    return false;
}

bool toy::showCostMore(double cost) {
    if (isCostMore(cost)) {
        cout << "Toy: " << this->getName() << "  " << this->getPrice() << "  " << *(this->getQuantPtr()) << endl;
        return true;
    }
    return false;
}

int* item::getQuantPtr() {
    return &this->quant;
}

storage::storage(int n) {
    this->database = new item*[n];
    this->current_count = 0;
    this->n = n;
}

void storage::searchName() {
    char buf_name[80];
    char b;
    cout << "Enter name to search: ";
    cin.get(buf_name, 80);
    cin.clear();
    cin.get(b);
    while (b != '\n') {
        cin.get(b);
    }
    for (int i = 0; i < current_count; i++) {
        if (this->database[i]->showName(buf_name)) {
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
    int type, len;
    outFile.write(reinterpret_cast<char*>(&current_count), sizeof(current_count));
    for (int i = 0; i < current_count; i++) {
        type = this->database[i]->getType();
        len = strlen(this->database[i]->getName());
        outFile.write(this->database[i]->getName(), sizeof(char)*(len + 1));
        outFile.write(reinterpret_cast<char*>(this->database[i]->getPricePtr()), sizeof(double));
        outFile.write(reinterpret_cast<char*>(this->database[i]->getQuantPtr()), sizeof(int));
        outFile.write(reinterpret_cast<char*>(&type), sizeof(int));
        switch (type) {
        case 1: {
            outFile.write(reinterpret_cast<char*>(((food*)(this->database[i]))->getDeliveryDatePtr()->getDayPtr()), sizeof(int));
            outFile.write(reinterpret_cast<char*>(((food*)(this->database[i]))->getDeliveryDatePtr()->getMonthPtr()), sizeof(int));
            outFile.write(reinterpret_cast<char*>(((food*)(this->database[i]))->getDeliveryDatePtr()->getYearPtr()), sizeof(int));
            break;
        }
        case 2:
            int ageLim = ((toy*)(this->database[i]))->getAgeLimit();
            outFile.write(reinterpret_cast<char*>(&ageLim), sizeof(int));
            break;
        }
    }
    outFile.close();
    return 0;
}

void storage::add() {
    if (this->current_count < this->n) {
        char b;
        int type;
        char buf_type[80];
        cout << "Enter type of item to add(1 - food, 2 - toy): ";
        cin.get(buf_type, 80);
        cin.clear();
        cin.get(b);
        while (b != '\n') {
            cin.get(b);
        }
        if (!checkInt(buf_type) || (atoi(buf_type) != 1 && atoi(buf_type) != 2)) {
            cout << "Incorrect type.\n";
            return;
        }
        type = atoi(buf_type);
        if (type == 1) {
            this->database[current_count] = new food();
            food* new_food = (food*)(this->database[current_count]);
            this->current_count += new_food->init();
        }
        else {
            this->database[current_count] = new toy();
            toy* new_toy = (toy*)(this->database[current_count]);
            this->current_count += new_toy->init();
        }
    }
    else {
        cout << "No available space in database." << endl;
    }
}

void storage::show() {
    if (current_count > 0) {
        for (int i = 0; i < current_count; i++) {
            if (this->database[i]->getType() == 1) {
                cout << *(food*)(this->database[i]) << endl;
            }
            else {
                cout << *(toy*)(this->database[i]) << endl;
            }
        }
    }
    else {
        cout << "No items.\n";
    }
}

void storage::searchCost() {
    char buf_cost[80];
    char b;
    cout << "Enter cost to search: ";
    cin.get(buf_cost, 80);
    cin.clear();
    cin.get(b);
    while (b != '\n') {
        cin.get(b);
    }
    if (!checkDouble(buf_cost)) {
        cout << "Not a valid number.\n";
        return;
    }
    double cost = strtod(buf_cost, NULL);
    bool isFound = false;
    for (int i = 0; i < current_count; i++) {
        if (this->database[i]->showCostMore(cost)) {
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
        int type;
        inFile.read(reinterpret_cast<char*>(&type), sizeof(int));
        switch (type) {
        case 1: {
            int day, month, year;
            inFile.read(reinterpret_cast<char*>(&day), sizeof(int));
            inFile.read(reinterpret_cast<char*>(&month), sizeof(int));
            inFile.read(reinterpret_cast<char*>(&year), sizeof(int));
            food* new_food = new food;
            this->current_count += new_food->init(name, len, price, quant, day, month, year);
            this->database[this->current_count - 1] = new_food;
            break;
        }
        case 2: {
            int age_limit;
            inFile.read(reinterpret_cast<char*>(&age_limit), sizeof(int));
            toy* new_toy = new toy;
            this->current_count += new_toy->init(name, len, price, quant, age_limit);
            this->database[this->current_count - 1] = new_toy;
            break;
        }
        }
    }
    inFile.close();
    return 0;
}

void storage::show_total() {
    cout << "Total amount of items: " << this->current_count << endl;
}

void storage::compare() {
    for (int i = 0; i < current_count; i++) {
        if (this->database[i]->getType() == 1)
        cout << *(food*)(this->database[i]) << endl;
    }
    cout << "Enter, which item to compare(index, starts with 0): ";
    char buf_index[80];
    char b;
    cin.get(buf_index, 80);
    cin.clear();
    cin.get(b);
    while (b != '\n') {
        cin.get(b);
    }
    if (!checkInt(buf_index)) {
        cout << "Incorrect number format.\n";
        return;
    }
    int index = atoi(buf_index);
    if (index < 0 || index >= current_count) {
        cout << "Incorrect index.\n";
        return;
    }
    bool found = false;
    int current_index = 0;
    food item_to_compare;
    for (int i = 0; i < current_count; i++) {
        if (this->database[i]->getType() == 1) {
            if (current_index == index) {
                item_to_compare = *((food*)(this->database[i]));
                found = true;
                break;
            }
            current_index++;
        }
    }
    if (!found) {
        cout << "Not found such food.\n";
        return;
    }
    cout << "Enter year to compare: ";
    char buf_year[80];
    cin.get(buf_year, 80);
    cin.clear();
    cin.get(b);
    while (b != '\n') {
        cin.get(b);
    }
    if (!checkInt(buf_year)) {
        cout << "Incorrect number format.\n";
        return;
    }
    int year = atoi(buf_year);
    cout << "Enter month to compare: ";
    char buf_month[80];
    cin.get(buf_month, 80);
    cin.clear();
    cin.get(b);
    while (b != '\n') {
        cin.get(b);
    }
    if (!checkInt(buf_month) || atoi(buf_month) < 1 || atoi(buf_month) > 12) {
        cout << "Incorrect number format.\n";
        return;
    }
    int month = atoi(buf_month);
    cout << "Enter day to compare: ";
    char buf_day[80];
    cin.get(buf_day, 80);
    cin.clear();
    cin.get(b);
    while (b != '\n') {
        cin.get(b);
    }
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
    char b;
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
        cout << "Choose a function to use to a warehouse:\n";
        cout << "1 - add new item\n";
        cout << "2 - show all items\n";
        cout << "3 - total amount of items\n"; 
        cout << "4 - find item by name\n";
        cout << "5 - find items with cost more than input\n";
        cout << "6 - compare item to date\n";
        cout << "Other number - leave the programm and save to file\n";
        cout << "Your choice: ";
        cin.get(buffer, 3);
        cin.clear();
        cin.get(b);
        while (b != '\n') {
            cin.get(b);
        }
        if (!checkInt(buffer)) {
            printf("Not a number!\n");
            system("pause");
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
    switch (write) {
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
