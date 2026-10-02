#include <iostream>
#include <string>
#include <fstream>
using namespace std;

#include "Finance.h"


void addBalance(Account* accounts, int size, int CardId, double amout) {
    if (amout <= 0) {
        throw -1;
    }

    int index = findAccount(accounts, size, CardId);

    if (index == -1) {
        throw 404;
    }

    accounts[index].balance += amout;
}