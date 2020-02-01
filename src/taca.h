#include "entity.h"
#include "animation.h"
#include "rand.h"


struct Taca : public Entity, public EntS<Taca>
{
	sf::Color m_color = sf::Color(200,0,0);
	sf::Vector2f m_offset;
	float counter = 100;
	Taca(vec position) {
		pos = position;
		m_offset.x = Random::roll(0, 3);
		m_offset.y = Random::roll(0, 3);
		m_color.r += Random::roll(0, 50);
		m_color.g += Random::roll(0, 50);
		m_color.b += Random::roll(0, 50);
	}

	void Draw(sf::Sprite& spr, sf::RenderTarget& window)
	{
		sf::RectangleShape rectangle;
		rectangle.setSize(sf::Vector2f(1, 1));
		rectangle.setFillColor(m_color);
		rectangle.setPosition(pos.x + m_offset.x, pos.y + m_offset.y);

		window.draw(rectangle);
	}

	void Update(float dt)
	{
		counter -= dt;
		if (counter < 0) alive = false;
	}
	void Draw(sf::VertexArray &vertexArray)
	{
		
	}


};