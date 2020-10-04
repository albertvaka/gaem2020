#pragma once

#include "mates.h"
#include "scene.h"
#include "vec.h"
#include "text.h"
#include "assets.h"

struct Car;
struct GunUp;
struct EnemyDoor;

struct MainScene : Scene {

	MainScene() : 
		timelapText(Assets::font_30, Assets::font_30_outline),
		timelapTimer(0.0f)
		{};
	void EnterScene() override;
	void ExitScene() override;
	void Update(float dt) override;
	void Draw() override;


	float cameraAngle = 0.0f;
	float cameraZoom = 1.0f;
	vec camCenter;

	Text timelapText;
	float timelapTimer;
};
