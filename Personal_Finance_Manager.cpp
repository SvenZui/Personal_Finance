#include <iostream>
#include <string>
#include <fstream>
#include "windows.h"
using namespace std;

#include "Expense.h"
#include "FileManager.h"
#include "Account.h"
#include "Reports.h"
#include "Finance.h"
#include "menu.h"


int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    int operationSize = 0;
    int accountSize = 0;
    int categorySize = 0;
    int expenceSize = 0;

    Account* accounts = new Account[0];
    string* categories = new string[0];
    Expence* expences = new Expence[0];
    Operation* operations = new Operation[0];

    try {
        loadAccounts(accounts, accountSize);
        loadCategories(categories, categorySize);
        loadExpences(expences, expenceSize);
        loadOperations(operations, operationSize);
    }
    catch (...) {
        cout << "Перший запуск або файли відсутні. Дані збережуться при виході." << endl;
    }

    int choice = -1;

    do {
        cout << endl;
        cout << "================================" << endl;
        cout << "     PERSONAL FINANCE MANAGER" << endl;
        cout << "================================" << endl;
        cout << "1. Рахунки" << endl;
        cout << "2. Поповнити рахунок"<< endl;
        cout << "3. Витрати" << endl;
        cout << "4. Категорії" << endl;
        cout << "5. Історія операцій" << endl;
        cout << "6. Пошук операцій" << endl;
        cout << "7. Звіти за період" << endl;
        cout << "8. ТОП-3 витрат та категорій" << endl;
        cout << "9. Експорт звіту у файл" << endl;
        cout << "10. Зберегти дані" << endl;
        cout << "0. Вихід " << endl;
        cout << endl;
        cout << "Ваш вибір: ";

        try {
            if (!(cin >> choice)) {
                cin.clear();
                cin.ignore(10000, '\n');
                throw "int err";
            }

            switch (choice) {
            case 1:
                handleAccountsMenu(accounts, accountSize, expences, expenceSize);
                break;

            case 2: {
                int id; 
                double sume;
                cout << "ID рахунку: "; cin >> id;
                cout << "Сума поповнення: "; cin >> sume;

                addBalance(accounts, accountSize, id, sume);

                Operation op;
                op.accountId = id;
                op.sum = sume;
                op.type = "Поповнення";

                cout << "Введіть день: "; cin >> op.date.day;
                cout << "Введіть місяць: "; cin >> op.date.month;
                cout << "Введіть рік: "; cin >> op.date.year;

                if (!isValidDate(op.date)) {
                    throw "Некоректна дата поповнення!";
                }

                cout << "Введіть категорію (наприклад, Дохід/Зарплата): ";
                cin >> op.category;

                cin.ignore();
                cout << "Введіть опис операції: ";
                getline(cin, op.description);

                addOperation(operations, operationSize, op);

                cout << "-> Рахунок успішно поповнено!" << endl;
                break;
            }

            case 3:
                handleExpensesMenu(expences, expenceSize, accounts, accountSize, operations, operationSize);
                break;

            case 4:
                handleCategoriesMenu(categories, categorySize, expences, expenceSize);
                break;

            case 5:
                handleOperationsMenu(operations, operationSize);
                break;

            case 6: {
                string desc;
                cout << "Введіть опис для пошуку: "; 
                cin.ignore(); 
                getline(cin, desc);
                searchOperations(operations, operationSize, desc);
                break;
            }

            case 7: {
                Date start, end;
                cout << "Початкова дата (День Місяць Рік): "; cin >> start.day >> start.month >> start.year;
                cout << "Кінцева дата (День Місяць Рік): "; cin >> end.day >> end.month >> end.year;
                createReport(expences, expenceSize, start, end, categories, categorySize, accounts, accountSize);
                break;
            }

            case 8: {
                Date start, end;
                cout << "Початкова дата (День Місяць Рік): "; cin >> start.day >> start.month >> start.year;
                cout << "Кінцева дата (День Місяць Рік): "; cin >> end.day >> end.month >> end.year;
                cout << endl;
                cout << "--- ТОП-3 ВИТРАТИ ---" << endl;
                top3Expences(expences, expenceSize, start, end);
                cout << endl;
                cout << "--- ТОП-3 КАТЕГОРІЇ ---" << endl;
                top3Categories(expences, expenceSize, start, end, categories, categorySize);
                break;
            }

            case 9: {
                Date start, end;
                cout << "Початкова дата (День Місяць Рік): "; cin >> start.day >> start.month >> start.year;
                cout << "Кінцева дата (День Місяць Рік): "; cin >> end.day >> end.month >> end.year;
                exportReport(expences, expenceSize, start, end, categories, categorySize, accounts, accountSize);
                cout << "-> Звіт успішно експортовано у файл!" << endl;
                break;
            }

            case 10:
                saveAccounts(accounts, accountSize);
                saveCategories(categories, categorySize);
                saveExpences(expences, expenceSize);
                saveOperations(operations, operationSize);
                cout << "-> Дані успішно збережено у файли!" << endl;
                break;

            case 0:
                saveAccounts(accounts, accountSize);
                saveCategories(categories, categorySize);
                saveExpences(expences, expenceSize);
                saveOperations(operations, operationSize);
                cout << "saved" << endl;
                break;

            default:
                cout << "whong choise" << endl;
            }
        }
        catch (const char* msg) {
            cout << endl;
            cout << "error: " << msg << endl;
            cin.clear();
            cin.ignore(10000, '\n');
        }
        catch (int msg) {
            cout << "eror: " << msg << endl;
            cin.clear();
            cin.ignore(10000, '\n');
        }
        catch (...) {
            cout << endl;
            cout << "error unknowm" << endl;
            cin.clear();
            cin.ignore(10000, '\n');
        }

    } while (choice != 0);

    delete[] accounts;
    delete[] categories;
    delete[] expences;
    delete[] operations;

    return 0;
}