#pragma once
#include <SFML/Graphics.hpp>


class Snake : public sf::Drawable
{

private:
	std::list<sf::Sprite> _snake;
	std::list<sf::Sprite>::iterator _head;
	std::list<sf::Sprite>::iterator _tail;

	sf::Texture _sample;

public:
	Snake();

	~Snake();

	void init(const sf::Texture& texture);
	void move(const sf::Vector2f& direction);
	bool collision(const sf::Sprite& collider);
	void grow(sf::Vector2f& direction);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
