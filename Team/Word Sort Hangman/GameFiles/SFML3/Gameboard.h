#pragma once
#include "Objects.h"
#include <SFML/Graphics.hpp>
#include "Sorting.h"
#include "Game.h"
#include "FrequencyCalculator.h"
#include "TextureManager.h"
#include <iostream>
using namespace std;
class Gameboard
{
	Objects startButton;
	vector<Objects> menuObjects;
	vector<Objects> playingObjects;
	vector<Objects> cowObjects;
	vector<Objects> kbObjects;
	vector<Objects> banners;
	vector<Objects> sorts;
	vector<Objects> guessing_word_even;
	vector<Objects> letters;
	vector<vector<Objects>> words;
	vector<Objects> guessing_word_odd;
	Objects hardCover;
	game hangman;
	string gameStatus;
	//sf::Event event;
	bool hardMode;
	int sortNum;
public:
	Gameboard(sf::RenderWindow& window);
	void editGameStatus(string status);
	string getGameStatus();
	void displayMenu(sf::RenderWindow& window);
	void press(sf::RenderWindow& window, Objects& obj,string buttonType);
	void play(sf::RenderWindow& window);
	void win(sf::RenderWindow& window);
	void lose(sf::RenderWindow& window);
	void displaySuggested(sf::RenderWindow& window);

	
};

