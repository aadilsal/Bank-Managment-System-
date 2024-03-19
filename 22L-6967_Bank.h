//22L-6967
#pragma once
#include<iostream>
#include<string.h>
#include"22l-6967_Account.h"
#include"22L-6967_Transcation.h"
template<typename T>
class Bank {
private:
    class Node {
    public:
        Account<T>* acc;
        Node* next;
        Node* prev;

        Node(Account<T>* a, Node* n = NULL, Node* p = NULL) {
            acc = a;
            next = n;
            prev = p;
        }
    };
    Node* head;
    int acc_serial;
    int trans_Serial;

public:
    Bank() {
        head = NULL;
        acc_serial = 0;
        trans_Serial = 0;
    }

    ~Bank() {
        Node* tmp = head;
        while (tmp) {
            Node* tmp2 = tmp;
            tmp = tmp->next;
            delete tmp2->acc;
            delete tmp2;
        }
    }

    void addAccount(string& accNum,string& title, double balance) {
        Account<T>* account = new Account<T>(accNum, title, balance);
        Node* temp = new Node(account);

        if (!head) {
            head = temp;
        }
        else {
            temp->next = head;
            head->prev = temp;
            head = temp;
        }
    }

    void removeAccount(string& aNum) {
        Node* current = head;
        while (current) {
            if (current->acc->accountNum == aNum) {
                if (current->prev != NULL) {
                    current->prev->next = current->next;
                }
                else {
                    head = current->next;
                }
                if (current->next != NULL) {
                    current->next->prev = current->prev;
                }
                delete current->acc;
                delete current;
                return;
            }
            current = current->next;
        }
        cout << "Account not found!\n";
    }

    void mergeAccount(string& acc1, string& acc2, string& newAccNum,string& newAccTitle) {
        Node* a1 = NULL;
        Node* a2 = NULL;

        Node* curr = head;
        while (curr) {
            if (curr->acc->accountNum == acc1) {
                a1 = curr;
            }
            if (curr->acc->accountNum == acc2) {
                a2 = curr;
            }
            curr = curr->next;
        }

        if (a1 && a2) {
            double nBal = a1->acc->accountBalance + a2->acc->accountBalance;

            addAccount(newAccNum,newAccTitle, nBal);

            string newAccNum = to_string(acc_serial++);
            Node* newAccNode = head;
            while (newAccNode->acc->accountNum != newAccNum) {
                newAccNode = newAccNode->next;
            }

            for (typename TransactionHis<T>::TransIterator iS = a1->acc->History.begin(); iS != a1->acc->History.end(); ++iS) {
                typename TransactionHis<T>::Transaction& trans = *iS; 
                newAccNode->acc->History.addTransaction(trans.transID, trans.transTime,
                    trans.transDate, trans.transType,
                    trans.transferredAmount, trans.accNum);
            }



            for (typename TransactionHis<T>::TransIterator i2S = a2->acc->History.begin(); i2S != a2->acc->History.end(); ++i2S) {
                typename TransactionHis<T>::Transaction& trans = *i2S; 
                newAccNode->acc->History.addTransaction(trans.transID, trans.transTime,
                    trans.transDate, trans.transType,
                    trans.transferredAmount, trans.accNum);
            }

            removeAccount(acc1);
            removeAccount(acc2);
        }
        else {
            cout << "Account not found!\n";
        }
    }

    void performTransaction(string& accNum, string TransType, double amount) {
        Node* curr = head;

        while (curr) {
            if (curr->acc->accountNum == accNum) {
                if (TransType == "credit") {
                    curr->acc->credit(amount);
                    cout << "Transaction Successful!\n";
                }
                else if (TransType == "debit") {
                    if (curr->acc->debit(amount)) {
                        string cTime = getCurrentTime();
                        string cDate = getCurrentDate();
                        int id = trans_Serial++;
                        curr->acc->History.addTransaction(id, cTime, cDate, TransType, amount, accNum);
                        cout << "Transaction Successful!\n";
                    }
                    else {
                        
                        return;
                    }
                }
                else {
                    cout << "Invalid Transaction Type\n";
                }
                return;
            }
            curr = curr->next;
        }
        cout << "Account not found!\n";
    }
    void displayAccount() {
        Node* temp = head;
        while (temp) {
            temp->acc->displayDetails();
            temp=temp->next;
        }
    }
    string getAccSerial() {
        ++acc_serial;
        return to_string(acc_serial);
    }
    string getTransSerial() {
        ++trans_Serial;
        return to_string(trans_Serial);
    }
};
                                      