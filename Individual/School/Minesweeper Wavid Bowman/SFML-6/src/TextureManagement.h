#pragma once
#include <fstream>
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <map>
#include <random>
using namespace std;
struct Random {
    static std::mt19937 random;

    static int Number(int min, int max) {
        std::uniform_int_distribution<int> dist(min, max);
        return dist(random);
    }
};
struct TextureManager {
    static map<string, sf::Texture> pictures;
    static void loadAll() {
        pictures["mine"].loadFromFile("images/mine.png");
        pictures["hidden"].loadFromFile("images/tile_hidden.png");
        pictures["revealed"].loadFromFile("images/tile_revealed.png");
        pictures["happyFace"].loadFromFile("images/face_happy.png");
        pictures["win"].loadFromFile("images/face_win.png");
        pictures["lose"].loadFromFile("images/face_lose.png");
        pictures["debug"].loadFromFile("images/debug.png");
        pictures["digits"].loadFromFile("images/digits.png");
        pictures["flag"].loadFromFile("images/flag.png");
        //for loop could do this if I could use itoa, but nope
        pictures["1"].loadFromFile("images/number_1.png");
        pictures["2"].loadFromFile("images/number_2.png");
        pictures["3"].loadFromFile("images/number_3.png");
        pictures["4"].loadFromFile("images/number_4.png");
        pictures["5"].loadFromFile("images/number_5.png");
        pictures["6"].loadFromFile("images/number_6.png");
        pictures["7"].loadFromFile("images/number_7.png");
        pictures["8"].loadFromFile("images/number_8.png");
        pictures["t1"].loadFromFile("images/test_1.png");
        pictures["t2"].loadFromFile("images/test_2.png");
        pictures["t3"].loadFromFile("images/test_3.png");
    }
    static sf::Texture& getTexture(string textureName) {
        return pictures[textureName];
    }
    static void Clear();
};
