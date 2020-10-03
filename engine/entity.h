#pragma once

#include "vec.h"
#include "selfregister.h"
#include "bounds.h"

struct Entity : SelfRegister<Entity>
{
	Entity() : pos(0.f,0.f) {}
	Entity(const vec& pos) : pos(pos) {}
	Entity(const vec& pos, const vec& vel) : pos(pos), vel(vel) {}
	virtual ~Entity() {}
	virtual void Update(float dt) = 0;
	virtual void Draw() const = 0;

	vec pos;
	vec vel = vec(0.f, 0.f);
	bool alive = true;
};

struct BoxEntity : Entity {
	BoxEntity(const vec& size) : size(size) {}
	BoxEntity(const vec& pos, const vec& size) : Entity(pos), size(size) {}
	BoxEntity(const Bounds& b) : Entity(b.Center()), size(b.Size()) {} //note that entities position is on their center

	vec size;

	[[nodiscard]] constexpr Bounds bounds() const {
		return Bounds::fromCenter(pos, size);
	}

	void DrawBounds(uint8_t r = 255, uint8_t g = 255, uint8_t b = 255) const {
		bounds().Draw(r,g,b);
	}
};

struct CircleEntity : Entity {
	CircleEntity() : radius(8.f) {}
	CircleEntity(float radius) : radius(radius) {}
	CircleEntity(const vec& pos, float radius) : Entity(pos), radius(radius) {}
	CircleEntity(const vec& pos, float radius, const vec& vel) : Entity(pos, vel), radius(radius) {}

	float radius;
	
	[[nodiscard]] constexpr CircleBounds bounds() const {
		return CircleBounds(pos, radius);
	}

	void DrawBounds(uint8_t r = 255, uint8_t g = 255, uint8_t b = 255) const {
		bounds().Draw(r,g,b);
	}
};


