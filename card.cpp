#include "pch.h"
#include "card.h"


std::map<int, std::string> nameCard =
{
	{1, "Разведчик"},
	{2, "Штурмовик"},
	{3, "Скаут"},
	{4, "Торговая колония"},
	{5, "Торговая станция"},
	{6, "Боевая станция"},
	{7, "Космическая станция"},
	{8, "Станция переработки"},
	{9, "Станция слизней"},
	{10, "Грузовой бот"},
	{11, "Ракетный бот"},
	{12, "Торговый бот"},
	{13, "Научный корабль"},
	{14, "Имперский фрегат"},
	{15, "Имперский истребитель"},
	{16, "Шаттл"},
	{17, "Резак"},
	{18, "Слизень-истребитель"},
	{19, "Торговый кокон"},
	{20, "Таран"},
	{21, "Слизень-разрушитель"},
	{22, "Грузовой корабль"},
	{23, "Посольская яхта"},
	{24, "Патрульный космотанк"},
	{25, "Корвет"},
	{26, "Боевой крейсер"},
	{27, "Дредноут"},
	{28, "Боевой слизень"},
	{29, "Слизеносец"},
	{30, "Корабль-матка"},
	{31, "Торговый конвой"},
	{32, "Штабной корабль"},
	{33, "Флагман"},
	{34, "Ракетный космотанк"},
	{35, "Боевой космотанк"},
	{36, "Свалка"},
	{37, "Технобаза"},
	{38, "Техноколония"},
	{39, "Улей"},
	{40, "Колония слизней"},
	{41, "Штаб флота"},
	{42, "Имперская цитадель"},
	{43, "Военная колония"},
	{44, "Космопорт"},
	{45, "Защитная станция"},
	{46, "Колючка"},
	{47, "Торговая станция слизей"},
	{48, "Грузовой челнок"},
	{49, "Боевой кокон"}
};

Card::Card()
{
}

Card::Card(int id, const sf::Texture& texture, int fractionType, int shipType, int cost, int name, bool isChoice, bool isFriend, bool isDestroy, std::map<int, int> firstAbility, std::map<int, int> friendAbility, std::map<int, int> destroyAbility)
{
	this->fractionType = fractionType;
	this->shipType = shipType;
	this->cost = cost;
	this->name = nameCard[name];
	this->isActive = true;

	this->isChoice = isChoice;
	this->isFriend = isFriend;
	this->isDestroy = isDestroy;

	this->firstAbility = firstAbility;
	this->friendAbility = friendAbility;
	this->destroyAbility = destroyAbility;

	this->shape.setPosition(0, 0);
	this->shape.setSize(sf::Vector2f(CardWidth, CardHeight));
	this->shape.setFillColor(sf::Color::White);
	this->shape.setOutlineThickness(1.f);
	this->shape.setOutlineColor(sf::Color::White);
	this->shape.setTexture(&texture);
	this->shape.setTextureRect(sf::IntRect((id % col) * CardWidth, (id / col) * CardHeight, CardWidth, CardHeight));
}

Card::~Card()
{

}

void Card::setPosition(float x, float y)
{
	this->shape.setPosition(x, y);
}

sf::Vector2f Card::getPosition() const
{
	return shape.getPosition();
}

void Card::render(sf::RenderTarget& target)
{
	if (this != nullptr)
		target.draw(this->shape);
}

