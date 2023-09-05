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

    // ����� ��� ������ ���� �� �����
    vector<string> readWordsFromFile(const string &filename);

    // ����� ��� ������ ���������� ����� �� ������
    string chooseRandomWord(const vector<string> &words);

    // ����� ��� ��������, ������� �� ����� ���������
    bool isWordGuessed(const string &word, const vector<char> &guessedLetters);

    // ����� ��� ����������� ��������� ���� � �����
    void displayWord(const string &word, const vector<char> &guessedLetters);

    // ����� ��� ��������� �������������� ����� �� ������
    char getGuess();

    // ����� ��� �������� ���������������� �������������� �����
    bool isGuessValid(char guess, const vector<char> &guessedLetters);

    // ����� ��� ����������� ���������� ����
    void displayGameStatistics(const string &wordToGuess, const vector<char> &guessedLetters, int attempts, double timeElapsed);
public:
    // ����������� ������, ��������� ��� ����� �� �������
    HangmanGame(const string &wordListFileName) : wordListFileName(wordListFileName) {
        words = readWordsFromFile(wordListFileName); // ������ ���� �� �����
        if (words.empty()) {
            cerr << "Error: Unable to load word list from file " << wordListFileName << endl;
            exit(1);
        }
    }

    // ����� ��� ������� ����
    void play();
};