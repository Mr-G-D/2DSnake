#include "Game.h"

Game::Game() : _construct(make_shared<Construct>()) {
	_construct->renderWindow->create(sf::VideoMode({ 200, 200 }), "SFML works!");
}

void Game::run() {
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	while (_construct->renderWindow->isOpen())
	{
		while (const std::optional event = _construct->renderWindow->pollEvent())
		{
			if (event->is<sf::Event::Closed>())
				_construct->renderWindow->close();
		}

		_construct->renderWindow->clear();
		_construct->renderWindow->draw(shape);
		_construct->renderWindow->display();
	}
}

