#include "database.h"

using namespace std;

const char* storage::filename = "data.bin";

bool checkInt(char* buffer) {
    for (int i = 0; i < strlen(buffer); i++) {
        if (buffer[i] == 10) return true;
        if (buffer[i] < 48 || buffer[i] > 57) return false;
    }
    return true;
}

bool checkDouble(char* buffer) {
    int have_digit = 0;
    int num_of_sep = 0;
    for (int i = 0; i < strlen(buffer); i++) {
        if (buffer[i] != 44 && buffer[i] != 10 && buffer[i] != 46 && (buffer[i] < 48 || buffer[i] > 57)) {
            cout << "Incorrect number format.\n";
            return false;
        }
        else if (buffer[i] < 58 && buffer[i] > 47) {
            have_digit = 1;
        }
        else if (buffer[i] == 44 || buffer[i] == 46) {
            num_of_sep++;
        }
    }
    if (!have_digit || num_of_sep > 1 || (buffer[0] < 48 || buffer[0] > 57)) {
        cout << "Incorrect number format.\n";
        return false;
    }
    return true;
}

int readNumber() {
    ifstream iFil(storage::filename, ios::binary);
    if (!iFil) {
        return 0;
    }
    int amount1=0;
    iFil.read(reinterpret_cast<char*>(&amount1), sizeof(amount1));
    if (iFil.eof()) {
        iFil.close();
        return 0;
    }
    iFil.close();
    return amount1;
}

int enterNumber() {
    char buff_n[80];
    int amount = readNumber();
    while (true) {
        cout << "Write n: ";
        cin >> buff_n;
        if (!checkInt(buff_n)) {
            cout << "Wrong.\n";
        }
        else if (atoi(buff_n) < amount) {
            cout << "Too small.\n";
        }
        else if (atoi(buff_n) <= 0) {
            cout << "Non positive.\n";
        }
        else {
            break;
        }
        system("pause");
    }
    return atoi(buff_n);
}

int item::init(char* name, int len, double price, int quant) {
    this->name = new char[len + 1];
    strcpy_s(this->name, len + 1, name);
    this->price = price;
    this->quant = quant;
    return 1;
}

int item::init() {
    char buf_name[80];
    cout << "Name: ";
    cin >> buf_name;

    this->name = new char[strlen(buf_name) + 1];
    strcpy_s(this->name, strlen(buf_name) + 1, buf_name);

    char buf_price[80];
    cout << "Price: ";
    cin >> buf_price;
    if (!checkDouble(buf_price)) {
        this->price = 10.0;
    }
    else {
        this->price = strtod(buf_price, NULL);
    }

    char buff_quant[80];
    cout << "Quant: ";
    cin >> buff_quant;
    if (!checkInt(buff_quant)) {
        cout << "Incorrect number format.\n";
        this->quant = 1;
    }
    else {
        this->quant = atoi(buff_quant);
    }
    return 1;
}

void item::show() {
    cout << name << "  " << price << "  " << quant << endl;
}

bool item::isName(char* name) {
    return strcmp(this->name, name) == 0;
}

bool item::showName(char* name) {
    if (isName(name)) {
        show();
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
        show();
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
    cout << "Name: ";
    cin >> buf_name;
    for (int i = 0; i < current_count; i++) {
        if (this->database[i].showName(buf_name)) {
            return;
        }
    }
    cout << "Not found.\n";
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
    }
    outFile.close();
    return 0;
}

void storage::add() {
    if (this->current_count < this->n) {
        this->current_count += this->database[current_count].init();
    }
    else {
        cout << "No available space" << endl;
    }
}

void storage::show() {
    for (int i = 0; i < current_count; i++) {
        this->database[i].show();
    }
}

void storage::searchCost() {
    char buf_cost[80];
    cout << "Cost: ";
    cin >> buf_cost;
    if (!checkDouble(buf_cost)) {
        cout << "Incorrect number format.\n";
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
        cout << "Not found.\n";
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
        this->current_count += this->database[i].init(name, len, price, quant);
    }
    inFile.close();
    return 0;
}

void storage::show_total() {
    cout << "Total: " << this->current_count << endl;
}

storage::~storage() {
    delete[] database;
}

storage* warehouse;

void database() {
    int n = 0;
    n = enterNumber();
    warehouse = new storage(n);
    int read = (*warehouse).readfile();
    switch (read) {
    case 1: {
        cout << "There is no file" << endl;
        break;
    }
    case 2: {
        cout << "Empty file" << endl;
        break;
    }
    case 0: {
        cout << "All corect" << endl;
        break;
    }
    }
    system("pause");
    int choose;
    char buffer[80];
    do {
        system("cls");
        choose = 1;
        cout << "Choose(1 - add, 2 - show, 3 - total, 4 - find name, 5 - find more cost): ";
        cin >> buffer;
        if (!checkInt(buffer)) {
            printf("Incorrect!\n");
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
        }
        system("pause");
    } while (choose > 0 && choose < 6);

    int write = (*warehouse).write_to_file();
    switch (read) {
    case 1: {
        cout << "Error openning file" << endl;
        break;
    }
    case 0: {
        cout << "All corect" << endl;
        break;
    }
    }
    delete warehouse;
}
