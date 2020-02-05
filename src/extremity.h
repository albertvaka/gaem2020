#pragma once

#include "entity.h"
#include "entity_system.h"

enum class ExtremityType
{
	BODY,
	RIGHT_LEG,
	LEFT_LEG,
	RIGHT_ARM,
	LEFT_ARM,
	HEAD,
	COUNT,
};

enum class ExtremityColor
{
	NONE_COLOR = 0,
	WHITE,
	BLACK,
	YELLOW,
	GREEN,
	BLUE,
	RED,
	SIZE_COLOR
};

inline ExtremityType RandomExtremityType() {
	return ExtremityType(Random::roll(int(ExtremityType::COUNT) - 2) + 1);
};

inline ExtremityColor RandomExtremityColor() {
	return ExtremityColor(Random::roll(int(ExtremityColor::SIZE_COLOR) - 2) + 1);
};

std::map<ExtremityColor, std::map<ExtremityType, sf::IntRect>> extremitySprPos;

struct Extremity : SortedDrawable, Cintable, EntS<Extremity>
{
	ExtremityType type;
	ExtremityColor color;
	bool isCarried = false;
	bool isLet = false;

	vec positionPlz() {
		return pos;
	}

	Extremity(vec position, ExtremityType t, ExtremityColor c)
	{
		color = c;
		type = t;
		pos = position;
	}

	void carryExtremity(int x, int y)
	{
		isCarried = true;

		pos.x = static_cast<float>(x);
		pos.y = static_cast<float>(y+1);
	}


	void Update(int dt)
	{
		SetSpeedWithCinta(speed);
		pos += speed * dt;
		speed.Zero();
	}


	void Draw(sf::Sprite& spr, sf::RenderTarget& wnd) override
	{
		vec carriedOffset;
		if (isCarried) {
			carriedOffset.y = -2;
		}
		spr.setPosition(pos+Offset()+carriedOffset);
		spr.setTextureRect(extremitySprPos[color][type]);
		wnd.draw(spr);
		spr.setScale(1, 1);


		//Bounds(pos.x , pos.y , 16, 16).Draw(wnd);
		////Bounds(pos.x - 1, pos.y - 1, 2, 2).Draw(wnd);

	}

	vec Offset()
	{
		if (type == ExtremityType::HEAD)
		{
			return vec(4,5);
		}
		if (type == ExtremityType::LEFT_ARM)
		{
			return vec(6, 3);
		}
		if (type == ExtremityType::LEFT_LEG)
		{
			return vec(5,2);
		}
		if (type == ExtremityType::RIGHT_ARM)
		{
			return vec(2,2);
		}
		if (type == ExtremityType::RIGHT_LEG)
		{
			return vec(3,2);
		}
		return vec(0, 0);
	}

};

void loadExtremityMap()
{
	extremitySprPos[ExtremityColor::WHITE][ExtremityType::RIGHT_LEG] = sf::IntRect(0, 64, 8, 8);
	extremitySprPos[ExtremityColor::WHITE][ExtremityType::LEFT_LEG] =sf::IntRect(8, 64, 8, 8);
	extremitySprPos[ExtremityColor::WHITE][ExtremityType::RIGHT_ARM] = sf::IntRect(16, 64, 8, 8);
	extremitySprPos[ExtremityColor::WHITE][ExtremityType::LEFT_ARM] = sf::IntRect(24, 64, 8, 8);
	extremitySprPos[ExtremityColor::WHITE][ExtremityType::HEAD] = sf::IntRect(32, 64, 8, 8);
	extremitySprPos[ExtremityColor::WHITE][ExtremityType::BODY] = sf::IntRect(40, 64, 8, 8);

	extremitySprPos[ExtremityColor::BLACK][ExtremityType::RIGHT_LEG] = sf::IntRect(0, 72, 8, 8);
	extremitySprPos[ExtremityColor::BLACK][ExtremityType::LEFT_LEG] = sf::IntRect(8, 72, 8, 8);
	extremitySprPos[ExtremityColor::BLACK][ExtremityType::RIGHT_ARM] = sf::IntRect(16, 72, 8, 8);
	extremitySprPos[ExtremityColor::BLACK][ExtremityType::LEFT_ARM] = sf::IntRect(24, 72, 8, 8);
	extremitySprPos[ExtremityColor::BLACK][ExtremityType::HEAD] = sf::IntRect(32, 72, 8, 8);
	extremitySprPos[ExtremityColor::BLACK][ExtremityType::BODY] = sf::IntRect(40, 72, 8, 8);

	extremitySprPos[ExtremityColor::YELLOW][ExtremityType::RIGHT_LEG] = sf::IntRect(0, 80, 8, 8);
	extremitySprPos[ExtremityColor::YELLOW][ExtremityType::LEFT_LEG] = sf::IntRect(8, 80, 8, 8);
	extremitySprPos[ExtremityColor::YELLOW][ExtremityType::RIGHT_ARM] = sf::IntRect(16, 80, 8, 8);
	extremitySprPos[ExtremityColor::YELLOW][ExtremityType::LEFT_ARM] = sf::IntRect(24, 80, 8, 8);
	extremitySprPos[ExtremityColor::YELLOW][ExtremityType::HEAD] = sf::IntRect(32, 80, 8, 8);
	extremitySprPos[ExtremityColor::YELLOW][ExtremityType::BODY] = sf::IntRect(40, 80, 8, 8);

	extremitySprPos[ExtremityColor::GREEN][ExtremityType::RIGHT_LEG] = sf::IntRect(0, 88, 8, 8);
	extremitySprPos[ExtremityColor::GREEN][ExtremityType::LEFT_LEG] = sf::IntRect(8, 88, 8, 8);
	extremitySprPos[ExtremityColor::GREEN][ExtremityType::RIGHT_ARM] = sf::IntRect(16, 88, 8, 8);
	extremitySprPos[ExtremityColor::GREEN][ExtremityType::LEFT_ARM] = sf::IntRect(24, 88, 8, 8);
	extremitySprPos[ExtremityColor::GREEN][ExtremityType::HEAD] = sf::IntRect(32, 88, 8, 8);
	extremitySprPos[ExtremityColor::GREEN][ExtremityType::BODY] = sf::IntRect(40, 88, 8, 8);

	extremitySprPos[ExtremityColor::BLUE][ExtremityType::RIGHT_LEG] = sf::IntRect(0, 96, 8, 8);
	extremitySprPos[ExtremityColor::BLUE][ExtremityType::LEFT_LEG] = sf::IntRect(8, 96, 8, 8);
	extremitySprPos[ExtremityColor::BLUE][ExtremityType::RIGHT_ARM] = sf::IntRect(16, 96, 8, 8);
	extremitySprPos[ExtremityColor::BLUE][ExtremityType::LEFT_ARM] = sf::IntRect(24, 96, 8, 8);
	extremitySprPos[ExtremityColor::BLUE][ExtremityType::HEAD] = sf::IntRect(32, 96, 8, 8);
	extremitySprPos[ExtremityColor::BLUE][ExtremityType::BODY] = sf::IntRect(40, 96, 8, 8);

	extremitySprPos[ExtremityColor::RED][ExtremityType::RIGHT_LEG] = sf::IntRect(0, 104, 8, 8);
	extremitySprPos[ExtremityColor::RED][ExtremityType::LEFT_LEG] = sf::IntRect(8, 104, 8, 8);
	extremitySprPos[ExtremityColor::RED][ExtremityType::RIGHT_ARM] = sf::IntRect(16, 104, 8, 8);
	extremitySprPos[ExtremityColor::RED][ExtremityType::LEFT_ARM] = sf::IntRect(24, 104, 8, 8);
	extremitySprPos[ExtremityColor::RED][ExtremityType::HEAD] = sf::IntRect(32, 104, 8, 8);
	extremitySprPos[ExtremityColor::RED][ExtremityType::BODY] = sf::IntRect(40, 104, 8, 8);
}
