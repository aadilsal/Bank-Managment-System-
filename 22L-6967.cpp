#include<iostream>
#include"22L-6967_Bank.h"
#include"22L-6967_Account.h"
#include"22L-6967_Transcation.h"
using namespace std;

int main() {
    Bank<TransactionHis<string>> b;

    int choice;
    while (true) {
        cout << "****Bank****\n";
        cout << "1. Add Account\n";
        cout << "2. Perform Transaction\n";
        cout << "3. Merge Accounts\n";
        cout << "4. Remove Account\n";
        cout << "5. Display Account Details\n";
        cout << "6. Quit\n";
        cout << "Enter your choice (1-6): ";
        cin >> choice;

        if (choice == 1) {
            string acNum = b.getAccSerial();
            string acTitle, acNumStr;
            double acBal;
            cout << "Enter account title: ";
            cin.ignore(); 
            getline(cin, acTitle);
            cout << "Enter initial account balance: ";
            cin >> acBal;
            b.addAccount(acNum, acTitle, acBal);
        }
        else if (choice == 2) {
            cout << "Enter account number: ";
            string accNum;
            cin >> accNum;
            cout << "Enter transaction type (credit/debit): ";
            string transType;
            cin >> transType;
            cout << "Enter transaction amount: ";
            double amount;
            cin >> amount;
            b.performTransaction(accNum, transType, amount);
        }
        else if (choice == 3) {
            cout << "Enter the first account number: ";
            string acc1;
            cin >> acc1;
            cout << "Enter the second account number: ";
            string acc2;
            cin >> acc2;
            string newAccNum = b.getAccSerial();
            string newAccTitle = "Merge";
            b.mergeAccount(acc1, acc2, newAccNum, newAccTitle);
        }
        else if (choice == 4) {
            cout << "Enter the account number to remove: ";
            string accToRemove;
            cin >> accToRemove;
            b.removeAccount(accToRemove);
        }
        else if (choice == 5) {
            cout << "Account Details:\n";
            b.displayAccount();
        }
        else if (choice == 6) {
            cout << "Exiting the menu.\n";
            break;
        }
        else {
            cout << "Invalid choice. Please enter a valid option.\n";
        }
    }

    return 0;
}
