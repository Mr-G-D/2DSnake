#include "GamePlay.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "MainMenu.h"
#include <memory>


GamePlay::GamePlay(shared_ptr<Construct> construct) :
	_construct(construct),
	_grass(_sample),
	_wall1(_sample), _wall2(_sample), _wall3(_sample), _wall4(_sample),
	_food(_sample),
	_direction(16, 0),
	_elapsedTime(sf::Time::Zero)
{
}

GamePlay::~GamePlay()
{
}

void GamePlay::Init()
{

	//Todo: Start snake at rest
	_construct->asset->addTexture(WALL, "../assets/Images/walls.png", true);
	_construct->asset->addTexture(GRASS, "../assets/Images/grass.jpg", true);
	_construct->asset->addTexture(FOOD, "../assets/Images/food1.png");
	_construct->asset->addTexture(SNAKE, "../assets/Images/snake.png");

	//GRASS
	_grass.setTexture(_construct->asset->getTexture(GRASS));
	_grass.setTextureRect(_construct->renderWindow->getViewport(_construct->renderWindow->getDefaultView()));

	//WALL
	for (sf::Sprite* _wall : _walls)
	{
		(*_wall).setTexture(_construct->asset->getTexture(WALL));
	}
	_wall2.setTexture(_construct->asset->getTexture(WALL));

	_wall1.setTextureRect(sf::Rect<int>({ 0, 0 }, { static_cast<int>(_construct->renderWindow->getSize().x), 16 }));
	_wall2.setTextureRect(sf::Rect<int>({ 0, 0 }, { 16, static_cast<int>(_construct->renderWindow->getSize().y) }));
	_wall3.setTextureRect(sf::Rect<int>({ 0, 0 }, { static_cast<int>(_construct->renderWindow->getSize().x), 16 }));
	_wall4.setTextureRect(sf::Rect<int>({ 0, 0 }, { 16, static_cast<int>(_construct->renderWindow->getSize().y) }));

	_wall3.setPosition(sf::Vector2f(0, static_cast<int>(_construct->renderWindow->getSize().y - 16)));
	_wall4.setPosition(sf::Vector2f(static_cast<int>(_construct->renderWindow->getSize().x) - 16, 0));

	//FOOD
	try
	{
		_food.setTexture(_construct->asset->getTexture(FOOD));
		sf::Vector2u windowSize = _construct->renderWindow->getSize();

		float scaleX = static_cast<float>(windowSize.x) / 2;
		float scaleY = static_cast<float>(windowSize.y) / 2;
		_food.setTextureRect(sf::Rect<int>({ 0, 0 }, { 16, 16 }));
		_food.setPosition(sf::Vector2f(scaleX, scaleY));
	}
	catch (const std::exception& err)
	{
		std::cout << err.what();
	}

	//SNAKE
	_snake.init(_construct->asset->getTexture(SNAKE));
}

void GamePlay::processInput()
{
	//Todo: 180 degree turn
	while (const optional event = _construct->renderWindow->pollEvent())
	{
		if (event->is<sf::Event::Closed>())
			_construct->renderWindow->close();

		if (event->is<sf::Event::KeyPressed>()) {

			const auto& key = event->getIf<sf::Event::KeyPressed>();
			switch (key->code)
			{
			case sf::Keyboard::Key::Up:
				_direction.x = 0;
				_direction.y = -16;
				break;

			case sf::Keyboard::Key::Down:
				_direction.x = 0;
				_direction.y = 16;
				break;

			case sf::Keyboard::Key::Left:
				_direction.x = -16;
				_direction.y = 0;
				break;

			case sf::Keyboard::Key::Right:
				_direction.x = 16;
				_direction.y = 0;
				break;

			default:
				break;
			}

		}
	}
}

void GamePlay::update(sf::Time deltaTime)
{
	_elapsedTime += deltaTime;

	if (_elapsedTime.asSeconds() >= 0.1) {
		_snake.move(_direction);
		_elapsedTime = sf::Time::Zero;


		if (_snake.collision(_food)) {
			_snake.grow(_direction);
			//Random Food Generator
			int x = ((rand() % 624) + 16);
			int y = (rand() % 464) + 16;
			// Todo: Check food postion for snake body;
			_food.setPosition(sf::Vector2f((x < 624) ? x : x % 624, (y < 464) ? y : y % 464)); 
		}
		for (auto& wall : _walls)
		{
			if (_snake.collision(*wall)) {
				_construct->state->add(make_unique<MainMenu>(_construct, false));
			}
		}
		//Todo: Game Pause Module

	}
}

void GamePlay::draw()
{
	_construct->renderWindow->clear();
	try
	{
		_construct->renderWindow->draw(_grass);
		for (sf::Sprite* _wall : _walls)
		{
			_construct->renderWindow->draw(*_wall);
		}
		_construct->renderWindow->draw(_food);
	}
	catch (const std::exception& err)
	{
		std::cout << err.what();
	}
	_construct->renderWindow->draw(_snake);
	_construct->renderWindow->display();
}
