#include "database.h"

void Fio::copyStr(char*& dest, const char* src) {
    if (src) {
        dest = new char[strlen(src) + 1];
        strcpy_s(dest, strlen(src)+1, src);
    }
    else {
        dest = new char[1];
        dest[0] = '\0';
    }
}

Fio::Fio() {
    lastName = new char[1] { '\0' };
    firstName = new char[1] { '\0' };
}

Fio::Fio(const char* ln, const char* fn) {
    copyStr(lastName, ln);
    copyStr(firstName, fn);
}

Fio::Fio(const Fio& other) {
    copyStr(lastName, other.lastName);
    copyStr(firstName, other.firstName);
}

Fio& Fio::operator=(const Fio& other) {
    if (this != &other) {
        delete[] lastName;
        delete[] firstName;
        copyStr(lastName, other.lastName);
        copyStr(firstName, other.firstName);
    }
    return *this;
}

Fio::~Fio() {
    delete[] lastName;
    delete[] firstName;
}

void Fio::update(const char* ln, const char* fn) {
    delete[] lastName;
    delete[] firstName;
    copyStr(lastName, ln);
    copyStr(firstName, fn);
}

Student::Student() : zk(0), grup(0) {}
Student::Student(const char* ln, const char* fn, int z, int g) : man(ln, fn), zk(z), grup(g) {}
int Student::getGroup() const { return grup; }
std::ostream& operator<<(std::ostream& out, const Student& s) {
    out << std::setw(15) << std::left << (s.man.lastName ? s.man.lastName : "")
        << std::setw(15) << std::left << (s.man.firstName ? s.man.firstName : "")
        << std::setw(12) << std::left << s.zk
        << std::setw(8) << std::left << s.grup;
    return out;
}

std::istream& operator>>(std::istream& in, Student& s) {
    char bufLn[256];
    char bufFn[256];

    std::cout << "Введите фамилию: ";
    in >> bufLn;
    std::cout << "Введите имя: ";
    in >> bufFn;

    s.man.update(bufLn, bufFn);

    std::cout << "Введите номер зачетной книжки: ";
    while (!(in >> s.zk) || s.zk <= 0) {
        std::cout << "Ошибка! Введите корректный числовой номер: ";
        in.clear();
        in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::cout << "Введите номер группы: ";
    while (!(in >> s.grup) || s.grup <= 0) {
        std::cout << "Ошибка! Введите корректный номер группы: ";
        in.clear();
        in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return in;
}

bool Student::operator==(const Fio& f) const {
    return (strcmp(this->man.lastName, f.lastName) == 0 &&
        strcmp(this->man.firstName, f.firstName) == 0);
}

void Student::saveToFile(std::ofstream& out) const {
    out << man.lastName << " " << man.firstName << " " << zk << " " << grup << "\n";
}

bool Student::loadFromFile(std::ifstream& in) {
    char bufLn[256];
    char bufFn[256];
    int tempZk, tempGrup;

    if (in >> bufLn >> bufFn >> tempZk >> tempGrup) {
        man.update(bufLn, bufFn);
        zk = tempZk;
        grup = tempGrup;
        return true;
    }
    return false;
}

void printHeader() {
    std::cout << std::string(52, '-') << "\n";
    std::cout << std::setw(15) << std::left << "Фамилия"
        << std::setw(15) << std::left << "Имя"
        << std::setw(12) << std::left << "Зачетка"
        << std::setw(8) << std::left << "Группа" << "\n";
    std::cout << std::string(52, '-') << "\n";
}

void printFooter() {
    std::cout << std::string(52, '-') << "\n\n";
}

void database() {
    setlocale(LC_ALL, "Rus");
    std::vector<Student> database;
    const std::string filename = "students_db.txt";
    std::ifstream inFile(filename);
    if (inFile.is_open()) {
        Student temp;
        while (temp.loadFromFile(inFile)) {
            database.push_back(temp);
        }
        inFile.close();
        std::cout << "[Система] База данных успешно загружена. Записей: " << database.size() << "\n\n";
    }
    else {
        std::cout << "[Система] Файл базы данных не найден. Будет создана новая база.\n\n";
    }

    int choice = 0;
    while (true) {
        std::cout << "=== Меню управления ===\n"
            << "1. Добавить студента (Оператор >>)\n"
            << "2. Вывести всех студентов в табличном виде (for_each)\n"
            << "3. Найти студента по ФИО (Оператор == и find_if)\n"
            << "4. Сформировать выборку по группе (transform)\n"
            << "5. Выход из программы (с сохранением)\n"
            << "Выберите действие: ";

        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Неверный пункт меню!\n\n";
            continue;
        }

        if (choice == 5) break;

        switch (choice) {
        case 1: {
            Student newStudent;
            std::cin >> newStudent;
            database.push_back(newStudent);
            std::cout << "Студент успешно добавлен!\n\n";
            break;
        }
        case 2: {
            if (database.empty()) {
                std::cout << "База данных пуста.\n\n";
                break;
            }
            printHeader();
            std::for_each(database.begin(), database.end(), [](const Student& s) {
                std::cout << s << "\n";
                });
            printFooter();
            break;
        }
        case 3: {
            if (database.empty()) {
                std::cout << "База данных пуста.\n\n";
                break;
            }

            char bufLn[256];
            char bufFn[256];
            std::cout << "Введите фамилию для поиска: ";
            std::cin >> bufLn;
            std::cout << "Введите имя для поиска: ";
            std::cin >> bufFn;

            Fio searchTarget(bufLn, bufFn);

            auto it = std::find_if(database.begin(), database.end(), [&searchTarget](const Student& s) {
                return s == searchTarget;
                });

            if (it != database.end()) {
                std::cout << "\nСтудент найден:\n";
                printHeader();
                std::cout << *it << "\n";
                printFooter();
            }
            else {
                std::cout << "Студент с такими ФИО не найден.\n\n";
            }
            break;
        }
        case 4: {
            if (database.empty()) {
                std::cout << "База данных пуста.\n\n";
                break;
            }
            int targetGroup;
            std::cout << "Введите номер группы для выборки: ";
            while (!(std::cin >> targetGroup)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Некорректный номер. Повторите: ";
            }

            std::vector<Student> goodsRez;

            std::transform(database.begin(), database.end(), std::back_inserter(goodsRez),
                [](const Student& s) {
                    return s; 
                });

            goodsRez.erase(std::remove_if(goodsRez.begin(), goodsRez.end(),
                [targetGroup](const Student& s) {
                    return s.getGroup() != targetGroup;
                }), goodsRez.end());

            if (goodsRez.empty()) {
                std::cout << "В группе " << targetGroup << " нет студентов.\n\n";
            }
            else {
                std::cout << "\nРезультаты поиска (сохранено в goodsRez):\n";
                printHeader();
                std::for_each(goodsRez.begin(), goodsRez.end(), [](const Student& s) {
                    std::cout << s << "\n";
                    });
                printFooter();
            }
            break;
        }
        default:
            std::cout << "Неверный пункт меню. Попробуйте снова.\n\n";
        }
    }

    std::ofstream outFile(filename);
    if (outFile.is_open()) {
        std::for_each(database.begin(), database.end(), [&outFile](const Student& s) {
            s.saveToFile(outFile);
            });
        outFile.close();
        std::cout << "[Система] Изменения успешно сохранены в '" << filename << "'. До встречи!\n";
    }
    else {
        std::cerr << "[Ошибка] Не удалось сохранить данные на диск!\n";
    }

    return 0;
}