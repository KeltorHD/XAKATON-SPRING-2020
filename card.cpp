#include "pch.h"
#include "card.h"


std::map<int, std::string> nameCard =
{
	{1, "���������"},
	{2, "���������"},
	{3, "�����"},
	{4, "�������� �������"},
	{5, "�������� �������"},
	{6, "������ �������"},
	{7, "����������� �������"},
	{8, "������� �����������"},
	{9, "������� �������"},
	{10, "�������� ���"},
	{11, "�������� ���"},
	{12, "�������� ���"},
	{13, "������� �������"},
	{14, "��������� ������"},
	{15, "��������� �����������"},
	{16, "�����"},
	{17, "�����"},
	{18, "�������-�����������"},
	{19, "�������� �����"},
	{20, "�����"},
	{21, "�������-�����������"},
	{22, "�������� �������"},
	{23, "���������� ����"},
	{24, "���������� ���������"},
	{25, "������"},
	{26, "������ �������"},
	{27, "��������"},
	{28, "������ �������"},
	{29, "����������"},
	{30, "�������-�����"},
	{31, "�������� ������"},
	{32, "������� �������"},
	{33, "�������"},
	{34, "�������� ���������"},
	{35, "������ ���������"},
	{36, "������"},
	{37, "���������"},
	{38, "������������"},
	{39, "����"},
	{40, "������� �������"},
	{41, "���� �����"},
	{42, "��������� ��������"},
	{43, "������� �������"},
	{44, "���������"},
	{45, "�������� �������"},
	{46, "�������"},
	{47, "�������� ������� ������"},
	{48, "�������� ������"},
	{49, "������ �����"}
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

