#include <iostream>

using namespace std;

class Person {
	char* firstName;
	char* lastName;
	friend istream& operator>>(istream& is, Company& comp);
public:
	Person(char* firstName, char* lastName) {
		this->firstName = new char[strlen(firstName) + 1];
		strcpy_s(this->firstName, strlen(firstName)+1, firstName);
		this->lastName = new char[strlen(lastName) + 1];
		strcpy_s(this->lastName, strlen(lastName) + 1, lastName);
	}
	
	Person(){
		this->firstName = nullptr;
		this->lastName = nullptr;
	}

	void set_firstName(char* firstName){
		this->firstName = new char[strlen(firstName) + 1];
		strcpy_s(this->firstName, strlen(firstName) + 1, firstName);
	}

	void set_lastName(char* lastName) {
		this->lastName = new char[strlen(lastName) + 1];
		strcpy_s(this->lastName, strlen(lastName) + 1, lastName);
	}

	char* get_firstName() {
		char* buff = new char[strlen(firstName) + 1];
		strcpy_s(buff, strlen(firstName) + 1, firstName);
		return buff;
	}

	char* get_lastName() {
		char* buff = new char[strlen(lastName) + 1];
		strcpy_s(buff, strlen(lastName) + 1, lastName);
		return buff;
	}

	~Person() {
		delete[] firstName;
		delete[] lastName;
	}

	friend istream& operator>>(istream& is, Person& pers);
	friend ostream& operator<<(ostream& os, Person& pers);
};

bool checkInt(char* buffer) {
	for (int i = 0; i < strlen(buffer); i++) {
		if (buffer[i] == 10) return true;
		if (buffer[i] < 48 || buffer[i] > 57) return false;
	}
	return true;
}

istream& operator>>(istream& is, Person& pers) {
	char buf_init[80];
	cout << "Enter first name: ";
	is >> buf_init;
	pers.firstName = new char[strlen(buf_init) + 1];
	strcpy_s(pers.firstName, strlen(buf_init) + 1, buf_init);
	cout << "Enter last name: ";
	is >> buf_init;
	pers.lastName = new char[strlen(buf_init) + 1];
	strcpy_s(pers.lastName, strlen(buf_init) + 1, buf_init);
	return is;
}

ostream& operator<<(ostream& os, Person& pers) {
	return os << pers.firstName << pers.lastName;
}

class Company {
	Person director;
	char* address;
	int INN;

public:
	Company(Person director, char* adress, int INN) {
		this->director = director;
		this->address = adress;
		this->INN = INN;
	}
	Company() {
		this->director = Person();
		this->address = nullptr;
		this->INN = 1;
	}
	~Company() {
		delete[] address;
	}
	Person& get_director() {
		return director;
	}
	void set_director(Person& director) {
		this->director = director;
	}
	char* get_address() {
		char* add = new char[strlen(address) + 1];
		strcpy_s(add, strlen(address) + 1, address);
		return add;
	}
	void set_address(char* address) {
		this->address = new char[strlen(address) + 1];
		strcpy_s(this->address, strlen(address) + 1, address);
	}
	int get_INN() {
		return INN;
	}
	void set_INN(int INN) {
		if (INN > 0) {
			this->INN = INN;
		}
	}

	bool operator==(Company& comp1) {
		if (strcmp(this->director.get_firstName(), comp1.director.get_firstName())==0) {
			if (strcmp(this->director.get_lastName(), comp1.director.get_lastName())==0) {
				return true;
			}
		}
		return false;
	}

	friend istream& operator>>(istream& is, Company& comp);
	friend ostream& operator<<(ostream& os, Company& comp);
};

istream& operator>>(istream& is, Company& comp) {
	Person director;
	char buf_init[80];
	cout << "Enter first name: ";
	is >> buf_init;
	director.firstName = new char[strlen(buf_init) + 1];
	strcpy_s(director.firstName, strlen(buf_init) + 1, buf_init);
	cout << "Enter last name: ";
	is >> buf_init;
	director.lastName = new char[strlen(buf_init) + 1];
	strcpy_s(director.lastName, strlen(buf_init) + 1, buf_init);
	return is;
	char buf_init[80];
	cout << "Enter address: ";
	is >> buf_init;
	char* address = new char[strlen(buf_init) + 1];
	strcpy_s(address, strlen(buf_init)+1, buf_init);
	cout << "Enter INN(positive integer): ";
	is >> buf_init;
	int INN = 0;
	if (!checkInt(buf_init)) {
		cout << "Not a positive integer.\n";
		INN = 1;
	}
	else {
		INN = atoi(buf_init);
	}
	comp.address = address;
	comp.director = director;
	comp.INN = INN;
	return is;
}

ostream& operator<<(ostream& os, Company& comp) {
	os << comp.director;
	os << comp.address << comp.INN;
	return os;
}

int main() {
	Company* faang = new Company[1];
	for (int i = 0; i < 1; i++) {
		cin >> faang[i];
	}
	for (int i = 0; i < 1; i++) {
		cout << faang[i] << '\n';
	}
	cout << "Equals:\n";
	for (int i = 0; i < 1; i++) {
		for (int j = 0; j < 1; j++) {
			if (faang[i] == faang[j]) {
				cout << faang[i] << "\n" << faang[j] << '\n';
			}
		}
	}

	delete[] faang;
}
