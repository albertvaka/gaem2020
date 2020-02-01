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
	bool isLet = false;


	int currentPlayer;
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

		currentPlayer = player;
	}

	void putCadaverOnTable(vec position)
	{
		isCarried = false;
		isLet = true;

		pos.x = position.x + 4;
		pos.y = position.y + 4;

		currentPlayer = -1;
	}

	void Update(int dt) 
	{
		Move(dt);
	}

	void Move(int dt)
	{

		auto oldPos = pos;

		SetSpeedWithCinta();
		pos += speed * dt;
		speed.x = 0;
		speed.y = 0;

	}

	
	void Draw(sf::Sprite& spr, sf::RenderTarget& wnd) override
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


	void DrawRightLeg(sf::Sprite& spr, sf::RenderTarget& wnd)
	{
		spr.setPosition(pos.x, pos.y);
		spr.setTextureRect(extremitySprPos.find(rightLeg.colorType)->second);
		wnd.draw(spr);
	}

	void DrawLeftLeg(sf::Sprite& spr, sf::RenderTarget& wnd)
	{
		spr.setPosition(pos.x, pos.y);
		spr.setTextureRect(extremitySprPos.find(leftLeg.colorType)->second);
		wnd.draw(spr);
	}
	
	void DrawRightArm(sf::Sprite& spr, sf::RenderTarget& wnd)
	{
		spr.setPosition(pos.x, pos.y);
		spr.setTextureRect(extremitySprPos.find(rightArm.colorType)->second);
		wnd.draw(spr);
	}
	
	void DrawLeftArm(sf::Sprite& spr, sf::RenderTarget& wnd)
	{
		spr.setPosition(pos.x, pos.y);
		spr.setTextureRect(extremitySprPos.find(leftArm.colorType)->second);
		wnd.draw(spr);
	}
	
	void DrawHead(sf::Sprite& spr, sf::RenderTarget& wnd)
	{
		spr.setPosition(pos.x, pos.y);
		spr.setTextureRect(extremitySprPos.find(head.colorType)->second);
		wnd.draw(spr);
	}

	void DrawBody(sf::Sprite& spr, sf::RenderTarget& wnd)
	{
		spr.setPosition(pos.x, pos.y);
		spr.setTextureRect(extremitySprPos.find(body.colorType)->second);
		wnd.draw(spr);
	}

	void DrawCarriable(sf::Sprite& spr, sf::RenderTarget& wnd)
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