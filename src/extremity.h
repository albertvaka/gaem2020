#pragma once

#include "entity.h"
#include "entity_system.h"

std::map<int, sf::IntRect> extremitySprPos;

enum ExtremityType {
	RIGHT_LEG,
	LEFT_LEG,
	RIGHT_ARM,
	LEFT_ARM,
	HEAD
};

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
		NONE_TYPE = 0,
		WHITE_RIGHT_LEG = 1,
		WHITE_LEFT_LEG = 2,
		WHITE_RIGHT_ARM = 3,
		WHITE_LEFT_ARM = 4,
		WHITE_HEAD = 5,
		WHITE_BODY = 6,
		BLACK_RIGHT_LEG = 7,
		BLACK_LEFT_LEG = 8,
		BLACK_RIGHT_ARM = 9,
		BLACK_LEFT_ARM = 10,
		BLACK_HEAD = 11,
		BLACK_BODY = 12,
		YELLOW_RIGHT_LEG = 13,
		YELLOW_LEFT_LEG = 14,
		YELLOW_RIGHT_ARM = 15,
		YELLOW_LEFT_ARM = 16,
		YELLOW_HEAD = 17,
		YELLOW_BODY = 18,
		GREEN_RIGHT_LEG = 19,
		GREEN_LEFT_LEG = 20,
		GREEN_RIGHT_ARM = 21,
		GREEN_LEFT_ARM = 22,
		GREEN_HEAD = 23,
		GREEN_BODY = 24,
		BLUE_RIGHT_LEG = 25,
		BLUE_LEFT_LEG = 26,
		BLUE_RIGHT_ARM = 27,
		BLUE_LEFT_ARM = 28,
		BLUE_HEAD = 29,
		BLUE_BODY = 30,
		RED_RIGHT_LEG = 31,
		RED_LEFT_LEG = 32,
		RED_RIGHT_ARM = 33,
		RED_LEFT_ARM = 34,
		RED_HEAD = 35,
		RED_BODY = 36,
		SIZE_TYPE = 37
	};

	BodyColorType colorType;
	int anim;
	int x, y;
};

struct Extremity : public SortedDrawable, EntS<Extremity> 
{

	ExtremityData data;
	bool isCarried;
	bool isCarriable; 

	Extremity(int x, int y) : Extremity()
	{
		pos.x = x;
		pos.y = y;
	}

	Extremity() 
	{
		isCarried = false;
		isCarriable = false;
	}

	void carryExtremity(int x, int y)
	{
		isCarried = true;

		pos.x = x;
		pos.y = y;
	}


	void Update(int dt)
	{
	}


	void Draw(sf::Sprite& spr, sf::RenderTarget& wnd) override
	{
		spr.setPosition(pos.x, pos.y);
		spr.setTextureRect(extremitySprPos.find(data.colorType)->second);
		wnd.draw(spr);
	}

};

void loadExtremityMap()
{
	extremitySprPos.insert(std::pair<int, sf::IntRect>(ExtremityData::WHITE_RIGHT_LEG, sf::IntRect(0, 64, 8, 8)));
	extremitySprPos.insert(std::pair<int, sf::IntRect>(ExtremityData::WHITE_LEFT_LEG, sf::IntRect(8, 64, 8, 8)));
	extremitySprPos.insert(std::pair<int, sf::IntRect>(ExtremityData::WHITE_RIGHT_ARM, sf::IntRect(16, 64, 8, 8)));
	extremitySprPos.insert(std::pair<int, sf::IntRect>(ExtremityData::WHITE_LEFT_ARM, sf::IntRect(24, 64, 8, 8)));
	extremitySprPos.insert(std::pair<int, sf::IntRect>(ExtremityData::WHITE_HEAD, sf::IntRect(32, 64, 8, 8)));
	extremitySprPos.insert(std::pair<int, sf::IntRect>(ExtremityData::WHITE_BODY, sf::IntRect(40, 64, 8, 8)));

	extremitySprPos.insert(std::pair<int, sf::IntRect>(ExtremityData::BLACK_RIGHT_LEG, sf::IntRect(0, 72, 8, 8)));
	extremitySprPos.insert(std::pair<int, sf::IntRect>(ExtremityData::BLACK_LEFT_LEG, sf::IntRect(8, 72, 8, 8)));
	extremitySprPos.insert(std::pair<int, sf::IntRect>(ExtremityData::BLACK_RIGHT_ARM, sf::IntRect(16, 72, 8, 8)));
	extremitySprPos.insert(std::pair<int, sf::IntRect>(ExtremityData::BLACK_LEFT_ARM, sf::IntRect(24, 72, 8, 8)));
	extremitySprPos.insert(std::pair<int, sf::IntRect>(ExtremityData::BLACK_HEAD, sf::IntRect(32, 72, 8, 8)));
	extremitySprPos.insert(std::pair<int, sf::IntRect>(ExtremityData::BLACK_BODY, sf::IntRect(40, 72, 8, 8)));

	extremitySprPos.insert(std::pair<int, sf::IntRect>(ExtremityData::YELLOW_RIGHT_LEG, sf::IntRect(0, 80, 8, 8)));
	extremitySprPos.insert(std::pair<int, sf::IntRect>(ExtremityData::YELLOW_LEFT_LEG, sf::IntRect(8, 80, 8, 8)));
	extremitySprPos.insert(std::pair<int, sf::IntRect>(ExtremityData::YELLOW_RIGHT_ARM, sf::IntRect(16, 80, 8, 8)));
	extremitySprPos.insert(std::pair<int, sf::IntRect>(ExtremityData::YELLOW_LEFT_ARM, sf::IntRect(24, 80, 8, 8)));
	extremitySprPos.insert(std::pair<int, sf::IntRect>(ExtremityData::YELLOW_HEAD, sf::IntRect(32, 80, 8, 8)));
	extremitySprPos.insert(std::pair<int, sf::IntRect>(ExtremityData::YELLOW_BODY, sf::IntRect(40, 80, 8, 8)));

	extremitySprPos.insert(std::pair<int, sf::IntRect>(ExtremityData::GREEN_RIGHT_LEG, sf::IntRect(0, 88, 8, 8)));
	extremitySprPos.insert(std::pair<int, sf::IntRect>(ExtremityData::GREEN_LEFT_LEG, sf::IntRect(8, 88, 8, 8)));
	extremitySprPos.insert(std::pair<int, sf::IntRect>(ExtremityData::GREEN_RIGHT_ARM, sf::IntRect(16, 88, 8, 8)));
	extremitySprPos.insert(std::pair<int, sf::IntRect>(ExtremityData::GREEN_LEFT_ARM, sf::IntRect(24, 88, 8, 8)));
	extremitySprPos.insert(std::pair<int, sf::IntRect>(ExtremityData::GREEN_HEAD, sf::IntRect(32, 88, 8, 8)));
	extremitySprPos.insert(std::pair<int, sf::IntRect>(ExtremityData::GREEN_BODY, sf::IntRect(40, 88, 8, 8)));

	extremitySprPos.insert(std::pair<int, sf::IntRect>(ExtremityData::BLUE_RIGHT_LEG, sf::IntRect(0, 96, 8, 8)));
	extremitySprPos.insert(std::pair<int, sf::IntRect>(ExtremityData::BLUE_LEFT_LEG, sf::IntRect(8, 96, 8, 8)));
	extremitySprPos.insert(std::pair<int, sf::IntRect>(ExtremityData::BLUE_RIGHT_ARM, sf::IntRect(16, 96, 8, 8)));
	extremitySprPos.insert(std::pair<int, sf::IntRect>(ExtremityData::BLUE_LEFT_ARM, sf::IntRect(24, 96, 8, 8)));
	extremitySprPos.insert(std::pair<int, sf::IntRect>(ExtremityData::BLUE_HEAD, sf::IntRect(32, 96, 8, 8)));
	extremitySprPos.insert(std::pair<int, sf::IntRect>(ExtremityData::BLUE_BODY, sf::IntRect(40, 96, 8, 8)));

	extremitySprPos.insert(std::pair<int, sf::IntRect>(ExtremityData::RED_RIGHT_LEG, sf::IntRect(0, 104, 8, 8)));
	extremitySprPos.insert(std::pair<int, sf::IntRect>(ExtremityData::RED_LEFT_LEG, sf::IntRect(8, 104, 8, 8)));
	extremitySprPos.insert(std::pair<int, sf::IntRect>(ExtremityData::RED_RIGHT_ARM, sf::IntRect(16, 104, 8, 8)));
	extremitySprPos.insert(std::pair<int, sf::IntRect>(ExtremityData::RED_LEFT_ARM, sf::IntRect(24, 104, 8, 8)));
	extremitySprPos.insert(std::pair<int, sf::IntRect>(ExtremityData::RED_HEAD, sf::IntRect(32, 104, 8, 8)));
	extremitySprPos.insert(std::pair<int, sf::IntRect>(ExtremityData::RED_BODY, sf::IntRect(40, 104, 8, 8)));
}
