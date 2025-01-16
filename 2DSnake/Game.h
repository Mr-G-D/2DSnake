#pragma once
#include <memory>
#include "StateManager.h"
#include "AssetManager.h"

using namespace std;

enum Fonts
{
	MAIN_FONT = 0,
};

struct Construct
{
	unique_ptr<Engine::StateManager> state;
	unique_ptr<Engine::AssetManager> asset;
	unique_ptr<sf::RenderWindow> renderWindow;

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

