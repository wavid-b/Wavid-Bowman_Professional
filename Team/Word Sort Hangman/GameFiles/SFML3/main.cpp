
#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include "Objects.h"
#include "Gameboard.h"
#include <iostream>
using namespace std;

//in order to keep main organized- the sfml functionality was pushed onto a different class
int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Screen");
    Gameboard screen(window);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            window.clear(sf::Color(188, 255, 195, 255));
            //if on the menu (default) the game displays the menu with its functionalities
            if (screen.getGameStatus() == "menu") {
                screen.displayMenu(window);
            }
            //after start was pressed- the main gmae is shown
            else if (screen.getGameStatus() == "playing") {
                screen.play(window);
            }
            //if you win the game- the win screen shows
            else if (screen.getGameStatus() == "win") {
                screen.win(window);
                //window.close();
                break;
            }
            //if you lose the game- the lose screen shows
            else if (screen.getGameStatus() == "lose") {
                screen.lose(window);
                //window.close();
                break;
            }
        }
        window.clear();
        
    }
    return 0;
}