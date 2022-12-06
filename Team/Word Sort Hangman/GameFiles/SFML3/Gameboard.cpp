#include "Gameboard.h"
#include <chrono>
using namespace chrono;
//set the gameboard with all the abjects to draw then display when the time comes
Gameboard::Gameboard(sf::RenderWindow& window)
{
	if (true) {
		gameStatus = "menu";
		//set all menu objects
		Objects item("title");
		menuObjects.push_back(item);
		item.UpdateObjTexture("hardOFF");
		menuObjects.push_back(item);
		hardMode = false;
		hardCover.UpdateObjTexture("hard");
		//set all playing objects
		item.UpdateObjTexture("pen");
		playingObjects.push_back(item);

		//setting the cows positions
		item.UpdateObjTexture("cow");
		item.setPosition(260, 360);
		cowObjects.push_back(item);
		item.setPosition(190, 300);
		cowObjects.push_back(item);
		item.setPosition(90, 360);
		cowObjects.push_back(item);
		item.setPosition(340, 300);
		cowObjects.push_back(item);
		item.setPosition(40, 300);
		cowObjects.push_back(item);
		item.setPosition(190, 440);
		cowObjects.push_back(item);
		item.setPosition(40, 440);
		cowObjects.push_back(item);
		item.setPosition(340, 440);
		cowObjects.push_back(item);

		//setting the letter positions
		item.UpdateObjTexture("a");
		item.setPosition(68.75, 67.5);
		kbObjects.push_back(item);

		item.UpdateObjTexture("b");
		item.setPosition(256.25, 105);
		kbObjects.push_back(item);

		item.UpdateObjTexture("c");
		item.setPosition(181.25, 105);
		kbObjects.push_back(item);

		item.UpdateObjTexture("d");
		item.setPosition(143.75, 67.5);
		kbObjects.push_back(item);

		item.UpdateObjTexture("e");
		item.setPosition(125, 30);
		kbObjects.push_back(item);

		item.UpdateObjTexture("f");
		item.setPosition(181.25, 67.5);
		kbObjects.push_back(item);

		item.UpdateObjTexture("g");
		item.setPosition(218.75, 67.5);
		kbObjects.push_back(item);

		item.UpdateObjTexture("h");
		item.setPosition(256.25, 67.5);
		kbObjects.push_back(item);

		item.UpdateObjTexture("i");
		item.setPosition(312.5, 30);
		kbObjects.push_back(item);

		item.UpdateObjTexture("j");
		item.setPosition(293.75, 67.5);
		kbObjects.push_back(item);

		item.UpdateObjTexture("k");
		item.setPosition(331.25, 67.5);
		kbObjects.push_back(item);

		item.UpdateObjTexture("l");
		item.setPosition(368.75, 67.5);
		kbObjects.push_back(item);

		item.UpdateObjTexture("m");
		item.setPosition(331.25, 105);
		kbObjects.push_back(item);

		item.UpdateObjTexture("n");
		item.setPosition(293.75, 105);
		kbObjects.push_back(item);

		item.UpdateObjTexture("o");
		item.setPosition(350, 30);
		kbObjects.push_back(item);

		item.UpdateObjTexture("p");
		item.setPosition(387.5, 30);
		kbObjects.push_back(item);

		item.UpdateObjTexture("q");
		item.setPosition(50, 30);
		kbObjects.push_back(item);

		item.UpdateObjTexture("r");
		item.setPosition(162.5, 30);
		kbObjects.push_back(item);

		item.UpdateObjTexture("s");
		item.setPosition(106.25, 67.5);
		kbObjects.push_back(item);

		item.UpdateObjTexture("t");
		item.setPosition(200, 30);
		kbObjects.push_back(item);

		item.UpdateObjTexture("u");
		item.setPosition(275, 30);
		kbObjects.push_back(item);

		item.UpdateObjTexture("v");
		item.setPosition(218.75, 105);
		kbObjects.push_back(item);

		item.UpdateObjTexture("w");
		item.setPosition(87.5, 30);
		kbObjects.push_back(item);

		item.UpdateObjTexture("x");
		item.setPosition(143.75, 105);
		kbObjects.push_back(item);

		item.UpdateObjTexture("y");
		item.setPosition(237.5, 30);
		kbObjects.push_back(item);

		item.UpdateObjTexture("z");
		item.setPosition(106.25, 105);
		kbObjects.push_back(item);

		//set banners!!!
		item.UpdateObjTexture("selectSort");
		banners.push_back(item);
		item.UpdateObjTexture("suggestLetter");
		banners.push_back(item);
		item.UpdateObjTexture("suggestWord");
		banners.push_back(item);
		//set sorts!!! (off)
		item.UpdateObjTexture("combON");
		item.button(1);
		sorts.push_back(item);
		item.UpdateObjTexture("bubbleOFF");
		item.button(0);
		sorts.push_back(item);
		item.UpdateObjTexture("selectionOFF");
		item.button(0);
		sorts.push_back(item);
		item.UpdateObjTexture("insertionOFF");
		item.button(0);
		sorts.push_back(item);
		item.UpdateObjTexture("quickOFF");
		item.button(0);
		sorts.push_back(item);
		item.UpdateObjTexture("mergeOFF");
		item.button(0);
		sorts.push_back(item);

		//set spaces
		item.UpdateObjTexture("empty");
		int initial = 50;
		for (int i = 0; i < 10; i++)
		{
			item.setPosition(initial+i*37.5, 180);
			guessing_word_even.push_back(item);
		}
		initial = 68.75;
		for (int i = 0; i < 9; i++)
		{
			item.setPosition(initial + i * 37.5, 180);
			guessing_word_odd.push_back(item);
		}

	}
	//add size of word and then push back objects
	//push back letter lol
	
}

//change game status (ex: playing -> win/lose)
void Gameboard::editGameStatus(string status)
{
	gameStatus = status;
}

string Gameboard::getGameStatus()
{
	return gameStatus;
}
//displays menu objects UNTIL the start button is pressed
void Gameboard::displayMenu(sf::RenderWindow& window)
{
	while (getGameStatus() == "menu") {
		//interact(window);
		window.clear(sf::Color(188, 255, 195, 255));
		//print out game title
		//anything else we should design (instructions?)
		//print out start button
		for (auto& i : menuObjects) {
			window.draw(i.GetSprite());
		}
		startButton.UpdateObjTexture("start");
		window.draw(startButton.GetSprite());
		//check is you press the button
		string start = "startButton";
		press(window, startButton, start);
		start = "hardButton";
		press(window, menuObjects[1], "hardButton");
		window.display();
	}
}
//press fucitonality for ALL pressable objects (ex: letters or start button)
void Gameboard::press(sf::RenderWindow& window, Objects& obj, string buttonType) {
	//window.setKeyRepeatEnabled(false);
	sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		sf::FloatRect rectangle = obj.GetSprite().getGlobalBounds();
		if (rectangle.contains(mousePosition.x, mousePosition.y)) {
			if (getGameStatus() == "menu") {
				//if you press the start button, game status changes to playing
				if (buttonType == "startButton") {
					editGameStatus("playing");
				}
				//if the hard mode button is pressed, hard mode is turned on!
				else if (buttonType == "hardButton") {
					if (hardMode != true) {
						hardMode = true;
						obj.UpdateObjTexture("hardON");
						//add hard obj 
						game hardhangman(true);
						hangman = &hardhangman;
					}

				}
			}
			if (getGameStatus() == "playing")
			{
				//if a letter was pressed (correct: filll in letter. incorrect: change cow to alien)
				if (buttonType == "keyboard") {
					if (obj.getTextureName() != "out") {
						//if cow objects includes an alien then take the alien away (only keep alien till next letter was chosen)
						if (cowObjects[cowObjects.size() - 1].getTextureName() == "alien") {
							cowObjects.pop_back();
						}

						//check if letter was correct or incorrect input and updates the game based on that information
						bool check = hangman.checkLetter(obj.getTextureName().at(0));
						displaySuggested(window);
						if (check)
						{
							if (hangman.evenCase)
							{
								for (int i = hangman.startIndex; i <= hangman.endIndex; i++)
								{
									if (hangman.wordSoFar.at(i - hangman.startIndex) == obj.getTextureName().at(0))
									{
										guessing_word_even[i].UpdateObjTexture(obj.getTextureName());
									}
								}
							}
							else
							{
								for (int i = hangman.startIndex; i <= hangman.endIndex; i++)
								{
									if (hangman.wordSoFar.at(i - hangman.startIndex) == obj.getTextureName().at(0))
									{
										guessing_word_odd[i].UpdateObjTexture(obj.getTextureName());
									}
								}
							}
						}
						else
						{
							//if letter selected was NOT part of the word.... change one of the cows to aliens
							cowObjects[cowObjects.size() - 1].UpdateObjTexture("alien");
							cowObjects[cowObjects.size() - 1].setPosition(cowObjects[cowObjects.size() - 1].GetSprite().getPosition().x, cowObjects[cowObjects.size() - 1].GetSprite().getPosition().y-10);
						}
						//cross letter out (cant use it anymore)
						obj.UpdateObjTexture("out");
					}
				}
				else if (buttonType == "s") {
					//if any of the sorts have been selected- then deselect them and update the new one
					//std::cout << "A SORT HAS BEEN PRESSED" << endl;
					int count = 0;
					bool alreadySelected = false;
					for (auto& i : sorts) {
						//turn off all buttons except for the chosen one
						if (i.getTextureName() == obj.getTextureName()) {
							if (i.getStatus() == true) {
								alreadySelected = true;
								sortNum = count;
							}
							else {
								i.button(1);
								//depending on the sort update sort item
								i.setTextureON(i.getTextureName());
								sortNum = count;
								
							}
						}
						else {
							i.button(0);
							//set textures to off
							i.setTextureOFF(i.getTextureName());
							count++;
						}
					}
					if (alreadySelected == false) {
						hangman.setSortOn(sortNum);
						displaySuggested(window);
					}
				}
			}
			if (gameStatus == "win" || gameStatus == "lose") {
				editGameStatus("end");
			}
		}
	}
}

void Gameboard::play(sf::RenderWindow& window)
{
	displaySuggested(window);
	while (getGameStatus() == "playing") {
		window.clear(sf::Color(188, 255, 195, 255));
		//draw rectangle base for the suggestions and operations panel
		sf::RectangleShape rectangle(sf::Vector2f(120, 50));
		rectangle.setSize(sf::Vector2f(window.getSize().x - (window.getSize().x - 470), window.getSize().y));
		rectangle.setPosition(470,0);
		rectangle.setFillColor(sf::Color(160, 82, 45));
		window.draw(rectangle);
		//draw all playing objects (cows, letters, suggested features etc.)
		for (auto& i : playingObjects) {
			window.draw(i.GetSprite());
		}
		for (auto& i : cowObjects) {
			window.draw(i.GetSprite());
		}
		for (auto& i : kbObjects) {
			window.draw(i.GetSprite());
		}
		for (auto& i : banners) {
			window.draw(i.GetSprite());
		}
		for (auto& i : sorts) {
			window.draw(i.GetSprite());
		}
		for (auto i : letters) {
			window.draw(i.GetSprite());
		}
		for (auto i : words) {
			for (auto j : i) {
				window.draw(j.GetSprite());
			}
		}
		//check if a letter was pressed
		for (auto& i : kbObjects) {
			press(window, i, "keyboard");
		}
		//check if a sort was pressed
		for (auto& i : sorts) {
			press(window, i, "s");
		}
		//drawing the suggested words and letters
		if (hangman.evenCase)
		{
			for (auto i = hangman.startIndex; i <= hangman.endIndex; i++) {
				window.draw(guessing_word_even[i].GetSprite());
			}
		}
		else
		{
			for (auto i = hangman.startIndex; i <= hangman.endIndex; i++) {
				window.draw(guessing_word_odd[i].GetSprite());
			}
		}
		//if hardmode is on then draw over the guessing word to keep the size anonymous
		if (hardMode == true) {
			window.draw(hardCover.GetSprite());
		}
		//if hangman.checkwin or check lose then update game status
		if (hangman.checkWin()) {
			editGameStatus("win");
		}
		if (hangman.guesses >= 8) {
			editGameStatus("lose");
		}
		window.display();
	}
}
void Gameboard::displaySuggested(sf::RenderWindow& window) {
	auto start = high_resolution_clock::now();

	//5 letters, 5 words of various sizes 
	//same even/odd cases for those words probably 
	//suggested words print out left-aligned -> 505 for x

	//37.5 x 37.5 size per letter and setScale to 0.1
	//textureName determines what letter is dislplayed
	letters.clear();
	words.clear();
	vector<string> lettersSug;
	vector<string> wordsSug;
	hangman.getSuggestions(wordsSug, lettersSug);
	//now assign each letter an object
	int initial = 505;
	for (int i = 0; i < lettersSug.size(); i++) {
		Objects temp(lettersSug[i]);
		temp.objSprite.setScale(0.25, 0.25);
		temp.objSprite.setPosition(initial+58*i, 310);
		letters.push_back(temp);
	}
	//display letters in right spot -> only show whats in "letters"

	//now assign letters to each letter for each word
	int heightInitial = 420;
	int widthInitial = 540;
	for (int i = 0; i < wordsSug.size(); i++) {
		string currentWord = wordsSug[i];
		vector<Objects> tempVector;
		words.push_back(tempVector);
		for (int j = 0; j < currentWord.size(); j++) {
			string initStr = "";
			initStr += currentWord[j];
			Objects toAdd(initStr);
			toAdd.objSprite.setScale(0.2, 0.2);
			toAdd.objSprite.setPosition(widthInitial+j*20,heightInitial+i*35);
			words[i].push_back(toAdd);
		}
	}
	auto end = high_resolution_clock::now();
	auto duration = duration_cast<milliseconds>(end - start);
	cout << duration.count() << " miliseconds; Set size: " << hangman.w.valid_words.size() << endl;
}
void Gameboard::lose(sf::RenderWindow& window)
{
	//while (gameStatus == "lose") {
		//display winning screen
		window.clear(sf::Color(188, 255, 195, 255));
		Objects lost("lose");
		window.draw(lost.GetSprite());
		press(window, lost, "lose");
		window.display();
	//}
}
void Gameboard::win(sf::RenderWindow& window)
{
	//while (gameStatus == "win") {
		//display winning screen
		window.clear(sf::Color(188, 255, 195, 255));
		Objects winner_winner_chicken_dinnner("win");
		window.draw(winner_winner_chicken_dinnner.GetSprite());
		press(window, winner_winner_chicken_dinnner, "win");
		window.display();
	//}
}
