#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <chrono>
#include <string>

using namespace std;

class HangmanGame {
private:
    string wordListFileName;
    vector<string> words;

    // Метод для чтения слов из файла
    vector<string> readWordsFromFile(const string &filename);

    // Метод для выбора случайного слова из списка
    string chooseRandomWord(const vector<string> &words);

    // Метод для проверки, угадано ли слово полностью
    bool isWordGuessed(const string &word, const vector<char> &guessedLetters);

    // Метод для отображения угаданных букв в слове
    void displayWord(const string &word, const vector<char> &guessedLetters);

    // Метод для получения предполагаемой буквы от игрока
    char getGuess();

    // Метод для проверки действительности предполагаемой буквы
    bool isGuessValid(char guess, const vector<char> &guessedLetters);

    // Метод для отображения статистики игры
    void displayGameStatistics(const string &wordToGuess, const vector<char> &guessedLetters, int attempts, double timeElapsed);
public:
    // Конструктор класса, принимает имя файла со словами
    HangmanGame(const string &wordListFileName) : wordListFileName(wordListFileName) {
        words = readWordsFromFile(wordListFileName); // Чтение слов из файла
        if (words.empty()) {
            cerr << "Error: Unable to load word list from file " << wordListFileName << endl;
            exit(1);
        }
    }

    // Метод для запуска игры
    void play();
};