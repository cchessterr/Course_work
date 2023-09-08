#pragma once
#include "Wallet.h"

// ����������� ������ FinanceManager ��� ���������� ���������
class FinanceManager {
private:
    vector<Wallet> wallets; // ������ ��� �������� ��������� � ����

    // ������� ��� ����������� ������ �������
    time_t startOfPeriod(const string &period);

    // ������� ��� ����������� ����� ������� 
    time_t endOfPeriod(const string &period);

    // ������� ��� ������ ���-N ��������� � ���������� ������ ����������
    void printTopNCategories(ofstream &file, const map<string, double> &categorySum, int n);

    // ������� ��� ������ ���-N ���������� � ���������� ������
    void printTopNExpenses(ofstream &file, const string &period, int n);

    // ������� ��� �������� �������� ��� ����� ����� ����
    void createWalletMenu();

    // ������� ��� ���������� �������� ��� ����� ����� ����
    void depositToWalletMenu();

    // ������� ��� �������� ������ � �������� ��� ����� ����� ����
    void spendFromWalletMenu();

    // ������� ��� ��������� ������ �� ������ ����� ����
    void generateReportForPeriodMenu();

    // ������� ��� ��������� ��������� ����� ����
    void generateRankingsMenu();
public:
    FinanceManager() {}

    // ������� ��� �������� ������ �������� ��� �����
    void createWallet(const string &name, bool isDebitCard = false);

    // ������� ��� ���������� ������� �������� ��� ����� �� �������
    void depositToWallet(int walletIndex, double amount);

    // ������� ��� �������� ������� � �������� ��� ����� �� ������� � ��������� �����, ��������� � �������
    void spendFromWallet(int walletIndex, double amount, const string &category, const time_t &timestamp);

    // ������� ��� ��������� ����������� ������ � ���������� ��� � ����
    void generateReport(const string &fileName);

    // ������� ��� ��������� ������ �� ��������� ������
    void generateReportForPeriod(const string &fileName, const time_t &start, const time_t &end);

    // ������� ��� ��������� ��������� �� ������������ ������
    void generateRankings(const string &fileName, const string &period);

    // ������� ��� ����������� �������� ����
    void displayMenu();

    // ������� ��� ������� �������� ������ ���������
    void run();
};