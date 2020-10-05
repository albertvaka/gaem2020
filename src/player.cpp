#include "player.h"

#include "animation2.h"
#include "anim_lib.h"
#include "rand.h"
#include "partsys.h"
#include "mates.h"
#include "camera.h"
#include "collide.h"
#include "input.h"
#include "fxmanager.h"
#include "shot.h"
#include "wall.h"
#include "assets.h"
#include "startline.h"

const float kShotSpeed = 400.f;

const float kTimeBetweenShots = 0.2f;

const float spriteScale = 0.5f;

const float width = 32* spriteScale;
const float height = 32* spriteScale;

Player::Player(const vec& position, float angle)
	: pos(position)
	, anim(AnimLib::GOOMBA)
	, angle(angle)
{
	int top = Rand::roll(10);
	int topX = top % 6;
	int topY = top / 6;
	spriteTop = {topX * 32.f, topY * 32.f, 32, 32};

	int bottom = Rand::roll(10);
	int bottomX = bottom % 6;
	int bottomY = bottom / 6;
	spriteBottom = { bottomX * 32.f, 64 + bottomY * 32.f, 32, 32 };
}

void Player::Move(float dt) 
{

	if (Input::IsPressed(0, GameKeys::LEFT) && !enemy)
	{
		angularSpeed -= kAngularAccel * dt;
	} 
	else if (Input::IsPressed(0, GameKeys::RIGHT) && !enemy)
	{
		angularSpeed += kAngularAccel * dt;
	}
	else 
	{
		if (angularSpeed > 0) 
		{
			angularSpeed -= kAngularDrag * dt;
			if (angularSpeed < 0) 
			{
				angularSpeed = 0;
			}
		}
		if (angularSpeed < 0) 
		{
			angularSpeed += kAngularDrag * dt;
			if (angularSpeed > 0) 
			{
				angularSpeed = 0;
			}
		}
	}

	Mates::Clamp(angularSpeed, -kMaxAngularSpeed, kMaxAngularSpeed);
	angle += angularSpeed * dt;

	vec heading = vec::FromAngleDegs(angle);

	if (is_derraping)
	{
		heading = vec::FromAngleDegs(angle_before_derraping);
	}

	if (enemy || Input::IsPressed(0, GameKeys::UP))
	{
		speed += kAccel * dt;
	}
	else if (Input::IsPressed(0, GameKeys::DOWN) && !enemy)
	{
		speed -= kBrake * dt;
	}
	else 
	{
		speed -= kDrag * dt;
	}
	Mates::Clamp(speed, 0, kMaxSpeed);

	vel = heading * speed;

	pos += vel * dt;
}


void Player::Update(float dt)
{
	anim.Update(dt);


	if (Input::IsJustPressed(0, GameKeys::DERRAPE) && !enemy)
	{
		is_derraping = true;
		angle_before_derraping = angle;

	}
	if (Input::IsJustReleased(0, GameKeys::DERRAPE) && !enemy)
	{
		is_derraping = false;
		//speed = kAccel * (timer_derraping / 2.0f);
	}

	Move(dt);

	bbounds = RotableBounds(pos.x, pos.y, width, height, angle);

	for (Wall* e : Wall::GetAll()) 
	{
		if (e->bounds().Collision(bbounds))
		{
			speed *= 0.65f;
			angle += e->inner ? -40 : 40;

			if (!enemy)
			{
				e->JustCollided();
				StartLine::instance()->AddPenalization();
			}
		}
	}

	attack_timer -= dt;

	if (Input::IsPressed(0, GameKeys::ATTACK) && attack_timer < 0.f && !enemy)
	{
		vec heading = vec::FromAngleDegs(angle);
		new Shot(pos, vel+heading*kShotSpeed);
		attack_timer = kTimeBetweenShots;
	}
}

void Player::Draw() const
{
	//Window::DrawPrimitive::Line(pos, pos + (vel * 0.25), 2, { 255,255,0,255 }); //Elmeao
	
	Window::Draw(Assets::spritesheet, pos)
		.withRect(spriteBottom)
		.withScale(spriteScale)
		.withRotationDegs(angle+90)
		.withOrigin(0, 32);

	Window::Draw(Assets::spritesheet, pos)
		.withRect(spriteTop)
		.withScale(spriteScale)
		.withRotationDegs(angle + 90)
		.withOrigin(0, 32);

	if (Debug::Draw) 
	{
		pos.Debuggerino();
		bbounds.Draw();
	}

}
