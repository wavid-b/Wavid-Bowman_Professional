#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "TextureManager.h"
using namespace std;
class Objects
{
	string textureName;
	int xPosition;
	int yPosition;
	bool isTransparent = false;
	sf::Texture objTexture;
	bool isPressed = false;
public:
	sf::Sprite objSprite;

	Objects() {
		textureName = "";
	}
	Objects(string objType) {
		textureName = objType;
		placeAndResize();
	}
	void button(int status) {
		if (status == 1) {
			isPressed = true;
		}
		else {
			isPressed = false;
		}
		
	}
	bool getStatus() {
		return isPressed;
	}
	string getTextureName() {
		return textureName;
	}
	void setPosition(int x, int y) {
		objSprite.setPosition(x, y);
		xPosition = x;
		yPosition = y;
	}
	//setting the position and scale of all out object types (all banners, letters etc.)
	void placeAndResize() {
		if (textureName == "cow") {
			objSprite.setScale(0.15, 0.15);
		}
		else if (textureName == "start") {
			objSprite.setScale(0.3, 0.3);
			if (isTransparent == true) {
				objSprite.setColor(sf::Color::Black);
			}
			objSprite.setPosition(210, 450);
		}
		else if (textureName == "pen") {
			objSprite.setPosition(0, 300);
			objSprite.setScale(0.3, 0.3);
		}
		else if (textureName == "title") {
			objSprite.setScale(0.5, 0.5);
			objSprite.setPosition(-15, 30);
		}
		else if (textureName == "hardON" || textureName == "hardOFF") {
			objSprite.setPosition(245, 320);
		}
		else if (textureName == "hard") {
			objSprite.setScale(0.9, 0.9);
			objSprite.setPosition(0, 180);
		}
		else if (textureName == "a") {
			objSprite.setScale(0.25, 0.25);
		}
		else if (textureName == "b") {
			objSprite.setScale(0.25, 0.25);
		}
		else if (textureName == "c") {
			objSprite.setScale(0.25, 0.25);
		}
		else if (textureName == "d") {
			objSprite.setScale(0.25, 0.25);
		}
		else if (textureName == "e") {
			objSprite.setScale(0.25, 0.25);
		}
		else if (textureName == "f") {
			objSprite.setScale(0.25, 0.25);
		}
		else if (textureName == "g") {
			objSprite.setScale(0.25, 0.25);
		}
		else if (textureName == "h") {
			objSprite.setScale(0.25, 0.25);
		}
		else if (textureName == "i") {
			objSprite.setScale(0.25, 0.25);
		}
		else if (textureName == "j") {
			objSprite.setScale(0.25, 0.25);
		}
		else if (textureName == "k") {
			objSprite.setScale(0.25, 0.25);
		}
		else if (textureName == "l") {
			objSprite.setScale(0.25, 0.25);
		}
		else if (textureName == "m") {
			objSprite.setScale(0.25, 0.25);
		}
		else if (textureName == "n") {
			objSprite.setScale(0.25, 0.25);
		}
		else if (textureName == "o") {
			objSprite.setScale(0.25, 0.25);
		}
		else if (textureName == "p") {
			objSprite.setScale(0.25, 0.25);
		}
		else if (textureName == "q") {
			objSprite.setScale(0.25, 0.25);
		}
		else if (textureName == "r") {
			objSprite.setScale(0.25, 0.25);
		}
		else if (textureName == "s") {
			objSprite.setScale(0.25, 0.25);
		}
		else if (textureName == "t") {
			objSprite.setScale(0.25, 0.25);
		}
		else if (textureName == "u") {
			objSprite.setScale(0.25, 0.25);
		}
		else if (textureName == "v") {
			objSprite.setScale(0.25, 0.25);
		}
		else if (textureName == "w") {
			objSprite.setScale(0.25, 0.25);
		}
		else if (textureName == "x") {
			objSprite.setScale(0.25, 0.25);
		}
		else if (textureName == "y") {
			objSprite.setScale(0.25, 0.25);
		}
		else if (textureName == "z") {
			objSprite.setScale(0.25, 0.25);
		}
		else if (textureName == "out") {
			objSprite.setScale(0.25, 0.25);
		}
		else if (textureName == "selectSort") {
			objSprite.setScale(.5, .5);
			objSprite.setPosition(505, 15);
		}
		else if (textureName == "suggestLetter") {
			objSprite.setScale(0.5, 0.5);
			objSprite.setPosition(505, 240);
		}
		else if (textureName == "suggestWord") {
			objSprite.setScale(0.5, 0.5);
			objSprite.setPosition(505, 360);
		}
		else if (textureName == "selectionOFF" || textureName == "selectionON") {
			objSprite.setScale(0.15, 0.15);
			objSprite.setPosition(505, 85);
		}
		else if (textureName == "insertionOFF" || textureName == "insertionON") {
			objSprite.setScale(0.15, 0.15);
			objSprite.setPosition(653, 85);
		}
		else if (textureName == "bubbleOFF" || textureName == "bubbleON") {
			objSprite.setScale(0.15, 0.15);
			objSprite.setPosition(505, 140);
		}
		else if (textureName == "combOFF" || textureName == "combON") {
			objSprite.setScale(0.15, 0.15);
			objSprite.setPosition(653, 140);
		}
		else if (textureName == "quickOFF" || textureName == "quickON") {
			objSprite.setScale(0.15, 0.15);
			objSprite.setPosition(505, 190);
		}
		else if (textureName == "mergeOFF" || textureName == "mergeON") {
			objSprite.setScale(0.15, 0.15);
			objSprite.setPosition(653, 190);
		}
		else if (textureName == "empty") {
			objSprite.setScale(0.25, 0.25);
		}
		else if (textureName == "alien") {
			objSprite.setScale(0.25, 0.25);
		}

	}
	//change the name of a texture (ex: cow -> alien)
	void UpdateObjTexture(string newTexture) {
		textureName = newTexture;
		placeAndResize();
	}
	void setTransparent() {
		isTransparent = true;
	}
	void setTextureOFF(string currTexture) {
		if (currTexture == "selectionON") {
			textureName = "selectionOFF";
		}
		else if (currTexture == "insertionON") {
			textureName = "insertionOFF";
		}
		else if (currTexture == "bubbleON") {
			textureName = "bubbleOFF";
		}
		else if (currTexture == "combON") {
			textureName = "combOFF";
		}
		else if (currTexture == "quickON") {
			textureName = "quickOFF";
		}
		else if (currTexture == "mergeON") {
			textureName = "mergeOFF";
		}
	}
	void setTextureON(string currTexture) {
		if (currTexture == "selectionOFF") {
			textureName = "selectionON";
		}
		else if (currTexture == "insertionOFF") {
			textureName = "insertionON";
		}
		else if (currTexture == "bubbleOFF") {
			textureName = "bubbleON";
		}
		else if (currTexture == "combOFF") {
			textureName = "combON";
		}
		else if (currTexture == "quickOFF") {
			textureName = "quickON";
		}
		else if (currTexture == "mergeOFF") {
			textureName = "mergeON";
		}
	}
	sf::Sprite GetSprite() {
		objTexture = TextureManager::GetTexture(textureName);
		objSprite.setTexture(objTexture);
		return objSprite;
	}
};

