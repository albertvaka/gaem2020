#include "entity.h"
#include "animation.h"
#include "rand.h"


struct Taca : public Cintable, public EntS<Taca>
{

	vec positionPlz() override {
		return pos;
	}

	vec sizePlz() override {
		return vec(16,16);
	}

	bool alive = true;
	vec pos;
	vec speed;
	sf::Color m_color = sf::Color(200,0,0);
	sf::Vector2f m_offset;
	float counter;
	Taca(vec position, EntityDirection dir) {
		currCintaDirection = dir;
		counter = 7500 + Random::roll(5000);
		pos = position;
		
		Random::CircularRoll(5, m_offset.x, m_offset.y);
		m_offset.x += 3 + 5;
		m_offset.y += 3 + 5;
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
		SetSpeedWithCinta(speed);
		counter -= dt;
		if (counter < 0) {
			if (currCintaDirection != EntityDirection::NONE  || prevCintaDirection != EntityDirection::NONE)
			{
				alive = false;
			}
		}
		pos += speed * 0.8 * dt;
		speed.Zero();
	}

	void Draw(sf::VertexArray &vertexArray)
	{
		
	}

	vec getFinalPos()
	{
		return vec(pos.x + m_offset.x, pos.y + m_offset.y);
	}

};