#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <ctime>

class Game
{
private:

	//variables
	std::string wordToBeGuessed;
	int numberOfTries;
	std::string guessedString;
	bool playerWin;
	bool playing;
	bool gameOver;

	//private function ni siya
	std::string loadRandomWord(std::string fileName);
	void initVars();
	void setUp();
	
public:

	//constructor and destructor
	Game();
	virtual ~Game();

	
	//accessors
	const bool running() const;

	//functions
	void drawGame();
	void printGameMessage(std::string message, bool printTop = true, bool printBottom = true);
	void drawHangMan(int numberOfTries);
	void printLetters(std::string guessedString, char from, char to);
	void printValidLetters(std::string guessedString);
	void printWord(std::string wordtoBeGuessed, std::string guessedString);
	int updateTries(std::string wordtoBeGuessed, std::string guessedString);
	void checkWin();
	void getInput();
	void getResponse();


	// updator and renderer
	void update();
	void render();

};

