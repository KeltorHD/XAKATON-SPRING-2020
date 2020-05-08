#include "pch.h"
#include "downLayer.h"

DownLayer::DownLayer()
{
	this->playerShape.setSize(sf::Vector2f(1920.f, 400.f));
	this->playerShape.setFillColor(sf::Color(84, 97, 156, 255));
	this->playerShape.setPosition(sf::Vector2f(0.f, 1080.f - 400.f));

	this->marketShape.setSize(sf::Vector2f(1920.f, 400.f));
	this->marketShape.setFillColor(sf::Color(25, 26, 21, 255));
	this->marketShape.setPosition(sf::Vector2f(0.f, 1080.f - 800.f));

	this->bossShape.setSize(sf::Vector2f(1920.f, 280.f));
	this->bossShape.setFillColor(sf::Color(211, 57, 45, 255));
	this->bossShape.setPosition(sf::Vector2f(0.f, 0.f));
}

DownLayer::~DownLayer()
{
}

void DownLayer::render(sf::RenderTarget& target)
{
	target.draw(playerShape);
	target.draw(marketShape);
	target.draw(bossShape);
}
