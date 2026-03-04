#include "database.h"

int checkInt(char* buffer) {
    for (int i = 0; i < strlen(buffer); i++) {
        if (buffer[i] == 10) return 1;
        if (buffer[i] < 48 || buffer[i] > 57) return 0;
    }
    return 1;
}

int checkDouble(char* buffer) {
    int have_digit = 0;
    int num_of_sep = 0;
    int is_breaked = 0;
    for (int i = 0; i < strlen(buffer); i++) {
        if (buffer[i] != 44 && buffer[i] != 10 && buffer[i] != 46 && (buffer[i] < 48 || buffer[i] > 57)) {
            printf("Неправильно введена стоимость.\n");
            is_breaked = 1;
            break;
        }
        else if (buffer[i] < 58 && buffer[i] > 47) {
            have_digit = 1;
        }
        else if (buffer[i] == 44 || buffer[i] == 46) {
            num_of_sep++;
        }
    }
    if (is_breaked) {
        return 0;
    }
    if (!have_digit || num_of_sep > 1 || (buffer[0] < 48 || buffer[0] > 57)) {
        printf("Неправильно введена стоимость.\n");
        return 0;
    }
    return 1;
}

void add_item(struct Product* warehouse, int n, int* cur, char* name, double price, int quant) {
    for (int i = 0; i < *cur; i++) {
        if ((strcmp(warehouse[i].name, name) == 0) && (warehouse[i].price == price)) {
            warehouse[i].quant += quant;
            return;
        }
    }
    if ((*cur) < n) {
        warehouse[(*cur)].quant = quant;
        strcpy_s(warehouse[(*cur)].name, 80, name);
        warehouse[(*cur)].price = price;
        (*cur)++;
        return;
    }
    printf("Склад переполнен.\n");
    return;
}

void write_to_file(struct Product* warehouse, int cur_n, const char* filename) {
    FILE* fp;
    fopen_s(&fp, filename, "wb");
    if (fp == NULL) {
        perror("Ошибка чтения.\n");
        fclose(fp);
        return;
    }
    fwrite(&cur_n, sizeof(cur_n), 1, fp);

    for (int i = 0; i < cur_n; i++) {
        int len = strlen(warehouse[i].name);
        fwrite(&len, sizeof(int), 1, fp);
        fwrite(warehouse[i].name, sizeof(char), len, fp);
        fwrite(&warehouse[i].price, sizeof(double), 1, fp);
        fwrite(&warehouse[i].quant, sizeof(int), 1, fp);
    }
    fclose(fp);
    return;
}

int readNumber(const char* filename) {
    FILE* fp;
    fopen_s(&fp, filename, "rb");
    if (fp == NULL) {
        perror("Ошибка чтения.\n");
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

void readfile(struct Product* warehouse, int n, const char* filename, int* cur) {
    FILE* fp;
    fopen_s(&fp, filename, "rb");
    if (fp == NULL) {
        perror("Ошибка чтения.\n");
        fclose(fp);
        return;
    }
    int amount;
    fread(&amount, sizeof(int), 1, fp);
    if (feof(fp)) {
        fclose(fp);
        return;
    }
    for (int i = 0; i < amount; i++) {
        int len;
        fread(&len, sizeof(int), 1, fp);
        fread(warehouse[i].name, sizeof(char), len, fp);
        fread(&warehouse[i].price, sizeof(double), 1, fp);
        fread(&warehouse[i].quant, sizeof(int), 1, fp);
    }
    *cur = amount;
    fclose(fp);
}

void input(struct Product* warehouse, int n, int* cur) {
    char name[80];
    double price;
    int quant;
    printf("Name: ");
    fgets(name, sizeof(name), stdin);
    if (strlen(name) > 0 && name[strlen(name) - 1] == '\n') {
        name[strlen(name) - 1] = '\0';
    }
    char buf_price[80];
    printf("Price: ");
    fgets(buf_price, sizeof(buf_price), stdin);

    if (!checkDouble(buf_price)) {
        return;
    }

    price = strtod(buf_price, NULL);
    char buff_quant[80];
    printf("Quant: ");
    fgets(buff_quant, sizeof(buff_quant), stdin);
    if (!checkInt(buff_quant)) {
        printf("Неправильно введено количество.\n");
        return;
    }
    quant = atoi(buff_quant);
    add_item(warehouse, n, cur, name, price, quant);
}

void showProducts(struct Product* warehouse, int cur, int n) {
    if (cur == 0) {
        printf("Ничего нету на складе\n");
        return;
    }
    else {
        printf("Название  Цена   Кол-во\n");
    }
    for (int i = 0; i < cur; i++) {
        printf("%8s  %2.2lf  %6d\n", warehouse[i].name, warehouse[i].price, warehouse[i].quant);
    }
}

void findName(struct Product* warehouse, int cur) {
    char name[80];
    printf("Имя для поиска: ");
    fgets(name, sizeof(name), stdin);
    name[strlen(name) - 1] = '\0';
    int isFound = 0;
    for (int i = 0; i < cur; i++) {
        if (strcmp(warehouse[i].name, name) == 0) {
            printf("%8s  %2.2lf  %6d\n", warehouse[i].name, warehouse[i].price, warehouse[i].quant);
            isFound = 1;
        }
    }
    if (!isFound) {
        printf("Ничего не найдено.\n");
    }
}

void findQuant(struct Product* warehouse, int cur) {
    int quant;
    char buff_quant[80];
    printf("Количество, меньше которого искать: ");
    fgets(buff_quant, sizeof(buff_quant), stdin);
    if (!checkInt(buff_quant)) {
        printf("Неправильно введено количество.\n");
        return;
    }
    quant = atoi(buff_quant);
    int isFound = 0;
    for (int i = 0; i < cur; i++) {
        if (warehouse[i].quant < quant) {
            printf("%8s  %2.2lf  %6d\n", warehouse[i].name, warehouse[i].price, warehouse[i].quant);
            isFound = 1;
        }
    }
    if (!isFound) {
        printf("Ничего не найдено.\n");
    }

}

void database() {
    int n = 0;
    int cur = 0;
    char buff_n[80];
    int amount = readNumber("data.bin");
    while (true) {
        printf("Введите вместимость склада n: ");
        fgets(buff_n, sizeof(buff_n), stdin);
        if (!checkInt(buff_n)) {
            printf("Неправильно введено число.\n"); 
        }
        else if (atoi(buff_n) < amount) {
            printf("Недостаточно места для считывания из файла.\n");
        }
        else if (atoi(buff_n) <= 0) {
            printf("Количество не может быть неположительным.\n");
        }
        else {
            break;
        }
        system("pause");
    }
    n = atoi(buff_n);
    struct Product* warehouse = (struct Product*)calloc(n, sizeof(struct Product));
    for (int i = 0; i < n; i++) {
        warehouse[i].name = (char*)calloc(80, sizeof(char));
    }
    readfile(warehouse, n, "data.bin", &cur);
    int choose;
    char buffer[80];
    do {
        system("cls");
        choose = 1;
        printf("Выберите действие (1 - добавить, 2 - показать, 3 - поиск по названию, 4 - по количеству, остальное - выход): ");
        fgets(buffer, sizeof(buffer), stdin);
        if (!checkInt(buffer)) {
            printf("Incorrect!\n");
            continue;
        };
        choose = atoi(buffer);
        switch (choose)
        {
        case 1: {
            input(warehouse, n, &cur);
            break;
        }
        case 2: {
            showProducts(warehouse, cur, n);
            break;
        }
        case 3: {
            findName(warehouse, cur);
            break;
        }
        case 4: {
            findQuant(warehouse, cur);
            break;
        }
        }
        system("pause");
    } while (choose > 0 && choose < 5);

    write_to_file(warehouse, cur, "data.bin");
    for (int i = 0; i < n; i++) {
        if (warehouse[i].name != NULL) {
            free(warehouse[i].name);
        }
    }
    free(warehouse);
    return;
}

