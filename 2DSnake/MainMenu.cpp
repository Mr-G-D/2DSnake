#include "MainMenu.h"


MainMenu::MainMenu(shared_ptr<Construct>& construct) : _construct(construct)
{
	//_construct = construct;
}

void MainMenu::Init() {
	_construct->asset->addFont(MAIN_FONT, "assets/Fonts/Press_Start_2P/PressStart2P - Regular.ttf");
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