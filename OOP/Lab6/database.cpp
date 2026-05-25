#include "database.h"

fio::fio(const char* name, const char* surname) {
    this->name = new char[strlen(name) + 1];
    this->surname = new char[strlen(surname) + 1];
    strcpy_s(this->name, strlen(name)+1, name);
    strcpy_s(this->surname, strlen(surname) + 1, surname);
}

fio::~fio() {
    delete[] name;
    delete[] surname;
}

fio::fio() : name(nullptr), surname(nullptr) {}

fio::fio(const fio& other) {
    name = new char[strlen(other.name) + 1];
    surname = new char[strlen(other.surname) + 1];
    strcpy_s(name, strlen(other.name) + 1, other.name);
    strcpy_s(surname, strlen(other.surname) + 1, other.surname);
}

char* fio::getName() const {
    char* buffer = new char[strlen(name) + 1];
    strcpy_s(buffer, strlen(name) + 1, name);
    return buffer;
}
    
char* fio::getSurname() const {
    char* buffer = new char[strlen(surname) + 1];
    strcpy_s(buffer, strlen(surname) + 1, surname);
    return buffer;
}
    
void fio::setName(const char* name) {
    delete[] this->name;
    this->name = new char[strlen(name) + 1];
    strcpy_s(this->name, strlen(name) + 1, name);
}

void fio::setSurname(const char* surname) {
    delete[] this->surname;
    this->surname = new char[strlen(surname) + 1];
    strcpy_s(this->surname, strlen(surname) + 1, surname);
}

std::ostream& operator<<(std::ostream& out, const fio& fio) {
    return out << fio.name << " " << fio.surname;
}

student::student() {
    man = fio();
    zk = 0;
    grup = 0;
}
void student::init() {
    char name[50], surname[50];
    std::cout << "Enter name: ";
    std::cin >> name;
    std::cout << "Enter surname: ";
    std::cin >> surname;
    man.setName(name);
    man.setSurname(surname);
    std::cout << "Enter zk: ";
    std::cin >> zk;
    std::cout << "Enter group: ";
    std::cin >> grup;
}
bool student::operator==(const fio& fio) {
    return strcmp(man.getName(), fio.getName()) == 0 && strcmp(man.getSurname(), fio.getSurname()) == 0;
}
int student::getGroup() const {
    return grup;
}

student* search(student* students, int count, int grup) {
    student* result = new student[count];
    int result_count = 0;
    for (int i = 0; i < count; i++) {
        if (students[i].getGroup() == grup) {
            result[result_count++] = students[i];
        }
    }
    if (result_count == 0) {
        delete[] result;
        return nullptr;
    }
    return result;
}

std::ostream& operator<<(std::ostream& out, const student& student) {
    return out << student.man << " " << student.zk << " " << student.grup;
}

std::istream& operator>>(std::istream& in, student& student) {
    char name[50], surname[50];
    std::cout << "Enter name: ";
    in >> name;
    std::cout << "Enter surname: ";
    in >> surname;
    student.man.setName(name);
    student.man.setSurname(surname);
    char buf_zk[80];
    std::cout << "Enter zk: ";
    in >> buf_zk;
    try {
        student.zk = atoi(buf_zk);
        if (student.zk < 0 || student.zk > 100) {
            throw std::out_of_range("zk must be between 0 and 100.");
        }
    }
    catch (std::invalid_argument& e) {
        std::cout << "Incorrect number format. Setting zk to 0." << std::endl;
        student.zk = 0;
    }
    catch (std::out_of_range& e) {
        std::cout << e.what() << " Setting zk to 0." << std::endl;
        student.zk = 0;
    }

    char buf_grup[80];
    std::cout << "Enter group: ";
    in >> buf_grup;
    try {
        student.grup = atoi(buf_grup);
        if (student.grup <= 0) {
            throw std::out_of_range("Group number must be a positive integer.");
        }
    }
    catch (std::invalid_argument& e) {
        std::cout << "Incorrect number format. Setting group to 0." << std::endl;
        student.grup = 0;
    }
    catch (std::out_of_range& e) {
        std::cout << e.what() << " Setting group to 0." << std::endl;
        student.grup = 0;
    }
    return in;
}

void database() {
    char buf_count[80];
    std::cout << "Enter number of students: ";
    std::cin >> buf_count;
    int count = 1;
    throw 1;
    try {
        count = atoi(buf_count);
        if (count <= 0) {
            throw std::out_of_range("Number of students must be a positive integer.");
        }

    }
    catch (std::invalid_argument& e) {
        std::cout << "Incorrect number format. Setting number of students to 1." << std::endl;
        count = 1;
    }
    catch (std::out_of_range& e) {
        std::cout << e.what() << " Setting number of students to 1." << std::endl;
        count = 1;
    }
    system("pause");
    student* students = new student[count];

    char buf_command[80];
    int command = 0;
    bool isWriten = false;
    do {
        system("cls");
        std::cout << "Choose a command:\n1 - Add students\n2 - Show all students\n3 - Find student by name and surname\n4 - Find students by group\nOther number - Exit\nYour choice: ";
        std::cin >> buf_command;
        try {
            command = atoi(buf_command);
            if (command <= 0) {
                throw std::out_of_range("Command must be a positive integer.");
            }
        }
        catch (std::invalid_argument& e) {
            std::cout << "Incorrect number format." << std::endl;
            command = 0;
        }
        catch (std::out_of_range& e) {
            std::cout << e.what() << std::endl;
            command = 0;
        }
        system("cls");
        switch (command)
        {
        case 1:
            for (int i = 0; i < count; i++) {
                std::cin >> students[i];
            }
            isWriten = true;
            break;
        case 2:
            if (!isWriten) {
                std::cout << "No students" << std::endl;
                break;
            }
            else {
                for (int i = 0; i < count; i++) {
                    std::cout << students[i] << std::endl;
                }
            }
            break;
        case 3:
        {
            if (!isWriten) {
                std::cout << "No students" << std::endl;
                break;
            }
            char buff_name[50], buff_surname[50];
            std::cout << "Enter name: ";
            std::cin >> buff_name;
            std::cout << "Enter surname: ";
            std::cin >> buff_surname;
            fio search_fio(buff_name, buff_surname);
            bool found = false;
            for (int i = 0; i < count; i++) {
                if (students[i] == search_fio) {
                    std::cout << students[i] << std::endl;
                    found = true;
                }
            }
            if (!found) {
                std::cout << "Student not found." << std::endl;
            }
            break;
        }
        case 4:
        {
            if (!isWriten) {
                std::cout << "No students" << std::endl;
                break;
            }
            char buf_grup[80];
            std::cout << "Enter group: ";
            std::cin >> buf_grup;
            int grup;
            try {
                grup = atoi(buf_grup);
                if (grup <= 0) {
                    throw std::out_of_range("Group number must be a positive integer.");
                }
            }
            catch (std::invalid_argument& e) {
                std::cout << "Incorrect number format." << std::endl;
                break;
            }
            catch (std::out_of_range& e) {
                std::cout << e.what() << std::endl;
                break;
            }
            student* grup_students = search(students, count, grup);
            if (grup_students == nullptr) {
                std::cout << "No students found in this group." << std::endl;
            }
            else {
                for (int i = 0; i < count; i++) {
                    if (grup_students[i].getGroup() == grup) {
                        std::cout << grup_students[i] << std::endl;
                    }
                }
                delete[] grup_students;
            }
            break;
        }
        }
        system("pause");
    } while (command >= 0 && command <= 4);
    delete[] students;
}