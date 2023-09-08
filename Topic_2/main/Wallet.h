#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <ctime>
#include <map>
#include <algorithm>
#include "Transaction.h"
using namespace std;

// Определение класса Wallet для представления кошельков и карт
class Wallet {
private:
    string name;            // Название кошелька или карты
    bool isDebitCard;       // Флаг, указывающий, является ли карта дебетовой
    double balance;         // Баланс кошелька или карты
    vector<Transaction> transactions; // Вектор транзакций

public:
    // Конструктор класса Wallet для инициализации объекта кошелька или карты
    Wallet(const string &name, bool isDebitCard = false)
        : name(name), isDebitCard(isDebitCard), balance(0.0) {}

    // Методы доступа к полям класса Wallet
    const string &getName() const;

    bool isDebit() const;

    double getBalance() const;

    const vector<Transaction> &getTransactions() const;

    // Метод для пополнения баланса кошелька или карты
    void deposit(double amount);

    // Метод для списания средств с кошелька или карты с указанием суммы, категории и времени
    void spend(double amount, const string &category, const time_t &timestamp);      
};
