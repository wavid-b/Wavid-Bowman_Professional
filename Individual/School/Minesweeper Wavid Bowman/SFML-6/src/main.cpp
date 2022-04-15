#include <SFML/Graphics.hpp>
#include "mine.h"
#include "TextureManagement.h"
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

int main()
{
    TextureManager::loadAll();
    //store the assets
   
    board gameBoard;
    gameBoard.setBoard();
    gameBoard.printBoard();
    
    
   

    TextureManager::Clear();
    return 0;
}

