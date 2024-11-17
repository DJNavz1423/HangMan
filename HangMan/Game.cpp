#include "Game.h"

std::string Game::loadRandomWord(std::string fileName)
{
	std::string randomWord;
	std::vector<std::string> wordList;
	std::ifstream reader(fileName);

	if (reader.is_open()) {
		while (std::getline(reader, randomWord)) wordList.push_back(randomWord);

		int randomLine = rand() % wordList.size(); // random word
		randomWord = wordList.at(randomLine);
		reader.close();
	}
	return randomWord;
}

// initialize variables
void Game::initVars()
{
	this->wordToBeGuessed = this->loadRandomWord("words.txt");
	this->numberOfTries = -1;
	this->playerWin = false;
	this->guessedString = "";
	this->playing = true;
	this->gameOver = false;
}


//setup the game
void Game::setUp()
{
	this->initVars();
}


// draw the entire game
void Game::drawGame()
{
	system("cls");
	this->printGameMessage("HANGMAN");
	this->drawHangMan(this->numberOfTries);
	this->printValidLetters(this->guessedString);
	this->printGameMessage("Guess The Word");
	this->printWord(this->wordToBeGuessed, this->guessedString);

	if (this->gameOver || this->playerWin) {
		if(this->gameOver) this->printGameMessage(("The Word Is " + this->wordToBeGuessed));

		std::cout << "> (Y) to continue | (Q) to quit : ";

		this->getResponse();
		return;
	}

	std::cout << ">";
}

// prints the game parts
void Game::printGameMessage(std::string message, bool printTop, bool printBottom)
{
	if (printTop) std::cout << "+---------------------------------+\n|";

	else std::cout << "|";

	bool front = true;

	for (int index = message.length(); index < 33; index++) {
		if (front) message = " " + message;

		else message = message + " ";

		front = !front;
	}
	std::cout << message.c_str();

	if (printBottom) std::cout << "|\n+---------------------------------+\n";

	else std::cout << "|\n";
}

// draw the hangman portion
void Game::drawHangMan(int numberOfTries)
{
	if (numberOfTries >= 1) this->printGameMessage("|", false, false);
	else this->printGameMessage("", false, false);

	if (numberOfTries >= 2) this->printGameMessage("|", false, false);
	else this->printGameMessage("", false, false);

	if (numberOfTries >= 3) this->printGameMessage("O", false, false);
	else this->printGameMessage("", false, false);

	if (numberOfTries == 4) this->printGameMessage("/", false, false);
	if (numberOfTries == 5) this->printGameMessage("/|", false, false);
	if (numberOfTries >= 6) this->printGameMessage("/|\\", false, false);

	if (numberOfTries >= 7) this->printGameMessage("|", false, false);

	if (numberOfTries == 8) this->printGameMessage("/", false, false);

	if (numberOfTries >= 9) this->printGameMessage("/ \\", false, false);

	if (this->playerWin == true) {
		this->printGameMessage("", false, false);
		this->printGameMessage("+---------+", false, false);
		this->printGameMessage("| S A F E |", false, false);
		this->printGameMessage("+---------+", false, false);
		this->printGameMessage("", false, false);
		this->printGameMessage("YOU WIN!", false, false);
		this->printGameMessage("+---------+", false, false);
		return;
	}

	if (numberOfTries >= 10) {
		this->printGameMessage("", false, false);
		this->printGameMessage("+---------+", false, false);
		this->printGameMessage("| D E A D |", false, false);
		this->printGameMessage("+---------+", false, false);
		this->printGameMessage("", false, false);
		this->printGameMessage("YOU LOSE!", false, false);
		this->printGameMessage("+---------+", false, false);
		return;
	}

	if (numberOfTries == 9) {
		this->printGameMessage("", false, false);
		this->printGameMessage("HELP ME!", false, false);
		this->printGameMessage("+---------+", false, false);
	}
}


// print alphabet letters
void Game::printLetters(std::string guessedString, char from, char to)
{
	std::string strToPrint;

	for (char index = from; index <= to; index++) {
		if (guessedString.find(index) == std::string::npos) {
			strToPrint += index;
			strToPrint += " ";
		}

		else strToPrint += " ";
	}
	this->printGameMessage(strToPrint, false, false);
}

void Game::printValidLetters(std::string guessedString)
{
	this->printGameMessage("AVAILABLE LETTERS");
	this->printLetters(guessedString, 'A', 'M');
	this->printLetters(guessedString, 'N', 'Z');
}

// get player input
void Game::getInput()
{
	char input = '\0';

	if (this->numberOfTries >= 0) {
		std::cin >> input;

		input = toupper(input);

		if (this->guessedString.find(input) == std::string::npos)
			this->guessedString += input;
	}
}


// get player response
void Game::getResponse()
{
	char response = '\0';

	std::cin >> response;

	response = toupper(response);

	if (response == 'Q') this->playing = false; // end game

	else if (response == 'Y') this->setUp(); // reset game
}

//print the word
void Game::printWord(std::string wordtoBeGuessed, std::string guessedString)
{
	std::string strToPrint;

	for (int index = 0; index < wordToBeGuessed.length(); index++) {
		if (guessedString.find(wordToBeGuessed[index]) == std::string::npos) {
			strToPrint += "_ ";
		}

		else {
			strToPrint += wordToBeGuessed[index];
			strToPrint += " ";
		}
	}
	this->printGameMessage(strToPrint);
}


//check if player won
void Game::checkWin()
{
	this->playerWin = true;
	
	for (char c : this->wordToBeGuessed)
		if (this->guessedString.find(c) == std::string::npos) {
			this->playerWin = false;
			break;
		}
}

// count the number of tries
int Game::updateTries(std::string wordtoBeGuessed, std::string guessedString)
{
	int incorrectTries = 0;

	for (int index = 0; index < guessedString.length(); index++)
		if (wordtoBeGuessed.find(guessedString[index]) == std::string::npos)
			incorrectTries++;

	return incorrectTries;
}


// constructor 
Game::Game()
{
	this->setUp();
}

//destructor
Game::~Game()
{
	//empty for now ... gamita lng kung naa kay i destroy na resource
}


//accessors
const bool Game::running() const
{
	return this->playing;
}


// game updator and renderer

void Game::update()
{
	if (!this->gameOver) {
		this->getInput();
		this->numberOfTries = this->updateTries(this->wordToBeGuessed, this->guessedString);
		this->checkWin();
	}

	if (this->numberOfTries >= 10)
		this->gameOver = true;
}

void Game::render()
{
	this->drawGame();
}
