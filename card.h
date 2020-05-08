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
	MONEY = 0,         /*������*/
	DAMAGE,            /*����*/
	HP,                /*��*/
	DROPP2TAKE,        /*����� �� 2-� �� ���� ��� ������ � ����� ������� ��*/
	DELL1,             /*����� ������� �� ���� ����� �� ���� ��� ������*/
	MONEY1DELL,        /*������, ����� ������� �� ���� ����� �� ���� ��� ������*/
	DAMAGE1DELL,       /*����, ����� ������� �� ���� ����� �� ���� ��� ������*/
	MONEY1TAKE,        /*������, ����� �����*/
	DAMAGE1ENEMYDROPP, /*����, ����� ����� ����������*/
	DAMAGEMARKETDROPP, /*����, ������ ������� �� ���� ���� � �����*/
	DAMAGE1TAKE,       /*����, ����� �����*/
	DAMAGEHP,          /*����, �������*/
	DAMAGEHP2TAKE,     /*����, �������, ����� 2 �����*/
	TAKE,              /*����� �����*/
	ENEMYDROPP,        /*����� ����� ����������*/
	MARKETTAKE,        /*������ ����� ������� � ����� � ������ ������ ������*/
	MONEYHP            /*������, ��*/
};


class Card
{
public:
	int fractionType; /*��� �������*/
	int shipType;     /*��� �����*/
	int cost;
	std::string name;
	bool isActive; /*������� �� ����� � ���� ������*/

	sf::RectangleShape shape; /*������������� ��� ��������*/

	bool isChoice; /*���� �� ����� � ��������� ��������*/
	std::map<int, int> firstAbility;   /*�������� ��������*/

	bool isFriend; /*���� �� ������ ��������*/
	std::map<int, int> friendAbility;  /*������� ��������*/

	bool isDestroy;/*����� �� ���������� ����� � ��������� ��������*/
	std::map<int, int> destroyAbility; /*�������� ��� �����������*/

	Card();
	Card(int id, const sf::Texture& texture, int fractionType, int shipType, int cost, int name, bool isChoice, bool isFriend, bool isDestroy, std::map<int, int> firstAbility, std::map<int, int> friendAbility, std::map<int, int> destroyAbility);
	~Card();

	void setPosition(float x, float y);
	sf::Vector2f getPosition() const;

	void render(sf::RenderTarget& target);
};

#endif // !CARD_H
