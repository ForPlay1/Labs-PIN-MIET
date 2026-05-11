#include <iostream>
#include <cstring>
#include <stdexcept>
using namespace std;

class fio{
    char* name;
    char* surname;
public:
    fio(const char* name, const char* surname){
        this->name = new char[strlen(name) + 1];
        this->surname = new char[strlen(surname) + 1];
        strcpy(this->name, name);
        strcpy(this->surname, surname);
    }
    ~fio(){
        delete[] name;
        delete[] surname;
    }
    friend ostream& operator<<(ostream& out, const fio& fio); 
    fio() : name(nullptr), surname(nullptr) {}
    fio(const fio& other){
        name = new char[strlen(other.name) + 1];
        surname = new char[strlen(other.surname) + 1];
        strcpy(name, other.name);
        strcpy(surname, other.surname);
    }
    char* getName() const {
        char* buffer = new char[strlen(name) + 1];
        strcpy(buffer, name);
        return buffer;
    }
    char* getSurname() const {
        char* buffer = new char[strlen(surname) + 1];
        strcpy(buffer, surname);
        return buffer;
    }
    void setName(const char* name){
        delete[] this->name;
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
    }
    void setSurname(const char* surname){
        delete[] this->surname;
        this->surname = new char[strlen(surname) + 1];
        strcpy(this->surname, surname);
    }
};

ostream& operator<<(ostream& out, const fio& fio){
    return out << fio.name << " " << fio.surname;
}

class student{
    fio man;
    int zk;
    int grup;
    public:
    student(){
        man = fio();
        zk = 0;
        grup = 0;
    }
    void init(){
        char name[50], surname[50];
        cout << "Enter name: ";
        cin >> name;
        cout << "Enter surname: ";
        cin >> surname;
        man.setName(name);
        man.setSurname(surname);
        cout << "Enter zk: ";
        cin >> zk;
        cout << "Enter group: ";
        cin >> grup;
    }
    friend ostream& operator<<(ostream& out, const student& student);
    friend istream& operator>>(istream& in, student& student);
    bool operator==(const fio& fio){
        return strcmp(man.getName(), fio.getName()) == 0 && strcmp(man.getSurname(), fio.getSurname()) == 0;
    }
    friend student* search(student* students, int count, int grup);
    int getGroup() const {
        return grup;
    }
};

student* search(student* students, int count, int grup){
    student* result = new student[count];
    int result_count = 0;
    for (int i = 0; i < count; i++){
        if (students[i].getGroup() == grup){
            result[result_count++] = students[i];
        }
    }
    if (result_count == 0){
        delete[] result;
        return nullptr;
    }
    return result;
}

ostream& operator<<(ostream& out, const student& student){
    return out << student.man << " " << student.zk << " " << student.grup;
}

istream& operator>>(istream& in, student& student){
    char name[50], surname[50];
    cout << "Enter name: ";
    in >> name;
    cout << "Enter surname: ";
    in >> surname;
    student.man.setName(name);
    student.man.setSurname(surname);
    char buf_zk[80];
    cout << "Enter zk: ";
    in >> buf_zk;
    try{
        student.zk = stoi(buf_zk);
        if (student.zk < 0 || student.zk > 100) {
            throw out_of_range("zk must be between 0 and 100.");
        }
    } catch (invalid_argument& e){
        cout << "Incorrect number format. Setting zk to 0." << endl;
        student.zk = 0;
    } catch (out_of_range& e){
        cout << e.what() << " Setting zk to 0." << endl;
        student.zk = 0;
    }
    
    char buf_grup[80];
    cout << "Enter group: ";
    in >> buf_grup;
    try{
        student.grup = stoi(buf_grup);
        if (student.grup <= 0) {
            throw out_of_range("Group number must be a positive integer.");
        }
    } catch (invalid_argument& e){
        cout << "Incorrect number format. Setting group to 0." << endl;
        student.grup = 0;
    } catch (out_of_range& e){
        cout << e.what() << " Setting group to 0." << endl;
        student.grup = 0;
    }
    return in;
}

int main(){
    char buf_count[80];
    cout << "Enter number of students: ";
    cin >> buf_count;
    int count = 1;
    try {
        count = stoi(buf_count);
        if (count <= 0) {
            throw out_of_range("Number of students must be a positive integer.");
        }
    } catch (invalid_argument& e){
        cout << "Incorrect number format. Setting number of students to 1." << endl;
        count = 1;
        return 1;
    } catch (out_of_range& e){
        cout << e.what() << " Setting number of students to 1." << endl;
        count = 1;
        return 1;
    }    
    system("pause");
    student* students = new student[count];
    
    char buf_command[80];
    int command = 0;
    do{
        system("cls");
        cout << "Choose a command:\n1 - Add students\n2 - Show all students\n3 - Find student by name and surname\n4 - Find students by group\nOther number - Exit\nYour choice: ";
        cin >> buf_command;
        try {
            command = stoi(buf_command);
            if (command <= 0) {
                throw out_of_range("Command must be a positive integer.");
            }
        } catch (invalid_argument& e){
            cout << "Incorrect number format." << endl;
            command = 0;
        } catch (out_of_range& e){
            cout << e.what() << endl;
            command = 0;
        }
        system("pause");
        system("cls");
        switch (command)
        {
        case 1:
            for (int i = 0; i < count; i++){
                cin >> students[i];
            }
            break;
        case 2:
            for (int i = 0; i < count; i++){
                cout << students[i] << endl;
            }
            break;
        case 3:
        {
            char buff_name[50], buff_surname[50];
            cout << "Enter name: ";
            cin >> buff_name;
            cout << "Enter surname: ";
            cin >> buff_surname;
            fio search_fio(buff_name, buff_surname);
            bool found = false;
            for (int i = 0; i < count; i++){
                if (students[i] == search_fio){
                    cout << students[i] << endl;
                    found = true;
                }
            }
            if (!found){
                cout << "Student not found." << endl;
            }
            break;
        }
        case 4:
        {
            char buf_grup[80];
            cout << "Enter group: ";
            cin >> buf_grup;
            int grup;
            try {
                grup = stoi(buf_grup);
                if (grup <= 0) {
                    throw out_of_range("Group number must be a positive integer.");
                }
            } catch (invalid_argument& e){
                cout << "Incorrect number format." << endl;
                break;
            } catch (out_of_range& e){
                cout << e.what() << endl;
                break;
            }
            student* grup_students = search(students, count, grup);
            if (grup_students == nullptr){
                cout << "No students found in this group." << endl;
            } else {
                for (int i = 0; i < count; i++){
                    if (grup_students[i].getGroup() == grup){
                        cout << grup_students[i] << endl;
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