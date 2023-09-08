#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <ctime>
#include <map>
#include <algorithm>
#include "Transaction.h"
#include "Wallet.h"
#include "FinanceManager.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "ru");
    FinanceManager manager;

    // Запускаем меню
    manager.run();

    return 0;
}
