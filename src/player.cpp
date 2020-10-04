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
#include "powerup.h"
#include "assets.h"
#include "startline.h"

const float kShotSpeed = 400.f;

const float kTimeBetweenShots = 0.2f;

const float spriteScale = 0.5f;
const float kRadius = 8.f;


Player::Player(const vec& position, float angle)
	: CircleEntity(position, kRadius)
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

	if (Input::IsPressed(0, GameKeys::LEFT)) 
	{
		angularSpeed -= kAngularAccel * dt;
	} 
	else if (Input::IsPressed(0, GameKeys::RIGHT)) 
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

	if (Input::IsPressed(0, GameKeys::UP)) 
	{
		speed += kAccel * dt;
	}
	else if (Input::IsPressed(0, GameKeys::DOWN)) 
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


	if (Input::IsJustPressed(0, GameKeys::DERRAPE))
	{
		is_derraping = true;
		angle_before_derraping = angle;
		timer_derraping = 0.0f;
	}
	if (Input::IsJustReleased(0, GameKeys::DERRAPE))
	{
		is_derraping = false;
		//speed = kAccel * (timer_derraping / 2.0f);
	}

	if (is_derraping)
	{
		timer_derraping += dt;
		if (timer_derraping > 2.0f)
		{
			timer_derraping = 2.0f;
		}
	}

	Move(dt);

	for (PowerUp* e : SelfRegister<PowerUp>::GetAll()) 
	{
		if (Collide(this, e)) 
		{
			e->alive = false;
			FxManager::StartScreenshakePreset(FxManager::ScreenShakePreset::Electroshok);
		}
	}

	for (StartLine* e : SelfRegister<StartLine>::GetAll())
	{
		if (Collide(this, e))
		{
			e->PlayerCollided();
		}
		else
		{
			e->playerColliding = false;
		}
	}


	attack_timer -= dt;

	if (Input::IsPressed(0, GameKeys::ATTACK) && attack_timer < 0.f) 
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
		.withOrigin(16, 16);

	Window::Draw(Assets::spritesheet, pos)
		.withRect(spriteTop)
		.withScale(spriteScale)
		.withRotationDegs(angle + 90)
		.withOrigin(16, 16);

	if (Debug::Draw) 
	{
		pos.Debuggerino();
		DrawBounds();
	}

}
