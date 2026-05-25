#include <iostream>
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
		char* name = new char[strlen(this->firstName)+1];
		strcpy_s(name, strlen(this->firstName) + 1, firstName);
		return name;
	}
	char* getLastName() {
		char* name = new char[strlen(this->lastName) + 1];
		strcpy_s(name, strlen(this->lastName) + 1, lastName);
		return name;
	}
	void setFirstName(char* firstName) {
		if (!this->firstName) {
			delete this->firstName;
		}
		this->firstName = new char[strlen(firstName) + 1];
		strcpy_s(this->firstName, strlen(firstName)+1, firstName);
	}
	void setLastName(char* lastName){
		if (!this->lastName) {
			delete this->lastName;
		}
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
		holder->setFirstName(account.getAccountHolder()->getFirstName());
		holder->setFirstName(account.getAccountHolder()->getLastName());
	}
	Account operator--() {
		money -= 100;
		return *this;
	}
	friend Account operator--(Account& account, int);
	friend istream& operator>>(istream& ins, Account& account);
	friend ostream& operator<<(ostream& out, Account& account);
	friend bool operator>(Account& ac1, Account& ac2);
};

Account operator--(Account& account, int){
	Account ob = account;
	account.money -= 100;
	return ob;
}

istream& operator>>(istream& ins, Account& account){
	int money;
	float number;
	char bufferFirst[80], bufferSecond[80];
	cout << "Enter money: ";
	ins >> money;
	cout << "Enter number: ";
	ins >> number;
	cout << "Enter firstname: ";
	ins >> bufferFirst;
	cout << "Enter lastname: ";
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

ostream& operator<<(ostream& out, Account& account){
	return out << account.getAccountHolder()->getFirstName() << account.getAccountHolder()->getLastName() << account.getMoney() << account.getNumber();
}

bool operator>(Account& ac1, Account& ac2){
	return ac1.getMoney() > ac2.getMoney();
}

int main() {
	setlocale(LC_ALL, "Rus");
	int num1, num2;
	float mon1, mon2;
	char bufferFirst[80], bufferSecond[80];
	cout << "Номер 1 карты: ";
	cin >> num1;
	cout << "Баланс 1 карты: ";
	cin >> mon1;
	cout << "Имя 1 владельца: ";
	cin >> bufferFirst;
	cout << "Фамилия 1 владельца: ";
	cin >> bufferSecond;
	AccountHolder first(bufferFirst, bufferSecond);
	Account ac(num1, mon1, first);
	cout << "Имя, Фамилия 1 владельца: " << ac.getAccountHolder()->getFirstName() << " " << ac.getAccountHolder()->getLastName() << endl;
	cout << "Номер 2 карты: ";
	cin >> num2;
	cout << "Баланс 1 карты: ";
	cin >> mon2;
	cout << "Имя 2 владельца: ";
	cin >> bufferFirst;
	cout << "Фамилия 2 владельца: ";
	cin >> bufferSecond;
	AccountHolder second(bufferFirst, bufferSecond);
	Account to(num2, mon2, second);
	cout << "Имя, Фамилия 2 владельца: " << to.getAccountHolder()->getFirstName() << " " << to.getAccountHolder()->getLastName() << endl;
	cout << "На 1 карте: " << ac.getMoney() << "\n";
	cout << "На 2 карте: " << to.getMoney() << "\n";
	int put, get, transfer;
	cout << "Внести на 1 карту: ";
	cin >> put;
	ac.putMoney(put);
	cout << "На 1 карте: " << ac.getMoney() << "\n";
	cout << "Снять с 1 карты: ";
	cin >> get;
	ac.getCash(get);
	cout << "На 1 карте: " << ac.getMoney() << "\n";
	cout << "Трансфер с 1 карты на 2 карту: ";
	cin >> transfer;
	ac.transfer(&to, transfer);
	cout << "На 1 карте: " << ac.getMoney() << "\n";
	cout << "На 2 карте: " << to.getMoney() << "\n";
	cout << "Новое имя для 1 владельца: ";
	cin >> bufferFirst;
	cout << "Новая фамилия для 1 владельца: ";
	cin >> bufferSecond;
	ac.getAccountHolder()->setFirstName(bufferFirst);
	ac.getAccountHolder()->setLastName(bufferSecond);
	cout << "Новое имя и фамилия для 1 владельца: " << ac.getAccountHolder()->getFirstName() << " " << ac.getAccountHolder()->getLastName() << endl;
	Account new1;
	cin >> new1;
	cout << new1;
}