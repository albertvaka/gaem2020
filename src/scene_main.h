#pragma once

#include "mates.h"
#include "scene.h"
#include "vec.h"

struct Car;
struct GunUp;
struct EnemyDoor;

struct MainScene : Scene {

	MainScene() {};
	void EnterScene() override;
	void ExitScene() override;
	void Update(float dt) override;
	void Draw() override;


	float cameraAngle = 0.0f;
	float cameraZoom = 1.0f;
	vec camCenter;
};
