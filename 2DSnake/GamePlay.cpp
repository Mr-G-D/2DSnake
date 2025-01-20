#include "GamePlay.h"
#include <SFML/Graphics.hpp>
#include <iostream>


GamePlay::GamePlay(shared_ptr<Construct> construct) :
	_construct(construct),
	_grass(_sample),
	_wall1(_sample), _wall2(_sample), _wall3(_sample), _wall4(_sample),
	_food(_sample)
{
}

GamePlay::~GamePlay()
{
}

void GamePlay::Init()
{
	_construct->asset->addTexture(WALL, "../assets/Images/walls.png", true);
	_construct->asset->addTexture(GRASS, "../assets/Images/grass.jpg", true);
	_construct->asset->addTexture(FOOD, "../assets/Images/food1.png");

	//GRASS
	_grass.setTexture(_construct->asset->getTexture(GRASS));
	_grass.setTextureRect(_construct->renderWindow->getViewport(_construct->renderWindow->getDefaultView()));

	//WALL
	for(sf::Sprite* _wall : _walls)
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
}

void GamePlay::processInput()
{
	while (const optional event = _construct->renderWindow->pollEvent())
	{
		if (event->is<sf::Event::Closed>())
			_construct->renderWindow->close();
	}
}

void GamePlay::update(sf::Time deltaTime)
{
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

	_construct->renderWindow->display();
}
