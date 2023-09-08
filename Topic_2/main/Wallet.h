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

// ����������� ������ Wallet ��� ������������� ��������� � ����
class Wallet {
private:
    string name;            // �������� �������� ��� �����
    bool isDebitCard;       // ����, �����������, �������� �� ����� ���������
    double balance;         // ������ �������� ��� �����
    vector<Transaction> transactions; // ������ ����������

public:
    // ����������� ������ Wallet ��� ������������� ������� �������� ��� �����
    Wallet(const string &name, bool isDebitCard = false)
        : name(name), isDebitCard(isDebitCard), balance(0.0) {}

    // ������ ������� � ����� ������ Wallet
    const string &getName() const;

    bool isDebit() const;

    double getBalance() const;

    const vector<Transaction> &getTransactions() const;

    // ����� ��� ���������� ������� �������� ��� �����
    void deposit(double amount);

    // ����� ��� �������� ������� � �������� ��� ����� � ��������� �����, ��������� � �������
    void spend(double amount, const string &category, const time_t &timestamp);      
};
