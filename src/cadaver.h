#pragma once

#include "rand.h"

#include "extremity.h"
#include "entity.h"



struct Cadaver : public Entity, EntS<Cadaver>
{ 
	ExtremityData rightLeg;
	ExtremityData leftLeg;
	ExtremityData rightArm;
	ExtremityData leftArm;
	ExtremityData head;
	ExtremityData body;

	bool isCarried = false;
	bool isCarriable = false;

	Cadaver(int x, int y) {

		pos.x = x;
		pos.y = y;
		
		int color = Random::roll(1, ExtremityData::BodyColor::SIZE_COLOR - 1);
		int type = color * (ExtremityData::BodyColor::SIZE_COLOR - 2);

		rightLeg.x = pos.x;
		rightLeg.y = pos.y;
		rightLeg.colorType = (ExtremityData::BodyColorType) (type + 1);

		leftLeg.x = pos.x;
		leftLeg.y = pos.y;
		leftLeg.colorType = (ExtremityData::BodyColorType) (type + 2);

		rightArm.x = pos.x;
		rightArm.y = pos.y;
		rightArm.colorType = (ExtremityData::BodyColorType) (type + 3);

		leftArm.x = pos.x;
		leftArm.y = pos.y;
		leftArm.colorType = (ExtremityData::BodyColorType) (type + 4);

		head.x = pos.x;
		head.y = pos.y;
		head.colorType = (ExtremityData::BodyColorType) (type + 5);

		body.x = pos.x;
		body.y = pos.y;
		body.colorType = (ExtremityData::BodyColorType) (type + 6);

		int noExtremity = Random::roll(1, 5);

		switch (noExtremity)
		{
		case 1: rightLeg.colorType = ExtremityData::BodyColorType::NONE_TYPE; break;
		case 2: leftLeg.colorType = ExtremityData::BodyColorType::NONE_TYPE; break;
		case 3: rightArm.colorType = ExtremityData::BodyColorType::NONE_TYPE; break;
		case 4: leftArm.colorType = ExtremityData::BodyColorType::NONE_TYPE; break;
		case 5: head.colorType = ExtremityData::BodyColorType::NONE_TYPE; break;
		}
	}

	void Update(int dt) 
	{
	}

<<<<<<< HEAD
	virtual void Draw(sf::Sprite& spr, sf::RenderTarget& window) {
		DrawRightLeg(spr);
		window.draw(spr);

		DrawLeftLeg(spr);
		window.draw(spr);

		DrawRightArm(spr);
		window.draw(spr);

		DrawLeftArm(spr);
		window.draw(spr);

		DrawHead(spr);
		window.draw(spr);

		DrawBody(spr);
		window.draw(spr);
	}
=======
	void Draw(sf::Sprite& spr, sf::RenderWindow& wnd)
	{
		if (rightLeg.colorType != ExtremityData::BodyColorType::NONE_TYPE)
		{
			DrawRightLeg(spr, wnd);
		}
		
		if (leftLeg.colorType != ExtremityData::BodyColorType::NONE_TYPE)
		{
			DrawLeftLeg(spr, wnd);
		}
>>>>>>> deprecated map (before born)

		if (rightArm.colorType != ExtremityData::BodyColorType::NONE_TYPE)
		{
			DrawRightArm(spr, wnd);
		}
		
		if (leftArm.colorType != ExtremityData::BodyColorType::NONE_TYPE)
		{
			DrawLeftArm(spr, wnd);
		}
		
		if (head.colorType != ExtremityData::BodyColorType::NONE_TYPE)
		{
			DrawHead(spr, wnd);
		}

		if (isCarriable)
		{
			DrawCarriable(spr, wnd);
		}
	}


	void DrawRightLeg(sf::Sprite& spr, sf::RenderWindow& wnd)
	{
		spr.setScale(4, 4);
		spr.setPosition(rightLeg.x, rightLeg.y);
		spr.setTextureRect(extremitySprPos.find(rightLeg.colorType)->second);
		wnd.draw(spr);
	}

	void DrawLeftLeg(sf::Sprite& spr, sf::RenderWindow& wnd)
	{
		spr.setScale(4, 4);
		spr.setPosition(leftLeg.x, leftLeg.y);
		spr.setTextureRect(extremitySprPos.find(leftLeg.colorType)->second);
		wnd.draw(spr);
	}
	
	void DrawRightArm(sf::Sprite& spr, sf::RenderWindow& wnd)
	{
		spr.setScale(4, 4);
		spr.setPosition(rightArm.x, rightArm.y);
		spr.setTextureRect(extremitySprPos.find(rightArm.colorType)->second);
		wnd.draw(spr);
	}
	
	void DrawLeftArm(sf::Sprite& spr, sf::RenderWindow& wnd)
	{
		spr.setScale(4, 4);
		spr.setPosition(leftArm.x, leftArm.y);
		spr.setTextureRect(extremitySprPos.find(leftArm.colorType)->second);
		wnd.draw(spr);
	}
	
	void DrawHead(sf::Sprite& spr, sf::RenderWindow& wnd)
	{
		spr.setScale(4, 4);
		spr.setPosition(head.x, head.y);
		spr.setTextureRect(extremitySprPos.find(head.colorType)->second);
		wnd.draw(spr);
	}

	void DrawBody(sf::Sprite& spr, sf::RenderWindow& wnd)
	{
		spr.setScale(4, 4);
		spr.setPosition(body.x, body.y);
		spr.setTextureRect(extremitySprPos.find(rightLeg.colorType)->second);
		wnd.draw(spr);
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