#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <time.h>
#define _CRT_SECURE_NO_WARNINGS	

struct Product {
    char* name;
    double price;
    int quant;
};

void database();
int readNumber(const char* filename);
void showProducts(struct Product* warehouse, int cur, int n);
void input(struct Product* warehouse, int n, int* cur);
void readfile(struct Product* warehouse, int n, const char* filename, int* cur);
void write_to_file(struct Product* warehouse, int cur_n, const char* filename);
void add_item(struct Product* warehouse, int n, int* cur, char* name, double price, int quant);
int checkDouble(char* buffer);
int checkInt(char* buffer);
void findQuant(struct Product* warehouse, int cur);
void findName(struct Product* warehouse, int cur);