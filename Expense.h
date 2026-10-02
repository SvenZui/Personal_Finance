#pragma once
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

#include "Account.h"



//система категорій
void showCategories(string* categories, int size);
void addCategory(string*& categories, int& size, string category);
void deleteCategory(string*& categories, int& size, string category);
int findCategory(string* categories, int size, string category);

//система витрат
struct Expence {
	int id = 0;
	double sume = 0;
	Date date = { 0,0,0 };
	string category = "None";
	int accountId = 0;
	string description = "None";
};

void addExpence(Expence*& expences, int& size, Expence expence, Account* accounts, int accountSize);

int findExpence(Expence* expences, int size, int id);
void editExpence(Expence* expences, int size, int id,double amount, string category, string description,Account* accounts, int accountSize);
void deleteExpence(Expence*& expences, int& size, int id,Account* accounts, int accountSize);

//історія операцій
struct Operation {
	Date date = { 0,0,0 };
	string type = "None";
	double sum = 0;
	int accountId = 0;
	string category = "None";
	string description = "None";
};

void addOperation(Operation*& operations, int& size, Operation operation);
void outputOperations(Operation* operations, int size);
void showAccountOperations(Operation* operations, int size, int accountId);
void showCategoryOperations(Operation* operations, int size, string category);
void showPeriodOperations(Operation* operations, int size, Date start, Date end);
void searchOperations(Operation* operations, int size, string description);
bool isDateBetween(Date date, Date start, Date end);

bool hasExpenses(Expence* expences, int expSize, int accountId);