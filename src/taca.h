#include "entity.h"
#include "animation.h"
#include "rand.h"
#include "cinta.h"


struct Taca : public Cintable, public EntS<Taca>
{
	bool alive = true;
	sf::Color m_color = sf::Color(200,0,0);
	sf::Vector2f m_offset;
	float counter;

	Taca(vec position) 
	{
		//currCintaDirection = dir;
		counter = 7500 + Random::roll(5000);
		pos = position;
		size = vec(16, 16);

		Random::CircularRoll(5, m_offset.x, m_offset.y);
		m_offset.x += 3 + 5;
		m_offset.y += 3 + 5;
		m_color.r += Random::roll(0, 50);
		m_color.g += Random::roll(0, 50);
		m_color.b += Random::roll(0, 50);
	}

	void Update(float dt)
	{
		counter -= dt;
		if (counter < 0) 
		{
			//if (currCintaDirection != EntityDirection::NONE  || prevCintaDirection != EntityDirection::NONE)
			{
				alive = false;
			}
		}

		//SetSpeedWithCinta(speed);
		//pos += speed * dt;
		//speed.Zero();
	}

	void Draw(sf::Sprite& spr, sf::RenderTarget& window)
	{
		sf::RectangleShape rectangle;
		rectangle.setSize(sf::Vector2f(1, 1));
		rectangle.setFillColor(m_color);

		rectangle.setPosition((int)(pos.x + m_offset.x), (int)(pos.y + m_offset.y));

		window.draw(rectangle);
	}

	void Draw(sf::VertexArray &vertexArray)
	{
		
	}

	vec getFinalPos()
	{
		return vec(pos.x + m_offset.x, pos.y + m_offset.y);
	}

};