#include "mine.h"
#include "TextureManagement.h"
#include <fstream>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <map>
#include <string>
#include <cmath>
using namespace std;
board::board() {
	mines = 0;
	rows = 0;
	collumns = 0;
	tileCount = 0;
	flagCount = 0;
	numRevealed = 0;
	lost = false;
	won = false;
}
board::tile::tile() {
	flagged = false;
	godMode = false;
	mine = false;
	number = 0;
	revealed = false;
	for (int i = 0; i < 8; i++) {
		neighbors[i] = nullptr;
	}
	interactableSmall = true;
}
void board::setBoard(int boardNumber) {
	ifstream config("boards/config.cfg");
	//config file - 3 lines: width, height, mine count 
	string width, height, mineCount;
	getline(config, width);
	getline(config, height);
	getline(config, mineCount);
	rows = stoi(height);
	collumns = stoi(width);
	//imported everything from the file 
	//do the arithmatic to get stuff to right values
	tileCount = rows * collumns;
	windowSize.x = collumns * 32;
	windowSize.y = (rows * 32) + 100;
	//create the vector of tiles
	for (int i = 0; i < collumns; i++) {
		game.emplace_back();
		for (int j = 0; j < rows; j++) {
			game[i].emplace_back();
			game[i][j].tileSpot.x = i;
			game[i][j].tileSpot.y = j;
			game[i][j].botLayer.setTexture(TextureManager::getTexture("hidden"));
			game[i][j].botLayer.setPosition(sf::Vector2f(game[i][j].tileSpot.x * 32.0f, game[i][j].tileSpot.y * 32.0f));
			game[i][j].interactableSmall = true;
		}
	}
	//create the mine counter vector;
	mineCounter.emplace_back();
	mineCounter.emplace_back();
	mineCounter.emplace_back();
	mineCounter.emplace_back();
	sf::Vector2f bottomCenter = sf::Vector2f(windowSize.x / 2 - 32, windowSize.y - 100);

	//set the rectangles and positon in the display fn 
	for (int i = 0; i < 4; i++) {
		mineCounter[i].setTexture(TextureManager::getTexture("digits"));
		mineCounter[i].setTextureRect(sf::IntRect(0, 0, 21, 32));
		mineCounter[i].setPosition(sf::Vector2f(53 + 21 * i, bottomCenter.y));
	}
	//do stuff for a specific board
	if (boardNumber == 0) {
		mines = stoi(mineCount);
		int ranCol, ranRow;
		for (int i = mines; i > 0; i--) {
			ranCol = Random::Number(0, collumns - 1);
			ranRow = Random::Number(0, rows - 1);
			if (game[ranCol][ranRow].mine) {
				i++;
			}
			else {
				game[ranCol][ranRow].mine = true;
			}
		}

		//create a random board 
		//random collumn, random row. Iterate n times, where n is number of bombs. Iterate again if randomly selected space is already a bomb
	}
	else if (boardNumber == 1) {
		//set board equal to the file
		ifstream theBoardInput("boards/testboard1.brd");
		string lineFromFile;
		int numberOfMines = 0;
		int i = 0;
		while (getline(theBoardInput, lineFromFile)) {
			cout << lineFromFile;
			
			for (int j = 0; j < collumns; j++) {
				char singleThing = lineFromFile.at(j);
				int numSingleThing = singleThing - 48;
				if (numSingleThing == 1) {
					game[j][i].mine = true;
					numberOfMines++;
				}
				else {
					game[j][i].mine = false;
				}
			}
			i++;
		}
		//set minecount based on mines in game
		
		mines = numberOfMines;
	}
	else if (boardNumber == 2) {
		//set board equal to the file
		ifstream theBoardInput("boards/testboard2.brd");
		string lineFromFile;
		int numberOfMines = 0;
		int i = 0;
		while (getline(theBoardInput, lineFromFile)) {
			cout << lineFromFile;

			for (int j = 0; j < collumns; j++) {
				char singleThing = lineFromFile.at(j);
				int numSingleThing = singleThing - 48;
				if (numSingleThing == 1) {
					game[j][i].mine = true;
					numberOfMines++;
				}
				else {
					game[j][i].mine = false;
				}
			}
			i++;
		}
		//set minecount based on mines in game
		mines = numberOfMines;
	}
	else if (boardNumber == 3) {
		//set board equal to the file
		ifstream theBoardInput("boards/testboard3.brd");
		string lineFromFile;
		int numberOfMines = 0;
		int i = 0;
		while (getline(theBoardInput, lineFromFile)) {
			cout << lineFromFile;

			for (int j = 0; j < collumns; j++) {
				char singleThing = lineFromFile.at(j);
				int numSingleThing = singleThing - 48;
				if (numSingleThing == 1) {
					game[j][i].mine = true;
					numberOfMines++;
				}
				else {
					game[j][i].mine = false;
				}
			}
			i++;
		}
		//set minecount based on mines in game
		mines = numberOfMines;
		cout << "bing bong";
	}
	//set neighbors 
	
	for (int i = 0; i < game.size(); i++) {
		for (int j = 0; j < game[i].size(); j++) {
			bool whichNeighbors[8];
			//set bool array to default
			for (int k = 0; k < 8; k++) {
				whichNeighbors[k] = true;
			}
			//x == 0
			if (i == 0) {
				//dont do 0 3 or 5
				whichNeighbors[0] = false;
				whichNeighbors[3] = false;
				whichNeighbors[5] = false;
			}
			//y == 0
			if (j == 0) {
				//dont do 0 1 or 2
				whichNeighbors[0] = false;
				whichNeighbors[1] = false;
				whichNeighbors[2] = false;
			}
			//x == max 
			if (i == game.size() - 1) {
				//dont do 2 4 or 7 
				whichNeighbors[2] = false;
				whichNeighbors[4] = false;
				whichNeighbors[7] = false;
			}
			//y == max
			if (j == game[i].size() - 1) {
				//dont do 5 6 or 7 
				whichNeighbors[5] = false;
				whichNeighbors[6] = false;
				whichNeighbors[7] = false;
			}
			for (int k = 0; k < 8; k++) {
				if (whichNeighbors[k]) {
					switch (k) {
					case 0:
						game[i][j].neighbors[0] = &game[i - 1][j - 1];
						break;
					case 1:
						game[i][j].neighbors[1] = &game[i][j - 1];
						break;
					case 2:
						game[i][j].neighbors[2] = &game[i + 1][j - 1];
						break;
					case 3:
						game[i][j].neighbors[3] = &game[i - 1][j];
						break;
					case 4:
						game[i][j].neighbors[4] = &game[i + 1][j];
						break;
					case 5:
						game[i][j].neighbors[5] = &game[i - 1][j + 1];
						break;
					case 6:
						game[i][j].neighbors[6] = &game[i][j + 1];
						break;
					case 7:
						game[i][j].neighbors[7] = &game[i + 1][j + 1];
						break;
					}
				}
			}

		}
	}
	//neighbors set, now numbers
	for (int i = 0; i < game.size(); i++) {
		for (int j = 0; j < game[i].size(); j++) {
			int count = 0;
			for (int k = 0; k < 8; k++) {
				if (game[i][j].neighbors[k] != nullptr) {
					if (game[i][j].neighbors[k]->mine) {
						count++;
					}
				}
			}
			game[i][j].number = count;
		}
	}
}
void board::tile::flag(int &flagCount) {
	if(interactableSmall){
		if (flagged) {
			flagged = false;
			flagCount--;
		}
		else if (!flagged) {
			if (!revealed) {
				flagged = true;
				flagCount++;
			}
		}
	}
	
}
void board::tile::print(sf::RenderWindow& window) {
	window.draw(botLayer);
	sf::Sprite temp;
	temp.setPosition(botLayer.getPosition());
	if (flagged) {
		temp.setTexture(TextureManager::getTexture("flag"));
		window.draw(temp);
	}
	if (mine && (revealed || godMode)) {
		temp.setTexture(TextureManager::getTexture("mine"));
		window.draw(temp);
	}
	else if (revealed && number != 0) {
		switch (number){
		case 1: 
			temp.setTexture(TextureManager::getTexture("1"));
			window.draw(temp);
			break;
		case 2:
			temp.setTexture(TextureManager::getTexture("2"));
			window.draw(temp);
			break;
		case 3:
			temp.setTexture(TextureManager::getTexture("3"));
			window.draw(temp);
			break;
		case 4:
			temp.setTexture(TextureManager::getTexture("4"));
			window.draw(temp);
			break;
		case 5:
			temp.setTexture(TextureManager::getTexture("5"));
			window.draw(temp);
			break;
		case 6:
			temp.setTexture(TextureManager::getTexture("6"));
			window.draw(temp);
			break;
		case 7:
			temp.setTexture(TextureManager::getTexture("7"));
			window.draw(temp);
			break;
		case 8:
			temp.setTexture(TextureManager::getTexture("8"));
			window.draw(temp);
			break;
		}
	}
}
void board::printBoard() {
	int mineCounterNumber;
	int baseOffset = 21;
	int offset[3] = { 0, 0 ,0 };
	sf::RenderWindow window(sf::VideoMode(windowSize.x, windowSize.y), "MINESWEEPER");
	sf::Sprite Face, debug, t1, t2, t3, digits, win, lose, baseFlag, baseMine;
	Face.setTexture(TextureManager::getTexture("happyFace"));
	debug.setTexture(TextureManager::getTexture("debug"));
	t1.setTexture(TextureManager::getTexture("t1"));
	t2.setTexture(TextureManager::getTexture("t2"));
	t3.setTexture(TextureManager::getTexture("t3"));
	sf::Vector2f bottomCenter = sf::Vector2f(windowSize.x / 2 - 32, windowSize.y - 100);
	//make buttons for the bottom and the mine counter
	Face.setPosition(bottomCenter);
	debug.setPosition(sf::Vector2f(bottomCenter.x + 128, bottomCenter.y));
	t1.setPosition(sf::Vector2f(bottomCenter.x + 192, bottomCenter.y));
	t2.setPosition(sf::Vector2f(bottomCenter.x + 256, bottomCenter.y));
	t3.setPosition(sf::Vector2f(bottomCenter.x + 320, bottomCenter.y));
	for (int i = 0; i < 3; i++) {
		mineCounter[i].setPosition(sf::Vector2f(64 + 21*i, bottomCenter.y));
	}
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Space) {
					flagAll();
				}
			}
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::MouseButtonPressed) {
				sf::Vector2i position;
				int x = 0;
				int y = 0;
				position = sf::Mouse::getPosition(window);
				x = position.x / 32;
				y = position.y / 32;
				//to find which block it is 


				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					if (y >= rows) {
						//check if its one of the special buttons - WORKS FOR DEFAULT SIZE
						x = position.x;
						y = position.y;
						//checks if its the bottom row of buttons
						if (y >= bottomCenter.y && y <= bottomCenter.y + 64) {
							//check if its the reset face
							if (x >= bottomCenter.x && x <= bottomCenter.x + 64) {
								cout << "Smiley face :)" << endl;
								reset();
							}
							//if on debug 
							if (x >= bottomCenter.x + 128 && x < bottomCenter.x + 196 && (!lost) && (!won)) {
								cout << "Debug ~_~" << endl;
								if (game[0][0].godMode) {
									//turn off godMode for all
									for (int i = 0; i < game.size(); i++) {
										for (int j = 0; j < game[i].size(); j++) {
											game[i][j].godMode = false;
										}
									}
								}
								else {
									//turn on godMode for all
									for (int i = 0; i < game.size(); i++) {
										for (int j = 0; j < game[i].size(); j++) {
											game[i][j].godMode = true;
										}
									}
								}
								
							}
							//if t1
							if (x >= bottomCenter.x + 196 && x < bottomCenter.x + 256) {
								cout << "T1" << endl;
								reset(1);
							}
							//if t2
							if (x >= bottomCenter.x + 256 && x < bottomCenter.x + 320) {
								cout << "T2" << endl;
								reset(2);
							}
							//if t3
							if (x >= bottomCenter.x + 320 && x < bottomCenter.x + 384) {
								cout << "T3" << endl;
								reset(3);
							}

						}
						
					}
					else {
						if (game[x][y].reveal()) {
							//set num revealed
							numRevealed = 0;
							for (int i = 0; i < game.size(); i++) {
								for (int j = 0; j < game[i].size(); j++) {
									if (game[i][j].revealed) {
										numRevealed++;
									}
								}
							}
						}
						if (game[x][y].mine) {
							lost = true;
						}
						//check win con
						else if ((numRevealed + mines) == tileCount) {
							won = true;
						}
						
					}
				}
				else if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
					if (x <= collumns && y <= rows) {
						game[x][y].flag(flagCount);
					}
				}
			}
		}

		window.clear();
		//window drawing
		//draw each tile
		for (int i = 0; i < collumns; i++) {
			for (int j = 0; j < rows; j++) {
				game[i][j].print(window);
			}
		}
		//set face based on condition
		if (lost) {
			Face.setTexture(TextureManager::getTexture("lose"));
			youLost();
		}
		else if (won) {
			Face.setTexture(TextureManager::getTexture("win"));
			youWon();
		}
		else {
			Face.setTexture(TextureManager::getTexture("happyFace"));
		}
		//draw the extra buttons 
		window.draw(Face);
		window.draw(debug);
		window.draw(t1);
		window.draw(t2);
		window.draw(t3);
		//draw the mine counter and mine counter logic
		mineCounterNumber = mines - flagCount;
		//for a win, change the counter
		if (won) mineCounterNumber = 0;
		//negative
		mineCounter[3].setTextureRect(sf::IntRect(250, 0, 21, 32));
		mineCounter[3].setPosition(32, bottomCenter.y);
		if (mineCounterNumber < 0) {
			//ik its messy, but i was told about negative tripple digits after I had done everything. Sue me
			if (mineCounterNumber <= -100) {
				mineCounter[3].setTextureRect(sf::IntRect(210, 0, 21, 32));
				offset[0] = baseOffset * (abs(mineCounterNumber) / 100);
				mineCounterNumber -= (mineCounterNumber / 100) * 100;
				offset[1] = abs(mineCounterNumber) / 10 * baseOffset;
				offset[2] = abs(mineCounterNumber) % 10 * baseOffset;
			}else if (mineCounterNumber <= -10) {
				offset[0] = baseOffset * 10;
				offset[1] = abs(mineCounterNumber)/10 * baseOffset;
				offset[2] = abs(mineCounterNumber)%10 * baseOffset;
			}
			else {
				offset[0] = baseOffset * 11;
				offset[1] = baseOffset * 10;
				offset[2] = baseOffset * abs(mineCounterNumber);
			}
		}
		else {
			//positive or 0
			if (mineCounterNumber >= 100) {
				offset[0] = baseOffset * (mineCounterNumber / 100);
				int temp = mineCounterNumber - 100 * (int(mineCounterNumber / 100));
				offset[1] = baseOffset * (temp / 10);
				offset[2] = baseOffset * (temp % 10);
			}
			else {
				offset[0] = baseOffset*11;
			}
			if (mineCounterNumber >= 10 && mineCounterNumber <=100) {
				offset[1] = baseOffset * (mineCounterNumber / 10);
				offset[2] = baseOffset * (mineCounterNumber % 10);
			}
			else if(mineCounterNumber <10) {
				offset[1] = baseOffset*11;
				offset[2] = mineCounterNumber * baseOffset;
			}
		}

		if (mineCounter.size() == 4) {
			window.draw(mineCounter[3]);
		}
		for (int i = 0; i < 3; i++) {
			mineCounter[i].setTextureRect(sf::IntRect(offset[i], 0, 21, 32));
			window.draw(mineCounter[i]);
		}
		

		window.display();

	}
}
bool board::tile::reveal() {
	if (revealed||flagged||(!interactableSmall)) {
		return false;
	}
	revealed = true;
	botLayer.setTexture(TextureManager::getTexture("revealed"));
	if (number == 0 && !mine) {
		//reveal unflagged neighbors
		for (int k = 0; k < 8; k++) {
			//check if it is a neighbor
			if (neighbors[k] != nullptr) {
				if (!(neighbors[k]->flagged)) {
					neighbors[k]->reveal();
				}
			}
		}
	}
	return true;
}
void board::showBoard() {
	for (int i = 0; i < game.size(); i++) {
		for (int j = 0; j < game[i].size(); j++) {
			game[i][j].reveal();
		}
	}
}
void board::reset(int boardNumber) {
	game.clear();
	mineCounter.clear();
	mines = 0;
	rows = 0;
	collumns = 0;
	tileCount = 0;
	flagCount = 0;
	numRevealed = 0;
	windowSize.x = 0;
	windowSize.y = 0;

	lost = false;
	won = false;
	setBoard(boardNumber);
}
void board::youWon() {
	for (int i = 0; i < game.size(); i++) {
		for (int j = 0; j < game[i].size(); j++) {
			game[i][j].interactableSmall = false;
			if (game[i][j].mine) {
				game[i][j].flagged = true;
				game[i][j].revealed = false;
			}
		}
	}
}
void board::youLost() {
	for (int i = 0; i < game.size(); i++) {
		for (int j = 0; j < game[i].size(); j++) {
			game[i][j].interactableSmall = false;
			if (game[i][j].mine) {
				game[i][j].mine = true;
				game[i][j].revealed = false;
				game[i][j].godMode = true;

			}
		}
	}
}
void board::flagAll() {
	for (int i = 0; i < game.size(); i++) {
		for (int j = 0; j < game[i].size(); j++) {
			game[i][j].flag(flagCount);
			
		}
	}
}