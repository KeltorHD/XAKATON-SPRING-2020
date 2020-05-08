#ifndef GAMESOLOSTATE_H

#include "cardMenu.h"
#include "downLayer.h"
#include "State.h"
#include "Gui.h"

/*TO-DO Очищение памяти!!!*/

class GameSoloState :
	public State
{
private:
	bool isEnd;
	sf::Texture bgTexture;
	sf::RectangleShape background;

	sf::Texture textureCards;
	sf::Texture textureBoss;          /*карта цена свободы*/
	DownLayer* downLayer;

	CardMenu* cardMenu;               /*само меню карты, лол*/
	CardMarketMenu* cardMarketMenu;   /*само меню маркета, лол*/
	CardMarketMenu* cardResearcherMenu;   /*само меню маркета, лол*/

	sf::Font font;

	gui::Button* done;                 /*кнопка перехода хода*/

	sf::RectangleShape backCard1, backCard2;   /*рубашка карт*/

	std::vector<Card*> playerHand;    /*карты в руке*/
	std::stack<Card*> playerDrop;     /*карты в сбросе*/
	std::stack<Card*> playerDeck;     /*карты в колоде*/
	int playerHp;                     /*влияние игрока*/
	int playerMoney;                  /*деньги игрока*/
	sf::Text textPlayerHp;            /*влияние игрока - текст*/
	sf::Text textPlayerMoney;         /*деньги игрока - текст*/
	sf::Text textPlayerDrop;          /*количество карт в сбросе*/
	sf::Text textPlayerDeck;          /*количество карт в колоде*/

	std::stack<Card*> researcherDeck; /*карты исследователей, 10 шт*/
	std::stack<Card*> marketDeck;     /*карты в торговой колоде*/
	std::vector<Card*> marketLine;    /*торговый ряд*/
	std::vector<Card*> trash;         /*утиль*/
	sf::Text textTrash;               /*количество удаленнных карт*/
	sf::Text textResearcher;          /*количество карт исследователей*/
	sf::Text textMarketDeck;          /*количество карт в торговой колоде*/
	
	int counterCardBoss;              /*количество карт у босса*/
	int bossHp;                       /*влияние босса*/
	sf::RectangleShape boss;          /*прямоугольник с босом*/
	sf::Text textBossDamage;          /*атака босса*/
	sf::Text textBossHp;              /*влияние босса*/

	bool isPlayerAttack;              /*атака ли игрока*/
	bool isFree;                      /*бесплатный корабль и торговой линии*/


	/*func*/
	void initBG(int var);
	void initButton();
	void initFonts();
	void initCards();
	void initKeybinds();

	bool handAdd(int count);          /*взять карту в руку из колоды*/
	void cardInDrop(const Card* tmp); /*засовывание карты в сброс*/

public:
	GameSoloState(StateData* state_data);
	~GameSoloState();

	/*func*/
	void updateText();
	void updateInput(const float& dt);

	void updatePlayerAttack();
	void updateBossAttack();

	void updateButtons();
	void update(const float& dt);

	void renderPlayerHand(sf::RenderTarget* target);
	void renderPlayerDeck(sf::RenderTarget* target);

	void renderResearcherDeck(sf::RenderTarget* target);
	void renderMarketLine(sf::RenderTarget* target);

	void renderBoss(sf::RenderTarget* target);

	void renderButton(sf::RenderTarget* target);
	void renderText(sf::RenderTarget* target);
	void render(sf::RenderTarget* target = NULL);
};

void randVector(std::vector<Card*>& temp);

#endif // !GAMESOLOSTATE_H
