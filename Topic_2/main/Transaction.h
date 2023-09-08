#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <ctime>
#include <map>
#include <algorithm>

using namespace std;

// Определение класса Transaction для представления транзакций
class Transaction {
private:
    string category;    // Категория транзакции
    double amount;      // Сумма транзакции
    time_t timestamp;   // Временная метка транзакции

public:
    // Конструктор класса Transaction для инициализации объекта транзакции
    Transaction(const string &category, double amount, const time_t &timestamp)
        : category(category), amount(amount), timestamp(timestamp) {}

    // Методы доступа к полям класса Transaction
    const string &getCategory() const;

    double getAmount() const;

    const time_t &getTimestamp() const;
};