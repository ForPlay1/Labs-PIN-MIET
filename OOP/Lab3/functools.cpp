#include "functools.h"

using namespace std;

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

int readNumber(const char* filename) {
    ifstream iFil(filename, ios::binary);
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

int enterNumber(const char* filename) {
    char buff_n[80];
    int amount = readNumber(filename);
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