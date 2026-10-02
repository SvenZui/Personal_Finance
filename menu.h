#pragma once
#include <iostream>
#include <string>
#include <fstream>

#include "Expense.h"
using namespace std;

void handleAccountsMenu(Account*& accounts, int& accountSize, Expence* expences, int expenceSize);
void handleExpensesMenu(Expence*& expences, int& expenceSize, Account* accounts, int accountSize, Operation*& operations, int& operationSize);
void handleCategoriesMenu(string*& categories, int& categorySize, Expence* expences, int expenceSize);
void handleOperationsMenu(Operation* operations, int operationSize);