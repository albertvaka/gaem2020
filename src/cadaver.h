#pragma once

#include "rand.h"

#include "extremity.h"
#include "entity.h"
#include "collider.h"


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


	int playerCarrying;
	Cadaver(vec pos) : Cadaver(pos.x, pos.y) { }

	Cadaver(int x, int y) {

		pos.x = x;
		pos.y = y;
		
		int color = Random::roll(0, ExtremityData::BodyColor::SIZE_COLOR - 2);
		int type = color * (ExtremityData::BodyColor::SIZE_COLOR - 1);

		rightLeg.colorType = (ExtremityData::BodyColorType) (type + 1);
		leftLeg.colorType = (ExtremityData::BodyColorType) (type + 2);
		rightArm.colorType = (ExtremityData::BodyColorType) (type + 3);
		leftArm.colorType = (ExtremityData::BodyColorType) (type + 4);
		head.colorType = (ExtremityData::BodyColorType) (type + 5);
		body.colorType = (ExtremityData::BodyColorType) (type + 6);

		int noExtremity = Random::roll(0, 4);

		switch (noExtremity)
		{
		case 0: rightLeg.colorType = ExtremityData::BodyColorType::NONE_TYPE; break;
		case 1: leftLeg.colorType = ExtremityData::BodyColorType::NONE_TYPE; break;
		case 2: rightArm.colorType = ExtremityData::BodyColorType::NONE_TYPE; break;
		case 3: leftArm.colorType = ExtremityData::BodyColorType::NONE_TYPE; break;
		case 4: head.colorType = ExtremityData::BodyColorType::NONE_TYPE; break;
		}
	}

	void carryCadaver(int x, int y, int player)
	{
		isCarried = true;

		pos.x = x + 5;
		pos.y = y + 3;

		playerCarrying = player;
	}

	void Update(int dt) 
	{
		Move(dt);
	}

	void Move(int dt)
	{
		SetSpeedWithCinta();
		sf::Vector2f oldpos = pos;
		pos += speed * dt;
		for (Cadaver* p : EntS<Cadaver>::getAll())
		{
			if (p == this) continue;
			float COLLISION_SIZE = 16;

			vec a = p->pos;
			vec b = pos;

			//rectangle colision
			bool colides =
				(a.x < b.x + COLLISION_SIZE && a.x + COLLISION_SIZE > b.x &&
					a.y < b.y + COLLISION_SIZE && a.y + COLLISION_SIZE > b.y);
			if (colides)
			{
				pos = oldpos;
				break;
			}
		}
		
		speed.x = 0;
		speed.y = 0;

	}

	
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

		DrawBody(spr, wnd);

		if (isCarriable)
		{
			DrawCarriable(spr, wnd);
		}
	}


	void DrawRightLeg(sf::Sprite& spr, sf::RenderWindow& wnd)
	{
		spr.setPosition(pos.x, pos.y);
		spr.setTextureRect(extremitySprPos.find(rightLeg.colorType)->second);
		wnd.draw(spr);
	}

	void DrawLeftLeg(sf::Sprite& spr, sf::RenderWindow& wnd)
	{
		spr.setPosition(pos.x, pos.y);
		spr.setTextureRect(extremitySprPos.find(leftLeg.colorType)->second);
		wnd.draw(spr);
	}
	
	void DrawRightArm(sf::Sprite& spr, sf::RenderWindow& wnd)
	{
		spr.setPosition(pos.x, pos.y);
		spr.setTextureRect(extremitySprPos.find(rightArm.colorType)->second);
		wnd.draw(spr);
	}
	
	void DrawLeftArm(sf::Sprite& spr, sf::RenderWindow& wnd)
	{
		spr.setPosition(pos.x, pos.y);
		spr.setTextureRect(extremitySprPos.find(leftArm.colorType)->second);
		wnd.draw(spr);
	}
	
	void DrawHead(sf::Sprite& spr, sf::RenderWindow& wnd)
	{
		spr.setPosition(pos.x, pos.y);
		spr.setTextureRect(extremitySprPos.find(head.colorType)->second);
		wnd.draw(spr);
	}

	void DrawBody(sf::Sprite& spr, sf::RenderWindow& wnd)
	{
		spr.setPosition(pos.x, pos.y);
		spr.setTextureRect(extremitySprPos.find(body.colorType)->second);
		wnd.draw(spr);
	}

	void DrawCarriable(sf::Sprite& spr, sf::RenderWindow& wnd)
	{
		sf::RectangleShape shape;
		shape.setFillColor(sf::Color::Transparent);
		shape.setOutlineColor(sf::Color::White);
		shape.setOutlineThickness(1);
		shape.setPosition(pos.x, pos.y);
		shape.setSize(sf::Vector2f(8, 8));

		wnd.draw(shape);
	}

	void Draw(sf::VertexArray &vertexArray)
	{

	}
};