#include <iostream>
#include <cstring>

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

class storage {
    char* name;
    double price;

public:
    int quant;
    static int count;

    storage() {
        char buf_name[80];
        cout << "Name: ";
        cin >> buf_name;
        
        this->name = new char[strlen(buf_name) + 1];
        strcpy(this->name, buf_name);

        char buf_price[80];
        cout << "Price: ";
        cin >> buf_price;
        if (!checkDouble(buf_price)) {
            this->price = 10.0;
        } else {
            this->price = strtod(buf_price, NULL);
        }

        char buff_quant[80];
        cout << "Quant: ";
        cin >> buff_quant;
        if (!checkInt(buff_quant)) {
            cout << "Incorrect number format.\n";
            this->quant = 1;
        } else {
            this->quant = atoi(buff_quant);
        }

        storage::count++;
    }

    void show() {
        printf("%8s  %2.2lf  %6d\n", name, price, quant);
    }

    bool isName(char* name) {
        return strcmp(this->name, name) == 0;
    }

    bool showName(char* name) {
        if (isName(name)) {
            show();
            return true;
        }
        return false;
    }

    bool isQuantLess(int quant) {
        return this->quant < quant;
    }

    bool showQuantLess(int quant) {
        if (isQuantLess(quant)) {
            show();
            return true;
        }
        return false;
    }

    bool isCostMore(double cost) {
        return price > cost;
    }

    bool showCostMore(double cost) {
        if (isCostMore(cost)) {
            show();
            return true;
        }
        return false;
    }
};

int storage::count = 0;

int readNumber(const char* filename) {
    FILE* fp;
    fopen_s(&fp, filename, "rb");
    if (fp == NULL) {
        perror("������ ������.\n");
        fclose(fp);
        return 0;
    }
    int amount;
    fread(&amount, sizeof(int), 1, fp);
    if (feof(fp)) {
        fclose(fp);
        return 0;
    }
    fclose(fp);
    return amount;
}

int enterNumber() {
    char buff_n[80];
    int amount = readNumber("data.bin");
    while (true) {
        cout << "������� ����������� ������ n: ";
        cin >> buff_n;
        if (!checkInt(buff_n)) {
            cout << "����������� ������� �����.\n"; 
        }
        else if (atoi(buff_n) < amount) {
            cout << "������������ ����� ��� ���������� �� �����.\n";
        }
        else if (atoi(buff_n) <= 0) {
            cout << "���������� �� ����� ���� ���������������.\n";
        }
        else {
            break;
        }
        system("pause");
    }
    return atoi(buff_n);
}

int main(){
    int n = 0;
    n = enterNumber();
    storage* warehouse = new storage[n];
    // readfile(warehouse, n, "data.bin", &cur);
    // int choose;
    // char buffer[80];
    // do {
    //     system("cls");
    //     choose = 1;
    //     printf("�������� �������� (1 - ��������, 2 - ��������, 3 - ����� �� ��������, 4 - �� ����������, ��������� - �����): ");
    //     fgets(buffer, sizeof(buffer), stdin);
    //     if (!checkInt(buffer)) {
    //         printf("Incorrect!\n");
    //         continue;
    //     };
    //     choose = atoi(buffer);
    //     switch (choose)
    //     {
    //     case 1: {
    //         input(warehouse, n, &cur);
    //         break;
    //     }
    //     case 2: {
    //         showProducts(warehouse, cur, n);
    //         break;
    //     }
    //     case 3: {
    //         findName(warehouse, cur);
    //         break;
    //     }
    //     case 4: {
    //         findQuant(warehouse, cur);
    //         break;
    //     }
    //     }
    //     system("pause");
    // } while (choose > 0 && choose < 5);

    // write_to_file(warehouse, cur, "data.bin");
    // for (int i = 0; i < n; i++) {
    //     if (warehouse[i].name != NULL) {
    //         free(warehouse[i].name);
    //     }
    // }
    // free(warehouse);
    return 0;
}
