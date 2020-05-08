#pragma once

#include "card.h"
#include "Gui.h"

class CardMarketMenu
{
private:
	Card* card;
	bool isActive;

	gui::Button* buy;
	bool BuyPressed;

	float keyTime;
	float keyTimeMax;

public:
	CardMarketMenu();
	CardMarketMenu(Card* card, sf::Font& font);
	~CardMarketMenu();

	/*accessors*/
	const bool getPress() const;
	const bool getActive() const;
	const bool buyPressed() const;
	const float getkeyTimeFloat();
	const bool getKeyTime();
	Card* getCard();

	void setActive(bool isActive);

	/*func*/
	void updateKeyTime(const float& dt);
	void update(const sf::Vector2i& mousePosWindow, const float& dt);

	void render(sf::RenderTarget& target);
};


class CardMenu
{
private:
	Card* card;
	bool isActive;

	gui::Button* firstAbility1;
	bool FirstAbility1Pressed;

	gui::Button* firstAbility2;
	bool FirstAbility2Pressed;

	gui::Button* friendAbility;
	bool FriendAbilityPressed;

	gui::Button* destroyAbility;
	bool DestroyAbilityPressed;


	float keyTime;
	float keyTimeMax;

public:
	CardMenu();
	CardMenu(Card* card, sf::Font& font);
	~CardMenu();

	/*accessors*/
	const bool getPress() const;
	const bool getActive() const;
	const bool isFirstAbility1Pressed() const;
	const bool isFirstAbility2Pressed() const;
	const bool isFriendAbilityPressed() const;
	const bool isDestroyAbilityPressed() const;
	const float getkeyTimeFloat();
	const bool getKeyTime();
	const Card* getCard();

	void setActive(bool isActive);

	/*func*/
	void updateKeyTime(const float& dt);
	void update(const sf::Vector2i& mousePosWindow, const float& dt);

	void render(sf::RenderTarget& target);
};

