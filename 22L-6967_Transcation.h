//22L-6967
#pragma once
#include<string>
#include<iostream>
using namespace std;
template<typename T>
class TransactionHis {
public:
    class Transaction {
    public:
        int transID;
        string transTime;
        string transDate;
        string transType;
        double transferredAmount;
        string accNum;

        Transaction(int id, string& time, string& date, string& type, double amount, string& acc) {
            transID = id;
            transTime = time;
            transDate = date;
            transType = type;
            transferredAmount = amount;
            accNum = acc;
        }
        Transaction* next; //  the next transaction
        Transaction* prev; //  the previous transaction
    };
    Transaction* head; //  first transaction in the list

    TransactionHis() {
        head = NULL;
    }

    void addTransaction(int id, string& time, string& date, string& type, double amount, string& acc) {
    Transaction* temp = new Transaction(id, time, date, type, amount, acc);
    temp->next = head;
    head = temp;
}


    void clearHistory() {
        while (head != NULL) {
            Transaction* temp = head;
            head = head->next;
            delete temp;
        }
    }

    class TransIterator {
    public:
        TransIterator(Transaction* start) {
            current = start;
        }

        TransIterator& operator++() {
            if (current != NULL) {
                current = current->next;
            }
            return *this;
        }

        bool operator!=(const TransIterator& t) const {
            return current != t.current;
        }


        Transaction& operator*() {
            return *current;
        }

    private:
        Transaction* current;
    };

    TransIterator begin() {
        return TransIterator(head);
    }

    TransIterator end() {
        return TransIterator(NULL);
    }
};
