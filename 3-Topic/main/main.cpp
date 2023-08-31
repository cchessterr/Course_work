#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <chrono>
#include <string>

using namespace std;

// Функция для чтения и дешифрования слов из файла
vector<string> readWordsFromFile(const string &filename) {
    ifstream file(filename);
    vector<string> words;

    if (file.is_open()) {
        string encryptedWord;
        while (getline(file, encryptedWord)) {
            string word = "";  // Переменная для расшифрованного слова
            for (char c : encryptedWord) {
                word += c - 1;  // Дешифруем символ и добавляем в расшифрованное слово
            }
            words.push_back(word);
        }
        file.close();
    }
    else {
        cout << "Unable to open file " << filename << endl;
    }

    return words;
}

// Функция для выбора случайного слова из списка
string chooseRandomWord(const vector<string> &words) {
    srand(static_cast<unsigned int>(time(nullptr)));
    int randomIndex = rand() % words.size();
    return words[randomIndex];
}

// Функция для проверки, угадано ли слово полностью
bool isWordGuessed(const string &word, const vector<char> &guessedLetters) {
    for (char letter : word) {
        if (find(guessedLetters.begin(), guessedLetters.end(), letter) == guessedLetters.end()) {
            return false;
        }
    }
    return true;
}

int main() {
    // Чтение слов из файла
    vector<string> words = readWordsFromFile("words.txt");
    if (words.empty()) {
        return 1;
    }

    // Выбор случайного слова для угадывания
    string wordToGuess = chooseRandomWord(words);
    int attempts = 6;
    vector<char> guessedLetters;

    cout << "Welcome to Hangman!" << endl;

    // Начало отсчета времени
    auto startTime = chrono::high_resolution_clock::now();

    while (attempts > 0) {
        cout << "Word: ";
        // Отображение угаданных букв в слове
        for (char letter : wordToGuess) {
            if (find(guessedLetters.begin(), guessedLetters.end(), letter) != guessedLetters.end()) {
                cout << letter;
            }
            else {
                cout << "_";
            }
        }
        cout << endl;

        // Проверка, угадано ли слово полностью
        if (isWordGuessed(wordToGuess, guessedLetters)) {
            cout << "Congratulations! You've guessed the word: " << wordToGuess << endl;
            break;
        }

        cout << "Attempts left: " << attempts << endl;
        cout << "Guess a letter: ";
        char guess;
        cin >> guess;

        // Проверка угаданной буквы и уменьшение количества попыток
        if (find(guessedLetters.begin(), guessedLetters.end(), guess) == guessedLetters.end()) {
            guessedLetters.push_back(guess);
            if (wordToGuess.find(guess) == string::npos) {
                cout << "Incorrect guess!" << endl;
                attempts--;
            }
        }
        else {
            cout << "You've already guessed that letter." << endl;
        }
    }

    // Окончание отсчета времени
    auto endTime = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = endTime - startTime;

    // Вывод статистики игры
    cout << "Game statistics:" << endl;
    cout << "Time taken: " << elapsed.count() << " seconds" << endl;
    cout << "Attempts made: " << 6 - attempts << endl;
    cout << "Word to guess: " << wordToGuess << endl;
    cout << "Letters guessed: ";
    for (char letter : guessedLetters) {
        cout << letter << " ";
    }
    cout << endl;

    // Вывод сообщения при неудачной игре
    if (attempts == 0) {
        cout << "You've run out of attempts. The word was: " << wordToGuess << endl;
    }

    return 0;
}
