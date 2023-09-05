#include "HangMan.h"

void HangmanGame::play()
{
    // Выбираем случайное слово для угадывания
    string wordToGuess = chooseRandomWord(words);
    int attempts = 6; // Количество попыток
    vector<char> guessedLetters; // Буквы, которые уже были угаданы

    cout << "Welcome to Hangman!" << endl;

    auto startTime = chrono::high_resolution_clock::now(); // Начало отсчета времени

    while (attempts > 0) {
        displayWord(wordToGuess, guessedLetters); // Отображаем текущее состояние слова с угаданными буквами
        if (isWordGuessed(wordToGuess, guessedLetters)) { // Проверяем, угадано ли слово полностью
            cout << "Congratulations! You've guessed the word: " << wordToGuess << endl;
            break;
        }

        cout << "Attempts left: " << attempts << endl;
        char guess = getGuess(); // Получаем букву, предполагаемую игроком
        if (isGuessValid(guess, guessedLetters)) { // Проверяем действительность предполагаемой буквы
            guessedLetters.push_back(guess); // Добавляем угаданную букву в список
            if (wordToGuess.find(guess) == string::npos) { // Проверяем, есть ли буква в слове
                cout << "Incorrect guess!" << endl;
                attempts--;
            }
        }
        else {
            cout << "You've already guessed that letter." << endl;
        }
    }

    auto endTime = chrono::high_resolution_clock::now(); // Окончание отсчета времени
    chrono::duration<double> elapsed = endTime - startTime;

    displayGameStatistics(wordToGuess, guessedLetters, attempts, elapsed.count()); // Вывод статистики игры
}

vector<string> HangmanGame::readWordsFromFile(const string &filename)
{
    ifstream file(filename); // Открытие файла
    vector<string> words;

    if (file.is_open()) { // Проверка успешного открытия файла
        string word;
        while (getline(file, word)) { // Чтение слов из файла
            words.push_back(word);
        }
        file.close(); // Закрытие файла
    }
    else {
        cerr << "Error: Unable to open file " << filename << endl; // Вывод ошибки, если файл не открывается
    }

    return words;
}

string HangmanGame::chooseRandomWord(const vector<string> &words)
{
    srand(static_cast<unsigned int>(time(nullptr))); // Инициализация генератора случайных чисел
    int randomIndex = rand() % words.size(); // Генерация случайного индекса
    return words[randomIndex]; // Возврат случайного слова
}

bool HangmanGame::isWordGuessed(const string &word, const vector<char> &guessedLetters)
{
    for (char letter : word) {
        if (find(guessedLetters.begin(), guessedLetters.end(), letter) == guessedLetters.end()) {
            return false;
        }
    }
    return true;
}

void HangmanGame::displayWord(const string &word, const vector<char> &guessedLetters)
{
    cout << "Word: ";
    for (char letter : word) {
        if (find(guessedLetters.begin(), guessedLetters.end(), letter) != guessedLetters.end()) {
            cout << letter;
        }
        else {
            cout << "_";
        }
    }
    cout << endl;
}

char HangmanGame::getGuess()
{
    cout << "Guess a letter: ";
    char guess;
    cin >> guess;
    return guess;
}

bool HangmanGame::isGuessValid(char guess, const vector<char> &guessedLetters)
{
    return find(guessedLetters.begin(), guessedLetters.end(), guess) == guessedLetters.end();
}

void HangmanGame::displayGameStatistics(const string &wordToGuess, const vector<char> &guessedLetters, int attempts, double timeElapsed)
{
    cout << "\nGame statistics:" << endl;
    cout << "\tTime taken: " << timeElapsed << " seconds" << endl;
    cout << "\tAttempts made: " << 6 - attempts << endl;
    cout << "\tWord to guess: " << wordToGuess << endl;
    cout << "\tLetters guessed: ";
    for (char letter : guessedLetters) {
        cout << letter << " ";
    }
    cout << endl;

    if (attempts == 0) {
        cout << "You've run out of attempts. The word was: " << wordToGuess << endl;
    }
}