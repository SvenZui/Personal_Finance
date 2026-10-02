#pragma once
#include <ctime>
#include <string>
#include <fstream>

#include "Expense.h"

using namespace std;

void createReport(Expence* expences, int size, Date start, Date end, string* categories, int categorySize, Account* accounts, int accountSize);

void top3Expences(Expence* expences, int size, Date start, Date end);
void top3Categories(Expence* expences, int size, Date start, Date end,string* categories, int categorySize);

