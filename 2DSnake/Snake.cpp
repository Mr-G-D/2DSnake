#include "Snake.h"
#include "SFML/Graphics.hpp"
#include <iostream>

Snake::Snake() 
{
	for (int i = 0; i < 4; i++)
	{
		_snake.push_back(sf::Sprite(_sample));
	}
	_head = --_snake.end();
	_tail = _snake.begin();
}

Snake::~Snake()
{
}

void Snake::init(const sf::Texture& texture)
{
	float x = 16;
	for (sf::Sprite& body : _snake)
	{
		body.setTexture(texture);
		body.setTextureRect(sf::Rect<int>({ 0,0 }, { 16, 16 }));
		body.setPosition(sf::Vector2f(x, 16));
		x += 16;
	}
}

void Snake::move(const sf::Vector2f& direction)
{
	
	_tail->setPosition(_head->getPosition() + direction);
	_head = _tail;
	++_tail;

	if (_tail == _snake.end()) {
		_tail = _snake.begin();
	}

}

bool Snake::collision(const sf::Sprite& collider)
{
	const sf::Rect<float>& _collider = collider.getGlobalBounds();
	const sf::Rect<float>& _snakeHead = _head->getGlobalBounds();
	if (_collider.findIntersection(_snakeHead)) {
		return true;
	}
	else {
		return false;
	}
}

void Snake::grow(sf::Vector2f& direction)
{
	sf::Sprite _newBody(_snake.begin()->getTexture());
	_newBody.setPosition(_head->getPosition() + direction);
	_snake.push_back(_newBody);
}

void Snake::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (auto& body : _snake)
	{
		target.draw(body);
	}
}


