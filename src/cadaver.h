#pragma once

#include "rand.h"

#include "extremity.h"
#include "entity.h"
#include "taca.h"

struct SpawnAnim : SortedDrawable, EntS<SpawnAnim>
{
	int timer = 0;

	vec offset;

	SpawnAnim(vec _pos, vec _offset = vec())
	{
		anim.Ensure(AnimationType::SPAWN);
		pos = _pos;

		pos.x = (((int)pos.x) / 16)*16.0f;

		pos.y = (((int)pos.y) / 16)*16.0f;
		pos.y += 150;

		offset = _offset;
		offset.y -= 150;
	}

	void Update(int dt)
	{
		timer += dt;
		if (timer > 650)
		{
			alive = false;
		}
	}

	void Draw(sf::Sprite& spr, sf::RenderTarget& window)
	{
		spr.setPosition(pos + offset);
		spr.setTextureRect(anim.CurrentFrame());
		window.draw(spr);

	}


};


extern sf::Clock mainClock;

bool withTaca = true;

struct Cadaver : SortedDrawable, Cintable, EntS<Cadaver>
{
	ExtremityColor rightLeg;
	ExtremityColor leftLeg;
	ExtremityColor rightArm;
	ExtremityColor leftArm;
	ExtremityColor head;
	ExtremityColor body;

	bool isCarried = false;
	bool isLet = false;
	float counterBloodTimeLeft = 100.f;

	bool HasExtremity(ExtremityType et) {
		switch (et) {
		case ExtremityType::HEAD:
			return head != ExtremityColor::NONE_COLOR;
		case ExtremityType::LEFT_ARM:
			return leftArm != ExtremityColor::NONE_COLOR;
		case ExtremityType::RIGHT_ARM:
			return rightArm != ExtremityColor::NONE_COLOR;
		case ExtremityType::LEFT_LEG:
			return leftLeg != ExtremityColor::NONE_COLOR;
		case ExtremityType::RIGHT_LEG:
			return rightLeg != ExtremityColor::NONE_COLOR;
		}
		return true;
	}

	void AttachExtremity(Extremity* e) {
		switch (e->type) {
		case ExtremityType::HEAD:
			head = e->color;
			break;
		case ExtremityType::LEFT_ARM:
			leftArm = e->color;
			break;
		case ExtremityType::RIGHT_ARM:
			rightArm = e->color;
			break;
		case ExtremityType::LEFT_LEG:
			leftLeg = e->color;
			break;
		case ExtremityType::RIGHT_LEG:
			rightLeg = e->color;
			break;
		}
		e->alive = false;

		new SpawnAnim(e->pos);
		new SpawnAnim(this->pos, vec(0, 0));

	}

	Extremity* DeatachExtremity(ExtremityType et, vec pos) {
		ExtremityColor color;
		switch (et) {
		case ExtremityType::HEAD:
			color = head;
			head = ExtremityColor::NONE_COLOR;
			break;
		case ExtremityType::LEFT_ARM:
			color = leftArm;
			leftArm = ExtremityColor::NONE_COLOR;
			break;
		case ExtremityType::RIGHT_ARM:
			color = rightArm;
			rightArm = ExtremityColor::NONE_COLOR;
			break;
		case ExtremityType::LEFT_LEG:
			color = leftLeg;
			leftLeg = ExtremityColor::NONE_COLOR;
			break;
		case ExtremityType::RIGHT_LEG:
			color = rightLeg;
			rightLeg = ExtremityColor::NONE_COLOR;
			break;
		}
		Extremity* e = new Extremity(pos, et, color);
		e->isLet = true;
		e->isCarried = false;

		new SpawnAnim(pos);
		new SpawnAnim(this->pos, vec(0, 0));

		return e;
	}

	Cadaver(vec _pos) {
		pos = _pos;

		ExtremityColor color = RandomExtremityColor();

		rightLeg = color;
		leftLeg = color;
		rightArm = color;
		leftArm = color;
		head = color;
		body = color;

		int noExtremity = Random::roll(0, 4);
		switch (noExtremity)
		{
		case 0: rightLeg = ExtremityColor::NONE_COLOR; break;
		case 1: leftLeg = ExtremityColor::NONE_COLOR; break;
		case 2: rightArm = ExtremityColor::NONE_COLOR; break;
		case 3: leftArm = ExtremityColor::NONE_COLOR; break;
		case 4: head = ExtremityColor::NONE_COLOR; break;
		}

	}

	vec positionPlz() override { return pos; }
	vec sizePlz() override { return size; }

	void carryCadaver(float x, float y)
	{
		isCarried = true;

		pos.x = x;
		pos.y = y + 2;

		isLet = false;
	}

	void putCadaverOnTable(vec position)
	{
		isCarried = false;
		isLet = true;

		isLetClock.restart();

		pos.x = position.x;
		pos.y = position.y+0.1f;
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

	void Draw(sf::Sprite& spr, sf::RenderTarget& window) override
	{

		//Bounds(pos, size, true).Draw(window, sf::Color::Green);
		if (!isLet)
		{
			spr.setRotation(-90);
		}
		else //DrawEfectito() de la mesa (TODO: mover a la mesa)
		{
			sf::RectangleShape shape;
			int color = std::max(std::min(1.0f, abs(sin(0.75f*isLetClock.getElapsedTime().asSeconds()))) * 255, 64.0f);
			shape.setFillColor(sf::Color(0, (color*3)/4, color));
			shape.setPosition(pos.x - 7.5f, pos.y - 8.5f);
			shape.setSize(sf::Vector2f(15, 15));
			window.draw(shape);
		}

		DrawBody(spr, window);

		if (rightLeg != ExtremityColor::NONE_COLOR)
		{
			DrawRightLeg(spr, window);
		}

		if (leftLeg != ExtremityColor::NONE_COLOR)
		{
			DrawLeftLeg(spr, window);
		}

		if (rightArm != ExtremityColor::NONE_COLOR)
		{
			DrawRightArm(spr, window);
		}

		if (leftArm != ExtremityColor::NONE_COLOR)
		{
			DrawLeftArm(spr, window);
		}

		if (head != ExtremityColor::NONE_COLOR)
		{
			DrawHead(spr, window);
		}


	/*	if (isCarriable)
		{
			DrawCarriable(spr, window);
		}*/
		spr.setRotation(0);

		//Bounds(pos.x - 1, pos.y - 1, 2, 2).Draw(window);
	}

	//floor
	const float xt = 3;
	const float yt = -5;

	//carried
	const float xp = 5.5;
	const float yp = -6.5;

	//let
	const float xs = 4;
	const float ys = 3;

	void DrawRightLeg(sf::Sprite& spr, sf::RenderTarget& window)
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
		spr.setTextureRect(extremitySprPos[rightLeg][ExtremityType::RIGHT_LEG]);
		window.draw(spr);
	}

	void DrawLeftLeg(sf::Sprite& spr, sf::RenderTarget& window)
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
		spr.setTextureRect(extremitySprPos[leftLeg][ExtremityType::LEFT_LEG]);
		window.draw(spr);
	}

	void DrawRightArm(sf::Sprite& spr, sf::RenderTarget& window)
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
		spr.setTextureRect(extremitySprPos[rightArm][ExtremityType::RIGHT_ARM]);
		window.draw(spr);
	}

	void DrawLeftArm(sf::Sprite& spr, sf::RenderTarget& window)
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
		spr.setTextureRect(extremitySprPos[leftArm][ExtremityType::LEFT_ARM]);
		window.draw(spr);
	}

	void DrawHead(sf::Sprite& spr, sf::RenderTarget& window)
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
		spr.setTextureRect(extremitySprPos[head][ExtremityType::HEAD]);
		window.draw(spr);
	}

	void DrawBody(sf::Sprite& spr, sf::RenderTarget& window)
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
		spr.setTextureRect(extremitySprPos[body][ExtremityType::BODY]);
		window.draw(spr);
	}

};
