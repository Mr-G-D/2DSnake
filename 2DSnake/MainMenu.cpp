#include "MainMenu.h"


MainMenu::MainMenu(shared_ptr<Construct>& construct) : _construct(construct), _gameTitle(_construct->asset->getFont(MAIN_FONT), "Test")
{
}

MainMenu::~MainMenu()
{
}

void MainMenu::Init() {
	_gameTitle.setFont(_construct->asset->getFont(MAIN_FONT));
	_gameTitle.setString("2D Snake Game");
}

void MainMenu::draw() {

	_construct->renderWindow->clear();
	_construct->renderWindow->draw(_gameTitle);
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
