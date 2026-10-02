#include <iostream>
#include <string>
#include <fstream>
using namespace std;

#include "Account.h"


bool isCard(Account account) {
    return account.cardType != cashCard;
}

void addAccount(Account*& accounts, int& size, Account account) {
    Account* newAccount = new Account[size + 1];

    for (int i = 0; i < size; i++) {
        newAccount[i] = accounts[i];
    }

    newAccount[size] = account;

    delete[] accounts;
    accounts = newAccount;
    size++;
}

void outputAllAccounts(Account*& accounts, int size) {
    for (int i = 0; i < size; i++) {
        cout << "ID: " << accounts[i].cardId << endl;
        cout << "name: " << accounts[i].cardName << endl;
        cout << "bal: " << accounts[i].balance << endl;
        cout << "val: " << accounts[i].currency << endl;
    }
}

void showAccount(Account* accounts, int size, int id) {
    for (int i = 0; i < size; i++) {
        if (accounts[i].cardId == id) {
            cout << "ID: " << accounts[i].cardId << endl;
            cout << "name: " << accounts[i].cardName << endl;
            cout << "bal: " << accounts[i].balance << endl;
            cout << "val: " << accounts[i].currency << endl;

            if (isCard(accounts[i])) {
                cout << "cardNum: " << accounts[i].cardNumber << endl;
                cout << "Termin: " << accounts[i].expirationDate.day<<"."<< accounts[i].expirationDate.month << "."<< accounts[i].expirationDate.year << "." << endl;
            }

            return;
        }
    }

    throw "404";
}

void editAccount(Account* accounts, int size, int cardId, Account account) {
    for (int i = 0; i < size; i++) {
        if (accounts[i].cardId == cardId) {

            account.cardId = cardId;
            accounts[i] = account;

            return;
        }
    }

    throw "404";
}


void deleteAccount(Account*& accounts, int& size, int cardId) {
    int deleteIndex = -1;

    for (int i = 0; i < size; i++) {
        if (accounts[i].cardId == cardId) {
            deleteIndex = i;
            break;
        }
    }

    if (deleteIndex == -1) {
        throw "notAccount";
    }

    Account* newAccount = new Account[size - 1];
    int index = 0;
    for (int i = 0; i < size; i++) {
        if (accounts[i].cardId != cardId) {
            newAccount[index] = accounts[i];
            index++;
        }
    }

    delete[] accounts;
    accounts = newAccount;
    size--;
}

int findAccount(Account* accounts, int size, int cardId) {
    for (int i = 0; i < size; i++) {
        if (accounts[i].cardId == cardId) {
            return i;
        }
    }

    return -1;
}

bool isValidDate(Date d) {
    if (d.year < 2000 || d.year > 2100) { 
        return false;
    }
    if (d.month < 1 || d.month > 12) {
        return false;
    }
    if (d.day < 1 || d.day > 31) {
        return false;
    }

    if ((d.month == 4 || d.month == 6 || d.month == 9 || d.month == 11) && d.day > 30) {
        return false;
    }

    if (d.month == 2) {
        bool isLeap = (d.year % 4 == 0 && d.year % 100 != 0) || (d.year % 400 == 0);
        if (d.day > (isLeap ? 29 : 28)) {
            return false;
        }
    }

    return true;
}