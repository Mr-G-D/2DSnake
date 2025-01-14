#include "Game.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include "MainMenu.h";

Game::Game() : _construct(make_shared<Construct>()) {
	_construct->renderWindow->create(sf::VideoMode({ 200, 200 }), "SFML works!");
	_construct->state->add(make_unique<MainMenu>(_construct));
}

void Game::run() {
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	sf::Clock clock;
	sf::Time timeSinceLastFrame = sf::Time::Zero;

	while (_construct->renderWindow->isOpen())
	{
		timeSinceLastFrame += clock.restart();
		while (timeSinceLastFrame >= _timePerFrame)
		{
			timeSinceLastFrame -= _timePerFrame;

			_construct->state->processStateChange();
			_construct->state->getCurrent()->processInput();
			_construct->state->getCurrent()->update(_timePerFrame);
			_construct->state->getCurrent()->draw();

		}
	}
}
