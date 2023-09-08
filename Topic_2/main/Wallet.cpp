#include <iostream>
#include <string>
#include "Wallet.h"

const string &Wallet::getName() const
{
	return name;
}

bool Wallet::isDebit() const
{
	return isDebitCard;
}

double Wallet::getBalance() const
{
	return balance;
}

const vector<Transaction> &Wallet::getTransactions() const
{
	return transactions;
}

void Wallet::deposit(double amount)
{
	balance += amount;
}

void Wallet::spend(double amount, const string &category, const time_t &timestamp)
{
    if (balance >= amount) {
        balance -= amount;
        transactions.emplace_back(category, amount, timestamp);
    }
    else {
        cout << "Недостаточно средств на кошельке." << endl;
    }
}
