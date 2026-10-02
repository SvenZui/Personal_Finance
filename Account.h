#pragma once
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

struct Date {
	int day = 0;
	int month = 0;
	int year = 0;
};

enum AccountType{
	cashCard,
	debitCard,
	creditCard
};

struct Account {
	int cardId = 0;
	string cardName = "none";
	AccountType  cardType;
	double balance = 0;
	string currency = "None";
	string cardNumber = "None";//за потреби поміняти
	Date expirationDate = { 0,0,0 };
};

bool isCard(Account account);	

void addAccount(Account*& accounts, int& size, Account account);
void outputAllAccounts(Account*& accounts, int size);
void showAccount(Account* accounts, int size, int id);
void editAccount(Account* accounts, int size, int cardId, Account account);
void deleteAccount(Account*& accounts, int& size, int cardId);

int findAccount(Account* accounts, int size, int cardId);

bool isValidDate(Date d);