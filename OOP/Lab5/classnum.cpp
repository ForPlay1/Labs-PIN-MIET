#include "classnum.h"

template <class num>
array<num>::array(int size) {
    srand(time(NULL));
    n = size;
    Bp = reinterpret_cast<int*>(new num[n]);
    Tp = Bp;
    for (int i = 0; i < n; i++) {
        num* target = reinterpret_cast<num*>(Tp);
        *target = static_cast<num>((double)(0));
        Tp = reinterpret_cast<int*>(reinterpret_cast<char*>(Tp) + sizeof(num));
    }
    Tp = Bp;
}

template <class num>
void array<num>::set_random() {
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        num* target = reinterpret_cast<num*>(Tp);
        *target = static_cast<num>((double)(rand() % 100 - 50) / 10);
        Tp = reinterpret_cast<int*>(reinterpret_cast<char*>(Tp) + sizeof(num));
    }
    Tp = Bp;
}

bool checkDouble(char* buffer) {
    int have_digit = 0;
    int num_of_sep = 0;
    for (int i = 0; i < strlen(buffer); i++) {
        if (buffer[i] != 44 && buffer[i] != 10 && buffer[i] != 46 && (buffer[i] < 48 || buffer[i] > 57)) {
            std::cout << "Incorrect number format.\n";
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
        std::cout << "Incorrect number format.\n";
        return false;
    }
    return true;
}

template <class num>
void array<num>::write() {
    double input;
    char b;
    char buf_init[80];
    for (int i = 0; i < n; i++) {
        do {
            std::cout << "Write " << i << " number: ";
            std::cin.get(buf_init, 80);
            std::cin.clear();
            std::cin.get(b);
            while (b != '\n') {
                std::cin.get(b);
            }
        } while (!checkDouble(buf_init));
        input = strtod(buf_init, NULL);
        num* target = reinterpret_cast<num*>(Tp);
        *target = static_cast<num>(input);
        Tp = reinterpret_cast<int*>(reinterpret_cast<char*>(Tp) + sizeof(num));
    }
    Tp = Bp;
}

template <class num>
array<num>::~array() {
    delete[] Bp;
}

template <class num>
void array<num>::show() {
    for (int i = 0; i < n; i++) {
        num* target = reinterpret_cast<num*>(Tp);
        std::cout << *target << " ";
        Tp = reinterpret_cast<int*>(reinterpret_cast<char*>(Tp) + sizeof(num));
    }
    std::cout << std::endl;
    Tp = Bp;
}

template <class num>
num* array<num>::negative() {
    num* negArr = new num[n];
    for (int i = 0; i < n; i++) {
        num* target = reinterpret_cast<num*>(Tp);
        if (*target < 0) {
            negArr[i] = *target;
        }
        else {
            negArr[i] = 0;
        }
        Tp = reinterpret_cast<int*>(reinterpret_cast<char*>(Tp) + sizeof(num));
    }
    Tp = Bp;
    return negArr;
}

bool checkInt(char* buffer) {
    for (int i = 0; i < strlen(buffer); i++) {
        if (buffer[i] == 10) return true;
        if (buffer[i] < 48 || buffer[i] > 57) return false;
    }
    return true;
}

void test2() {
    array<int> arr(10);
    array<double> arrD(10);
    int choose;
    char b;
    char buffer[80];
    do {
        system("cls");
        choose = 1;
        std::cout << "Choose a function to use to an arrays:\n";
        std::cout << "1 - random integers\n";
        std::cout << "2 - random double\n";
        std::cout << "3 - write integers yourself\n";
        std::cout << "4 - write double yourself\n";
        std::cout << "5 - show integers\n";
        std::cout << "6 - show double\n";
        std::cout << "7 - show all negatives\n";
        std::cout << "Other number - leave the programm and save to file\n";
        std::cout << "Your choice: ";
        std::cin.get(buffer, 3);
        std::cin.clear();
        std::cin.get(b);
        while (b != '\n') {
            std::cin.get(b);
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
            arr.set_random();
            break;
        }
        case 2: {
            arrD.set_random();
            break;
        }
        case 3: {
            arr.write();
            break;
        }
        case 4: {
            arrD.write();
            break;
        }
        case 5: {
            arr.show();
            break;
        }

        case 6: {
            arrD.show();
            break;
        }
        case 7: {
            int* negArr = arr.negative();
            double* negArrD = arrD.negative();
            std::cout << "Negative elements: ";
            for (int i = 0; i < 10; i++) {
                if (negArr[i] != 0) {
                    std::cout << negArr[i] << " ";
                }
            }
            std::cout << std::endl;
            std::cout << "Negative elements (double): ";
            for (int i = 0; i < 10; i++) {
                if (negArrD[i] != 0) {
                    std::cout << negArrD[i] << " ";
                }
            }
            std::cout << std::endl;
            delete[] negArr;
            delete[] negArrD;
            break;
        }
        }
        system("pause");

    } while (choose > 0 && choose < 8);
    
}