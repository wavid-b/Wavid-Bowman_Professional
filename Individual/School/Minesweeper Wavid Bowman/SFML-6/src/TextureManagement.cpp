#include "TextureManagement.h"
map<string, sf::Texture> TextureManager::pictures;
std::mt19937 Random::random;
void TextureManager::Clear() {
	pictures.clear();
}