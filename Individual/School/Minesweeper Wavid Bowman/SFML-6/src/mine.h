#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
using namespace std;
struct board {
	//config file - 3 lines: width, height, mine count 
	struct tile
	{
		bool interactableSmall;
		bool godMode;
		sf::Sprite botLayer;
		bool flagged;
		bool mine;
		int number;
		bool revealed;
		sf::Vector2i tileSpot;
		tile* neighbors[8];
		/* Schema for neighbors:
		*   0   1   2 
		*   3   X   4 
		*   5   6   7  */
		tile();
		//when left clicked 
		bool reveal();
			//reveal my tile. If number = 0, reveal neighbors 
		//when right clicked
		void flag(int &flagCount);
			//toggle flag. If off -> on, increase flaggedcount; vice versa
		void print(sf::RenderWindow& window);
	};
	//for the mine counter 
	vector<sf::Sprite> mineCounter;
	//variables
	bool lost = false;
	bool won = false;
	int numRevealed = 0;
	int mines = 0;
	sf::Vector2i windowSize;
	int rows = 0;
	int collumns = 0;
	int tileCount = 0;
	int flagCount = 0;
	vector<vector<tile>> game;
		//row x collumn
	board();
	void reset(int boardNumber = 0);
	void showBoard();
	void setBoard(int boardNumber = 0);
	void printBoard();
	void youLost();
	void youWon();
	void flagAll();
		//open boards/config.cfg ; get the data from that to build the board
	
};


