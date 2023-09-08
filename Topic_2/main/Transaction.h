#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <ctime>
#include <map>
#include <algorithm>

using namespace std;

// ����������� ������ Transaction ��� ������������� ����������
class Transaction {
private:
    string category;    // ��������� ����������
    double amount;      // ����� ����������
    time_t timestamp;   // ��������� ����� ����������

public:
    // ����������� ������ Transaction ��� ������������� ������� ����������
    Transaction(const string &category, double amount, const time_t &timestamp)
        : category(category), amount(amount), timestamp(timestamp) {}

    // ������ ������� � ����� ������ Transaction
    const string &getCategory() const;

    double getAmount() const;

    const time_t &getTimestamp() const;
};