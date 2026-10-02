#include "pch.h"
#include "CppUnitTest.h"

#include "../Personal_Finance_Manager/Account.h"
#include "../Personal_Finance_Manager/Expense.h"
#include "../Personal_Finance_Manager/FileManager.h"
#include "../Personal_Finance_Manager/Finance.h"
#include "../Personal_Finance_Manager/Reports.h"
#include "../Personal_Finance_Manager/menu.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace PersonalFinanceManagerTests
{
    TEST_CLASS(AccountTests)
    {
    public:

        TEST_METHOD(FindAccountReturnsCorrectIndex)
        {
            Account accounts[2];

            accounts[0].cardId = 10;
            accounts[1].cardId = 20;

            int result = findAccount(accounts, 2, 20);

            Assert::AreEqual(1, result);
        }

        TEST_METHOD(FindAccountReturnsMinusOneIfNotFound)
        {
            Account accounts[2];

            accounts[0].cardId = 10;
            accounts[1].cardId = 20;

            int result = findAccount(accounts, 2, 50);

            Assert::AreEqual(-1, result);
        }

        TEST_METHOD(IsValidDateReturnsTrueForCorrectDate)
        {
            Date date;

            date.day = 15;
            date.month = 6;
            date.year = 2026;

            Assert::IsTrue(isValidDate(date));
        }

        TEST_METHOD(IsValidDateReturnsFalseForIncorrectDate)
        {
            Date date;

            date.day = 32;
            date.month = 6;
            date.year = 2026;

            Assert::IsFalse(isValidDate(date));
        }
    };
}