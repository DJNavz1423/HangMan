#include "Game.h"

// main
int main()
{
    srand(static_cast<unsigned int>(time(0))); // seed randomizer para random ang mo generate na word

    Game hangman{}; // instantiation ni siya bai haha

    while (hangman.running()) {

            hangman.update(); // update game 

            hangman.render(); // render game display

            if (std::cin.fail()) break;
    }
}

