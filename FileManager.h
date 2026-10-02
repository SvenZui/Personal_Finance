#pragma once
#include <fstream>
#include "Account.h"
#include "Expense.h"


void saveAccounts(Account* accounts, int size);
void loadAccounts(Account*& accounts, int& size);

void saveCategories(string* categories, int size);
void loadCategories(string*& categories, int& size);

void saveExpences(Expence* expences, int size);
void loadExpences(Expence*& expences, int& size);

void saveOperations(Operation* operations, int size);
void loadOperations(Operation*& operations, int& size);

void exportReport(Expence* expences, int size, Date start, Date end,string* categories, int categorySize, Account* accounts, int accountSize);

void exportMainReport(ofstream& file, Expence* expences, int size,Date start, Date end);

void exportCategoryReport(ofstream& file, Expence* expences, int size,Date start, Date end, string* categories, int categorySize);

void exportAccountReport(ofstream& file, Expence* expences, int size,Date start, Date end, Account* accounts, int accountSize);

void exportTop3Expences(ofstream& file, Expence* expences, int size,Date start, Date end);

void exportTop3Categories(ofstream& file, Expence* expences, int size,Date start, Date end, string* categories, int categorySize);