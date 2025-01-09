
#include "AssetManager.h"
#include "memory"

using namespace std;

Engine::AssetManager::AssetManager() {};

Engine::AssetManager::~AssetManager() {};

void Engine::AssetManager::addTexture(int id, const string& filepath, bool repeated) {
	unique_ptr<sf::Texture> texture = make_unique<sf::Texture>();

	if (texture->loadFromFile(filepath)) {
		texture->setRepeated(repeated);
		_texture[id] = move(texture);
	}
}

void Engine::AssetManager::addFont(int id, const string& filepath) {
	unique_ptr<sf::Font> font = make_unique<sf::Font>();

	if (font->openFromFile(filepath)) {
		_font[id] = move(font);
	}
}

const sf::Texture& Engine::AssetManager::getTexture(int id) const{
	return *(_texture.at(id).get());
}

const sf::Font& Engine::AssetManager::getFont(int id) const {
	return *(_font.at(id).get());
}