#include <iostream>
#include "HangMan.h"

using namespace std;

int main() {
    HangmanGame game("words.txt");
    game.play();

    return 0;
}
