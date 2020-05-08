#ifndef GAMESOLOSTATE_H

#include "cardMenu.h"
#include "downLayer.h"
#include "State.h"
#include "Gui.h"

/*TO-DO �������� ������!!!*/

class GameSoloState :
	public State
{
private:
	bool isEnd;
	sf::Texture bgTexture;
	sf::RectangleShape background;

	sf::Texture textureCards;
	sf::Texture textureBoss;          /*����� ���� �������*/
	DownLayer* downLayer;

	CardMenu* cardMenu;               /*���� ���� �����, ���*/
	CardMarketMenu* cardMarketMenu;   /*���� ���� �������, ���*/
	CardMarketMenu* cardResearcherMenu;   /*���� ���� �������, ���*/

	sf::Font font;

	gui::Button* done;                 /*������ �������� ����*/

	sf::RectangleShape backCard1, backCard2;   /*������� ����*/

	std::vector<Card*> playerHand;    /*����� � ����*/
	std::stack<Card*> playerDrop;     /*����� � ������*/
	std::stack<Card*> playerDeck;     /*����� � ������*/
	int playerHp;                     /*������� ������*/
	int playerMoney;                  /*������ ������*/
	sf::Text textPlayerHp;            /*������� ������ - �����*/
	sf::Text textPlayerMoney;         /*������ ������ - �����*/
	sf::Text textPlayerDrop;          /*���������� ���� � ������*/
	sf::Text textPlayerDeck;          /*���������� ���� � ������*/

	std::stack<Card*> researcherDeck; /*����� ��������������, 10 ��*/
	std::stack<Card*> marketDeck;     /*����� � �������� ������*/
	std::vector<Card*> marketLine;    /*�������� ���*/
	std::vector<Card*> trash;         /*�����*/
	sf::Text textTrash;               /*���������� ���������� ����*/
	sf::Text textResearcher;          /*���������� ���� ��������������*/
	sf::Text textMarketDeck;          /*���������� ���� � �������� ������*/
	
	int counterCardBoss;              /*���������� ���� � �����*/
	int bossHp;                       /*������� �����*/
	sf::RectangleShape boss;          /*������������� � �����*/
	sf::Text textBossDamage;          /*����� �����*/
	sf::Text textBossHp;              /*������� �����*/

	bool isPlayerAttack;              /*����� �� ������*/
	bool isFree;                      /*���������� ������� � �������� �����*/


	/*func*/
	void initBG(int var);
	void initButton();
	void initFonts();
	void initCards();
	void initKeybinds();

	bool handAdd(int count);          /*����� ����� � ���� �� ������*/
	void cardInDrop(const Card* tmp); /*����������� ����� � �����*/

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
