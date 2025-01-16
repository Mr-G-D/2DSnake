#include "MainMenu.h"


MainMenu::MainMenu(shared_ptr<Construct>& construct) : _construct(construct), 
_gameTitle(_construct->asset->getFont(MAIN_FONT), "Test"), 
_playButton(_construct->asset->getFont(MAIN_FONT), "Test"), 
_quitButton(_construct->asset->getFont(MAIN_FONT), "Test")
{
}

MainMenu::~MainMenu()
{
}

void MainMenu::Init() {

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

void MainMenu::draw() {

	_construct->renderWindow->clear();
	_construct->renderWindow->draw(_gameTitle);
	_construct->renderWindow->draw(_playButton);
	_construct->renderWindow->draw(_quitButton);
	_construct->renderWindow->display();
}



void MainMenu::processInput() {
	while (const optional event = _construct->renderWindow->pollEvent())
	{
		if (event->is<sf::Event::Closed>())
			_construct->renderWindow->close();
	}
}

void MainMenu::update(sf::Time deltaTime)
{
}
