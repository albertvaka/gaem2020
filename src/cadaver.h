#pragma once

#include "rand.h"

#include "extremity.h"
#include "entity.h"
#include "collider.h"
#include "taca.h"

struct SpawnAnim : public SortedDrawable, EntS<SpawnAnim>
{
	int timer = 0;

	vec offset;

	SpawnAnim(vec _pos, vec _offset = vec())
	{
		anim.Ensure(AnimationType::SPAWN);
		pos = _pos;
		offset = _offset;
	}

	void Update(int dt)
	{
		timer += dt;
		if (timer > 650)
		{
			alive = false;
		}
	}

	void Draw(sf::Sprite& spr, sf::RenderTarget& wnd)
	{

		spr.setPosition(pos + offset);
		spr.setTextureRect(anim.CurrentFrame());
		wnd.draw(spr);

	}


};


extern sf::Clock mainClock;

bool withTaca = true;

struct Cadaver : public SortedDrawable, public Cintable, EntS<Cadaver>
{ 
	ExtremityData rightLeg;
	ExtremityData leftLeg;
	ExtremityData rightArm;
	ExtremityData leftArm;
	ExtremityData head;
	ExtremityData body;

	bool HasExtremity(ExtremityType et) {
		switch (et) {
		case ExtremityType::HEAD:
			return head.colorType != ExtremityData::BodyColorType::NONE_TYPE;
		case ExtremityType::LEFT_ARM:
			return leftArm.colorType != ExtremityData::BodyColorType::NONE_TYPE;
		case ExtremityType::RIGHT_ARM:
			return rightArm.colorType != ExtremityData::BodyColorType::NONE_TYPE;
		case ExtremityType::LEFT_LEG:
			return leftLeg.colorType != ExtremityData::BodyColorType::NONE_TYPE;
		case ExtremityType::RIGHT_LEG:
			return rightLeg.colorType != ExtremityData::BodyColorType::NONE_TYPE;
		}
		return true;
	}

	void AttachExtremity(Extremity* e) {
		switch (e->type) {
		case ExtremityType::HEAD:
			head = e->data;
			break;
		case ExtremityType::LEFT_ARM:
			leftArm = e->data;
			break;
		case ExtremityType::RIGHT_ARM:
			rightArm = e->data;
			break;
		case ExtremityType::LEFT_LEG:
			leftLeg = e->data;
			break;
		case ExtremityType::RIGHT_LEG:
			rightLeg = e->data;
			break;
		}
		e->alive = false;

		new SpawnAnim(e->pos);
		new SpawnAnim(this->pos, vec(-4, -4));

	}

	Extremity* DeatachExtremity(ExtremityType et, vec pos) {
		Extremity* e = new Extremity(pos.x,pos.y, et);
		switch (et) {
		case ExtremityType::HEAD:
			e->data = head;
			head.colorType = ExtremityData::BodyColorType::NONE_TYPE;
			break;
		case ExtremityType::LEFT_ARM:
			e->data = leftArm;
			leftArm.colorType = ExtremityData::BodyColorType::NONE_TYPE;
			break;
		case ExtremityType::RIGHT_ARM:
			e->data = rightArm;
			rightArm.colorType = ExtremityData::BodyColorType::NONE_TYPE;
			break;
		case ExtremityType::LEFT_LEG:
			e->data = leftLeg;
			leftLeg.colorType = ExtremityData::BodyColorType::NONE_TYPE;
			break;
		case ExtremityType::RIGHT_LEG:
			e->data = rightLeg;
			rightLeg.colorType = ExtremityData::BodyColorType::NONE_TYPE;
			break;
		}
		e->isCarried = false;

		e->PonBien();


		new SpawnAnim(pos);
		new SpawnAnim(this->pos, vec(-4, -4));

		return e;
	}

	bool isCarried = false;
	bool isLet = false;
	float counterBloodTimeLeft = 100.f;

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

	vec positionPlz() {
		return pos;
	}

	vec sizePlz() override {
		return vec(16, 16);
	}

	void carryCadaver(int x, int y, int player)
	{
		isCarried = true;

		pos.x = x;
		pos.y = y + 3;

		isLet = false;
		currentPlayer = player;
	}

	void putCadaverOnTable(vec position)
	{
		isCarried = false;
		isLet = true;

		isLetClock.restart();

		pos.x = position.x + 4;
		pos.y = position.y + 4;

		currentPlayer = -1;
	}


	void Update(int dt) 
	{
		counterBloodTimeLeft -= dt * Random::roll(0, 3);
		if (counterBloodTimeLeft < 0 && withTaca)
		{
			Taca *t = new Taca(pos, currCintaDirection);
			counterBloodTimeLeft = 100;
			for (Taca* p : EntS<Taca>::getAll())
			{
				if (p == t) continue;
				if (p->getFinalPos() == t->getFinalPos())
				{
					t->alive = false;
				}
			}
		}
		Move(dt);

	}

	void Move(int dt)
	{

		SetSpeedWithCinta(speed);
		sf::Vector2f oldpos = pos;
		pos += speed * dt;
		
		speed.x = 0;
		speed.y = 0;

	}

	bool IsOk()
	{
		bool has_all = true;
		for (int i = 0; i < (int)ExtremityType::COUNT; ++i)
		{
			has_all &= HasExtremity((ExtremityType)i);
		}
		return has_all;
	}

	sf::Clock isLetClock;

	void Draw(sf::Sprite& spr, sf::RenderTarget& wnd) override
	{

		if (!isLet) 
		{
			spr.setRotation(-90);
		}
		else 
		{
			sf::RectangleShape shape;
			int color = std::min(1.0f, abs(sin(0.5f*isLetClock.getElapsedTime().asSeconds()))) * 255;
			shape.setFillColor(sf::Color(0, (color*3)/4, color));
			shape.setPosition(pos.x-4.f, pos.y - 6.5f);
			shape.setSize(sf::Vector2f(15, 15));
			wnd.draw(shape);
		}

		DrawBody(spr, wnd);

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


	/*	if (isCarriable)
		{
			DrawCarriable(spr, wnd);
		}*/
		spr.setRotation(0);
	}

	const int xt = 4;
	const int yt = 12;

	const int xp = 5;
	const int yp = 8;


	const float xs = -0.5;
	const float ys = -3;
	void DrawRightLeg(sf::Sprite& spr, sf::RenderTarget& wnd)
	{
		if (isLet) {
			spr.setPosition(pos.x + 1 + xs, pos.y + 3 + ys);
		}
		else if (isCarried) {
			spr.setPosition(pos.x + 3 + xp, pos.y - 1 + yp);
		}
		else {
			spr.setPosition(pos.x + 3 + xt, pos.y - 1 + yt);
		}
		spr.setTextureRect(extremitySprPos.find(rightLeg.colorType)->second);
		wnd.draw(spr);
	}

	void DrawLeftLeg(sf::Sprite& spr, sf::RenderTarget& wnd)
	{
		if (isLet) {
			spr.setPosition(pos.x - 1 + xs, pos.y + 3 + ys);
		}
		else if (isCarried) {
			spr.setPosition(pos.x + 3 + xp, pos.y + 1 + yp);
		}
		else {
			spr.setPosition(pos.x + 3 + xt, pos.y + 1 + yt);
		}
		spr.setTextureRect(extremitySprPos.find(leftLeg.colorType)->second);
		wnd.draw(spr);
	}
	
	void DrawRightArm(sf::Sprite& spr, sf::RenderTarget& wnd)
	{
		if (isLet) {
			spr.setPosition(pos.x+1 + xs, pos.y - 0 + ys);
		}
		else if (isCarried) {
			spr.setPosition(pos.x + xp, pos.y - 1 + yp);
		}
		else {
			spr.setPosition(pos.x + xt, pos.y - 1 + yt);
		}
		spr.setTextureRect(extremitySprPos.find(rightArm.colorType)->second);
		wnd.draw(spr);
	}
	
	void DrawLeftArm(sf::Sprite& spr, sf::RenderTarget& wnd)
	{
		if (isLet) {
			spr.setPosition(pos.x-1 + xs, pos.y-0 + ys);
		}
		else if (isCarried) {
			spr.setPosition(pos.x + xp, pos.y + 1 + yp);
		}
		else {
			spr.setPosition(pos.x + xt, pos.y+1 + yt);
		}
		spr.setTextureRect(extremitySprPos.find(leftArm.colorType)->second);
		wnd.draw(spr);
	}
	
	void DrawHead(sf::Sprite& spr, sf::RenderTarget& wnd)
	{
		if (isLet) {
			spr.setPosition(pos.x + xs, pos.y-3 + ys);
		}
		else if (isCarried) {
			spr.setPosition(pos.x - 3 + xp, pos.y + yp);
		}
		else {
			spr.setPosition(pos.x - 3 + xt, pos.y + yt);
		}
		spr.setTextureRect(extremitySprPos.find(head.colorType)->second);
		wnd.draw(spr);
	}

	void DrawBody(sf::Sprite& spr, sf::RenderTarget& wnd)
	{
		if (isLet) {
			spr.setPosition(pos.x + xs, pos.y + ys);
		}
		else if (isCarried) {
			spr.setPosition(pos.x + xp, pos.y + yp);
		}
		else {
			spr.setPosition(pos.x + xt, pos.y + yt);

		}
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