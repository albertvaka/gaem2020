#pragma once

#include "entity.h"
#include "animation.h"
#include "rand.h"


struct Persona : public Entity, public EntS<Persona>
{ 
	enum BodyColor {
		NONE = 0,
		WHITE,
		BLACK,
		YELLOW,
		GREEN,
		BLUE,
		RED,
		SIZE
	};

	int rightLeg;
	int leftLeg;
	int rightArm;
	int leftArm;
	int head;
	int body;

	int anim;


	Persona() {

		int color = Random::roll(0, BodyColor::SIZE - 1);

		rightLeg = color;
		leftLeg = color;
		rightArm = color;
		leftArm = color;
		head = color;
		body = color;


	}

	void Update(int dt) { }


	void DrawRightLeg(sf::Sprite& spr) 
	{
		spr.setTextureRect(sf::IntRect(1 * anim * 8, rightLeg * 8, 8, 8));
	}

	void DrawLeftLeg(sf::Sprite& spr)
	{
		spr.setTextureRect(sf::IntRect(2 * anim * 8, leftLeg * 8, 8, 8));
	}
	
	void DrawRightArm(sf::Sprite& spr)
	{
		spr.setTextureRect(sf::IntRect(3 * anim * 8, rightArm * 8, 8, 8));
	}
	
	void DrawLeftArm(sf::Sprite& spr)
	{
		spr.setTextureRect(sf::IntRect(4 * anim * 8, leftArm * 8, 8, 8));
	}
	
	void DrawHead(sf::Sprite& spr)
	{
		spr.setTextureRect(sf::IntRect(5 * anim * 8, head * 8, 8, 8));
	}

	void DrawBody(sf::Sprite& spr)
	{
		spr.setTextureRect(sf::IntRect(6 * anim * 8, body * 8, 8, 8));
	}



};