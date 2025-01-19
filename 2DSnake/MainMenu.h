#pragma once
#include "State.h"
#include "Game.h"
#include <SFML/Graphics/Text.hpp>
#include <string.h>


using namespace std;

class MainMenu : public Engine::State
{
private:
	shared_ptr<Construct> _construct;
	sf::Text _gameTitle;
	sf::Text _playButton;
	sf::Text _quitButton;

	sf::Texture _background;

	bool _isPlaySelected;
	bool _isPlaypressed;
	bool _isQuitSelected;
	bool _isQuitPressed;

public:
	MainMenu(shared_ptr<Construct>& _construct);
	~MainMenu();

	void Init();

	void processInput();

	void update(sf::Time deltaTime);

	void draw();
};

