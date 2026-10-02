#include <iostream>
#include <string>
#include <fstream>
using namespace std;

#include "Expense.h"


//система категорій
void showCategories(string* categories, int size) {
	for (int i = 0; i < size; i++) {
		cout << i << ". " << categories[i] << endl;
	}
}

void addCategory(string*& categories, int& size, string category) {
    string* newCategory = new string[size + 1];

    for (int i = 0; i < size; i++) {
        newCategory[i] = categories[i];
    }

    newCategory[size] = category;

    delete[] categories;
    categories = newCategory;
    size++;
}

void deleteCategory(string*& categories, int& size, string category) {
    int deleteIndex = findCategory(categories, size, category);

    if (deleteIndex == -1) {
        throw "notCategory";
    }


    string* newCategory = new string[size - 1];
    int index = 0;
    for (int i = 0; i < size; i++) {
        if (i != deleteIndex) {
            newCategory[index] = categories[i];
            index++;
        }
    }

    delete[] categories;
    categories = newCategory;
    size--;
}

int findCategory(string* categories, int size, string category) {
    for (int i = 0; i < size; i++) {
        if (categories[i] == category) {
            return i;
        }
    }

    return -1;
}


//система витрат
void addExpence(Expence*& expences, int& size, Expence expence, Account* accounts, int accountSize) {
    if (expence.sume <= 0) {
        throw "-1 sume";
    }
    int accountIndex = findAccount(accounts, accountSize, expence.accountId);

    if (accountIndex == -1) {
        throw "-1 account";
    }
    if (accounts[accountIndex].balance < expence.sume) {
        throw "мала деняк";
    }

    accounts[accountIndex].balance -= expence.sume;
    Expence* newExpences = new Expence[size + 1];

    for (int i = 0; i < size; i++) {
        newExpences[i] = expences[i];
    }

    newExpences[size] = expence;

    delete[] expences;
    expences = newExpences;
    size++;
}

int findExpence(Expence* expences, int size, int id) {
    for (int i = 0; i < size; i++) {
        if (expences[i].id == id) {
            return i;
        }
    }

    return -1;
}

void deleteExpence(Expence*& expences, int& size, int id, Account* accounts, int accountSize) {
    int deleteIndex = findExpence(expences, size, id);

    if (deleteIndex == -1) {
        throw "notExpence";
    }
    int accountIndex = findAccount(accounts, accountSize, expences[deleteIndex].accountId);
    if (accountIndex != -1) {
        accounts[accountIndex].balance += expences[deleteIndex].sume;
    }
    
    Expence* newExpences = new Expence[size - 1];
    int index = 0;
    for (int i = 0; i < size; i++) {
        if (i != deleteIndex) {
            newExpences[index] = expences[i];
            index++;
        }
    }

    delete[] expences;
    expences = newExpences;
    size--;
}

void editExpence(Expence* expences, int size, int id, double newAmount, string newCategory, string newDescription, Account* accounts, int accountSize) {
    int expIdx = findExpence(expences, size, id);
    if (expIdx == -1) {
        throw 404;  
    }

    int accIdx = findAccount(accounts, accountSize, expences[expIdx].accountId);

    if (accIdx == -1) {
        throw 404;
    }

    double diff = newAmount - expences[expIdx].sume;

    if (accounts[accIdx].balance < diff) {
        throw - 1;
    }

    accounts[accIdx].balance -= diff;
    expences[expIdx].sume = newAmount;
    expences[expIdx].category = newCategory;
    expences[expIdx].description = newDescription;
}

//історія операцій
void addOperation(Operation*& operations, int& size, Operation operation) {
    Operation* newOperation = new Operation[size + 1];

    if (operation.sum <= 0) {
        throw "sum err";
    }

    for (int i = 0; i < size; i++) {
        newOperation[i] = operations[i];
    }

    newOperation[size] = operation;

    delete[] operations;
    operations = newOperation;
    size++;
}

void outputOperations(Operation* operations, int size) {
    if (size == 0) {
        throw 404;
    }

    for (int i = 0; i < size; i++) {
        cout << "Дата операції: " << operations[i].date.day<<"."<<operations[i].date.month <<"." << operations[i].date.year << " | \n" << "Тип операції: " << operations[i].type << " | \n" << "Сума операції: " << operations[i].sum << " | \n" << "Рахунок  номер: " << operations[i].accountId << " | \n" << "Категорія операції: " << operations[i].category << " | \n" << "Опис операції: " << operations[i].description << " | " << endl;
    }
}

void showAccountOperations(Operation* operations, int size, int accountId) {
    bool found = false;
    for (int i = 0; i < size; i++) {
        if (operations[i].accountId == accountId) {
            found = true;
            cout << "Дата операції: " << operations[i].date.day << "." << operations[i].date.month << "." << operations[i].date.year << " | \n" << "Тип операції: " << operations[i].type << " | \n" << "Сума операції: " << operations[i].sum << " | \n" << "Рахунок  номер: " << operations[i].accountId << " | \n" << "Категорія операції: " << operations[i].category << " | \n" << "Опис операції: " << operations[i].description << " | " << endl;
        }
    }
    if (!found) {
        throw 404;
    }
}
void showCategoryOperations(Operation* operations, int size, string category) {
    bool found = false;
    for (int i = 0; i < size; i++) {
        if (operations[i].category == category) {
            found = true;
            cout << "Дата операції: " << operations[i].date.day << "." << operations[i].date.month << "." << operations[i].date.year << " | \n" << "Тип операції: " << operations[i].type << " | \n" << "Сума операції: " << operations[i].sum << " | \n" << "Рахунок  номер: " << operations[i].accountId << " | \n" << "Категорія операції: " << operations[i].category << " | \n" << "Опис операції: " << operations[i].description << " | " << endl;
        }
    }
    if (!found) {
        throw 404;
    }
}
bool isDateBetween(Date date, Date start, Date end) {
    if (date.year < start.year || date.year > end.year) {
        return false;
    }

    if (date.year == start.year && date.month < start.month) {
        return false;
    }

    if (date.year == start.year && date.month == start.month && date.day < start.day) {
        return false;
    }

    if (date.year == end.year && date.month > end.month) {
        return false;
    }

    if (date.year == end.year && date.month == end.month && date.day > end.day) {
        return false;
    }

    return true;
}


void showPeriodOperations(Operation* operations, int size, Date start, Date end) {
    bool found = false;
    for (int i = 0; i < size; i++) {
        if (isDateBetween(operations[i].date, start, end)) {
            found = true;
            cout << "Дата операції: " << operations[i].date.day << "." << operations[i].date.month << "." << operations[i].date.year << " | \n" << "Тип операції: " << operations[i].type << " | \n" << "Сума операції: " << operations[i].sum << " | \n" << "Рахунок  номер: " << operations[i].accountId << " | \n" << "Категорія операції: " << operations[i].category << " | \n" << "Опис операції: " << operations[i].description << " | " << endl;
        }
    }
    if (!found) {
        throw 404;
    }
}
void searchOperations(Operation* operations, int size, string description) {
    bool found = false;
    for (int i = 0; i < size; i++) {
        if (operations[i].description.find(description) != string::npos) {
            found = true;
            cout << "Дата операції: " << operations[i].date.day << "." << operations[i].date.month << "." << operations[i].date.year << " | \n" << "Тип операції: " << operations[i].type << " | \n" << "Сума операції: " << operations[i].sum << " | \n" << "Рахунок  номер: " << operations[i].accountId << " | \n" << "Категорія операції: " << operations[i].category << " | \n" << "Опис операції: " << operations[i].description << " | " << endl;
        }
    }
    if (!found) {
        throw 404;
    }
}

bool hasExpenses(Expence* expences, int expSize, int accountId) {
    for (int i = 0; i < expSize; i++) {
        if (expences[i].accountId == accountId) {
            return true;
        }
    }
    return false;
}