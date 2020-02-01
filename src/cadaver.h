#pragma once

#include "rand.h"

#include "extremity.h"
#include "entity.h"



struct Cadaver : public Entity, EntS<Cadaver>
{ 
	Extremity rightLeg;
	Extremity leftLeg;
	Extremity rightArm;
	Extremity leftArm;
	Extremity head;
	Extremity body;

	Cadaver(int x, int y) {

		pos.x = x;
		pos.y = y;
		
		int color = Random::roll(1, Extremity::BodyColor::SIZE - 1);

		rightLeg.pos.x = pos.x + 3;
		rightLeg.pos.y = pos.y + 3;
		rightLeg.color = color;
		rightLeg.anim = 0;

		leftLeg.pos.x = pos.x - 3;
		leftLeg.pos.y = pos.y + 3;
		leftLeg.color = color;
		leftLeg.anim = 0;

		rightArm.pos.x = pos.x + 3;
		rightArm.pos.y = pos.y + 1;
		rightArm.color = color;
		rightArm.anim = 0;

		leftArm.pos.x = pos.x - 3;
		leftArm.pos.y = pos.y + 1;
		leftArm.color = color;
		leftArm.anim = 0;

		head.pos.x = pos.x;
		head.pos.y = pos.y - 3;
		head.color = color;
		head.anim = 0;

		body.pos.x = pos.x;
		body.pos.y = pos.y - 3;
		body.color = color;
		body.anim = 0;

		int noExtremity = Random::roll(1, 5);

		switch (noExtremity)
		{
		case 1: rightLeg.color = 0; break;
		case 2: leftLeg.color = 0; break;
		case 3: rightArm.color = 0; break;
		case 4: leftArm.color = 0; break;
		case 5: head.color = 0; break;
		}
	}

	void Update(int dt) { }

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

	void DrawRightLeg(sf::Sprite& spr) 
	{
		spr.setScale(4, 4);
		spr.setPosition(rightLeg.pos.x, rightLeg.pos.y);
		if(rightLeg.color != 0)
			spr.setTextureRect(sf::IntRect((0 + rightLeg.anim) * 8, (rightLeg.color - 1) * 8, 8, 8));
	}

	void DrawLeftLeg(sf::Sprite& spr)
	{
		spr.setScale(4, 4);
		spr.setPosition(leftLeg.pos.x, leftLeg.pos.y);
		if (leftLeg.color != 0)
			spr.setTextureRect(sf::IntRect((2 + leftLeg.anim) * 8, (leftLeg.color - 1) * 8, 8, 8));
	}
	
	void DrawRightArm(sf::Sprite& spr)
	{
		spr.setScale(4, 4);
		spr.setPosition(rightArm.pos.x, rightArm.pos.y);
		if (rightArm.color != 0)
			spr.setTextureRect(sf::IntRect((4 + rightArm.anim) * 8, (rightArm.color - 1) * 8, 8, 8));
	}
	
	void DrawLeftArm(sf::Sprite& spr)
	{
		spr.setScale(4, 4);
		spr.setPosition(leftArm.pos.x, leftArm.pos.y);
		if (leftArm.color != 0)
			spr.setTextureRect(sf::IntRect((6 + leftArm.anim) * 8, (leftArm.color - 1) * 8, 8, 8));
	}
	
	void DrawHead(sf::Sprite& spr)
	{
		spr.setScale(4, 4);
		spr.setPosition(head.pos.x, head.pos.y);
		if (head.color != 0)
			spr.setTextureRect(sf::IntRect((8 + head.anim) * 8, (head.color - 1) * 8, 8, 8));
	}

	void DrawBody(sf::Sprite& spr)
	{
		spr.setScale(4, 4);
		spr.setPosition(body.pos.x, body.pos.y);
		spr.setTextureRect(sf::IntRect((10 + body.anim) * 8, (body.color - 1) * 8, 8, 8));
	}

	void Draw(sf::VertexArray &vertexArray)
	{

	}
};