#pragma once
#include "State.h"
#include "SFML/Graphics.hpp"
#include <memory>
#include "Game.h"
#include "Snake.h"

class GamePlay : public Engine::State
{
private:
	shared_ptr<Construct> _construct;
	sf::Texture _sample;

	sf::Sprite _grass;
	sf::Sprite _food;
	sf::Sprite _wall1;
	sf::Sprite _wall2;
	sf::Sprite _wall3;
	sf::Sprite _wall4;

	sf::Text _pauseText;
	sf::RectangleShape _pauseScreen;
	
	Snake _snake;
	sf::Vector2f _direction;
	sf::Time _elapsedTime;

	std::array<sf::Sprite*, 4> _walls = { &_wall1, &_wall2, &_wall3, &_wall4 };

	bool _ispaused;
	bool _game;

public:
	GamePlay(shared_ptr<Construct> construct);
	~GamePlay() override;

	void Init() override;

	void processInput() override;

	void update(sf::Time deltaTime) override;

	void changeDirection(const float& x, const float& y);

	void draw() override;


	void pause() override;

};

