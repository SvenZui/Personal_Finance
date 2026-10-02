#include <ctime>
#include <string>
#include <fstream>

#include "Reports.h"
using namespace std;

void createReport(Expence* expences, int size, Date start, Date end, string* categories, int categorySize, Account* accounts, int accountSize) {
    double* categorySums = new double[categorySize];

    for (int i = 0; i < categorySize; i++) {
        categorySums[i] = 0.0;
    }

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

    for (int i = 0; i < size; i++) {
        if (isDateBetween(expences[i].date, start, end)) {

            for (int j = 0; j < categorySize; j++) {

                if (expences[i].category == categories[j]) {
                    categorySums[j] += expences[i].sume;
                }

            }
        }
    }

    double* accountSums = new double[accountSize];

    for (int i = 0; i < accountSize; i++) {
        accountSums[i] = 0.0;
    }

    for (int i = 0; i < accountSize; i++) {
        for (int j = 0; j < size; j++) {

            if (isDateBetween(expences[j].date, start, end)) {

                if (expences[j].accountId == accounts[i].cardId) {
                    accountSums[i] += expences[j].sume;
                }

            }
        }
    }

    if (count == 0) {
        delete[] categorySums;
        delete[] accountSums;
        throw "0";
    }

    double average = total / count;

    cout << "total: " << total << endl;
    cout << "cout: " << count << endl;
    cout << "max: " << max << endl;
    cout << "min: " << min << endl;
    cout << "avg: " << average << endl;

    for (int i = 0; i < categorySize; i++) {
        cout << categories[i] << ": " << categorySums[i] << endl;
    }

    for (int i = 0; i < accountSize; i++) {
        cout << "Рахунок " << accounts[i].cardId<< ": " << accountSums[i] << endl;
    }
    delete[] categorySums;
    delete[] accountSums;
}




void top3Expences(Expence* expences, int size, Date start, Date end) {

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

    if (topSize == 0) {
        delete[] top;
        throw "0";
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

    cout << "========== ТОП-3 ВИТРАТИ ==========" << endl;

    for (int i = 0; i < topSize; i++) {
        cout << i + 1 << ". "<< top[i].sume << " грн — " << top[i].category << " — " << top[i].description << endl;
    }

    delete[] top;
}



void top3Categories(Expence* expences, int size, Date start, Date end,
    string* categories, int categorySize) {

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

    if (topSize == 0) {
        delete[] categorySums;
        delete[] top;

        throw "0";
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

    cout << "========== ТОП-3 КАТЕГОРІЙ ==========" << endl;

    for (int i = 0; i < topSize; i++) {
        cout << i + 1 << ". "<< categories[top[i]] << " — " << categorySums[top[i]] << " грн" << endl;
    }

    delete[] categorySums;
    delete[] top;
}