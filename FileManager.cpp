#include <iostream>
#include <fstream>
#include "FileManager.h"

using namespace std;

void saveAccounts(Account* accounts, int size) {

    ofstream file("accounts.txt");

    if (!file.is_open()) {
        throw "!open(accounts.txt!)";
    }

    file << size << endl;

    for (int i = 0; i < size; i++) {

        file << accounts[i].cardId << endl;
        file << accounts[i].cardName << endl;
        file << accounts[i].cardType << endl;
        file << accounts[i].balance << endl;
        file << accounts[i].currency << endl;
        file << accounts[i].cardNumber << endl;

        file << accounts[i].expirationDate.day << endl;
        file << accounts[i].expirationDate.month << endl;
        file << accounts[i].expirationDate.year << endl;
    }

    file.close();
}


void loadAccounts(Account*& accounts, int& size) {
    ifstream file("accounts.txt");
    if (!file.is_open()) {
        ofstream newFile("accounts.txt");
        newFile.close();
        return;
    }

    int count = 0;
    if (!(file >> count) || count <= 0) {
        file.close();
        return;
    }

    delete[] accounts;
    accounts = new Account[count];
    size = count;

    for (int i = 0; i < size; i++) {
        file >> accounts[i].cardId;
        file.ignore();
        getline(file, accounts[i].cardName);
        int type; file >> type; accounts[i].cardType = (AccountType)type;
        file >> accounts[i].balance >> accounts[i].currency >> accounts[i].cardNumber;
        file >> accounts[i].expirationDate.day >> accounts[i].expirationDate.month >> accounts[i].expirationDate.year;
    }

    file.close();
}




void saveCategories(string* categories, int size) {

    ofstream file("categories.txt");

    if (!file.is_open()) {
        throw "!open(categories.txt!)";
    }

    file << size << endl;

    for (int i = 0; i < size; i++) {
        file << categories[i] << endl;
    }

    file.close();
}



void loadCategories(string*& categories, int& size) {
    ifstream file("categories.txt");
    if (!file.is_open()) {
        ofstream newFile("categories.txt");
        newFile.close();
        return;
    }

    int count = 0;
    if (!(file >> count) || count <= 0) {
        file.close();
        return;
    }

    delete[] categories;
    categories = new string[count];
    size = count;

    file.ignore();
    for (int i = 0; i < size; i++) {
        getline(file, categories[i]);
    }

    file.close();
}

void saveExpences(Expence* expences, int size) {

    ofstream file("expenses.txt");

    if (!file.is_open()) {
        throw "!open(expenses.txt!)";
    }

    file << size << endl;

    for (int i = 0; i < size; i++) {

        file << expences[i].id << endl;
        file << expences[i].sume << endl;

        file << expences[i].date.day << endl;
        file << expences[i].date.month << endl;
        file << expences[i].date.year << endl;

        file << expences[i].category << endl;
        file << expences[i].accountId << endl;
        file << expences[i].description << endl;
    }

    file.close();
}


void loadExpences(Expence*& expences, int& size) {
    ifstream file("expenses.txt");
    if (!file.is_open()) {
        ofstream newFile("expenses.txt");
        newFile.close();
        return;
    }

    int count = 0;
    if (!(file >> count) || count <= 0) {
        file.close();
        return;
    }

    delete[] expences;
    expences = new Expence[count];
    size = count;

    for (int i = 0; i < size; i++) {
        file >> expences[i].id;
        file >> expences[i].sume;
        file >> expences[i].date.day >> expences[i].date.month >> expences[i].date.year;
        file.ignore();
        getline(file, expences[i].category);
        file >> expences[i].accountId;
        file.ignore();
        getline(file, expences[i].description);
    }

    file.close();
}

void saveOperations(Operation* operations, int size) {

    ofstream file("operations.txt");

    if (!file.is_open()) {
        throw "!open(operations.txt!)";
    }

    file << size << endl;

    for (int i = 0; i < size; i++) {

        file << operations[i].date.day << endl;
        file << operations[i].date.month << endl;
        file << operations[i].date.year << endl;

        file << operations[i].type << endl;
        file << operations[i].sum << endl;
        file << operations[i].accountId << endl;
        file << operations[i].category << endl;
        file << operations[i].description << endl;
    }

    file.close();
}

void loadOperations(Operation*& operations, int& size) {
    ifstream file("operations.txt");
    if (!file.is_open()) {
        ofstream newFile("operations.txt");
        newFile.close();
        return;
    }

    int count = 0;
    if (!(file >> count) || count <= 0) {
        file.close();
        return;
    }

    delete[] operations;
    operations = new Operation[count];
    size = count;

    for (int i = 0; i < size; i++) {
        file >> operations[i].date.day >> operations[i].date.month >> operations[i].date.year;
        file.ignore();
        getline(file, operations[i].type);
        file >> operations[i].sum >> operations[i].accountId;
        file.ignore();
        getline(file, operations[i].category);
        getline(file, operations[i].description);
    }

    file.close();
}


void exportReport(Expence* expences, int size, Date start, Date end, string* categories, int categorySize, Account* accounts, int accountSize) {

    string fileName = "report_"+ to_string(start.year) + "_" + to_string(start.month) + ".txt";

    ofstream file(fileName);

    if (!file.is_open()) {
        throw "!createFileRep";
    }

    exportMainReport(file, expences, size, start, end);
    exportCategoryReport(file, expences, size, start, end,categories, categorySize);
    exportAccountReport(file, expences, size, start, end,accounts, accountSize);
    exportTop3Expences(file, expences, size, start, end);
    exportTop3Categories(file, expences, size, start, end,categories, categorySize);

    file.close();
}

void exportMainReport(ofstream& file, Expence* expences, int size, Date start, Date end) {

    double total = 0;
    int count = 0;
    double max = 0;
    double min = 0;

    for (int i = 0; i < size; i++) {

        if (isDateBetween(expences[i].date, start, end)) {

            total += expences[i].sume;
            count++;

            if (count == 1) {
                max = expences[i].sume;
                min = expences[i].sume;
            }

            if (expences[i].sume > max) {
                max = expences[i].sume;
            }

            if (expences[i].sume < min) {
                min = expences[i].sume;
            }
        }
    }

    if (count == 0) {
        throw "За цей період витрат немає!";
    }

    double average = total / count;

    file << "========== ЗВІТ ==========" << endl;

    file << "Період: "
        << start.day << "." << start.month << "." << start.year
        << " - "
        << end.day << "." << end.month << "." << end.year
        << endl;

    file << "all expended: " << total << " грн" << endl;
    file << "к-сть витрат: " << count << endl;
    file << "макс витрата: " << max << " грн" << endl;
    file << "мін витрата: " << min << " грн" << endl;
    file << "авг витрата: " << average << " грн" << endl;
}


void exportCategoryReport(ofstream& file, Expence* expences, int size, Date start, Date end, string* categories, int categorySize) {

    double* categorySums = new double[categorySize];

    for (int i = 0; i < categorySize; i++) {
        categorySums[i] = 0;
    }

    for (int i = 0; i < size; i++) {

        if (isDateBetween(expences[i].date, start, end)) {

            for (int j = 0; j < categorySize; j++) {

                if (expences[i].category == categories[j]) {
                    categorySums[j] += expences[i].sume;
                }
            }
        }
    }

    file << endl;
    file << "========== ВИТРАТИ ПО КАТЕГОРІЯХ ==========" << endl;

    for (int i = 0; i < categorySize; i++) {

        if (categorySums[i] > 0) {

            file << categories[i]
                << " — "
                << categorySums[i]
                << " грн"
                << endl;
        }
    }

    delete[] categorySums;
}

void exportAccountReport(ofstream& file, Expence* expences, int size,Date start, Date end, Account* accounts, int accountSize) {

    double* accountSums = new double[accountSize];

    for (int i = 0; i < accountSize; i++) {
        accountSums[i] = 0;
    }

    for (int i = 0; i < size; i++) {

        if (isDateBetween(expences[i].date, start, end)) {

            for (int j = 0; j < accountSize; j++) {

                if (expences[i].accountId == accounts[j].cardId) {
                    accountSums[j] += expences[i].sume;
                }
            }
        }
    }

    file << endl;
    file << "========== ВИТРАТИ ПО РАХУНКАХ ==========" << endl;

    for (int i = 0; i < accountSize; i++) {

        if (accountSums[i] > 0) {

            file << "Рахунок "
                << accounts[i].cardId
                << " — "
                << accountSums[i]
                << " грн"
                << endl;
        }
    }

    delete[] accountSums;
}


void exportTop3Expences(ofstream& file, Expence* expences, int size,Date start, Date end) {

    Expence* top = new Expence[3];
    int topSize = 0;

    for (int i = 0; i < size; i++) {

        if (!isDateBetween(expences[i].date, start, end)) {
            continue;
        }

        if (topSize < 3) {
            top[topSize] = expences[i];
            topSize++;
        }
        else {

            int minIndex = 0;

            for (int j = 1; j < 3; j++) {

                if (top[j].sume < top[minIndex].sume) {
                    minIndex = j;
                }
            }

            if (expences[i].sume > top[minIndex].sume) {
                top[minIndex] = expences[i];
            }
        }
    }

    for (int i = 0; i < topSize - 1; i++) {

        for (int j = i + 1; j < topSize; j++) {

            if (top[j].sume > top[i].sume) {

                Expence temp = top[i];
                top[i] = top[j];
                top[j] = temp;
            }
        }
    }

    file << endl;
    file << "========== ТОП-3 ВИТРАТИ ==========" << endl;

    for (int i = 0; i < topSize; i++) {

        file << i + 1 << ". "
            << top[i].sume << " грн — "
            << top[i].category << " — "
            << top[i].description
            << endl;
    }

    delete[] top;
}

void exportTop3Categories(ofstream& file, Expence* expences, int size,Date start, Date end, string* categories, int categorySize) {

    double* categorySums = new double[categorySize];

    for (int i = 0; i < categorySize; i++) {
        categorySums[i] = 0;
    }

    for (int i = 0; i < size; i++) {

        if (isDateBetween(expences[i].date, start, end)) {

            for (int j = 0; j < categorySize; j++) {

                if (expences[i].category == categories[j]) {
                    categorySums[j] += expences[i].sume;
                }
            }
        }
    }

    int* top = new int[3];
    int topSize = 0;

    for (int i = 0; i < categorySize; i++) {

        if (categorySums[i] == 0) {
            continue;
        }

        if (topSize < 3) {
            top[topSize] = i;
            topSize++;
        }
        else {

            int minIndex = 0;

            for (int j = 1; j < 3; j++) {

                if (categorySums[top[j]] < categorySums[top[minIndex]]) {
                    minIndex = j;
                }
            }

            if (categorySums[i] > categorySums[top[minIndex]]) {
                top[minIndex] = i;
            }
        }
    }

    for (int i = 0; i < topSize - 1; i++) {

        for (int j = i + 1; j < topSize; j++) {

            if (categorySums[top[j]] > categorySums[top[i]]) {

                int temp = top[i];
                top[i] = top[j];
                top[j] = temp;
            }
        }
    }

    file << endl;
    file << "========== ТОП-3 КАТЕГОРІЙ ==========" << endl;

    for (int i = 0; i < topSize; i++) {

        file << i + 1 << ". "
            << categories[top[i]]
            << " — "
            << categorySums[top[i]]
            << " грн"
            << endl;
    }

    delete[] categorySums;
    delete[] top;
}
