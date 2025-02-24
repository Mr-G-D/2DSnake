#pragma once
#include <SFML/System/Time.hpp>

namespace Engine
{
	class State {
	public: 
		State() {};
		virtual ~State() {};

		virtual void Init() = 0;
		virtual void processInput() = 0;
		virtual void update(sf::Time deltaTime) = 0;
		virtual void draw() = 0;

		virtual void pause() {};
		virtual void start() {};
	};
}