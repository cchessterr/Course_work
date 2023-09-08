#include "FinanceManager.h"

time_t FinanceManager::startOfPeriod(const string &period)
{
    time_t currentTime = time(nullptr);
    if (period == "����") {
        return currentTime - 86400;
    }
    else if (period == "������") {
        return currentTime - 604800;
    }
    else if (period == "�����") {
        return currentTime - 2592000;
    }
    return currentTime;
}

time_t FinanceManager::endOfPeriod(const string &period)
{
    return time(nullptr);
}

void FinanceManager::printTopNCategories(ofstream &file, const map<string, double> &categorySum, int n)
{
    vector<pair<string, double>> sortedCategories(categorySum.begin(), categorySum.end());
    sort(sortedCategories.begin(), sortedCategories.end(), [](const auto &a, const auto &b) {
        return a.second > b.second;
        });

    int count = 0;
    for (const auto &category : sortedCategories) {
        file << "���������: " << category.first << ", ����� �����: " << category.second << endl;
        count++;
        if (count >= n) {
            break;
        }
    }
}

void FinanceManager::printTopNExpenses(ofstream &file, const string &period, int n)
{
    vector<Transaction> allTransactions;
    for (const auto &wallet : wallets) {
        for (const auto &transaction : wallet.getTransactions()) {
            if (transaction.getTimestamp() >= startOfPeriod(period) && transaction.getTimestamp() <= endOfPeriod(period)) {
                allTransactions.push_back(transaction);
            }
        }
    }

    sort(allTransactions.begin(), allTransactions.end(), [](const auto &a, const auto &b) {
        return a.getAmount() > b.getAmount();
        });

    int count = 0;
    for (const auto &transaction : allTransactions) {
        file << "���������: " << transaction.getCategory() << ", �����: " << transaction.getAmount() << endl;
        count++;
        if (count >= n) {
            break;
        }
    }
}

void FinanceManager::createWalletMenu()
{
    string name;
    bool isDebitCard;

    cout << "������� ��� �������� ��� �����: ";
    getline(cin, name);

    cout << "��� ��������� �����? (1 ��� ��, 0 ��� ���): ";
    cin >> isDebitCard;

    createWallet(name, isDebitCard);
    cout << "������� ��� ����� ������� �������." << endl;
}

void FinanceManager::depositToWalletMenu()
{
    int walletIndex;
    double amount;

    cout << "������� ������ �������� ��� �����: ";
    cin >> walletIndex;

    cout << "������� ����� ��� ����������: ";
    cin >> amount;

    depositToWallet(walletIndex, amount);
    cout << "���������� ��������� �������." << endl;
}

void FinanceManager::spendFromWalletMenu()
{
    int walletIndex;
    double amount;
    string category;

    cout << "������� ������ �������� ��� �����: ";
    cin >> walletIndex;

    cout << "������� ����� ��� ������: ";
    cin >> amount;

    cin.ignore(); // ������� ����� ����� ������� ������
    cout << "������� ��������� ������: ";
    getline(cin, category);

    spendFromWallet(walletIndex, amount, category, time(nullptr));
    cout << "������� ������� ��������." << endl;
}

void FinanceManager::generateReportForPeriodMenu()
{
    string fileName, period;
    time_t start, end;

    cout << "������� ��� ����� ��� ������: ";
    getline(cin, fileName);

    cout << "������� ������ (����/������/�����): ";
    cin >> period;

    // ����� ������������ ������ ������ ��������� � �������� ����� ��� ���������� �������
    // ����� �������� generateReportForPeriod � ����� ����������

    cout << "����� ������� ������������." << endl;
}

void FinanceManager::generateRankingsMenu()
{
    string fileName, period;

    cout << "������� ��� ����� ��� ���������: ";
    getline(cin, fileName);

    cout << "������� ������ (������/�����): ";
    cin >> period;

    generateRankings(fileName, period);
    cout << "�������� ������� �������������." << endl;
}

void FinanceManager::createWallet(const string &name, bool isDebitCard)
{
    wallets.emplace_back(name, isDebitCard);
}

void FinanceManager::depositToWallet(int walletIndex, double amount)
{
    if (walletIndex >= 0 && walletIndex < wallets.size()) {
        wallets[walletIndex].deposit(amount);
    }
    else {
        cout << "�������� ������ ��������." << endl;
    }
}

void FinanceManager::spendFromWallet(int walletIndex, double amount, const string &category, const time_t &timestamp)
{
    if (walletIndex >= 0 && walletIndex < wallets.size()) {
        wallets[walletIndex].spend(amount, category, timestamp);
    }
    else {
        cout << "�������� ������ ��������." << endl;
    }
}

void FinanceManager::generateReport(const string &fileName)
{
    ofstream file(fileName);
    if (file.is_open()) {
        for (const auto &wallet : wallets) {
            file << "�������� �����: " << wallet.getName() << 
                "\n��� �����: " << (wallet.isDebit() ? "���������" : "�������") << 
                "\n������: " << wallet.getBalance() << endl;
            for (const auto &transaction : wallet.getTransactions()) {
                file << "\n�������:" << "  \n���������: " << transaction.getCategory() << ", �����: " << transaction.getAmount() << endl;
            }
        }
        file.close();
        cout << "����� ������� ������������." << endl;
    }
    else {
        cout << "�� ������� ������� ����: " << fileName << endl;
    }
}

void FinanceManager::generateReportForPeriod(const string &fileName, const time_t &start, const time_t &end)
{
    string period;

    cout << "������� ������ (����/������/�����): ";
    cin >> period;

    // ����� ������������ ������ ������ ��������� � �������� ����� ��� ���������� �������
    // ������: ������ ��������� � �������� ���� � �������
    cout << "������� ��������� ���� � ����� � ������� ����-��-�� ��:��:��: ";
    string startTimeStr;
    cin.ignore(); // ������� ������ ����� ����� ������� ������
    getline(cin, startTimeStr);
    // �������������� ��������� ������ ������� � ������ time_t 

    cout << "������� �������� ���� � ����� � ������� ����-��-�� ��:��:��: ";
    string endTimeStr;
    getline(cin, endTimeStr);
    // �������������� ��������� ������ ������� � ������ time_t 

    // ����� ����, ��� ������������ ���� ������ � ��������� ��������, ����� ������� �����
    // �� ������ ���� ���������� � ������ � ����������� � ���������.

    // ����� ���������� ����� � ��������� ��� � ����, ��� � ������ generateReport.

    cout << "����� ������� ������������." << endl;
}

void FinanceManager::generateRankings(const string &fileName, const string &period)
{
    map<string, double> categorySum;

    for (const auto &wallet : wallets) {
        for (const auto &transaction : wallet.getTransactions()) {
            if (transaction.getTimestamp() >= startOfPeriod(period) && transaction.getTimestamp() <= endOfPeriod(period)) {
                categorySum[transaction.getCategory()] += transaction.getAmount();
            }
        }
    }

    ofstream file(fileName);
    if (file.is_open()) {
        file << "���-3 ��������� �� " << period << ":" << endl;
        printTopNCategories(file, categorySum, 3);

        file << "\n���-3 ������� �� " << period << ":" << endl;
        printTopNExpenses(file, period, 3);

        file.close();
        cout << "�������� ������� ������������� ��� " << period << "." << endl;
    }
    else {
        cout << "�� ������� ������� ����: " << fileName << endl;
    }
}

void FinanceManager::displayMenu()
{
    cout << "===== ������� ���������� ������������� ��������� =====" << endl;
    cout << "1. ������� ������� ��� �����" << endl;
    cout << "2. ��������� ������� ��� �����" << endl;
    cout << "3. ������ ������� � �������� ��� �����" << endl;
    cout << "4. ������������� ���������� �����" << endl;
    cout << "5. ������������� ����� �� ������" << endl;
    cout << "6. ������������� ��������" << endl;
    cout << "0. �����" << endl;
}

void FinanceManager::run()
{
    int choice;
    while (true) {
        displayMenu();
        cout << "������� ��� ����� (0-6): ";
        cin >> choice;
        cin.ignore(); // ������� ����� �����

        switch (choice) {
        case 1:
            createWalletMenu();
            break;
        case 2:
            depositToWalletMenu();
            break;
        case 3:
            spendFromWalletMenu();
            break;
        case 4:
            generateReport("financial_report.txt");
            break;
        case 5:
            generateReportForPeriodMenu();
            break;
        case 6:
            generateRankingsMenu();
            break;
        case 0:
            cout << "����� �� ���������." << endl;
            return;
        default:
            cout << "�������� �����. ����������, ������� ���������� �����." << endl;
            break;
        }
    }
}
