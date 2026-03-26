#include <iostream>
#include <locale>

using namespace std;

class Account {
	int number;
	float money;
public:
	Account(int number, float money) {
		if (money >= 0) {
			this->money = money;
		}
		else {
			this->money = 0;
		}
		this->number = number;
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
};

int main() {
	setlocale(LC_ALL, "Rus");
	int num1, num2;
	float mon1, mon2;
	cout << "Номер 1 карты: ";
	cin >> num1;
	cout << "Баланс 1 карты: ";
	cin >> mon1;
	cout << "Номер 2 карты: ";
	cin >> num2;
	cout << "Баланс 1 карты: ";
	cin >> mon2;
	Account ac(num1, mon1), to(num2, mon2);
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
}