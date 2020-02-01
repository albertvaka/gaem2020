#pragma once

#include "entity.h"
#include "entity_system.h"

std::map<int, sf::IntRect> extremitySprPos;

struct ExtremityData 
{

	enum BodyColor {
		NONE_COLOR = 0,
		WHITE,
		BLACK,
		YELLOW,
		GREEN,
		BLUE,
		RED,
		SIZE_COLOR
	};

	enum BodyColorType {
		NONE_TYPE,
		WHITE_RIGHT_LEG,
		WHITE_LEFT_LEG,
		WHITE_RIGHT_ARM,
		WHITE_LEFT_ARM,
		WHITE_HEAD,
		WHITE_BODY,
		BLACK_RIGHT_LEG,
		BLACK_LEFT_LEG,
		BLACK_RIGHT_ARM,
		BLACK_LEFT_ARM,
		BLACK_HEAD,
		BLACK_BODY,
		YELLOW_RIGHT_LEG,
		YELLOW_LEFT_LEG,
		YELLOW_RIGHT_ARM,
		YELLOW_LEFT_ARM,
		YELLOW_HEAD,
		YELLOW_BODY,
		GREEN_RIGHT_LEG,
		GREEN_LEFT_LEG,
		GREEN_RIGHT_ARM,
		GREEN_LEFT_ARM,
		GREEN_HEAD,
		GREEN_BODY,
		BLUE_RIGHT_LEG,
		BLUE_LEFT_LEG,
		BLUE_RIGHT_ARM,
		BLUE_LEFT_ARM,
		BLUE_HEAD,
		BLUE_BODY,
		RED_RIGHT_LEG,
		RED_LEFT_LEG,
		RED_RIGHT_ARM,
		RED_LEFT_ARM,
		RED_HEAD,
		RED_BODY,
		SIZE_TYPE
	};

	BodyColorType colorType;
	int anim;
	int x, y;
};

struct Extremity : public Entity, EntS<Extremity> 
{

	ExtremityData data;
	bool isCarried;
	bool isCarriable; 

	Extremity(int x, int y)
	{
		data.x = x;
		data.y = y;
		pos.x = x;
		pos.y = y;
		Extremity();
	}

	Extremity() 
	{
		isCarried = false;
		isCarriable = false;
	}


	void Update(int dt)
	{
	}


	void Draw(sf::Sprite& spr, sf::RenderWindow& wnd)
	{
		spr.setScale(4, 4);
		spr.setPosition(pos.x, pos.y);
		spr.setTextureRect(extremitySprPos.find(data.colorType)->second);
		wnd.draw(spr);

		DrawCarriable(spr, wnd);
	}

	void DrawCarriable(sf::Sprite& spr, sf::RenderWindow& wnd)
	{
		sf::RectangleShape shape;
		shape.setFillColor(sf::Color::White);
		shape.setPosition(pos.x, pos.y);
		shape.setSize(sf::Vector2f(16, 16));

		wnd.draw(shape);
	}
};

void loadExtremityMap()
{
	extremitySprPos.insert(std::pair<int, sf::IntRect>(ExtremityData::WHITE_RIGHT_LEG, sf::IntRect(0, 48, 8, 8)));
	extremitySprPos.insert(std::pair<int, sf::IntRect>(ExtremityData::WHITE_LEFT_LEG, sf::IntRect(8, 48, 8, 8)));
	extremitySprPos.insert(std::pair<int, sf::IntRect>(ExtremityData::WHITE_RIGHT_ARM, sf::IntRect(16, 48, 8, 8)));
	extremitySprPos.insert(std::pair<int, sf::IntRect>(ExtremityData::WHITE_LEFT_ARM, sf::IntRect(24, 48, 8, 8)));
	extremitySprPos.insert(std::pair<int, sf::IntRect>(ExtremityData::WHITE_HEAD, sf::IntRect(32, 48, 8, 8)));
	extremitySprPos.insert(std::pair<int, sf::IntRect>(ExtremityData::WHITE_BODY, sf::IntRect(40, 48, 8, 8)));

	extremitySprPos.insert(std::pair<int, sf::IntRect>(ExtremityData::BLACK_RIGHT_LEG, sf::IntRect(0, 56, 8, 8)));
	extremitySprPos.insert(std::pair<int, sf::IntRect>(ExtremityData::BLACK_LEFT_LEG, sf::IntRect(8, 56, 8, 8)));
	extremitySprPos.insert(std::pair<int, sf::IntRect>(ExtremityData::BLACK_RIGHT_ARM, sf::IntRect(1, 56, 8, 8)));
	extremitySprPos.insert(std::pair<int, sf::IntRect>(ExtremityData::BLACK_LEFT_ARM, sf::IntRect(24, 56, 8, 8)));
	extremitySprPos.insert(std::pair<int, sf::IntRect>(ExtremityData::BLACK_HEAD, sf::IntRect(32, 0, 56, 8)));
	extremitySprPos.insert(std::pair<int, sf::IntRect>(ExtremityData::BLACK_BODY, sf::IntRect(40, 0, 56, 8)));

	extremitySprPos.insert(std::pair<int, sf::IntRect>(ExtremityData::YELLOW_RIGHT_LEG, sf::IntRect(0, 64, 8, 8)));
	extremitySprPos.insert(std::pair<int, sf::IntRect>(ExtremityData::YELLOW_LEFT_LEG, sf::IntRect(8, 64, 8, 8)));
	extremitySprPos.insert(std::pair<int, sf::IntRect>(ExtremityData::YELLOW_RIGHT_ARM, sf::IntRect(16, 64, 8, 8)));
	extremitySprPos.insert(std::pair<int, sf::IntRect>(ExtremityData::YELLOW_LEFT_ARM, sf::IntRect(24, 64, 8, 8)));
	extremitySprPos.insert(std::pair<int, sf::IntRect>(ExtremityData::YELLOW_HEAD, sf::IntRect(32, 64, 8, 8)));
	extremitySprPos.insert(std::pair<int, sf::IntRect>(ExtremityData::YELLOW_BODY, sf::IntRect(40, 64, 8, 8)));

	extremitySprPos.insert(std::pair<int, sf::IntRect>(ExtremityData::GREEN_RIGHT_LEG, sf::IntRect(0, 72, 8, 8)));
	extremitySprPos.insert(std::pair<int, sf::IntRect>(ExtremityData::GREEN_LEFT_LEG, sf::IntRect(8, 72, 8, 8)));
	extremitySprPos.insert(std::pair<int, sf::IntRect>(ExtremityData::GREEN_RIGHT_ARM, sf::IntRect(16, 72, 8, 8)));
	extremitySprPos.insert(std::pair<int, sf::IntRect>(ExtremityData::GREEN_LEFT_ARM, sf::IntRect(24, 72, 8, 8)));
	extremitySprPos.insert(std::pair<int, sf::IntRect>(ExtremityData::GREEN_HEAD, sf::IntRect(32, 72, 8, 8)));
	extremitySprPos.insert(std::pair<int, sf::IntRect>(ExtremityData::GREEN_BODY, sf::IntRect(40, 72, 8, 8)));

	extremitySprPos.insert(std::pair<int, sf::IntRect>(ExtremityData::BLUE_RIGHT_LEG, sf::IntRect(0, 80, 8, 8)));
	extremitySprPos.insert(std::pair<int, sf::IntRect>(ExtremityData::BLUE_LEFT_LEG, sf::IntRect(8, 80, 8, 8)));
	extremitySprPos.insert(std::pair<int, sf::IntRect>(ExtremityData::BLUE_RIGHT_ARM, sf::IntRect(16, 80, 8, 8)));
	extremitySprPos.insert(std::pair<int, sf::IntRect>(ExtremityData::BLUE_LEFT_ARM, sf::IntRect(24, 80, 8, 8)));
	extremitySprPos.insert(std::pair<int, sf::IntRect>(ExtremityData::BLUE_HEAD, sf::IntRect(32, 80, 8, 8)));
	extremitySprPos.insert(std::pair<int, sf::IntRect>(ExtremityData::BLUE_BODY, sf::IntRect(40, 80, 8, 8)));

	extremitySprPos.insert(std::pair<int, sf::IntRect>(ExtremityData::RED_RIGHT_LEG, sf::IntRect(0, 88, 8, 8)));
	extremitySprPos.insert(std::pair<int, sf::IntRect>(ExtremityData::RED_LEFT_LEG, sf::IntRect(8, 88, 8, 8)));
	extremitySprPos.insert(std::pair<int, sf::IntRect>(ExtremityData::RED_RIGHT_ARM, sf::IntRect(16, 88, 8, 8)));
	extremitySprPos.insert(std::pair<int, sf::IntRect>(ExtremityData::RED_LEFT_ARM, sf::IntRect(24, 88, 8, 8)));
	extremitySprPos.insert(std::pair<int, sf::IntRect>(ExtremityData::RED_HEAD, sf::IntRect(32, 88, 8, 8)));
	extremitySprPos.insert(std::pair<int, sf::IntRect>(ExtremityData::RED_BODY, sf::IntRect(40, 88, 8, 8)));
}
