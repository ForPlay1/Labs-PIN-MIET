#include <iostream>
#include <cstring>

using namespace std;

class Company;

class Person {
    char* firstName;
    char* lastName;
    friend istream& operator>>(istream& is, Company& comp);
public:
    Person(const char* firstName, const char* lastName) {
        this->firstName = new char[strlen(firstName) + 1];
        strcpy_s(this->firstName, strlen(firstName) + 1, firstName);
        this->lastName = new char[strlen(lastName) + 1];
        strcpy_s(this->lastName, strlen(lastName) + 1, lastName);
    }

    Person() {
        this->firstName = nullptr;
        this->lastName = nullptr;
    }

    Person(const Person& other) {
        if (other.firstName) {
            this->firstName = new char[strlen(other.firstName) + 1];
            strcpy_s(this->firstName, strlen(other.firstName) + 1, other.firstName);
        }
        else this->firstName = nullptr;

        if (other.lastName) {
            this->lastName = new char[strlen(other.lastName) + 1];
            strcpy_s(this->lastName, strlen(other.lastName) + 1, other.lastName);
        }
        else this->lastName = nullptr;
    }

    Person& operator=(const Person& other) {
        if (this != &other) {
            delete[] firstName;
            delete[] lastName;

            if (other.firstName) {
                this->firstName = new char[strlen(other.firstName) + 1];
                strcpy_s(this->firstName, strlen(other.firstName) + 1, other.firstName);
            }
            else this->firstName = nullptr;

            if (other.lastName) {
                this->lastName = new char[strlen(other.lastName) + 1];
                strcpy_s(this->lastName, strlen(other.lastName) + 1, other.lastName);
            }
            else this->lastName = nullptr;
        }
        return *this;
    }

    void set_firstName(const char* firstName) {
        delete[] this->firstName;
        this->firstName = new char[strlen(firstName) + 1];
        strcpy_s(this->firstName, strlen(firstName) + 1, firstName);
    }

    void set_lastName(const char* lastName) {
        delete[] this->lastName;
        this->lastName = new char[strlen(lastName) + 1];
        strcpy_s(this->lastName, strlen(lastName) + 1, lastName);
    }

    const char* get_firstName() const {
        return firstName ? firstName : "";
    }

    const char* get_lastName() const {
        return lastName ? lastName : "";
    }

    ~Person() {
        delete[] firstName;
        firstName = nullptr;
        delete[] lastName;
        lastName = nullptr;
    }

    friend istream& operator>>(istream& is, Person& pers);
    friend ostream& operator<<(ostream& os, const Person& pers);
};

bool checkInt(const char* buffer) {
    for (size_t i = 0; i < strlen(buffer); i++) {
        if (buffer[i] == 10) return true;
        if (buffer[i] < '0' || buffer[i] > '9') return false;
    }
    return true;
}

istream& operator>>(istream& is, Person& pers) {
    char buf_init[80];
    cout << "Enter first name: ";
    is >> buf_init;
    pers.set_firstName(buf_init);

    cout << "Enter last name: ";
    is >> buf_init;
    pers.set_lastName(buf_init);
    return is;
}

ostream& operator<<(ostream& os, const Person& pers) {
    return os << pers.get_firstName() << " " << pers.get_lastName();
}

class Company {
    Person director;
    char* address;
    int INN;

public:
    Company(Person director, const char* address, int INN) {
        this->director = director;
        this->address = new char[strlen(address) + 1];
        strcpy_s(this->address, strlen(address) + 1, address);
        this->INN = INN;
    }
    Company() {
        this->director = Person();
        this->address = nullptr;
        this->INN = 1;
    }

    Company(const Company& other) {
        this->director = other.director;
        this->INN = other.INN;
        if (other.address) {
            this->address = new char[strlen(other.address) + 1];
            strcpy_s(this->address, strlen(other.address) + 1, other.address);
        }
        else this->address = nullptr;
    }

    Company& operator=(const Company& other) {
        if (this != &other) {
            delete[] address;
            this->director = other.director;
            this->INN = other.INN;
            if (other.address) {
                this->address = new char[strlen(other.address) + 1];
                strcpy_s(this->address, strlen(other.address) + 1, other.address);
            }
            else this->address = nullptr;
        }
        return *this;
    }

    ~Company() {
        delete[] address;
    }

    Person& get_director() {
        return director;
    }
    void set_director(const Person& director) {
        this->director = director;
    }
    const char* get_address() const {
        return address ? address : "";
    }
    void set_address(const char* address) {
        delete[] this->address;
        this->address = new char[strlen(address) + 1];
        strcpy_s(this->address, strlen(address) + 1, address);
    }
    int get_INN() const {
        return INN;
    }
    void set_INN(int INN) {
        if (INN > 0) {
            this->INN = INN;
        }
    }

    bool operator==(const Company& comp1) const {
        if (strcmp(this->director.get_firstName(), comp1.director.get_firstName()) == 0) {
            if (strcmp(this->director.get_lastName(), comp1.director.get_lastName()) == 0) {
                return true;
            }
        }
        return false;
    }

    friend istream& operator>>(istream& is, Company& comp);
    friend ostream& operator<<(ostream& os, const Company& comp);
};

istream& operator>>(istream& is, Company& comp) {
    is >> comp.director;

    char buf_init[80];
    cout << "Enter address: ";
    is >> buf_init;
    comp.set_address(buf_init);

    cout << "Enter INN(positive integer): ";
    is >> buf_init;
    if (!checkInt(buf_init)) {
        cout << "Not a positive integer. Set to 1.\n";
        comp.INN = 1;
    }
    else {
        comp.INN = atoi(buf_init);
    }

    return is;
}

ostream& operator<<(ostream& os, const Company& comp) {
    os << "Director: " << comp.director << " | Address: " << comp.get_address() << " | INN: " << comp.INN;
    return os;
}

int main() {
    Company* faang = new Company[3];

    for (int i = 0; i < 3; i++) {
        cin >> faang[i];
    }

    cout << "\n--- Result ---\n";
    for (int i = 0; i < 3; i++) {
        cout << faang[i] << '\n';
    }

    cout << "\nEquals:\n";
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (faang[i] == faang[j]) {
                cout << faang[i] << "\n" << faang[j] << '\n';
            }
        }
    }

    delete[] faang;
    return 0;
}