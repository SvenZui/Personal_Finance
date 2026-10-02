#include <iostream>
#include <string>
#include <fstream>

#include "menu.h"
using namespace std;



void handleAccountsMenu(Account*& accounts, int& accountSize, Expence* expences, int expenceSize) {
    int choice = -1;
    do {
        cout << endl;
        cout << "========== РАХУНКИ ==========" << endl;
        cout << "1. Додати рахунок" << endl;
        cout << "2. Показати всі рахунки" << endl;
        cout << "3. Показати рахунок" << endl;
        cout << "4. Редагувати рахунок" << endl;
        cout << "5. Видалити рахунок" << endl;
        cout << "0. Назад" << endl;
        cout << "Ваш вибір: ";

        try {
            if (!(cin >> choice)) {
                cin.clear();
                cin.ignore(10000, '\n');
                throw "Введіть число!";
            }

            switch (choice) {
            case 1: {
                Account acc;
                cout << "Введіть ID: ";
                if (!(cin >> acc.cardId)) {
                    throw "non intId";
                }

                if (findAccount(accounts, accountSize, acc.cardId) != -1) {
                    throw "isID";
                }

                cout << "Назва рахунку: ";
                cin.ignore(); 
                getline(cin, acc.cardName);
                cout << "Тип (0 - готівка, 1 - дебетова, 2 - кредитна): ";

                int type;

                if (!(cin >> type)) {
                    throw "typeErr";
                }
                acc.cardType = (AccountType)type;

                cout << "Баланс: ";
                if (!(cin >> acc.balance)) {
                    throw "errBal";
                }

                cout << "Валюта: "; cin >> acc.currency;

                if (acc.cardType != cashCard) {
                    cout << "Номер картки: "; cin >> acc.cardNumber;
                    cout << "День закінчення дії: "; cin >> acc.expirationDate.day;
                    cout << "Місяць закінчення дії: "; cin >> acc.expirationDate.month;
                    cout << "Рік закінчення дії: "; cin >> acc.expirationDate.year;

                    if (!isValidDate(acc.expirationDate)) {
                        throw "Некоректна дата закінчення дії картки!";
                    }
                }
                else {
                    
                    acc.cardNumber = "None";
                    acc.expirationDate = { 0, 0, 0 };
                }

                addAccount(accounts, accountSize, acc);
                cout << "рахунок додано" << endl;
                break;
            }
            case 2:
                outputAllAccounts(accounts, accountSize);
                break;

            case 3: {
                int id;
                cout << "Введіть ID рахунку: ";
                if (!(cin >> id)) {
                    throw "int err";
                }
                  
                showAccount(accounts, accountSize, id);
                break;
            }
            case 4: {
                int id;
                cout << "ID рахунку для редагування: ";
                if (!(cin >> id)) {
                    throw "int err";
                }

                if (findAccount(accounts, accountSize, id) == -1) {
                    throw 404;
                }

                Account acc;
                cout << "Нова назва: "; cin.ignore(); getline(cin, acc.cardName);
                cout << "Новий тип (0 - готівка, 1 - дебетова, 2 - кредитна): ";
                int type;
                if (!(cin >> type)) {
                    throw "type err";
                }
                acc.cardType = (AccountType)type;

                cout << "Новий баланс: ";
                if (!(cin >> acc.balance)) {
                    throw "-1";
                }

                cout << "Нова валюта: "; cin >> acc.currency;

                if (acc.cardType != cashCard) {
                    cout << "Новий номер картки: "; cin >> acc.cardNumber;
                    cout << "День закінчення дії: "; cin >> acc.expirationDate.day;
                    cout << "Місяць закінчення дії: "; cin >> acc.expirationDate.month;
                    cout << "Рік закінчення дії: "; cin >> acc.expirationDate.year;

                    if (!isValidDate(acc.expirationDate)) {
                        throw "Некоректна дата закінчення дії картки!";
                    }
                }
                else {
                    acc.cardNumber = "None";
                    acc.expirationDate = { 0, 0, 0 };
                }

                editAccount(accounts, accountSize, id, acc);
                cout << "-> Рахунок змінено!" << endl;
                break;
            }
            case 5: {
                int id;
                cout << "ID рахунку для видалення: ";
                if (!(cin >> id)){
                    throw "errID";
                }

                if (hasExpenses(expences, expenceSize, id)) {
                    throw -1;
                }

                deleteAccount(accounts, accountSize, id);
                cout << "-> Рахунок видалено!" << endl;
                break;
            }
            case 0: break;
            default: cout << "Невірний пункт меню!" << endl;
            }
        }
        catch (const char* msg) {
            cout << endl;
            cout << "error: " << msg << endl;
            cin.clear();
            cin.ignore(10000, '\n');
        }
        catch (...) {
            cout << endl;
            cout << "erorr unknown" << endl;
            cin.clear();
            cin.ignore(10000, '\n');
        }

    } while (choice != 0);
}

void handleExpensesMenu(Expence*& expences, int& expenceSize, Account* accounts, int accountSize, Operation*& operations, int& operationSize) {
    int choice = -1;
    do {
        cout << endl;
        cout << "========== ВИТРАТИ ==========" << endl;
        cout << "1. Додати витрату" << endl;
        cout << "2. Редагувати витрату" << endl;
        cout << "3. Видалити витрату" << endl;
        cout << "0. Назад" << endl;
        cout << "Ваш вибір: ";
        if (!(cin >> choice)) throw "Потрібне число";

        switch (choice) {
        case 1: {
            Expence exp;
            cout << "ID витрати: "; if (!(cin >> exp.id))
            {
                throw "Некоректний ID!";
            }
            cout << "Сума: "; if (!(cin >> exp.sume)) { 
                throw "Некоректна сума!"; }


            cout << "Дата (День Місяць Рік): "; cin >> exp.date.day >> exp.date.month >> exp.date.year;
            cout << "Категорія: ";


            cin.ignore();
            getline(cin, exp.category);

            cout << "ID рахунку: "; cin >> exp.accountId;
            cout << "Опис: ";

            cin.ignore();
            getline(cin, exp.description);

            addExpence(expences, expenceSize, exp, accounts, accountSize);

            Operation op = { exp.date, "Витрата", exp.sume, exp.accountId, exp.category, exp.description };
            addOperation(operations, operationSize, op);

            cout << "-> Витрату додано!" << endl;
            break;
        }
        case 2: {
            int id; double amount; string category, description;
            cout << "ID витрати для редагування: "; cin >> id;
            cout << "Нова сума: "; cin >> amount;
            cout << "Нова категорія: ";
            cin.ignore();
            getline(cin, category);
            cout << "Новий опис: ";
            getline(cin, description);

            editExpence(expences, expenceSize, id, amount, category, description, accounts, accountSize);
            cout << "-> Витрату змінено!" << endl;
            break;
        }
        case 3: {
            int id;
            cout << "ID витрати для видалення: "; cin >> id;
            deleteExpence(expences, expenceSize, id, accounts, accountSize);
            cout << "-> Витрату видалено!" << endl;
            break;
        }
        case 0: break;
        default: cout << "Невірний пункт меню!" << endl;
        }
    } while (choice != 0);
}

void handleCategoriesMenu(string*& categories, int& categorySize, Expence* expences, int expenceSize) {
    int choice = -1;
    do {
        cout << endl;
        cout << "========== КАТЕГОРІЇ ==========" << endl;
        cout << "1. Показати всі категорії" << endl;
        cout << "2. Додати категорію" << endl;
        cout << "3. Видалити категорію" << endl;
        cout << "0. Назад" << endl;
        cout << "Ваш вибір: ";
        if (!(cin >> choice)) {
            throw "Потрібно ввести число!"; 
        }

        switch (choice) {
        case 1:
            showCategories(categories, categorySize);
            break;
        case 2: {
            string category;
            cout << "Назва нової категорії: ";
            cin.ignore();
            getline(cin, category);
            addCategory(categories, categorySize, category);
            cout << "-> Категорію додано!" << endl;
            break;
        }
        case 3: {
            string category;
            cout << "Назва категорії для видалення: ";
            cin.ignore();
            getline(cin, category);

            bool isUsed = false;
            for (int i = 0; i < expenceSize; i++) {
                if (expences[i].category == category) { isUsed = true; break; }
            }
            if (isUsed) throw "Неможливо видалити категорію, вона використовується у витратах!";

            deleteCategory(categories, categorySize, category);
            cout << "-> Категорію видалено!" << endl;
            break;
        }
        case 0: break;
        default: cout << "Невірний пункт меню!" << endl;
        }
    } while (choice != 0);
}

void handleOperationsMenu(Operation* operations, int operationSize) {
    int choice = -1;
    do {
        cout << endl;
        cout << "========== ІСТОРІЯ ОПЕРАЦІЙ ==========" << endl;
        cout << "1. Показати всі операції" << endl;
        cout << "2. Операції за рахунком" << endl;
        cout << "3. Операції за категорією" << endl;
        cout << "4. Операції за період" << endl;
        cout << "0. Назад" << endl;
        cout << "Ваш вибір: ";
        if (!(cin >> choice)) throw "Потрібно ввести число!";

        switch (choice) {
        case 1:

            outputOperations(operations, operationSize);
            break;

        case 2: {

            int id; 
            cout << "ID рахунку: "; cin >> id;

            showAccountOperations(operations, operationSize, id);
            break;
        }
        case 3: {

            string cat; 
            cout << "Категорія: "; 
            cin.ignore(); 
            getline(cin, cat);

            showCategoryOperations(operations, operationSize, cat);
            break;
        }
        case 4: {
            Date start, end;
            cout << "Початкова дата (День Місяць Рік): "; cin >> start.day >> start.month >> start.year;
            cout << "Кінцева дата (День Місяць Рік): "; cin >> end.day >> end.month >> end.year;
            showPeriodOperations(operations, operationSize, start, end);
            break;
        }
        case 0: break;

        default: cout << "Невірний пункт меню!" << endl;
        }
    } while (choice != 0);
}