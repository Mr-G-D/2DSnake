#include "Game.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include "MainMenu.h"
#include <iostream>

using namespace std;

Game::Game() : _construct(make_shared<Construct>()) {
	try
	{
		_construct->renderWindow->create(sf::VideoMode({ 640, 480 }), "SFML works!");
		_construct->asset->addFont(MAIN_FONT, "../assets/Fonts/Press_Start_2P/PressStart2P.ttf");
		_construct->state->add(make_unique<MainMenu>(_construct, true));


	}
	catch (const std::exception& exec)
	{
		cout << exec.what();
	}
}

void Game::run() {

	try
	{
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
	catch (const std::exception& exec)
	{
		cout << exec.what();
	}
}
