#include "pch.h"
#include "Gui.h"

gui::Button::Button(float x, float y, float width, float height,
	sf::Font* font, std::string text,
	unsigned character_size,
	sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
	sf::Color idle_color, sf::Color hover_color,
	sf::Color active_color, sf::Color outline_idle_color,
	sf::Color outline_hover_color, sf::Color outline_active_color, short unsigned id)
{
	this->buttonState = BTN_IDLE;
	this->id = id;

	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setSize(sf::Vector2f(width, height));
	this->text.setFillColor(idle_color);
	this->shape.setOutlineThickness(1.f);
	this->shape.setOutlineColor(outline_idle_color);

	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(text_idle_color);
	this->text.setCharacterSize(character_size);
	
	this->text.setPosition(
		//this->shape.getPosition().x + (this->shape.getPosition().x / 2.f) - this->text.getGlobalBounds().width / 2,
		//this->shape.getPosition().y + (this->shape.getPosition().y / 2.f) - this->text.getGlobalBounds().height / 2
		this->shape.getPosition().x + (this->shape.getGlobalBounds().width - this->text.getGlobalBounds().width) / 2,
		this->shape.getPosition().y + (this->shape.getGlobalBounds().height / 2) - (this->text.getGlobalBounds().height)
	);

	this->textIdleColor = text_idle_color;
	this->textHoverColor = text_hover_color;
	this->textActiveColor = text_active_color;

	this->idleColor = idle_color;
	this->hoverColor = hover_color;
	this->activeColor = active_color;

	this->outlineIdleColor = outline_idle_color;
	this->outlineHoverColor = outline_hover_color;
	this->outlineActiveColor = outline_active_color;
}

gui::Button::~Button()
{

}


//Accessors
const bool gui::Button::isPressed() const
{
	if (this->buttonState == BTN_ACTIVE)
		return true;

	return false;
}

const std::string gui::Button::getText() const
{
	return this->text.getString();
}

const short unsigned& gui::Button::getId() const
{
	return this->id;
}

//Modifier
void gui::Button::setText(const std::string text)
{
	this->text.setString(text);
}

void gui::Button::setId(const short unsigned id)
{
	this->id = id;
}

//Func
void gui::Button::update(const sf::Vector2i& mousePosWindow)
{
	/*Update bool for hover and pressed*/

	//idle 
	this->buttonState = BTN_IDLE;

	//hover
	if (this->shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWindow)))
	{
		this->buttonState = BTN_HOVER;

		//pressed
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->buttonState = BTN_ACTIVE;
		}
	}


	switch (this->buttonState)
	{
	case BTN_IDLE:
		this->shape.setFillColor(this->idleColor);
		this->text.setFillColor(this->textIdleColor);
		this->shape.setOutlineColor(this->outlineIdleColor);
		break;
	case BTN_HOVER:
		this->shape.setFillColor(this->hoverColor);
		this->text.setFillColor(this->textHoverColor);
		this->shape.setOutlineColor(this->outlineHoverColor);
		break;
	case BTN_ACTIVE:
		this->shape.setFillColor(this->activeColor);
		this->text.setFillColor(this->textActiveColor);
		this->shape.setOutlineColor(this->outlineActiveColor);
		break;
	default:
		this->shape.setFillColor(sf::Color::Red);
		this->text.setFillColor(sf::Color::Blue);
		this->shape.setOutlineColor(sf::Color::Red);
		break;
	}

}

void gui::Button::render(sf::RenderTarget& target)
{
	target.draw(this->shape);
	target.draw(this->text);
}

/*

Drop down list ============================================

*/

gui::DropDownList::DropDownList(float x, float y, 
	float width, float height, 
	sf::Font& font, std::string list[], 
	unsigned nrOfElemetn, unsigned default_index)
	: font(font), showList(false), keyTimeMax(1.f), keyTime(0.f)
{
	//unsigned nrOfElemetn = sizeof(list) / sizeof(std::string);
	
	this->activeElement = new gui::Button(
		x, y, width, height,
		&this->font, list[default_index], 14,

		sf::Color(255, 255, 255, 150),
		sf::Color(255, 255, 255, 200),
		sf::Color(20, 20, 20, 50),

		sf::Color(70, 70, 70, 200),
		sf::Color(150, 150, 150, 200),
		sf::Color(20, 20, 20, 200),

		sf::Color(255, 255, 255, 200),
		sf::Color(255, 255, 255, 255),
		sf::Color(20, 20, 20, 50)
	);

	for (unsigned short i = 0; i < nrOfElemetn; i++)
	{
		this->list.push_back
		(
			new gui::Button(
				x, y + ((i+1) * height), width, height,
				&this->font, list[i], 14,

				sf::Color(255, 255, 255, 120),
				sf::Color(255, 255, 255, 250),
				sf::Color(20, 20, 20, 50),

				sf::Color(70, 70, 70, 200),
				sf::Color(150, 150, 150, 200),
				sf::Color(20, 20, 20, 200),

				sf::Color(255, 255, 255, 0),
				sf::Color(255, 255, 255, 0),
				sf::Color(20, 20, 20, 0),
				i
			)
		);
	}

}

gui::DropDownList::~DropDownList()
{
	delete this->activeElement;
	for (size_t i = 0; i < this->list.size(); i++)
	{
		delete this->list[i];
	}
}


//accessors
const short unsigned& gui::DropDownList::getActiveElementId() const
{
	return this->activeElement->getId();
}

const bool gui::DropDownList::getKeyTime()
{
	if (this->keyTime >= this->keyTimeMax)
	{
		this->keyTime = 0.f;
		return true;
	}
	return false;
}

//func
void gui::DropDownList::updateKeyTime(const float& dt)
{
	if (this->keyTime < this->keyTimeMax)
	{
		this->keyTime += 10.f * dt;
	}
}

void gui::DropDownList::update(const sf::Vector2i& mousePosWindow, const float& dt)
{
	this->updateKeyTime(dt);

	this->activeElement->update(mousePosWindow);

	//show list
	if (this->activeElement->isPressed() && this->getKeyTime())
	{
		if (this->showList)
			this->showList = false;
		else
			this->showList = true;
	}

	if (this->showList)
	{
		for (auto& i : this->list)
		{
			i->update(mousePosWindow);

			if (i->isPressed() && this->getKeyTime())
			{
				this->showList = false;
				this->activeElement->setText(i->getText());
				this->activeElement->setId(i->getId());
			}
		}
	}
}

void gui::DropDownList::render(sf::RenderTarget& target)
{
	this->activeElement->render(target);
	if (this->showList)
	{
		for (auto& i : this->list)
		{
			i->render(target);
		}
	}
}