#ifndef DOWNLAYER_H

class  DownLayer
{
private:
	sf::RectangleShape playerShape;
	sf::RectangleShape marketShape;
	sf::RectangleShape bossShape;

public:
	 DownLayer();
	~DownLayer();

	void render(sf::RenderTarget& target);
};


#endif // !DOWNLAYER_H
