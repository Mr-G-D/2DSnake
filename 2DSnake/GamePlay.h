#pragma once
#include "State.h"
#include "SFML/Graphics.hpp"
#include <memory>
#include "Game.h"

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

	std::array<sf::Sprite*, 4> _walls = { &_wall1, &_wall2, &_wall3, &_wall4 };

public:
	GamePlay(shared_ptr<Construct> construct);
	~GamePlay() override;

	void Init() override;

	void processInput() override;

	void update(sf::Time deltaTime) override;

	void draw() override;

};

