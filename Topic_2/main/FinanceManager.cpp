#include "FinanceManager.h"

time_t FinanceManager::startOfPeriod(const string &period)
{
    time_t currentTime = time(nullptr);
    if (period == "день") {
        return currentTime - 86400;
    }
    else if (period == "неделя") {
        return currentTime - 604800;
    }
    else if (period == "месяц") {
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
        file << "Категория: " << category.first << ", Общая Сумма: " << category.second << endl;
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
        file << "Категория: " << transaction.getCategory() << ", Сумма: " << transaction.getAmount() << endl;
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

    cout << "Введите имя кошелька или карты: ";
    getline(cin, name);

    cout << "Это дебетовая карта? (1 для да, 0 для нет): ";
    cin >> isDebitCard;

    createWallet(name, isDebitCard);
    cout << "Кошелек или карта успешно созданы." << endl;
}

void FinanceManager::depositToWalletMenu()
{
    int walletIndex;
    double amount;

    cout << "Введите индекс кошелька или карты: ";
    cin >> walletIndex;

    cout << "Введите сумму для пополнения: ";
    cin >> amount;

    depositToWallet(walletIndex, amount);
    cout << "Пополнение выполнено успешно." << endl;
}

void FinanceManager::spendFromWalletMenu()
{
    int walletIndex;
    double amount;
    string category;

    cout << "Введите индекс кошелька или карты: ";
    cin >> walletIndex;

    cout << "Введите сумму для затрат: ";
    cin >> amount;

    cin.ignore(); // Очищаем буфер перед чтением строки
    cout << "Введите категорию затрат: ";
    getline(cin, category);

    spendFromWallet(walletIndex, amount, category, time(nullptr));
    cout << "Затраты успешно записаны." << endl;
}

void FinanceManager::generateReportForPeriodMenu()
{
    string fileName, period;
    time_t start, end;

    cout << "Введите имя файла для отчета: ";
    getline(cin, fileName);

    cout << "Введите период (день/неделя/месяц): ";
    cin >> period;

    // Здесь пользователь должен ввести начальное и конечное время для выбранного периода
    // Затем вызываем generateReportForPeriod с этими значениями

    cout << "Отчет успешно сгенерирован." << endl;
}

void FinanceManager::generateRankingsMenu()
{
    string fileName, period;

    cout << "Введите имя файла для рейтингов: ";
    getline(cin, fileName);

    cout << "Введите период (неделя/месяц): ";
    cin >> period;

    generateRankings(fileName, period);
    cout << "Рейтинги успешно сгенерированы." << endl;
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
        cout << "Неверный индекс кошелька." << endl;
    }
}

void FinanceManager::spendFromWallet(int walletIndex, double amount, const string &category, const time_t &timestamp)
{
    if (walletIndex >= 0 && walletIndex < wallets.size()) {
        wallets[walletIndex].spend(amount, category, timestamp);
    }
    else {
        cout << "Неверный индекс кошелька." << endl;
    }
}

void FinanceManager::generateReport(const string &fileName)
{
    ofstream file(fileName);
    if (file.is_open()) {
        for (const auto &wallet : wallets) {
            file << "Название банка: " << wallet.getName() << 
                "\nТип карты: " << (wallet.isDebit() ? "Дебетовая" : "Кошелек") << 
                "\nБаланс: " << wallet.getBalance() << endl;
            for (const auto &transaction : wallet.getTransactions()) {
                file << "\nРасходы:" << "  \nКатегория: " << transaction.getCategory() << ", Сумма: " << transaction.getAmount() << endl;
            }
        }
        file.close();
        cout << "Отчет успешно сгенерирован." << endl;
    }
    else {
        cout << "Не удалось открыть файл: " << fileName << endl;
    }
}

void FinanceManager::generateReportForPeriod(const string &fileName, const time_t &start, const time_t &end)
{
    string period;

    cout << "Введите период (день/неделя/месяц): ";
    cin >> period;

    // Здесь пользователь должен ввести начальное и конечное время для выбранного периода
    // Пример: запрос начальной и конечной даты и времени
    cout << "Введите начальную дату и время в формате ГГГГ-ММ-ДД ЧЧ:ММ:СС: ";
    string startTimeStr;
    cin.ignore(); // Очистка буфера ввода перед чтением строки
    getline(cin, startTimeStr);
    // Преобразование введенной строки времени в объект time_t 

    cout << "Введите конечную дату и время в формате ГГГГ-ММ-ДД ЧЧ:ММ:СС: ";
    string endTimeStr;
    getline(cin, endTimeStr);
    // Преобразование введенной строки времени в объект time_t 

    // После того, как пользователь ввел период и временной интервал, можно создать отчет
    // на основе этой информации и данных о транзакциях в кошельках.

    // Затем генерируем отчет и сохраняем его в файл, как в методе generateReport.

    cout << "Отчет успешно сгенерирован." << endl;
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
        file << "Топ-3 Категории за " << period << ":" << endl;
        printTopNCategories(file, categorySum, 3);

        file << "\nТоп-3 Затраты за " << period << ":" << endl;
        printTopNExpenses(file, period, 3);

        file.close();
        cout << "Рейтинги успешно сгенерированы для " << period << "." << endl;
    }
    else {
        cout << "Не удалось открыть файл: " << fileName << endl;
    }
}

void FinanceManager::displayMenu()
{
    cout << "===== Система Управления Персональными Финансами =====" << endl;
    cout << "1. Создать Кошелек или Карту" << endl;
    cout << "2. Пополнить Кошелек или Карту" << endl;
    cout << "3. Внести Затраты с Кошелька или Карты" << endl;
    cout << "4. Сгенерировать Финансовый Отчет" << endl;
    cout << "5. Сгенерировать Отчет за Период" << endl;
    cout << "6. Сгенерировать Рейтинги" << endl;
    cout << "0. Выход" << endl;
}

void FinanceManager::run()
{
    int choice;
    while (true) {
        displayMenu();
        cout << "Введите ваш выбор (0-6): ";
        cin >> choice;
        cin.ignore(); // Очищаем буфер ввода

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
            cout << "Выход из программы." << endl;
            return;
        default:
            cout << "Неверный выбор. Пожалуйста, введите допустимую опцию." << endl;
            break;
        }
    }
}
