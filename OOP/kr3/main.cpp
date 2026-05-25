#include "main.h"

product::product() {
	id = 0;
	name = nullptr;
	cost = 0;
}

product::~product() {
	delete name;
}

void product::set_id(int id) {
	this->id = id;
}

void product::set_name(char* name) {
	delete this->name;
	this->name = new char[strlen(name) + 1];
	strcpy_s(this->name, strlen(name) + 1, name);
}

void product::set_cost(float cost) {
	this->cost = cost;
}

float product::get_cost() {
	return cost;
}

int product::get_id() {
	return id;
}

char* product::get_name() {
	char* buff = new char[strlen(name) + 1];
	strcpy_s(buff, strlen(name) + 1, name);
	return buff;
}

groupOfProducts::groupOfProducts() {
	id = 0;
	name = nullptr;
}

groupOfProducts::~groupOfProducts() {
	delete name;
}

void groupOfProducts::set_id(int id) {
	this->id = id;
}

void groupOfProducts::set_name(char* name) {
	delete this->name;
	this->name = new char[strlen(name) + 1];
	strcpy_s(this->name, strlen(name) + 1, name);
}

int groupOfProducts::get_id() {
	return id;
}

char* groupOfProducts::get_name() {
	char* buff = new char[strlen(name) + 1];
	strcpy_s(buff, strlen(name) + 1, name);
	return buff;
}

void User::set_name(char* name) {
	delete[] this->name;  // используйте delete[] для массивов char

	if (name == nullptr) {
		this->name = nullptr;
		return;
	}

	this->name = new char[strlen(name) + 1];
	strcpy_s(this->name, strlen(name) + 1, name);
}

void User::set_surname(char* surname) {
	delete[] this->surname;  // используйте delete[] для массивов char

	if (surname == nullptr) {
		this->surname = nullptr;
		return;
	}

	this->surname = new char[strlen(surname) + 1];
	strcpy_s(this->surname, strlen(surname) + 1, surname);
}

void User::set_phone(char* phone) {
	delete[] this->phone;  // используйте delete[] для массивов char

	if (phone == nullptr) {
		this->phone = nullptr;
		return;
	}

	this->phone = new char[strlen(phone) + 1];
	strcpy_s(this->phone, strlen(phone) + 1, phone);
}

void User::set_basePercent(float basePercent) {
	this->basePercent = basePercent;
}

char* User::get_name() {
	char* buff = new char[strlen(name) + 1];
	strcpy_s(buff, strlen(name) + 1, name);
	return buff;
}

char* User::get_surname() {
	char* buff = new char[strlen(surname) + 1];
	strcpy_s(buff, strlen(surname) + 1, surname);
	return buff;
}

char* User::get_phone() {
	char* buff = new char[strlen(phone) + 1];
	strcpy_s(buff, strlen(phone) + 1, phone);
	return buff;
}

float User::get_basePercent() {
	return basePercent;
}

standartUser::standartUser() {
	set_name(nullptr);
	set_surname(nullptr);
	set_phone(nullptr);
	set_basePercent(0);
}

standartUser::~standartUser() {
	set_name(nullptr);
	set_surname(nullptr);
	set_phone(nullptr);
}

pensionerUser::pensionerUser() {
	set_name(nullptr);
	set_surname(nullptr);
	set_phone(nullptr);
	set_basePercent(0);
	set_extraPercent(0);
}

pensionerUser::~pensionerUser() {
	set_name(nullptr);
	set_surname(nullptr);
	set_phone(nullptr);
}

void pensionerUser::set_extraPercent(float exPer){
	extraPercent = exPer;
}

float pensionerUser::get_extraPercent() {
	return extraPercent;
}

float pensionerUser::calc_percent() {
	return get_extraPercent() * get_basePercent();
}

int pensionerUser::calc_price(product& prod) {
	float percent = calc_percent();
	return prod.get_cost() * (1 - percent);
}

VIPUser::VIPUser() {
	set_name(nullptr);
	set_surname(nullptr);
	set_phone(nullptr);
	set_basePercent(0);
	set_extraPercent(0);
	set_dates(nullptr, 0);
}

VIPUser::~VIPUser() {
	set_name(nullptr);
	set_surname(nullptr);
	set_phone(nullptr);
	set_dates(nullptr, 0);
}

void VIPUser::set_extraPercent(float extraPercent) {
	this->extraPercent = extraPercent;
}

float VIPUser::get_extraPercent() {
	return extraPercent;
}

void VIPUser::set_dates(tm** dates, int countDates) {
	// Очищаем старые данные
	for (int i = 0; i < this->countDates; i++) {
		delete this->dates[i];
	}
	delete[] this->dates;

	this->countDates = countDates;
	if (countDates == 0) {
		this->dates = nullptr;
		return;
	}

	this->dates = new tm * [countDates];
	for (int i = 0; i < countDates; i++) {
		this->dates[i] = new tm;
		this->dates[i]->tm_year = dates[i]->tm_year;
		this->dates[i]->tm_mon = dates[i]->tm_mon;
		this->dates[i]->tm_mday = dates[i]->tm_mday;
	}
}

tm** VIPUser::get_dates() {
	tm** buffer = new tm * [countDates];
	for (int i = 0; i < countDates; i++) {
		buffer[i]->tm_year = this->dates[i]->tm_year;
		buffer[i]->tm_mon = this->dates[i]->tm_mon;
		buffer[i]->tm_mday = this->dates[i]->tm_mday;
	}
	return buffer;
}

int VIPUser::get_countDates() {
	return countDates;
}

float VIPUser::calc_percent() {
	time_t now = time(0);
	tm ltm;
	localtime_s(&ltm, &now); // Правильный вызов

	for (int i = 0; i < countDates; i++) {
		if (ltm.tm_year == dates[i]->tm_year &&
			ltm.tm_mon == dates[i]->tm_mon &&
			ltm.tm_mday == dates[i]->tm_mday) {
			return get_basePercent() + get_extraPercent();
		}
	}
	return get_basePercent();
}

int VIPUser::calc_price(product& prod) {
	float percent = calc_percent();
	return prod.get_cost() * (1 - percent);
}

float standartUser::calc_percent() {
	return get_basePercent();
}

int standartUser::calc_price(product& prod) {
	return prod.get_cost() * (1 - calc_percent());
}

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
		cout << "Standart user " << i << " name: ";
		cin >> name;
		cout << "Standart user " << i << " surname: ";
		cin >> surname;
		cout << "Standart user " << i << " phone: ";
		cin >> phone;
		cout << "Standart user " << i << " basePercent: ";
		cin >> basePercent;
		standUsers[i].set_name(name);
		standUsers[i].set_surname(surname);
		standUsers[i].set_phone(phone);
		standUsers[i].set_basePercent(basePercent);
		cout << "pensioner user " << i << " name: ";
		cin >> name;
		cout << "pensioner user " << i << " surname: ";
		cin >> surname;
		cout << "pensioner user " << i << " phone: ";
		cin >> phone;
		cout << "pensioner user " << i << " basePercent: ";
		cin >> basePercent;
		cout << "pensioner user " << i << " extraPercent: ";
		cin >> extraPercent;
		pensUsers[i].set_name(name);
		pensUsers[i].set_surname(surname);
		pensUsers[i].set_phone(phone);
		pensUsers[i].set_basePercent(basePercent);
		pensUsers[i].set_extraPercent(extraPercent);
		cout << "VIP user " << i << " name: ";
		cin >> name;
		cout << "VIP user " << i << " surname: ";
		cin >> surname;
		cout << "VIP user " << i << " phone: ";
		cin >> phone;
		cout << "VIP user " << i << " basePercent: ";
		cin >> basePercent;
		cout << "VIP user " << i << " extraPercent: ";
		cin >> extraPercent;
		cout << "VIP user " << i << " countDates: ";
		cin >> countDates;
		tm** dates = new tm * [countDates];
		for (int j = 0; j < countDates; j++) {
			cout << "VIP user " << i << " date№ " << j << " year: ";
			cin >> dates[i]->tm_year;
			dates[i]->tm_year -= 1900;
			cout << "VIP user " << i << " date№ " << j << " month: ";
			cin >> dates[i]->tm_mon;
			cout << "VIP user " << i << " date№ " << j << " day: ";
			cin >> dates[i]->tm_mday;
		}
		vipUsers[i].set_dates(dates, countDates);
		vipUsers[i].set_name(name);
		vipUsers[i].set_surname(surname);
		vipUsers[i].set_phone(phone);
		vipUsers[i].set_basePercent(basePercent);
		vipUsers[i].set_extraPercent(extraPercent);
	}
	int id;
	char name[80];
	float cost;
	cout << "Write product's id: ";
	cin >> id;
	cout << "Write product's name: ";
	cin >> name;
	cout << "Write product's cost: ";
	cin >> cost;
	product pr;
	pr.set_cost(cost);
	pr.set_id(id);
	pr.set_name(name);
	for (int i = 0; i < 3; i++) {
		cout << standUsers[i].calc_price(pr);
		cout << pensUsers[i].calc_price(pr);
		cout << vipUsers[i].calc_price(pr);
	}
}