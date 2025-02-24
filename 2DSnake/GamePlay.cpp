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
	_elapsedTime(sf::Time::Zero),
	_pauseText(_construct->asset->getFont(MAIN_FONT), "PAUSED")
{
	_ispaused = false;
	_game = false;
}

GamePlay::~GamePlay()
{
}

void GamePlay::Init()
{

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

	_wall3.setPosition(sf::Vector2f(0.f, static_cast<float>(_construct->renderWindow->getSize().y - 16.f)));
	_wall4.setPosition(sf::Vector2f(static_cast<float>(_construct->renderWindow->getSize().x) - 16.f, 0.f));

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

	//PAUSE STATE
	_pauseText.setPosition(sf::Vector2f(_construct->renderWindow->getSize().x / 2.0f, _construct->renderWindow->getSize().y / 2.f));
	_pauseText.setOrigin(_pauseText.getLocalBounds().getCenter());
	_pauseText.setString("");

	_pauseScreen.setSize(sf::Vector2f(_construct->renderWindow->getSize()));
	_pauseScreen.setFillColor(sf::Color(0, 0, 0, 0));
	_pauseScreen.setTextureRect(sf::Rect<int>({ 0, 0 }, 
		{ static_cast<int>(_construct->renderWindow->getSize().x), static_cast<int>(_construct->renderWindow->getSize().y) }));
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
				changeDirection(0.f, -16.f);
				break;

			case sf::Keyboard::Key::Down:
				changeDirection(0.f, 16.f);
				break;

			case sf::Keyboard::Key::Left:
				changeDirection(-16.f, 0);
				break;

			case sf::Keyboard::Key::Right:
				changeDirection(16.f, 0.f);
				break;

			case sf::Keyboard::Key::Escape:
				pause();
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
		if(!_ispaused && _game)
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
				_construct->state->popCurrent();
				_construct->state->add(make_unique<MainMenu>(_construct, false));
			}
		}

	}
}

void GamePlay::changeDirection(const float& x, const float& y)
{
	if (!_ispaused)
	{
		if (!_game) {
			_game = true;
		}
		if (std::abs(_direction.x) != std::abs(x) || std::abs(_direction.y) != std::abs(y))
		{
			_direction.x = x;
			_direction.y = y;
		}
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
	_construct->renderWindow->draw(_pauseText);
	_construct->renderWindow->draw(_pauseScreen);
	_construct->renderWindow->display();
}

void GamePlay::pause()
{
	if (!_ispaused) {
		_ispaused = true;
		_pauseText.setString("Paused");
		_pauseScreen.setFillColor(sf::Color(0, 0, 0, 128));
	}
	else {
		_ispaused = false;
		_pauseText.setString("");
		_pauseScreen.setFillColor(sf::Color(0, 0, 0, 0));
	}
}
