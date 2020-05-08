#include "pch.h"
#include "cardMenu.h"

CardMarketMenu::CardMarketMenu()
{
}

CardMarketMenu::CardMarketMenu(Card* card, sf::Font& font)
{
	this->card = card;
	this->isActive = true;

	this->BuyPressed = false;

	this->keyTime = 0.f;
	this->keyTimeMax = 10.f;

	
	this->buy =
		new gui::Button
		(
			card->getPosition().x + CardWidth + 15, card->getPosition().y,
			100.f, 65.f, &font,
			"BUY", 25,
			sf::Color(250, 250, 250, 250),
			sf::Color(250, 250, 250, 250),
			sf::Color(250, 250, 250, 250),

			sf::Color::Black,
			sf::Color::Black,
			sf::Color::Black,

			sf::Color::Yellow,
			sf::Color::Yellow,
			sf::Color::Yellow
		);
}

CardMarketMenu::~CardMarketMenu()
{
	delete this->buy;
}

const bool CardMarketMenu::getPress() const
{
	if (this->BuyPressed)
		return true;

	return false;
}

const bool CardMarketMenu::getActive() const
{
	return this->isActive;
}

const bool CardMarketMenu::buyPressed() const
{
	return this->BuyPressed;
}

const float CardMarketMenu::getkeyTimeFloat()
{
	return this->keyTime;
}

const bool CardMarketMenu::getKeyTime()
{
	if (this->keyTime >= keyTimeMax)
	{
		this->keyTime = 0.f;
		return true;
	}
	return false;
}

Card* CardMarketMenu::getCard()
{
	return this->card;
}

void CardMarketMenu::setActive(bool isActive)
{
	this->isActive = isActive;
}

void CardMarketMenu::updateKeyTime(const float& dt)
{
	if (this->keyTime < this->keyTimeMax)
		this->keyTime += 50.f * dt;
}

void CardMarketMenu::update(const sf::Vector2i& mousePosWindow, const float& dt)
{
	this->buy->update(mousePosWindow);
	this->updateKeyTime(dt);

	bool isPressed = false;

	if (buy->isPressed() && getKeyTime())
	{
		this->BuyPressed = true;
		isActive = false;
		isPressed = true;
	}
	/*если не туда тыкнул*/
	if (this->getActive() && sf::Mouse::isButtonPressed(sf::Mouse::Left) && !isPressed && this->getKeyTime())
		this->isActive = false;
}

void CardMarketMenu::render(sf::RenderTarget& target)
{
	buy->render(target);
}


CardMenu::CardMenu()
{
}

CardMenu::CardMenu(Card* card, sf::Font& font)
{
	this->card = card;
	this->isActive = true;

	this->FirstAbility1Pressed = false;
	this->FirstAbility2Pressed = false;
	this->FriendAbilityPressed = false;
	this->DestroyAbilityPressed = false;

	this->keyTime = 0.f;
	this->keyTimeMax = 10.f;

	this->firstAbility1 = 
		new gui::Button
		(
			card->getPosition().x + CardWidth + 15, card->getPosition().y,
			100.f, 65.f, &font,
			"ABILITY 1", 25,
			sf::Color(250, 250, 250, 250),
			sf::Color(250, 250, 250, 250),
			sf::Color(250, 250, 250, 250),

			sf::Color::Black,
			sf::Color::Black,
			sf::Color::Black,

			sf::Color::Yellow,
			sf::Color::Yellow,
			sf::Color::Yellow
		);
	this->firstAbility2 = nullptr;
	this->friendAbility = nullptr;
	this->destroyAbility = nullptr;
	if (card->isChoice)
	{
		this->firstAbility2 =
			new gui::Button
			(
				card->getPosition().x + CardWidth + 130, card->getPosition().y,
				100.f, 65.f, &font,
				"ABILITY 2", 25,
				sf::Color(250, 250, 250, 250),
				sf::Color(250, 250, 250, 250),
				sf::Color(250, 250, 250, 250),

				sf::Color::Black,
				sf::Color::Black,
				sf::Color::Black,

				sf::Color::Yellow,
				sf::Color::Yellow,
				sf::Color::Yellow
			);
	}
	if (card->isFriend)
	{
		this->friendAbility =
			new gui::Button
			(
				card->getPosition().x + CardWidth + 15, card->getPosition().y + 80,
				100.f, 65.f, &font,
				"FRIEND", 25,
				sf::Color(250, 250, 250, 250),
				sf::Color(250, 250, 250, 250),
				sf::Color(250, 250, 250, 250),

				sf::Color::Black,
				sf::Color::Black,
				sf::Color::Black,

				sf::Color::Yellow,
				sf::Color::Yellow,
				sf::Color::Yellow
			);
	}
	if (card->isDestroy)
	{
		this->destroyAbility =
			new gui::Button
			(
				card->getPosition().x + CardWidth + 15, card->getPosition().y + 160,
				100.f, 65.f, &font,
				"DESTROY", 25,
				sf::Color(250, 250, 250, 250),
				sf::Color(250, 250, 250, 250),
				sf::Color(250, 250, 250, 250),
				
				sf::Color::Black,
				sf::Color::Black,
				sf::Color::Black,

				sf::Color::Yellow,
				sf::Color::Yellow,
				sf::Color::Yellow
			);
	}
}

CardMenu::~CardMenu()
{
	delete this->firstAbility1;
	if (this->card->isChoice)
		delete this->firstAbility2;
	if (this->card->isFriend)
		delete this->friendAbility;
	if (this->card->isDestroy)
		delete this->destroyAbility;
}

const bool CardMenu::getPress() const
{
	if (this->FirstAbility1Pressed || this->FirstAbility2Pressed
		|| this->FriendAbilityPressed || this->DestroyAbilityPressed)
		return true;

	return false;
}

const bool CardMenu::getActive() const
{
	return this->isActive;
}

const bool CardMenu::isFirstAbility1Pressed() const
{
	return this->FirstAbility1Pressed;
}

const bool CardMenu::isFirstAbility2Pressed() const
{
	return this->FirstAbility2Pressed;
}

const bool CardMenu::isFriendAbilityPressed() const
{
	return this->FriendAbilityPressed;
}

const bool CardMenu::isDestroyAbilityPressed() const
{
	return this->DestroyAbilityPressed;
}

const float CardMenu::getkeyTimeFloat()
{
	return this->keyTime;
}

const bool CardMenu::getKeyTime()
{
	if (this->keyTime >= keyTimeMax)
	{
		this->keyTime = 0.f;
		return true;
	}
	return false;
}

const Card* CardMenu::getCard()
{
	return this->card;
}

void CardMenu::setActive(bool isActive)
{
	this->isActive = isActive;
}

void CardMenu::updateKeyTime(const float& dt)
{
	if (this->keyTime < this->keyTimeMax)
		this->keyTime += 50.f * dt;
}

void CardMenu::update(const sf::Vector2i& mousePosWindow, const float& dt)
{
	this->firstAbility1->update(mousePosWindow);
	this->updateKeyTime(dt);

	if (this->card->isChoice)
		this->firstAbility2->update(mousePosWindow);
	if (this->card->isFriend)
		this->friendAbility->update(mousePosWindow);
	if (this->card->isDestroy)
		this->destroyAbility->update(mousePosWindow);

	bool isPressed = false;

	if (firstAbility1->isPressed() && getKeyTime())
	{
		this->FirstAbility1Pressed = true;
		isActive = false;
		isPressed = true;
	}
	else if (this->card->isChoice)
	{
		if (this->firstAbility2->isPressed() && getKeyTime())
		{
			this->FirstAbility2Pressed = true;
			isActive = false;
			isPressed = true;
		}
	}
	else if (this->card->isFriend)
	{
		if (this->friendAbility->isPressed() && getKeyTime())
		{
			this->FriendAbilityPressed = true;
			isActive = false;
			isPressed = true;
		}
	}
	else if (this->card->isDestroy)
	{
		if (this->destroyAbility->isPressed() && getKeyTime())
		{
			this->DestroyAbilityPressed = true;
			isActive = false;
			isPressed = true;
		}
	}
		

	/*если не туда тыкнул*/
	if (this->getActive() && sf::Mouse::isButtonPressed(sf::Mouse::Left) && !isPressed && this->getKeyTime())
		this->isActive = false;
}

void CardMenu::render(sf::RenderTarget& target)
{
	firstAbility1->render(target);
	if (this->card->isChoice)
		firstAbility2->render(target);
	if (this->card->isFriend)
		friendAbility->render(target);
	if (this->card->isDestroy)
		destroyAbility->render(target);
}
