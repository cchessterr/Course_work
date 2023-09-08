#pragma once
#include "Wallet.h"

// Определение класса FinanceManager для управления финансами
class FinanceManager {
private:
    vector<Wallet> wallets; // Вектор для хранения кошельков и карт

    // Функция для определения начала периода
    time_t startOfPeriod(const string &period);

    // Функция для определения конца периода 
    time_t endOfPeriod(const string &period);

    // Функция для вывода топ-N категорий с наибольшей суммой транзакций
    void printTopNCategories(ofstream &file, const map<string, double> &categorySum, int n);

    // Функция для вывода топ-N транзакций с наибольшей суммой
    void printTopNExpenses(ofstream &file, const string &period, int n);

    // Функция для создания кошелька или карты через меню
    void createWalletMenu();

    // Функция для пополнения кошелька или карты через меню
    void depositToWalletMenu();

    // Функция для внесения затрат с кошелька или карты через меню
    void spendFromWalletMenu();

    // Функция для генерации отчета за период через меню
    void generateReportForPeriodMenu();

    // Функция для генерации рейтингов через меню
    void generateRankingsMenu();
public:
    FinanceManager() {}

    // Функция для создания нового кошелька или карты
    void createWallet(const string &name, bool isDebitCard = false);

    // Функция для пополнения баланса кошелька или карты по индексу
    void depositToWallet(int walletIndex, double amount);

    // Функция для списания средств с кошелька или карты по индексу с указанием суммы, категории и времени
    void spendFromWallet(int walletIndex, double amount, const string &category, const time_t &timestamp);

    // Функция для генерации финансового отчета и сохранения его в файл
    void generateReport(const string &fileName);

    // Функция для генерации отчета за указанный период
    void generateReportForPeriod(const string &fileName, const time_t &start, const time_t &end);

    // Функция для генерации рейтингов по максимальным суммам
    void generateRankings(const string &fileName, const string &period);

    // Функция для отображения главного меню
    void displayMenu();

    // Функция для запуска основной логики программы
    void run();
};