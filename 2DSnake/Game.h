#pragma once
#include <memory>
#include "StateManager.h"
#include "AssetManager.h"

using namespace std;

enum Assets
{
	MAIN_FONT,
	BACKGROUND,
	WALL,
	GRASS,
	FOOD,
	SNAKE,
};

struct Construct
{
	unique_ptr<Engine::StateManager> state;
	unique_ptr<Engine::AssetManager> asset;
	unique_ptr<sf::RenderWindow> renderWindow;

	sf::Texture temp;

	Construct()
	{
		state = make_unique<Engine::StateManager>();
		asset = make_unique<Engine::AssetManager>();
		renderWindow = make_unique<sf::RenderWindow>();


	}

};

class Game
{

private:
	shared_ptr<Construct> _construct;
	const sf::Time _timePerFrame = sf::seconds(1.f / 60.f);

public:
	Game();

	~Game() {};

	void run();


};

