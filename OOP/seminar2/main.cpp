#include <iostream>
#include <cstring>
#include <locale>
#define _CRT_SECURE_NO_WARNINGS

using namespace std;

class AccountHolder {
	char* firstName;
	char* lastName;
public:
	AccountHolder() {
		firstName = nullptr;
		lastName = nullptr;
	}
	AccountHolder(AccountHolder& holder1) {
		firstName = new char[strlen(holder1.firstName) + 1];
		strcpy_s(firstName, strlen(holder1.firstName)+1, holder1.firstName);
		lastName = new char[strlen(holder1.lastName) + 1];
		strcpy_s(lastName, strlen(holder1.lastName)+1, holder1.lastName);
	}
	AccountHolder(char* firstName, char* lastName) {
		this->firstName = new char[strlen(firstName) + 1];
		strcpy_s(this->firstName, strlen(firstName)+1, firstName);
		this->lastName = new char[strlen(lastName) + 1];
		strcpy_s(this->lastName, strlen(lastName)+1, lastName);
	}
	char* getFirstName() {
		return firstName;
	}
	char* getLastName() {
		return lastName;
	}
	void setFirstName(char* firstName) {
		this->firstName = new char[strlen(firstName) + 1];
		strcpy_s(this->firstName, strlen(firstName)+1, firstName);
	}
	void setLastName(char* lastName){
		this->lastName = new char[strlen(lastName) + 1];
		strcpy_s(this->lastName, strlen(lastName)+1, lastName);
	}
	~AccountHolder() {
		delete[] firstName;
		delete[] lastName;
	}
};

class Account {
	int number;
	float money;
	AccountHolder* holder;
public:
	Account() {
		number = 0;
		money = 0;
		holder = nullptr;
	}
	Account(int number, float money, AccountHolder& holder) {
		if (money >= 0) {
			this->money = money;
		}
		else {
			this->money = 0;
		}
		this->number = number;
		this->holder = new AccountHolder(holder);
	}
	Account(Account& account) {
		number = account.number;
		money = account.money;
		holder = new AccountHolder(*account.holder);
	}
	AccountHolder* getAccountHolder() {
		return holder;
	}
	void setAccountHolder(AccountHolder& holder) {
		this->holder = new AccountHolder(holder);
	}
	int getNumber() {
		return this->number;
	}
	float getMoney() {
		return this->money;
	}
	void setNumber(int number) {
		this->number = number;
	}
	void setMoney(float money) {
		if (money >= 0) {
			this->money = money;
		}
	}
	bool putMoney(float money) {
		if (money > 0) {
			this->money += money;
			return true;
		}
		return false;
	}
	bool getCash(float money) {
		if (money > 0 && this->money >= money) {
			this->money -= money;
			return true;
		}
		return false;
	}
	bool transfer(Account* to, float money) {
		if (money > 0) {
			if (this->getCash(money)) {
				to->putMoney(money);
				return true;
			}
		}
		return false;
	}
	~Account() {
		delete holder;
	}
	Account operator=(Account account) {
		number = account.number;
		money = account.money;
		holder = new AccountHolder(*account.holder);
	}
	Account operator--() {
		money -= 100;
		return *this;
	}
	friend Account operator--(Account account, int);
	friend istream& operator>>(istream& ins, Account& account);
	friend ostream& operator<<(ostream& out, Account account);
	friend bool operator>(Account ac1, Account ac2);
};

Account operator--(Account account, int){
	Account ob = account;
	account.money -= 100;
	return ob;
}

istream& operator>>(istream& ins, Account& account){
	int money;
	float number;
	char bufferFirst[80], bufferSecond[80];
	ins >> money;
	ins >> number;
	ins >> bufferFirst;
	ins >> bufferSecond;
	AccountHolder holder(bufferFirst, bufferSecond);
	if (money >= 0) {
		account.setMoney(money);
	}
	else {
		account.setMoney(0);
	}
	account.setNumber(number);
	account.setAccountHolder(holder);
	return ins;
}

ostream& operator<<(ostream& out, Account account){
	return out << account.getAccountHolder()->getFirstName() << " " << account.getAccountHolder()->getLastName() << " " << account.getMoney() << " " << account.getNumber();
}

bool operator>(Account ac1, Account ac2){
	return ac1.getMoney() > ac2.getMoney();
}

int main() {
	setlocale(LC_ALL, "Rus");
	int num1, num2;
	float mon1, mon2;
	char bufferFirst[80], bufferSecond[80];
	cout << "����� 1 �����: ";
	cin >> num1;
	cout << "������ 1 �����: ";
	cin >> mon1;
	cout << "��� 1 ���������: ";
	cin >> bufferFirst;
	cout << "������� 1 ���������: ";
	cin >> bufferSecond;
	AccountHolder first(bufferFirst, bufferSecond);
	Account ac(num1, mon1, first);
	cout << "���, ������� 1 ���������: " << ac.getAccountHolder()->getFirstName() << " " << ac.getAccountHolder()->getLastName() << endl;
	cout << "����� 2 �����: ";
	cin >> num2;
	cout << "������ 1 �����: ";
	cin >> mon2;
	cout << "��� 2 ���������: ";
	cin >> bufferFirst;
	cout << "������� 2 ���������: ";
	cin >> bufferSecond;
	AccountHolder second(bufferFirst, bufferSecond);
	Account to(num2, mon2, second);
	cout << "���, ������� 2 ���������: " << to.getAccountHolder()->getFirstName() << " " << to.getAccountHolder()->getLastName() << endl;
	cout << "�� 1 �����: " << ac.getMoney() << "\n";
	cout << "�� 2 �����: " << to.getMoney() << "\n";
	int put, get, transfer;
	cout << "������ �� 1 �����: ";
	cin >> put;
	ac.putMoney(put);
	cout << "�� 1 �����: " << ac.getMoney() << "\n";
	cout << "����� � 1 �����: ";
	cin >> get;
	ac.getCash(get);
	cout << "�� 1 �����: " << ac.getMoney() << "\n";
	cout << "�������� � 1 ����� �� 2 �����: ";
	cin >> transfer;
	ac.transfer(&to, transfer);
	cout << "�� 1 �����: " << ac.getMoney() << "\n";
	cout << "�� 2 �����: " << to.getMoney() << "\n";
	cout << "����� ��� ��� 1 ���������: ";
	cin >> bufferFirst;
	cout << "����� ������� ��� 1 ���������: ";
	cin >> bufferSecond;
	ac.getAccountHolder()->setFirstName(bufferFirst);
	ac.getAccountHolder()->setLastName(bufferSecond);
	cout << "����� ��� � ������� ��� 1 ���������: " << ac.getAccountHolder()->getFirstName() << " " << ac.getAccountHolder()->getLastName() << endl;
	Account new1;
	cin >> new1;
	cout << new1 << endl;
	cout << "����� 1 ����� ����� 2 �����: " << (ac > to) << endl;
}