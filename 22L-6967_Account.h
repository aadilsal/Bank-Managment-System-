//22L-6967
#pragma once
#pragma warning(disable : 4996) //Included to ignore error for localtime 
#include<iostream>
#include<string>
#include"22L-6967_Transcation.h"
#include<ctime>
#include<cstdlib>
using namespace std;

int generateID() {
	int acc_serial = 0;
	return acc_serial++;
}
string getCurrentDate() {
	time_t currT = time(NULL);
	tm* localTime = localtime(&currT);

	int year = localTime->tm_year + 1900;//years since 1900
	int month = localTime->tm_mon + 1; //0-11
	int day = localTime->tm_mday; //day of month

	string yr, mon, da;
	if (month < 10) {
		mon = "0" + to_string(month);
	}
	else {
		mon = to_string(month);
	}
	if (day < 10) {
		da = "0" + to_string(day);
	}
	else {
		da = to_string(day);
	}

	string currentDate = da + "-" + mon + "-" + to_string(year);
	return currentDate;
}
string getCurrentTime() {
	time_t currT = time(NULL);
	tm* localTime = localtime(&currT);

	int hour = localTime->tm_hour; //HOUR
	int minutes = localTime->tm_min; //MINUTES
	int seconds = localTime->tm_sec; //Seconds

	string hr, min, sec;
	if (hour < 10) {
		hr = "0" + to_string(hour);
	}
	else {
		hr = to_string(hour);
	}
	if(minutes < 10) {
		min = "0" + to_string(minutes);
	}
	else {
		min = to_string(minutes);
	}
	if (seconds < 10) {
		sec = "0" + to_string(seconds);
	}
	else {
		sec = to_string(seconds);
	}
	string currentTime = hr + ":" + min + ":" + sec;
	return currentTime;
}
template<typename T>
class Account {
public:
	string accountNum;
	string accountTitle;
	double accountBalance;
	TransactionHis<T> History;

	Account(string& accNum, string& accT, double accBal) {
		accountNum = accNum;
		accountTitle = accT;
		accountBalance = accBal;
	}

	void credit(double amount) {
		accountBalance += amount;
		int id = generateID();
		string date = getCurrentDate();
		string time = getCurrentTime();
		string type = "credit";
		History.addTransaction(id, time, date, type, amount, accountNum);
	}

	bool debit(double amount) {
		if (accountBalance < amount) {
			cout << "Insufficient Balance\n";
			return false;
		}
		else {
			accountBalance -= amount;
			int id = generateID();
			string date = getCurrentDate();
			string time = getCurrentTime();
			string type = "debit";
			History.addTransaction(id, time, date, type, amount, accountNum);
			return true;
		}
	}

	void displayDetails() {
		cout << "Account Number: " << accountNum << endl;
		cout << "Account Title: " << accountTitle << endl;
		cout << "Account Balance: " << accountBalance << endl;
		cout << "Transaction History: " << endl;
		for (typename TransactionHis<T>::TransIterator It = History.begin(); It != History.end(); ++It) {
			const typename TransactionHis<T>::Transaction& trans = *It;

			cout << "Transaction ID: " << trans.transID << endl;
			cout << "Transaction Time: " << trans.transTime << endl;
			cout << "Transaction Date: " << trans.transDate << endl;
			cout << "Transaction Type: " << trans.transType << endl;
			cout << "Transfer Amount: " << trans.transferredAmount << endl;
			cout << "Account Number: " << trans.accNum << endl;
		}
		cout << endl;
	}
	
};