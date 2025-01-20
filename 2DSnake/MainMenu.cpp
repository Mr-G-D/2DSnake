#include "MainMenu.h"
#include <SFML/Window/Event.hpp>
#include <iostream>
#include "GamePlay.h"


MainMenu::MainMenu(shared_ptr<Construct>& construct) : _construct(construct),
_gameTitle(_construct->asset->getFont(MAIN_FONT), "Test"),
_playButton(_construct->asset->getFont(MAIN_FONT), "Test"),
_quitButton(_construct->asset->getFont(MAIN_FONT), "Test"),
_background(_construct->temp),
_isPlaypressed(false),
_isPlaySelected(true),
_isQuitPressed(false),
_isQuitSelected(false)
{}

MainMenu::~MainMenu()
{}

void MainMenu::Init() {

	//BACKGROUND
	_construct->asset->addTexture(BACKGROUND, "../assets/Images/background.jpg");

	//GAME TITLE
	_gameTitle.setFont(_construct->asset->getFont(MAIN_FONT));
	_gameTitle.setString("2D Snake Game");
	_gameTitle.setOrigin(_gameTitle.getLocalBounds().getCenter());
	int x = _construct->renderWindow->getSize().x / 2.0;
	int y = (_construct->renderWindow->getSize().y / 2.0) - 150;
	_gameTitle.setPosition(sf::Vector2<float>(x, y));

	//PLAY BUTTON
	_playButton.setFont(_construct->asset->getFont(MAIN_FONT));
	_playButton.setString("Play");
	_playButton.setOrigin(_playButton.getLocalBounds().getCenter());
	x += 250;
	y += 175;
	_playButton.setPosition(sf::Vector2<float>(x, y));
	_playButton.setCharacterSize(20);

	//QUIT BUTTON	
	_quitButton.setString("Quit");
	_quitButton.setOrigin(_quitButton.getLocalBounds().getCenter());
	y += 25;
	_quitButton.setPosition(sf::Vector2<float>(x, y));
	_quitButton.setCharacterSize(20);
}




void MainMenu::processInput() {
	while (const optional event = _construct->renderWindow->pollEvent())
	{
		if (event->is<sf::Event::Closed>())
			_construct->renderWindow->close();
		else if (event->is<sf::Event::KeyPressed>())
		{
			auto key = event->getIf<sf::Event::KeyPressed>();

			switch (key->code)
			{
			case sf::Keyboard::Key::Up:
				_isPlaySelected = !_isPlaySelected;
				_isQuitSelected = !_isQuitSelected;
				break;
			case sf::Keyboard::Key::Down:
				_isPlaySelected = !_isPlaySelected;
				_isQuitSelected = !_isQuitSelected;
				break;
			case sf::Keyboard::Key::Enter:
				if (_isPlaySelected)
				{
					_isPlaypressed = true;
				}
				else
				{
					_isQuitPressed = true;
				}
				break;
			default:
				break;
			}
		}
	}
}


void MainMenu::update(sf::Time deltaTime)
{
	if (_isPlaySelected) {
		_playButton.setFillColor(sf::Color::Green);
		_quitButton.setFillColor(sf::Color::White);
	}
	else if (_isQuitSelected) {
		_quitButton.setFillColor(sf::Color::Green);
		_playButton.setFillColor(sf::Color::White);
	}
	if (_isPlaypressed) {
		_construct->state->add(make_unique<GamePlay>(_construct), true);
	}
	else if (_isQuitPressed) {
		_construct->renderWindow->close();
	}
}



void MainMenu::draw() {

	_construct->renderWindow->clear();
	_background.setTexture(_construct->asset->getTexture(BACKGROUND), true);

	sf::Vector2u windowSize = _construct->renderWindow->getSize();

	sf::Vector2u textureSize = _construct->asset->getTexture(BACKGROUND).getSize();
	float scaleX = static_cast<float>(windowSize.x) / static_cast<float>(textureSize.x);
	float scaleY = static_cast<float>(windowSize.y) / static_cast<float>(textureSize.y);
	_background.setScale(sf::Vector2f(scaleX, scaleY));
	_construct->renderWindow->draw(_background);
	_construct->renderWindow->draw(_gameTitle);
	_construct->renderWindow->draw(_playButton);
	_construct->renderWindow->draw(_quitButton);
	_construct->renderWindow->display();
}