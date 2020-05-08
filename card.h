#ifndef CARD_H

#define CardWidth 258
#define CardHeight 360
#define col 6

enum class Fraction
{
	EMPIRE = 0, TRADE, SLIME, CULT, NONE
};

enum class SHIP
{
	SHIP = 0, BASE, OUTPOST
};

enum class ABILITY
{
	MONEY = 0,         /*деньги*/
	DAMAGE,            /*урон*/
	HP,                /*хп*/
	DROPP2TAKE,        /*сброс до 2-х из руки или сброса и взять столько же*/
	DELL1,             /*можно удалить из игры карту из руки или сброса*/
	MONEY1DELL,        /*деньги, можно удалить из игры карту из руки или сброса*/
	DAMAGE1DELL,       /*урон, можно удалить из игры карту из руки или сброса*/
	MONEY1TAKE,        /*деньги, взять карту*/
	DAMAGE1ENEMYDROPP, /*урон, сброс карты соперником*/
	DAMAGEMARKETDROPP, /*урон, можешь удалить до неск карт с рынка*/
	DAMAGE1TAKE,       /*урон, взять карту*/
	DAMAGEHP,          /*урон, влияние*/
	DAMAGEHP2TAKE,     /*урон, влияние, взять 2 карты*/
	TAKE,              /*возми карту*/
	ENEMYDROPP,        /*сброс карты соперником*/
	MARKETTAKE,        /*возьми любой корабль с рынка и положи наверх колоды*/
	MONEYHP            /*деньги, хп*/
};


class Card
{
public:
	int fractionType; /*тип фракции*/
	int shipType;     /*тип карты*/
	int cost;
	std::string name;
	bool isActive; /*активна ли карта в руке игрока*/

	sf::RectangleShape shape; /*прямоугольник для карточки*/

	bool isChoice; /*если ли выбор в первичном свойстве*/
	std::map<int, int> firstAbility;   /*перичные свойства*/

	bool isFriend; /*есть ли союное свойство*/
	std::map<int, int> friendAbility;  /*союзные свойства*/

	bool isDestroy;/*можно ли уничтожить карту и выполнить свойство*/
	std::map<int, int> destroyAbility; /*свойство при уничтожении*/

	Card();
	Card(int id, const sf::Texture& texture, int fractionType, int shipType, int cost, int name, bool isChoice, bool isFriend, bool isDestroy, std::map<int, int> firstAbility, std::map<int, int> friendAbility, std::map<int, int> destroyAbility);
	~Card();

	void setPosition(float x, float y);
	sf::Vector2f getPosition() const;

	void render(sf::RenderTarget& target);
};

#endif // !CARD_H
