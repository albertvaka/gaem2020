#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

#include "vector.h"
#include "setter.h"

struct PartSys {

	vec pos = vec();

	vec max_vel = vec();
	vec min_vel = vec();
	setter<vec> vel = setter<vec>([this](vec n) { max_vel = min_vel = n; });

	vec acc = vec();

	float min_ttl = 1.f;
	float max_ttl = 1.f;
	setter<float> ttl = setter<float>([this](float n) { max_ttl = min_ttl = n; });

	float min_interval = 0.2f; //min_interval < 0: no particles are created automatically
	float max_interval = 0.2f;
	setter<float> interval = setter<float>([this](float n) { max_interval = min_interval = n; });

	float min_scale = 1.f;
	float max_scale = 1.f;
	setter<float> scale = setter<float>([this](float n) { max_scale = min_scale = n; });

	float scale_vel = 0.f;

	float min_rotation = 0.f;
	float max_rotation = 0.f;
	setter<float> rotation = setter<float>([this](float n) { max_rotation = min_rotation = n; });

	float rotation_vel = 0.f;

	float alpha = 1.f;
	float alpha_vel = 0.f;

	float time = 0.f;

	void AddSprite(const sf::Texture& texture, const sf::IntRect& rect) {
		sprites.emplace_back(texture, rect);
		sprites.back().setOrigin(rect.width/2,rect.height/2);
	}

	void Update(float dt);
	void Draw(sf::RenderTarget& rt);

	void AddParticle();

	void DrawImGUI(const char* title = "Particles");

private:
	struct Particle {
		int sprite;
		vec pos;
		vec vel;
		float ttl;
		float scale;
		float rotation;
		float alpha;
	};

	std::vector<Particle> particles;
	std::vector<sf::Sprite> sprites;
};

