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

	bool alive;
	vec pos;
	vec speed;
	sf::Color m_color = sf::Color(200,0,0);
	sf::Vector2f m_offset;
	float counter;
	Taca(vec position, EntityDirection dir) {
		currCintaDirection = dir;
		counter = 7500 + Random::roll(5000);
		pos = position;
		m_offset.x = Random::roll(0, 16);
		m_offset.y = Random::roll(0, 16);
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
			alive = false;
		}
		pos += speed * dt;
		speed.Zero();
	}

	void Draw(sf::VertexArray &vertexArray)
	{
		
	}


};