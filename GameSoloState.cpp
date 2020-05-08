#include "pch.h"
#include "GameSoloState.h"

void GameSoloState::initBG(int var)
{
	this->background.setSize(sf::Vector2f(static_cast<float>(this->window->getSize().x),
		static_cast<float>(this->window->getSize().y)));
	if (var == 1)
	{
		if (!this->bgTexture.loadFromFile("Resources/Images/Backgrounds/bgWin.jpeg"))
		{
			throw "ERROR::FAILED_LOAD_BACKGROUND";
		}
	}
	else
	{
		if (!this->bgTexture.loadFromFile("Resources/Images/Backgrounds/bgLose.jpeg"))
		{
			throw "ERROR::FAILED_LOAD_BACKGROUND";
		}
	}
	
	this->background.setTexture(&this->bgTexture);
}

void GameSoloState::initButton()
{
	this->done = new gui::Button
	(
		1700.f, 1080.f - 150.f,
		200.f, 65.f, &font,
		"DONE", 25, 
		sf::Color(0, 0, 0, 255),
		sf::Color(250, 250, 250, 250),
		sf::Color(20, 20, 20, 50),

		sf::Color(70, 70, 70, 0),
		sf::Color(150, 150, 150, 0),
		sf::Color(20, 20, 20, 0)
	);
}

void GameSoloState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Dosis-Light.ttf"))
	{
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
	}
}

void GameSoloState::initCards()
{
	this->textureCards.loadFromFile("Resources/Images/Sprites/cards.png");
	this->textureBoss.loadFromFile("Resources/Images/Sprites/boss.png");
	this->playerHp = 50;
	this->bossHp = 30;
	this->playerMoney = 0;

	this->cardMenu = nullptr;
	this->cardMarketMenu = nullptr;
	this->cardResearcherMenu = nullptr;

	this->isFree = false;

	this->isPlayerAttack = true;

	this->boss.setSize(sf::Vector2f(CardHeight, CardWidth));
	this->boss.setTexture(&textureBoss);
	this->boss.setFillColor(sf::Color::White);
	this->boss.setOutlineThickness(1.f);
	this->boss.setOutlineColor(sf::Color::White);
	this->boss.setPosition(1920.f / 2 - CardHeight / 2, 10.f);

	this->backCard1.setSize(sf::Vector2f(CardWidth, CardHeight));
	this->backCard1.setFillColor(sf::Color::White);
	this->backCard1.setOutlineThickness(1.f);
	this->backCard1.setOutlineColor(sf::Color::White);
	this->backCard1.setTexture(&textureCards);
	this->backCard1.setTextureRect(sf::IntRect(0, 0, CardWidth, CardHeight));

	this->backCard2 = backCard1;
	this->backCard2.setPosition(1410.f, 1080.f - 380.f); /*отображение колоды игрока*/

	/*текст, игрок*/
	this->textPlayerHp.setFont(this->font);
	this->textPlayerHp.setFillColor(sf::Color::White);
	this->textPlayerHp.setCharacterSize(25);
	this->textPlayerHp.setPosition(1700.f, 1080.f - 350.f);

	this->textPlayerDrop.setFont(this->font);
	this->textPlayerDrop.setFillColor(sf::Color::White);
	this->textPlayerDrop.setCharacterSize(25);
	this->textPlayerDrop.setPosition(1700.f, 1080.f - 300.f);

	this->textPlayerDeck.setFont(this->font);
	this->textPlayerDeck.setFillColor(sf::Color::White);
	this->textPlayerDeck.setCharacterSize(25);
	this->textPlayerDeck.setPosition(1700.f, 1080.f - 250.f);

	this->textPlayerMoney.setFont(this->font);
	this->textPlayerMoney.setFillColor(sf::Color::White);
	this->textPlayerMoney.setCharacterSize(25);
	this->textPlayerMoney.setPosition(1700.f, 1080.f - 200.f);
	
	/*торговая площадка*/
	this->textMarketDeck.setFont(this->font);
	this->textMarketDeck.setFillColor(sf::Color::White);
	this->textMarketDeck.setCharacterSize(25);
	this->textMarketDeck.setPosition(1700.f, 1080.f - 750.f);

	this->textResearcher.setFont(this->font);
	this->textResearcher.setFillColor(sf::Color::White);
	this->textResearcher.setCharacterSize(25);
	this->textResearcher.setPosition(1700.f, 1080.f - 700.f);

	this->textTrash.setFont(this->font);
	this->textTrash.setFillColor(sf::Color::White);
	this->textTrash.setCharacterSize(25);
	this->textTrash.setPosition(1700.f, 1080.f - 650.f);

	/*босс*/
	this->textBossHp.setFont(this->font);
	this->textBossHp.setFillColor(sf::Color::White);
	this->textBossHp.setCharacterSize(25);
	this->textBossHp.setPosition(1700.f, 70.f);

	this->textBossDamage.setFont(this->font);
	this->textBossDamage.setFillColor(sf::Color::White);
	this->textBossDamage.setCharacterSize(25);
	this->textBossDamage.setPosition(1700.f, 120.f);

	std::ifstream ifs("Config/cards.ini");

	std::vector<Card*> temp;

	if (ifs.is_open())
	{
		int var;
		int fractionType, shipType, cost, id;
		int name;
		bool isChoice, isFriend, isDestroy;
		std::map<int, int> firstAbility;
		std::map<int, int> friendAbility;
		std::map<int, int> destroyAbility;
		int first, last;

		ifs >> var;

		for (int i = 0; i < var; i++)
		{
			firstAbility.clear();
			friendAbility.clear();
			destroyAbility.clear();
			fractionType = shipType = cost = id = 0;
			isChoice = isFriend = isDestroy = name = first = last = 0;

			ifs >> id >> fractionType >> shipType >> cost;
			ifs >> name;
			ifs >> isChoice >> isFriend >> isDestroy; 
			ifs >> first >> last;
			firstAbility[first] = last;

			if (isChoice)
			{
				ifs >> first >> last;
				firstAbility[first] = last;
			}
			if (isFriend)
			{
				ifs >> first >> last;
				friendAbility[first] = last;
			}
			if (isDestroy)
			{
				ifs >> first >> last;
				destroyAbility[first] = last;
			}

			temp.push_back(new Card(id, textureCards, fractionType, shipType, cost, name, isChoice, isFriend, isDestroy, firstAbility, friendAbility, destroyAbility));
		}

		/*колода игрока, рука игрока*/
		std::vector<Card*> tempDeck;
		for (int i = 0; i < 10; i++)
		{
			tempDeck.push_back(temp[i]);
		}
		randVector(tempDeck);
		for (int i = 0; i < 10; i++)
		{
			playerDeck.push(tempDeck[i]);
		}
		for (int i = 0; i < 3; i++)
		{
			playerHand.push_back(playerDeck.top()); /*добавление элемента из стэка*/
			playerDeck.pop(); /*удаление элемента из стека*/
		}
		tempDeck.clear();

		/*ряд разведчиков*/
		for (int i = 10; i < 20; i++)
		{
			tempDeck.push_back(temp[i]);
		}
		randVector(tempDeck);
		for (int i = 0; i < 10; i++)
		{
			researcherDeck.push(tempDeck[i]);
		}
		tempDeck.clear();

		/*торговый ряд, торговая линия*/
		for (int i = 20; i < temp.size(); i++)
		{
			tempDeck.push_back(temp[i]);
		}
		randVector(tempDeck);
		for (int i = 0; i < temp.size() - 20; i++)
		{
			marketDeck.push(tempDeck[i]);
		}
		for (int i = 0; i < 5; i++)
		{
			marketLine.push_back(marketDeck.top());
			marketDeck.pop();
		}
		tempDeck.clear();
	}
	else
	{
		std::cout << "Ошибка при вводе значений карт";
	}



	ifs.close();
}

void GameSoloState::initKeybinds()
{
	std::ifstream ifs("Config/gamesolostate_keybinds.ini");

	if (ifs.is_open())
	{
		std::string key = "";
		std::string key2 = "";
		while (ifs >> key >> key2)
		{
			this->keybinds[key] = this->supportedKeys->at(key2);
		}
	}

	ifs.close();
}

bool GameSoloState::handAdd(int count)
{
	int tempSize = playerHand.size() + count;
	if (tempSize >= 5) tempSize = 5;
	if (playerHand.size() < 5)
	{
		while (playerDeck.size() && playerHand.size() != tempSize)
		{
			playerHand.push_back(playerDeck.top());
			playerDeck.pop();
		}

		/*если колода закончилась, а в руке меньше карт*/
		if (playerHand.size() < 5 && playerDrop.size() != 0)
		{
			std::vector<Card*> temp; /*заполнение из сброса*/
			while (playerDrop.size())
			{
				temp.push_back(playerDrop.top());
				playerDrop.pop();
			}
			randVector(temp);
			for (int i = 0; i < temp.size(); i++)
			{
				playerDeck.push(temp[i]); /*засовываем сброс в колоду*/
			}
			while (playerDeck.size() && playerHand.size() != tempSize)  /*из колоды в руку*/
			{
				playerHand.push_back(playerDeck.top());
				playerDeck.pop();
			}
		}
		else
			return true;
	}
	return false;
}

void GameSoloState::cardInDrop(const Card* tmp)
{
	for (int i = 0; i < this->playerHand.size(); i++)
	{
		if (this->playerHand[i] == tmp)
		{
			this->playerDrop.push(this->playerHand[i]);
			for (int j = i + 1; j < this->playerHand.size(); j++)
			{
				this->playerHand[j - 1] = this->playerHand[j];
			}
			this->playerHand.pop_back();
			break;
		}
	}
}

GameSoloState::GameSoloState(StateData* state_data)
	:State(state_data)
{
	this->initFonts();
	this->initCards();
	this->initKeybinds();
	this->initButton();

	this->downLayer = new DownLayer();
	this->isEnd = false;
}

GameSoloState::~GameSoloState()
{
	delete this->downLayer;
	delete this->done;

	if (this->cardMenu != nullptr)
		delete this->cardMenu;
	if (this->cardMarketMenu != nullptr)
		delete this->cardMarketMenu;
	if (this->cardResearcherMenu != nullptr)
		delete this->cardResearcherMenu;

	while (!this->playerDeck.empty())
	{
		delete this->playerDeck.top();
		this->playerDeck.pop();
	}
	while (!this->playerDrop.empty())
	{
		delete this->playerDrop.top();
		this->playerDrop.pop();
	}
	while (!this->researcherDeck.empty())
	{
		delete this->researcherDeck.top();
		this->researcherDeck.pop();
	}
	while (!this->marketDeck.empty())
	{
		delete this->marketDeck.top();
		this->marketDeck.pop();
	}

	for (int i = 0; i < this->playerHand.size(); i++)
	{
		delete this->playerHand[i];
	}
	this->playerHand.clear();
	for (int i = 0; i < this->marketLine.size(); i++)
	{
		delete this->marketLine[i];
	}
	this->marketLine.clear();
	for (int i = 0; i < this->trash.size(); i++)
	{
		delete this->trash[i];
	}
	this->trash.clear();

}

void GameSoloState::updateText()
{
	this->textPlayerHp.setString("HP: " + std::to_string(this->playerHp));
	this->textPlayerDrop.setString("CARD IN DROP: " + std::to_string(this->playerDrop.size()));
	this->textPlayerDeck.setString("CARD IN DECK: " + std::to_string(this->playerDeck.size()));
	this->textPlayerMoney.setString("MONEY: " + std::to_string(this->playerMoney));


	this->textMarketDeck.setString("CARD IN DECK: " + std::to_string(this->marketDeck.size()));
	this->textResearcher.setString("CARD OF RES.: " + std::to_string(this->researcherDeck.size()));
	this->textTrash.setString("CARD IN TRASH: " + std::to_string(this->trash.size()));


	this->textBossHp.setString("HP: " + std::to_string(this->bossHp));
	this->textBossDamage.setString("Damage: " + std::to_string(this->counterCardBoss));
}

void GameSoloState::updateInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))) && this->isEnd)
	{
		this->quit = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))))
	{
		this->quit = true;
	}
}

void GameSoloState::updatePlayerAttack()
{
	for (auto it : this->playerHand)
	{
		if (it->shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWindow)))
		{
			//pressed
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->cardMenu == nullptr && this->getKeyTime())
			{
				this->cardMenu = new CardMenu(it, font);
			}
		}
	}
	for (auto it : this->marketLine)
	{
		if (it->shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWindow)))
		{
			//pressed
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->cardMarketMenu == nullptr && this->getKeyTime())
			{
				this->cardMarketMenu = new CardMarketMenu(it, font);
			}
		}
	}
	if (!researcherDeck.empty() && researcherDeck.top()->shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWindow)))
	{
		//pressed
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->cardResearcherMenu == nullptr && this->getKeyTime())
		{
			this->cardResearcherMenu = new CardMarketMenu(researcherDeck.top(), font);
		}
	}
	if (this->cardMenu != nullptr && !(this->cardMenu->getActive()))
	{
		/*обработка если нажата кнопка*/
		bool isDelete = true; /*нужно ли удалять*/

		/*если нажата кнопка  первичного свойства*/
		if (this->cardMenu->isFirstAbility1Pressed())
		{
			int type = this->cardMenu->getCard()->firstAbility.begin()->first;
			int value = this->cardMenu->getCard()->firstAbility.begin()->second;
			int value1 = 0;
			switch (type)
			{
				case 0: 
					this->playerMoney += value;
					break;
				case 1:
					this->bossHp -= value;
					if (this->bossHp < 0) this->bossHp = 0;
					break;
				case 2:
					this->playerHp += value;
					break;
				case 5:
					this->playerMoney += value;
					break;
				case 6:
					this->bossHp -= value;
					if (this->bossHp < 0) this->bossHp = 0;
					break;
				case 7:
					this->playerHp += value;
					handAdd(1); /*взять карту*/
					break;
				case 8:
					this->bossHp -= value;
					if (this->bossHp < 0) this->bossHp = 0;
					this->counterCardBoss--;
					if (this->counterCardBoss < 0) this->counterCardBoss = 0;
					break;
				case 9:
					this->bossHp -= value;
					if (this->bossHp < 0) this->bossHp = 0;
					/*вставить удаление из торговой линии*/
					break;
				case 10:
					this->bossHp -= value;
					if (this->bossHp < 0) this->bossHp = 0;
					handAdd(1); /*взять карту*/
					break;
				case 11:
					this->bossHp -= value;
					if (this->bossHp < 0) this->bossHp = 0;
					if (this->cardMenu->getCard()->name == "Торговый конвой")
					{
						this->playerHp += 4;
					}
					break;
				case 12:
					this->bossHp -= value;
					if (this->bossHp < 0) this->bossHp = 0;
					this->playerHp += 4;
					handAdd(2);
					break;
				case 13:
					handAdd(1);
					break;
				case 14:
					this->counterCardBoss--;
					if (this->counterCardBoss < 0) this->counterCardBoss = 0;
					break;
				case 15:
					this->isFree = true;
					break;
				case 17:
					if (this->cardMenu->getCard()->name == "Резак")
					{
						this->playerMoney += 2;
						this->playerHp += 4;
					}
					if (this->cardMenu->getCard()->name == "Посольская яхта")
					{
						this->playerMoney += 2;
						this->playerHp += 3;
					}
					break;
			default:
				isDelete = false;
				break;
			}
			/*засовывание карты в сброс*/
			cardInDrop(this->cardMenu->getCard());
		}
		/*если нажата кнопка 2 первичного свойства*/
		else if (this->cardMenu->isFirstAbility2Pressed())
		{
			auto it = ++this->cardMenu->getCard()->firstAbility.begin();
			int type = it->first;
			int value = it->second;
			int value1 = 0;
			switch (type)
			{
			case 0:
				this->playerMoney += value;
				break;
			case 1:
				this->bossHp -= value;
				if (this->bossHp < 0) this->bossHp = 0;
				break;
			case 2:
				this->playerHp += value;
				break;
			case 5:
				this->playerMoney += value;
				break;
			case 6:
				this->bossHp -= value;
				if (this->bossHp < 0) this->bossHp = 0;
				break;
			case 7:
				this->playerHp += value;
				handAdd(1); /*взять карту*/
				break;
			case 8:
				this->bossHp -= value;
				if (this->bossHp < 0) this->bossHp = 0;
				this->counterCardBoss--;
				if (this->counterCardBoss < 0) this->counterCardBoss = 0;
				break;
			case 9:
				this->bossHp -= value;
				if (this->bossHp < 0) this->bossHp = 0;
				/*вставить удаление из торговой линии*/
				break;
			case 10:
				this->bossHp -= value;
				if (this->bossHp < 0) this->bossHp = 0;
				handAdd(1); /*взять карту*/
				break;
			case 11:
				this->bossHp -= value;
				if (this->bossHp < 0) this->bossHp = 0;
				if (this->cardMenu->getCard()->name == "Торговый конвой")
				{
					this->playerHp += 4;
				}
				break;
			case 12:
				this->bossHp -= value;
				if (this->bossHp < 0) this->bossHp = 0;
				this->playerHp += 4;
				handAdd(2);
				break;
			case 13:
				handAdd(1);
				break;
			case 14:
				this->counterCardBoss--;
				if (this->counterCardBoss < 0) this->counterCardBoss = 0;
				break;
			case 15:
				this->isFree = true;
				break;
			case 17:
				if (this->cardMenu->getCard()->name == "Резак")
				{
					this->playerMoney += 2;
					this->playerHp += 4;
				}
				if (this->cardMenu->getCard()->name == "Посольская яхта")
				{
					this->playerMoney += 2;
					this->playerHp += 3;
				}
				break;
			default:
				isDelete = false;
				break;
			}
			/*засовывание карты в сброс*/
			cardInDrop(this->cardMenu->getCard());
		}
		/*если нажата кнопка союзного свойства*/
		else if (this->cardMenu->isFriendAbilityPressed())
		{
			isDelete = false;
			for (int i = 0; i < this->playerHand.size(); i++)
			{
				if (this->playerHand[i] == this->cardMenu->getCard() || this->playerHand[i]->fractionType == 4)
					continue;
				if (this->playerHand[i]->fractionType == this->cardMenu->getCard()->fractionType)
					isDelete = true;
			}
			if (isDelete)
			{
				int type = this->cardMenu->getCard()->friendAbility.begin()->first;
				int value = this->cardMenu->getCard()->friendAbility.begin()->second;
				int value1 = 0;
				switch (type)
				{
				case 0:
					this->playerMoney += value;
					break;
				case 1:
					this->bossHp -= value;
					if (this->bossHp < 0) this->bossHp = 0;
					break;
				case 2:
					this->playerHp += value;
					break;
				case 5:
					this->playerMoney += value;
					break;
				case 6:
					this->bossHp -= value;
					if (this->bossHp < 0) this->bossHp = 0;
					break;
				case 7:
					this->playerHp += value;
					handAdd(1); /*взять карту*/
					break;
				case 8:
					this->bossHp -= value;
					if (this->bossHp < 0) this->bossHp = 0;
					this->counterCardBoss--;
					if (this->counterCardBoss < 0) this->counterCardBoss = 0;
					break;
				case 9:
					this->bossHp -= value;
					if (this->bossHp < 0) this->bossHp = 0;
					/*вставить удаление из торговой линии*/
					break;
				case 10:
					this->bossHp -= value;
					if (this->bossHp < 0) this->bossHp = 0;
					handAdd(1); /*взять карту*/
					break;
				case 11:
					this->bossHp -= value;
					if (this->bossHp < 0) this->bossHp = 0;
					if (this->cardMenu->getCard()->name == "Торговый конвой")
					{
						this->playerHp += 4;
					}
					break;
				case 12:
					this->bossHp -= value;
					if (this->bossHp < 0) this->bossHp = 0;
					this->playerHp += 4;
					handAdd(2);
					break;
				case 13:
					handAdd(1);
					break;
				case 14:
					this->counterCardBoss--;
					if (this->counterCardBoss < 0) this->counterCardBoss = 0;
					break;
				case 15:
					this->isFree = true;
					break;
				case 17:
					if (this->cardMenu->getCard()->name == "Резак")
					{
						this->playerMoney += 2;
						this->playerHp += 4;
					}
					if (this->cardMenu->getCard()->name == "Посольская яхта")
					{
						this->playerMoney += 2;
						this->playerHp += 3;
					}
					break;
				default:
					isDelete = false;
					break;
				}
				/*засовывание карты в сброс*/
				cardInDrop(this->cardMenu->getCard());
			}
			else
			{
				this->cardMenu->setActive(false);
			}
			
		}
		/*если нажата кнопка уничтожить*/
		else if (this->cardMenu->isDestroyAbilityPressed())
		{
			int type = this->cardMenu->getCard()->destroyAbility.begin()->first;
			int value = this->cardMenu->getCard()->destroyAbility.begin()->second;
			int value1 = 0;
			switch (type)
			{
			case 0:
				this->playerMoney += value;
				break;
			case 1:
				this->bossHp -= value;
				if (this->bossHp < 0) this->bossHp = 0;
				break;
			case 2:
				this->playerHp += value;
				break;
			case 5:
				this->playerMoney += value;
				break;
			case 6:
				this->bossHp -= value;
				if (this->bossHp < 0) this->bossHp = 0;
				break;
			case 7:
				this->playerHp += value;
				handAdd(1); /*взять карту*/
				break;
			case 8:
				this->bossHp -= value;
				if (this->bossHp < 0) this->bossHp = 0;
				this->counterCardBoss--;
				if (this->counterCardBoss < 0) this->counterCardBoss = 0;
				break;
			case 9:
				this->bossHp -= value;
				if (this->bossHp < 0) this->bossHp = 0;
				/*вставить удаление из торговой линии*/
				break;
			case 10:
				this->bossHp -= value;
				if (this->bossHp < 0) this->bossHp = 0;
				handAdd(1); /*взять карту*/
				break;
			case 11:
				this->bossHp -= value;
				if (this->bossHp < 0) this->bossHp = 0;
				if (this->cardMenu->getCard()->name == "Торговый конвой")
				{
					this->playerHp += 4;
				}
				break;
			case 12:
				this->bossHp -= value;
				if (this->bossHp < 0) this->bossHp = 0;
				this->playerHp += 4;
				handAdd(2);
				break;
			case 13:
				handAdd(1);
				break;
			case 14:
				this->counterCardBoss--;
				if (this->counterCardBoss < 0) this->counterCardBoss = 0;
				break;
			case 15:
				this->isFree = true;
				break;
			case 17:
				if (this->cardMenu->getCard()->name == "Резак")
				{
					this->playerMoney += 2;
					this->playerHp += 4;
				}
				if (this->cardMenu->getCard()->name == "Посольская яхта")
				{
					this->playerMoney += 2;
					this->playerHp += 3;
				}
				break;
			default:
				isDelete = false;
				break;
			}

			/*засовывание карты в trash*/
			for (int i = 0; i < this->playerHand.size(); i++)
			{
				if (this->playerHand[i] == this->cardMenu->getCard())
				{
					this->trash.push_back(this->playerHand[i]);
					for (int j = i + 1; j < this->playerHand.size(); j++)
					{
						this->playerHand[j - 1] = this->playerHand[j];
					}
					this->playerHand.pop_back();
					break;
				}
			}
		}

		if (isDelete) /*удалять ли*/
		{
			delete this->cardMenu;
			this->cardMenu = nullptr;
		}
	}
	else if (this->cardMarketMenu != nullptr && !(this->cardMarketMenu->getActive()))
	{
		/*обработка если нажата кнопка*/
		bool isDelete = true; /*нужно ли удалять*/

		if (this->cardMarketMenu->buyPressed())
		{
			if (this->isFree)
			{
				for (int i = 0; i < this->marketLine.size(); i++)
				{
					if (this->marketLine[i] == this->cardMarketMenu->getCard())
					{
						this->playerDrop.push(this->marketLine[i]);
						for (int j = i + 1; j < this->marketLine.size(); j++)
						{
							this->marketLine[j - 1] = this->marketLine[j];
						}
						
						this->marketLine.pop_back();
						break;
					}
				}
				this->isFree = false;
			}
			else
			{
				if (this->playerMoney >= this->cardMarketMenu->getCard()->cost)
				{
					for (int i = 0; i < this->marketLine.size(); i++)
					{
						if (this->marketLine[i] == this->cardMarketMenu->getCard())
						{
							this->playerDrop.push(this->marketLine[i]);
							for (int j = i + 1; j < this->marketLine.size(); j++)
							{
								this->marketLine[j - 1] = this->marketLine[j];
							}
							
							this->marketLine.pop_back();
							break;
						}
					}
					this->playerMoney -= this->cardMarketMenu->getCard()->cost;
				}
				else
				{
					isDelete = false;
				}
			}
		}


		if (isDelete) /*удалять ли*/
		{
			delete this->cardMarketMenu;
			this->cardMarketMenu = nullptr;
		}
	}
	else if (this->cardResearcherMenu != nullptr && !(this->cardResearcherMenu->getActive()))
	{
		/*обработка если нажата кнопка*/
		bool isDelete = true; /*нужно ли удалять*/
		

		if (this->cardResearcherMenu->buyPressed())
		{
			if (this->isFree)
			{
				this->playerDrop.push(this->researcherDeck.top());

				this->researcherDeck.pop();

				this->isFree = false;
			}
			else
			{
				if (this->playerMoney >= this->cardResearcherMenu->getCard()->cost)
				{
					this->playerDrop.push(this->researcherDeck.top());
					this->researcherDeck.pop();

					this->playerMoney -= this->cardResearcherMenu->getCard()->cost;
				}
			}
		}


		if (isDelete) /*удалять ли*/
		{
			delete this->cardResearcherMenu;
			this->cardResearcherMenu = nullptr;
		}
	}
}

void GameSoloState::updateBossAttack()
{
	if (!this->marketLine.empty())
	{
		delete marketLine[0];
		marketLine[0] = nullptr;
		for (int i = 1; i < marketLine.size(); i++)
		{
			this->marketLine[i - 1] = this->marketLine[i];
		}
		marketLine.pop_back();
		if (!this->marketDeck.empty())
		{
			this->marketLine.push_back(marketDeck.top());
			this->marketDeck.pop();
		}
		counterCardBoss++;
	}
	/*сделать вызов окна о том, сколько урона босс нанес*/
	this->playerHp -= counterCardBoss;
	if (this->playerHp < 0) 
		this->playerHp = 0;
}

void GameSoloState::updateButtons()
{
	this->done->update(this->mousePosWindow);

	if (this->done->isPressed() && this->getKeyTime())
	{
		this->isFree = false;
		this->isPlayerAttack = false;

		/*заполнение руки игрока*/
		if (playerHand.size() < 5)
		{
			while (playerDeck.size() && playerHand.size() != 5)
			{
				playerHand.push_back(playerDeck.top());
				playerDeck.pop();
			}

			/*если колода закончилась, а в руке меньше пяти карт*/
			if (playerHand.size() < 5 && playerDrop.size() != 0)
			{
				std::vector<Card*> temp; /*заполнение из сброса*/
				while (playerDrop.size())
				{
					temp.push_back(playerDrop.top());
					playerDrop.pop();
				}
				randVector(temp);
				for (int i = 0; i < temp.size(); i++)
				{
					playerDeck.push(temp[i]); /*засовываем сброс в колоду*/
				}
				while (playerDeck.size() && playerHand.size() != 5)  /*из колоды в руку*/
				{
					playerHand.push_back(playerDeck.top());
					playerDeck.pop();
				}
			}
			else if (!playerHand.size())
			{
				quit = true;
			}
		}
		/*заполнение торговой линии*/
		if (marketLine.size() < 5)
		{
			while (marketDeck.size() && marketLine.size() != 5)
			{
				marketLine.push_back(marketDeck.top());
				marketDeck.pop();
			}
		}
	}
}

void GameSoloState::update(const float& dt)
{
	this->updateInput(dt);
	this->updateKeyTime(dt);

	if (playerHp > 0 && bossHp > 0)
	{
		this->updateMousePositions();
		this->updateText();
		this->updateButtons();

		if (this->isPlayerAttack)
		{
			this->updatePlayerAttack();

			if (this->cardMenu != nullptr)
			{
				this->cardMenu->update(mousePosWindow, dt);
				this->keyTime = cardMenu->getkeyTimeFloat();
			}
			if (this->cardMarketMenu != nullptr)
			{
				this->cardMarketMenu->update(mousePosWindow, dt);
				this->keyTime = cardMarketMenu->getkeyTimeFloat();
			}
			if (this->cardResearcherMenu != nullptr)
			{
				this->cardResearcherMenu->update(mousePosWindow, dt);
				this->keyTime = cardResearcherMenu->getkeyTimeFloat();
			}
		}
		else
		{
			this->playerMoney = 0;
			updateBossAttack();
			this->isPlayerAttack = true;
		}
	}
	else
	{
		this->isEnd = true;
		if (playerHp == 0)
		{
			this->initBG(2);
		}
		else
		{
			this->initBG(1);
		}
	}
}

void GameSoloState::renderPlayerHand(sf::RenderTarget* target)
{
	for (int i = 0; i < playerHand.size(); i++)
	{
		if (this->playerHand[i] != nullptr)
		{
			playerHand[i]->setPosition(10.f + i * 280, 1080.f - 380.f);
			playerHand[i]->render(*target);
		}
	}
}

void GameSoloState::renderPlayerDeck(sf::RenderTarget* target)
{
	if (!playerDeck.empty())
	{
		target->draw(backCard2);
	}
		
}

void GameSoloState::renderResearcherDeck(sf::RenderTarget* target)
{
	if (!researcherDeck.empty())
	{
		researcherDeck.top()->setPosition(10.f, 1080.f - 2.f * 390.f);
		researcherDeck.top()->render(*target);
	}
}

void GameSoloState::renderMarketLine(sf::RenderTarget* target)
{
	for (int i = 0; i < this->marketLine.size(); i++)
	{
		if (this->marketLine[i] != nullptr)
		{
			this->marketLine[i]->setPosition(290.f + i * 280.f, 1080 - 2.f * 390.f);
			this->marketLine[i]->render(*target);
		}
	}
}

void GameSoloState::renderBoss(sf::RenderTarget* target)
{
	target->draw(this->boss);
}

void GameSoloState::renderButton(sf::RenderTarget* target)
{
	this->done->render(*target);
}

void GameSoloState::renderText(sf::RenderTarget* target)
{
	target->draw(textPlayerHp);
	target->draw(textPlayerDrop);
	target->draw(textPlayerDeck);
	target->draw(textPlayerMoney);

	target->draw(textMarketDeck);
	target->draw(textResearcher);
	target->draw(textTrash);

	target->draw(textBossHp);
	target->draw(textBossDamage);
}

void GameSoloState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	if (!this->isEnd)
	{
		this->downLayer->render(*target); /*отрисовка поля*/
		this->renderButton(target);       /*отрисовка кнопки*/

		this->renderPlayerHand(target);   /*отрисовка руки*/
		this->renderPlayerDeck(target);   /*отрисовка колоды*/
		this->renderResearcherDeck(target); /*отрисовка колоды разведчиков*/
		this->renderMarketLine(target);     /*отрисовка торговой линии*/

		this->renderBoss(target);

		this->renderText(target);

		if (this->cardMenu != nullptr)
			this->cardMenu->render(*target);
		if (this->cardMarketMenu != nullptr)
			this->cardMarketMenu->render(*target);
		if (this->cardResearcherMenu != nullptr)
			this->cardResearcherMenu->render(*target);
	}
	else
	{
		target->draw(background);
	}
}

void randVector(std::vector<Card*>& temp)
{
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	shuffle(temp.begin(), temp.end(), std::default_random_engine(seed));
}
